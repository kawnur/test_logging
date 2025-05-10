#include <chrono>
#include <QCoreApplication>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <thread>

#include "utils.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Class c;

    QString mark1 { "mark1" };
    QString mark2 { "mark2" };
    QString mark3 { "mark3" };

    QNetworkAccessManager manager;
//    QEventLoop loop;

    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

//    QNetworkReply* replyPtr = new QNetworkReply;

//    QObject::connect(replyPtr, SIGNAL(finished()),
//                     &loop, SLOT(quit()));

    QString ipAddress { std::getenv("FLUENTD_SERVICE_ADDRESS") };
    QString port { std::getenv("FLUENTD_SERVICE_PORT") };
//    QString ipAddress { std::getenv("FLUENTBIT_SERVICE_ADDRESS") };
//    QString port { std::getenv("FLUENTBIT_SERVICE_PORT") };
//    QString ipAddress { std::getenv("LOGSTASH_SERVICE_ADDRESS") };
//    QString port { std::getenv("LOGSTASH_SERVICE_PORT") };

//    std::vector<QString> paths { "log.Db.1", "log.Db.2" };
    std::vector<QString> paths { "log.Db.1" };

    int i = 0;

    while (true) {
//    while (i++ < 10) {
        for (auto& path : paths) {
            QEventLoop loop;

            QString urlString = QString("http://%1:%2/%3").arg(
                        ipAddress, port, path);

            request.setUrl(QUrl(urlString));
//            qDebug() << request.url();

            QString format { "yyyy-MM-dd hh:mm:ss.zzz" };
//            QString format { "yyyy-MM-dd hh:mm:ss" };

            QString dataString = QString("[%1][%2][%3][%4]: %5").arg(
                        QDateTime::currentDateTime().toString(format),
                        mark1, mark2, mark3, getRandomString(20));

//            qDebug() << dataString;

            QJsonObject jsonObject;
            jsonObject["data"] = dataString;

            QNetworkReply *replyPtr = manager.post(request, QJsonDocument(jsonObject).toJson());
    //        manager.post(request, QJsonDocument(jsonObject).toJson());

            QObject::connect(replyPtr, SIGNAL(finished()),
                    &loop, SLOT(quit()));

            loop.exec();

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    return a.exec();
}
