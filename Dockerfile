FROM php:7.2.9-apache

RUN apt-get update && apt-get install -y libpq-dev libfreetype6-dev libjpeg62-turbo-dev libpng-dev && docker-php-ext-install pdo pdo_pgsql pgsql && docker-php-ext-configure gd --with-freetype --with-jpeg && docker-php-ext-install -j$(nproc) gd

RUN a2enmod rewrite

COPY ./www/ /var/www/html
RUN export PATH="$PATH:/usr/local/bin/" 
