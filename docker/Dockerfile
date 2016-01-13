FROM ubuntu:14.04

MAINTAINER Alexander Skjolden alex@plastboks.net

RUN apt-get update
#RUN apt-get upgrade
RUN apt-get -y install build-essential
RUN apt-get -y install git
RUN apt-get -y install libssl-dev

VOLUME /lispy/shared

WORKDIR /lispy
RUN git clone https://github.com/plastboks/Lispy.git app
WORKDIR /lispy/app
RUN make
RUN make install
