/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _DICT_H_RPCGEN
#define _DICT_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define DICTPROG 0x20000001
#define INSERTVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define INSERT 1
extern  int * insert_1(char **, CLIENT *);
extern  int * insert_1_svc(char **, struct svc_req *);
extern int dictprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define INSERT 1
extern  int * insert_1();
extern  int * insert_1_svc();
extern int dictprog_1_freeresult ();
#endif /* K&R C */
#define LOOKUPVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define LOOKUP 1
extern  char ** lookup_1(char **, CLIENT *);
extern  char ** lookup_1_svc(char **, struct svc_req *);
extern int dictprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define LOOKUP 1
extern  char ** lookup_1();
extern  char ** lookup_1_svc();
extern int dictprog_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_DICT_H_RPCGEN */