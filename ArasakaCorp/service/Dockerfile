FROM debian:stable

RUN useradd -d /home/ctf/ -m -p ctf -s /bin/bash ctf
RUN echo "ctf:ctf" | chpasswd
RUN passwd -d ctf

WORKDIR /home/ctf

COPY ArasakaCorp .
COPY flag .
COPY ynetd .

RUN chown -R root:root /home/ctf
RUN chmod +x ynetd
RUN chmod +x ArasakaCorp

USER ctf
EXPOSE 8085
CMD ./ynetd -p 8085 ./ArasakaCorp
