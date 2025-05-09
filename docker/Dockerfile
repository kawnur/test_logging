FROM debian AS service
USER root
COPY ./conf/ld/my_ld.conf /etc/ld.so.conf.d/

FROM debian AS fluentdservice
USER root
COPY /home/user/test/sources.list /etc/apt
#RUN mv /etc/apt/sources.list.d/debian.sources /etc/apt/sources.list.d/debian.sources1
RUN apt update
RUN apt install -y wget sudo curl
RUN apt install -y build-essential
RUN apt install -y ruby-dev
RUN apt install -y libpq5 libpq-dev
RUN wget https://toolbelt.treasuredata.com/sh/install-debian-bookworm-fluent-package5.sh
RUN sh /install-debian-bookworm-fluent-package5.sh
RUN fluent-gem install fluent-plugin-sql --no-document
RUN fluent-gem install pg --no-document

FROM debian AS logstashservice
USER root
RUN mkdir /logstash
COPY /home/user/distrib/logstash-9.0.1/ /logstash/
RUN mkdir -p /logstash/vendor/jar/jdbc
COPY /home/user/distrib/postgresql-42.7.5.jar /logstash/vendor/jar/jdbc/
RUN useradd logstashuser
RUN chown -R logstashuser:logstashuser /logstash
RUN /logstash/bin/logstash-plugin install logstash-output-jdbc
USER logstashuser

#FROM logstash:5.6.16 AS logstashserviceold
#WORKDIR /usr/share/logstash
#RUN ./bin/logstash-plugin install logstash-output-jdbc

FROM postgres AS dbservice
