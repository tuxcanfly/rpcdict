dict.h dict_clnt.c dict_svc.c dict_xdr.c:
	rpcgen -N dict.x

rdict: rdict.c dict_clnt.c
	cc rdict.c dict_clnt.c dict_xdr.c -o rdict -lnsl

dict_server: dict_proc.c dict_svc.c dict_xdr.c
	cc dict_proc.c dict_svc.c dict_xdr.c -o dict_server -lnsl

clean:
	rm -rf dict_server rdict dict.h dict_clnt.c dict_svc.c

all: dict_server rdict

.PHONY: all clean
