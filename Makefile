rprintmsg: msg_clnt.c
	cc rprintmsg.c msg_clnt.c -o rprintmsg -lnsl

msg_server: msg_svc.c
	cc msg_proc.c msg_svc.c -o msg_server -lnsl

clean:
	rm -rf rprintmsg msg_server

all: rprintmsg msg_server

.PHONY: all clean
