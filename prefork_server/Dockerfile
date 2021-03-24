FROM ubuntu:20.04 AS release
MAINTAINER Timofei Makarov

RUN  apt-get update
RUN  yes | apt-get install cmake

WORKDIR /app

COPY . .

COPY ./httptest ./var/www/html/httptest

RUN mkdir ./mybuild && cd ./mybuild
RUN cmake -DCMAKE_BUILD_TYPE=Release ./
RUN make

CMD ./static_server