FROM debian:buster

EXPOSE 3306

RUN apt-get update -y && \
    apt-get upgrade -y && \
    apt-get install -y vim dumb-init \
    mariadb-server \
    mariadb-client && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir -p /var/run/mysqld
RUN chown -R mysql:mysql /var/run/mysqld
RUN chmod 777 /var/run/mysqld

COPY conf/mysqld.conf /etc/mysql/mariadb.conf.d/50-server.cnf

COPY ./tools/mariadb_setup.sh /usr/local/bin/

RUN chmod +x /usr/local/bin/mariadb_setup.sh

ENTRYPOINT [ "/usr/bin/dumb-init", "--", "/usr/local/bin/mariadb_setup.sh" ]

CMD [ "mysqld", "--bind-address=0.0.0.0" ]
