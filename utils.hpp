#ifndef UTILS_HPP
#define UTILS_HPP

#include <QObject>
#include <QNetworkReply>
#include <QString>

class Class : public QObject
{
    Q_OBJECT

public:
    Class() = default;
    ~Class() = default;

public slots:
    void slot(QNetworkReply *) {};
};

QString getRandomString(std::size_t);

#endif // UTILS_HPP
