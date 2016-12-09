/*
 * Progarm Name: c-primer.h
 * Created Time: 2016-12-09 23:19:02
 * Last modified: 2016-12-10 00:13:57
 * @author: minphone.linails linails@foxmail.com 
 */

#ifndef _C_PRIMER_H_
#define _C_PRIMER_H_
#ifdef __cplusplus
extern "C" {
#endif

    typedef struct cPrimer_{
        void (*other_test)(void);
        int  (*process_token)(void);
        int  (*cprimer_main)(void *cthis, int argc, char **argv);
        int  (*destructor)(struct cPrimer_ **pobj);
    }cPrimer_t;

    extern cPrimer_t *cprimer_constructor(void);

#ifdef __cplusplus
}
#endif
#endif //_C_PRIMER_H_

