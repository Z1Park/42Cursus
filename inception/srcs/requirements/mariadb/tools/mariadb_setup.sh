#!/bin/bash

if [ -d "/var/lib/mysql/$MARIADB_DATABASE" ]
then
	echo "database already exiests"
else
>/tmp/init.sql cat <<EOF
USE  mysql;
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MARIADB_ROOT_PASSWORD}';
FLUSH PRIVILEGES;
CREATE DATABASE IF NOT EXISTS ${MARIADB_DATABASE};
USE  ${MARIADB_DATABASE};
CREATE USER ${MARIADB_USER}@'%';
GRANT ALL PRIVILEGES ON ${MARIADB_DATABASE}.* TO ${MARIADB_USER}@'%' IDENTIFIED BY '${MARIADB_PASSWORD}';
FLUSH PRIVILEGES;
EOF

exec mysqld_safe --init-file /tmp/init.sql
mysqld stop

fi

exec "$@"
