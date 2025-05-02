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

FROM postgres AS dbservice
