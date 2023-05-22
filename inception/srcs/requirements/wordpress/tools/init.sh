#!/bin/sh

if  [ -f ./wp-config.php ]
then
	echo "wordpress is already exist"
else
	wget http://wordpress.org/latest.tar.gz
	tar xfz latest.tar.gz
	mv wordpress/* /var/www/html/
	chown -R www-data:www-data /var/www/html
	rm -rf latest.tar.gz wordpress

	sed -i "s/username_here/$MARIADB_USER/g" wp-config-sample.php
	sed -i "s/password_here/$MARIADB_PASSWORD/g" wp-config-sample.php
	sed -i "s/localhost/mariadb/g" wp-config-sample.php
	sed -i "s/database_name_here/$MARIADB_DATABASE/g" wp-config-sample.php
	mv /var/www/html/wp-config-sample.php /var/www/html/wp-config.php

	cd /var/www/html
	wp core install --url=$DOMAIN_NAME --admin_user=$WP_ADMIN --admin_password=$WP_ADMIN_PASSWORD --admin_email=$WP_ADMIN_EMAIL --title="$WP_TITLE" --allow-root
	wp user create $WP_USER $WP_USER_EMAIL --user_pass=$WP_USER_PASSWORD --allow-root
fi

exec "$@"
