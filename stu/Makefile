CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi selsc.cgi addsc.cgi delsc.cgi del2.cgi teacher.cgi student.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi
install:
		cp *.cgi /usr/lib/cgi-bin/sx
		cp student.html /usr/lib/cgi-bin/sx
		cp teacher.html /usr/lib/cgi-bin/sx

