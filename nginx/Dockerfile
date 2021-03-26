FROM ubuntu:20.04 AS release

RUN apt-get -y update && apt-get install -y tzdata

ENV TZ=Russia/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update

RUN yes | apt-get install software-properties-common


# nginx
RUN \
  add-apt-repository -y ppa:nginx/stable && \
  apt-get update && \
  apt-get install -y nginx && \
  rm -rf /var/lib/apt/lists/* && \
  chown -R www-data:www-data /var/lib/nginx

COPY nginx.conf /etc/nginx/nginx.conf

WORKDIR /etc/nginx

COPY  ./static /etc/nginx/static

CMD ["nginx", "-g", "daemon off;"]
