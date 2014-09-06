rpcgen dict:
============

Remote dictionary using rpcgen

Build:
======

    make all

Usage:
======

server:

    ./dict_server

client:

    ./rdict localhost

Notes:
======

If you face this error:

    Cannot register service: RPC: Authentication error; why = Client credential
    too weak unable to register (X_PROG, X_VERS, udp)

run rpcbind with `-i`:

http://stackoverflow.com/a/14087503
