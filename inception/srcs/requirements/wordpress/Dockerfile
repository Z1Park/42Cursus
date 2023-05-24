FROM debian:buster

EXPOSE 9000

RUN apt-get update -y && \
	apt-get upgrade -y && \
	apt-get install -y \
	dumb-init \
	curl \
	php \
	php-fpm \
	php-cli \
	php-mysql \
	php-cgi \
	php-pdo \
	php-gd \
	php-mbstring \
	wget && \
	rm -rf /var/lib/apt/lists/*

RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN chmod +x wp-cli.phar
RUN mv wp-cli.phar /usr/bin/wp

COPY ./conf/www.conf /etc/php/7.3/fpm/pool.d/
COPY ./tools/init.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/init.sh

RUN mkdir /run/php

ENTRYPOINT ["/usr/bin/dumb-init", "--", "/usr/local/bin/init.sh"]

WORKDIR /var/www/html/

CMD ["php-fpm7.3", "-F"]
