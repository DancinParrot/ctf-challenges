FROM ubuntu:20.04

RUN useradd -d /home/ctf/ -m -p ctf -s /bin/bash ctf
RUN echo "ctf:ctf" | chpasswd
RUN passwd -d ctf

WORKDIR /home/ctf

COPY TheBananaKey .
COPY flag .
COPY ynetd .

RUN chown -R root:root /home/ctf
RUN chmod +x ynetd
RUN chmod +x TheBananaKey

USER ctf
EXPOSE 1024
CMD ./ynetd -p 1024 ./TheBananaKey
