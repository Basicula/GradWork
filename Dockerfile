FROM ubuntu:18.04

RUN apt-get update
RUN apt-get -y install python3.7 python3-pip
RUN apt-get -y install cmake
RUN apt-get -y install freeglut3-dev
RUN apt-get -y install libgl1-mesa-dev

WORKDIR /GradWork

COPY . /GradWork

RUN pip3 install -r requirements.txt

CMD ["./run.sh"]
