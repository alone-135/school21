FROM nginx
USER root
COPY ./hello.c /home/hello.c
COPY ./begin.sh /home/begin.sh
COPY ./nginx/nginx.conf /etc/nginx/nginx.conf
RUN apt-get update; \
    apt-get install -y gcc spawn-fcgi libfcgi-dev;
WORKDIR /home/
ENTRYPOINT ["sh", "./begin.sh"]