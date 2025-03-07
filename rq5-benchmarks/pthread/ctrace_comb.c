/* Generated by CIL v. 1.3.6 */
/* print_CIL_Input is true */

typedef unsigned long pthread_t;
union __anonunion_pthread_attr_t_4 {
   char __size[36] ;
   long __align ;
};
typedef union __anonunion_pthread_attr_t_4 pthread_attr_t;
union __anonunion_sem_t_27 {
   char __size[16] ;
   long __align ;
};
typedef union __anonunion_sem_t_27 sem_t;
typedef unsigned int uint_t;
typedef char const   cchar_t;
typedef pthread_t tid_t;
typedef uint_t tenable_t;
typedef uint_t ton_t;
typedef uint_t tlevel_t;
typedef uint_t tserver_t;
typedef uint_t taction_t;
typedef unsigned int size_t;
typedef long long __quad_t;
typedef long __off_t;
typedef __quad_t __off64_t;
typedef long __time_t;
typedef unsigned int __socklen_t;
struct _IO_FILE;
typedef struct _IO_FILE FILE;
typedef __builtin_va_list __gnuc_va_list;
typedef void _IO_lock_t;
struct _IO_marker {
   struct _IO_marker *_next ;
   struct _IO_FILE *_sbuf ;
   int _pos ;
};
struct _IO_FILE {
   int _flags ;
   char *_IO_read_ptr ;
   char *_IO_read_end ;
   char *_IO_read_base ;
   char *_IO_write_base ;
   char *_IO_write_ptr ;
   char *_IO_write_end ;
   char *_IO_buf_base ;
   char *_IO_buf_end ;
   char *_IO_save_base ;
   char *_IO_backup_base ;
   char *_IO_save_end ;
   struct _IO_marker *_markers ;
   struct _IO_FILE *_chain ;
   int _fileno ;
   int _flags2 ;
   __off_t _old_offset ;
   unsigned short _cur_column ;
   signed char _vtable_offset ;
   char _shortbuf[1] ;
   _IO_lock_t *_lock ;
   __off64_t _offset ;
   void *__pad1 ;
   void *__pad2 ;
   void *__pad3 ;
   void *__pad4 ;
   size_t __pad5 ;
   int _mode ;
   char _unused2[(15U * sizeof(int ) - 4U * sizeof(void *)) - sizeof(size_t )] ;
};
typedef __gnuc_va_list va_list;
typedef __time_t time_t;
struct __pthread_internal_slist {
   struct __pthread_internal_slist *__next ;
};
typedef struct __pthread_internal_slist __pthread_slist_t;
union __anonunion____missing_field_name_14 {
   int __spins ;
   __pthread_slist_t __list ;
};
struct __pthread_mutex_s {
   int __lock ;
   unsigned int __count ;
   int __owner ;
   int __kind ;
   unsigned int __nusers ;
   union __anonunion____missing_field_name_14 __annonCompField1 ;
};
union __anonunion_pthread_mutex_t_13 {
   struct __pthread_mutex_s __data ;
   char __size[24] ;
   long __align ;
};
typedef union __anonunion_pthread_mutex_t_13 pthread_mutex_t;
union __anonunion_pthread_mutexattr_t_15 {
   char __size[4] ;
   long __align ;
};
typedef union __anonunion_pthread_mutexattr_t_15 pthread_mutexattr_t;
typedef __socklen_t socklen_t;
typedef unsigned short sa_family_t;
struct sockaddr {
   sa_family_t sa_family ;
   char sa_data[14] ;
};
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef uint16_t in_port_t;
typedef uint32_t in_addr_t;
struct in_addr {
   in_addr_t s_addr ;
};
struct sockaddr_in {
   sa_family_t sin_family ;
   in_port_t sin_port ;
   struct in_addr sin_addr ;
   unsigned char sin_zero[((sizeof(struct sockaddr ) - sizeof(unsigned short )) - sizeof(in_port_t )) - sizeof(struct in_addr )] ;
};
struct hostent {
   char *h_name ;
   char **h_aliases ;
   int h_addrtype ;
   int h_length ;
   char **h_addr_list ;
};
struct tm {
   int tm_sec ;
   int tm_min ;
   int tm_hour ;
   int tm_mday ;
   int tm_mon ;
   int tm_year ;
   int tm_wday ;
   int tm_yday ;
   int tm_isdst ;
   long tm_gmtoff ;
   char const   *tm_zone ;
};
struct tthread_t {
   tid_t id ;
   char name[10] ;
   int on ;
   tlevel_t level ;
   char wspace[44] ;
   char fmt[1024] ;
   char trace[1098] ;
   struct tthread_t *next ;
};
typedef struct tthread_t tthread_t;
struct tunit_t {
   int on ;
   tlevel_t level ;
};
typedef struct tunit_t tunit_t;
#pragma merger(0,"/tmp/cil-DDXCGPyu.i","-g")
extern  __attribute__((__nothrow__)) int pthread_create(pthread_t * __restrict  __newthread ,
                                                        pthread_attr_t const   * __restrict  __attr ,
                                                        void *(*__start_routine)(void * ) ,
                                                        void * __restrict  __arg )  __attribute__((__nonnull__(1,3))) ;
extern int pthread_join(pthread_t __th , void **__thread_return ) ;
extern  __attribute__((__nothrow__)) int sem_init(sem_t *__sem , int __pshared , unsigned int __value ) ;
extern  __attribute__((__nothrow__)) int sem_destroy(sem_t *__sem ) ;
extern int sem_wait(sem_t *__sem ) ;
extern  __attribute__((__nothrow__)) int sem_post(sem_t *__sem ) ;
tenable_t _trc ;
int trc_init(cchar_t *file , tenable_t trc , ton_t on , tlevel_t level , uint_t umax ,
             tserver_t server ) ;
void trc_end(void) ;
int trc_add_thread(cchar_t *tname , tid_t id ) ;
int trc_remove_thread(tid_t id ) ;
int trc_turn_thread_on(tid_t id ) ;
int trc_add_level(tlevel_t level ) ;
int trc_set_thread_level(tlevel_t level , tid_t id ) ;
int trc_add_thread_level(tlevel_t level , tid_t id ) ;
int trc_remove_thread_level(tlevel_t level , tid_t id ) ;
char *trc_varargs(char const   *fmt  , ...) ;
void trc_trace(taction_t a , uint_t i , tlevel_t level , cchar_t *file , uint_t line ,
               cchar_t *fn , cchar_t *kword , cchar_t *s ) ;
void *thread1(void *arg ) ;
void *thread2(void *arg ) ;
sem_t sem  ;
void myprocedure(void) 
{ char *tmp ;

  {
  if (_trc) {
    tmp = trc_varargs((char const   *)((void *)0));
    trc_trace(0U, 0U, 1U, "main.c", 12U, "myprocedure", (cchar_t *)((void *)0), (cchar_t *)tmp);
  }
  if (_trc) {
    trc_trace(2U, 0U, 1U, "main.c", 13U, "myprocedure", (cchar_t *)((void *)0), (cchar_t *)((void *)0));
  }
  return;
}
}
int main(int argc , char **argv ) 
{ int i ;
  tid_t tid1 ;
  tid_t tid2 ;
  char *tmp ;
  int tmp___0 ;
  int tmp___1 ;
  char *tmp___2 ;
  char *tmp___3 ;
  char *tmp___4 ;

  {
  i = 6;
  sem_init(& sem, 0, 1U);
  trc_init((cchar_t *)((void *)0), 1U, 1U, 1U, 0U, 0U);
  trc_add_thread((cchar_t *)*(argv + 0), 0UL);
  if (_trc) {
    tmp = trc_varargs("%d, %s", 1, "string");
    trc_trace(0U, 0U, 1U, "main.c", 26U, "main", (cchar_t *)((void *)0), (cchar_t *)tmp);
  }
  trc_add_level(4U);
  tmp___0 = pthread_create((pthread_t * __restrict  )(& tid1), (pthread_attr_t const   * __restrict  )((void *)0),
                           & thread1, (void * __restrict  )((void *)0));
  if (tmp___0) {
    return (1);
  }
  tmp___1 = pthread_create((pthread_t * __restrict  )(& tid2), (pthread_attr_t const   * __restrict  )((void *)0),
                           & thread2, (void * __restrict  )((void *)0));
  if (tmp___1) {
    return (1);
  }
  sem_post(& sem);
  sem_post(& sem);
  myprocedure();
  if (_trc) {
    tmp___2 = trc_varargs("i=%d", 0);
    trc_trace(3U, 0U, 1U, "main.c", 42U, "main", (cchar_t *)((void *)0), (cchar_t *)tmp___2);
  }
  if (_trc) {
    tmp___3 = trc_varargs("mystring=%s", "stringval");
    trc_trace(4U, 0U, 64U, "main.c", 43U, "main", (cchar_t *)((void *)0), (cchar_t *)tmp___3);
  }
  pthread_join(tid1, (void **)((void *)0));
  trc_remove_thread(tid1);
  pthread_join(tid2, (void **)((void *)0));
  trc_remove_thread(tid2);
  if (_trc) {
    tmp___4 = trc_varargs("%d", i);
    trc_trace(1U, 0U, 1U, "main.c", 51U, "main", (cchar_t *)((void *)0), (cchar_t *)tmp___4);
  }
  return (i);
  trc_end();
  sem_destroy(& sem);
}
}
void *thread1(void *arg ) 
{ char *tmp ;
  char *tmp___0 ;
  char *tmp___1 ;
  char *tmp___2 ;
  char *tmp___3 ;
  char *tmp___4 ;
  char *tmp___5 ;

  {
  trc_add_thread("thread1", 0UL);
  trc_set_thread_level(16U, 0UL);
  trc_add_thread_level(1U, 0UL);
  trc_remove_thread_level(16U, 0UL);
  trc_turn_thread_on(0UL);
  sem_wait(& sem);
  if (_trc) {
    tmp = trc_varargs("%d", 1);
    trc_trace(0U, 0U, 1U, "main.c", 65U, "thread1", (cchar_t *)((void *)0), (cchar_t *)tmp);
  }
  if (_trc) {
    tmp___0 = trc_varargs("level0: i=%d", 1);
    trc_trace(3U, 0U, 1U, "main.c", 66U, "thread1", (cchar_t *)((void *)0), (cchar_t *)tmp___0);
  }
  if (_trc) {
    tmp___1 = trc_varargs("level1: i=%d", 1);
    trc_trace(3U, 0U, 2U, "main.c", 67U, "thread1", (cchar_t *)((void *)0), (cchar_t *)tmp___1);
  }
  if (_trc) {
    tmp___2 = trc_varargs("level2: i=%d", 1);
    trc_trace(3U, 0U, 4U, "main.c", 68U, "thread1", (cchar_t *)((void *)0), (cchar_t *)tmp___2);
  }
  if (_trc) {
    tmp___3 = trc_varargs("level3: i=%d", 1);
    trc_trace(3U, 0U, 8U, "main.c", 69U, "thread1", (cchar_t *)((void *)0), (cchar_t *)tmp___3);
  }
  if (_trc) {
    tmp___4 = trc_varargs("level4: i=%d", 1);
    trc_trace(3U, 0U, 16U, "main.c", 70U, "thread1", (cchar_t *)((void *)0), (cchar_t *)tmp___4);
  }
  if (_trc) {
    tmp___5 = trc_varargs("0x%x", (void *)0);
    trc_trace(1U, 0U, 1U, "main.c", 72U, "thread1", (cchar_t *)((void *)0), (cchar_t *)tmp___5);
  }
  return ((void *)0);
}
}
void *thread2(void *arg ) 
{ char *tmp ;
  char *tmp___0 ;
  char *tmp___1 ;
  char *tmp___2 ;
  char *tmp___3 ;
  char *tmp___4 ;
  char *tmp___5 ;

  {
  trc_add_thread("thread2", 0UL);
  sem_wait(& sem);
  if (_trc) {
    tmp = trc_varargs("%d", 2);
    trc_trace(0U, 0U, 1U, "main.c", 79U, "thread2", (cchar_t *)((void *)0), (cchar_t *)tmp);
  }
  if (_trc) {
    tmp___0 = trc_varargs("level0: i=%d", 2);
    trc_trace(3U, 0U, 1U, "main.c", 80U, "thread2", (cchar_t *)((void *)0), (cchar_t *)tmp___0);
  }
  if (_trc) {
    tmp___1 = trc_varargs("level1: i=%d", 2);
    trc_trace(3U, 0U, 2U, "main.c", 81U, "thread2", (cchar_t *)((void *)0), (cchar_t *)tmp___1);
  }
  if (_trc) {
    tmp___2 = trc_varargs("level2: i=%d", 2);
    trc_trace(3U, 0U, 4U, "main.c", 82U, "thread2", (cchar_t *)((void *)0), (cchar_t *)tmp___2);
  }
  if (_trc) {
    tmp___3 = trc_varargs("level3: i=%d", 2);
    trc_trace(3U, 0U, 8U, "main.c", 83U, "thread2", (cchar_t *)((void *)0), (cchar_t *)tmp___3);
  }
  if (_trc) {
    tmp___4 = trc_varargs("level4: i=%d", 2);
    trc_trace(3U, 0U, 16U, "main.c", 84U, "thread2", (cchar_t *)((void *)0), (cchar_t *)tmp___4);
  }
  if (_trc) {
    tmp___5 = trc_varargs("0x%x", (void *)0);
    trc_trace(1U, 0U, 1U, "main.c", 85U, "thread2", (cchar_t *)((void *)0), (cchar_t *)tmp___5);
  }
  return ((void *)0);
}
}
/* compiler builtin: 
   void __builtin_va_end(__builtin_va_list  ) ;  */
/* compiler builtin: 
   void __builtin_va_start(__builtin_va_list  ) ;  */
#pragma merger(0,"/tmp/cil-25ldxckG.i","")
extern struct _IO_FILE *stdout ;
extern struct _IO_FILE *stderr ;
extern int fclose(FILE *__stream ) ;
extern FILE *fopen(char const   * __restrict  __filename , char const   * __restrict  __modes ) ;
extern int fprintf(FILE * __restrict  __stream , char const   * __restrict  __format 
                   , ...) ;
extern int printf(char const   * __restrict  __format  , ...) ;
extern  __attribute__((__nothrow__)) int sprintf(char * __restrict  __s , char const   * __restrict  __format 
                                                 , ...) ;
extern  __attribute__((__nothrow__)) int vsprintf(char * __restrict  __s , char const   * __restrict  __format ,
                                                  __gnuc_va_list __arg ) ;
extern void perror(char const   *__s ) ;
extern  __attribute__((__nothrow__)) int socket(int __domain , int __type , int __protocol ) ;
extern  __attribute__((__nothrow__)) int bind(int __fd , struct sockaddr  const  *__addr ,
                                              socklen_t __len ) ;
extern int connect(int __fd , struct sockaddr  const  *__addr , socklen_t __len ) ;
extern  __attribute__((__nothrow__)) int setsockopt(int __fd , int __level , int __optname ,
                                                    void const   *__optval , socklen_t __optlen ) ;
extern  __attribute__((__nothrow__)) int listen(int __fd , int __n ) ;
extern int accept(int __fd , struct sockaddr * __restrict  __addr , socklen_t * __restrict  __addr_len ) ;
extern  __attribute__((__nothrow__)) uint32_t htonl(uint32_t __hostlong )  __attribute__((__const__)) ;
extern  __attribute__((__nothrow__)) uint16_t htons(uint16_t __hostshort )  __attribute__((__const__)) ;
extern struct hostent *gethostbyname(char const   *__name ) ;
extern  __attribute__((__nothrow__)) time_t time(time_t *__timer ) ;
extern  __attribute__((__nothrow__)) size_t strftime(char * __restrict  __s , size_t __maxsize ,
                                                     char const   * __restrict  __format ,
                                                     struct tm  const  * __restrict  __tp ) ;
extern  __attribute__((__nothrow__)) struct tm *localtime(time_t const   *__timer ) ;
extern  __attribute__((__nothrow__)) pthread_t pthread_self(void)  __attribute__((__const__)) ;
extern  __attribute__((__nothrow__)) int pthread_mutex_init(pthread_mutex_t *__mutex ,
                                                            pthread_mutexattr_t const   *__mutexattr )  __attribute__((__nonnull__(1))) ;
extern  __attribute__((__nothrow__)) int pthread_mutex_destroy(pthread_mutex_t *__mutex )  __attribute__((__nonnull__(1))) ;
extern  __attribute__((__nothrow__)) int pthread_mutex_lock(pthread_mutex_t *__mutex )  __attribute__((__nonnull__(1))) ;
extern  __attribute__((__nothrow__)) int pthread_mutex_unlock(pthread_mutex_t *__mutex )  __attribute__((__nonnull__(1))) ;
static tlevel_t _tlevel ;
int trc_file(cchar_t *file ) ;
void trc_turn_on(void) ;
void trc_turn_off(void) ;
int trc_turn_thread_off(tid_t id ) ;
int trc_turn_unit_on(uint_t i ) ;
int trc_turn_unit_off(uint_t i ) ;
int trc_set_level(tlevel_t level ) ;
int trc_remove_level(tlevel_t level ) ;
int trc_set_unit_level(uint_t i , tlevel_t level ) ;
int trc_add_unit_level(uint_t i , tlevel_t level ) ;
int trc_remove_unit_level(uint_t i , tlevel_t level ) ;
void trc_state(void) ;
void trc_print_threads(void) ;
tenable_t _trc  =    (tenable_t )0;
static ton_t _on  =    (ton_t )0;
static tlevel_t _tlevel  =    (tlevel_t )0;
static FILE *_fp  =    (FILE *)((void *)0);
static tserver_t _server  =    (tserver_t )0;
static int _msgs  =    0;
static pthread_t _sid  ;
static int _serv_sockfd  ;
static sem_t _startclient  ;
static int _initialised  =    0;
static tthread_t *_thread[307]  ;
static uint_t _numthreads  =    (uint_t )0;
static pthread_mutex_t _hashmutex  ;
static int _hashreads  =    0;
static sem_t _hashsem  ;
static tunit_t *_unit  =    (tunit_t *)((void *)0);
static uint_t _unitmax  =    (uint_t )0;
void *trc_start_server(void) ;
int trc_stop_server(void) ;
extern int ( /* missing proto */  malloc)() ;
int trc_start_client(void) ;
int trc_init(cchar_t *file , tenable_t trc , ton_t on , tlevel_t level , uint_t umax ,
             tserver_t server ) 
{ int i ;
  int ret ;
  int tmp ;
  int tmp___0 ;
  int tmp___1 ;
  int tmp___2 ;

  {
  ret = 0;
  if (_initialised) {
    return (1);
  }
  _trc = trc;
  _on = on;
  _tlevel = level;
  _server = server;
  tmp = trc_file(file);
  if (tmp) {
    return (1);
  }
  i = 0;
  while (i < 307) {
    _thread[i] = (tthread_t *)((void *)0);
    i ++;
  }
  if (umax > 0U) {
    _unitmax = umax;
    tmp___0 = malloc(sizeof(tunit_t ) * _unitmax);
    _unit = (tunit_t *)tmp___0;
    i = 0;
    while ((uint_t )i < _unitmax) {
      (_unit + i)->on = 0;
      (_unit + i)->level = 127U;
      i ++;
    }
  }
  tmp___1 = pthread_mutex_init(& _hashmutex, (pthread_mutexattr_t const   *)((void *)0));
  if (tmp___1) {
    return (1);
  }
  sem_init(& _hashsem, 0, 1U);
  sem_init(& _startclient, 0, 1U);
  if (_server == 1U) {
    sem_wait(& _startclient);
    tmp___2 = pthread_create((pthread_t * __restrict  )(& _sid), (pthread_attr_t const   * __restrict  )((void *)0),
                             (void *(*)(void * ))(& trc_start_server), (void * __restrict  )((void *)0));
    if (tmp___2) {
      trc_end();
      return (1);
    }
    trc_start_client();
  }
  _initialised = 1;
  return (0);
}
}
int trc_stop_client(void) ;
extern int ( /* missing proto */  free)() ;
void trc_end(void) 
{ int i ;
  tthread_t *cur ;
  tthread_t *next ;

  {
  _trc = 0U;
  if (_server) {
    trc_stop_server();
    pthread_join(_sid, (void **)((void *)0));
    trc_stop_client();
  }
  i = 0;
  while (i < 307) {
    cur = _thread[i];
    while ((unsigned int )cur != (unsigned int )((void *)0)) {
      next = cur->next;
      free(cur);
      cur = next;
    }
    i ++;
  }
  pthread_mutex_destroy(& _hashmutex);
  sem_destroy(& _hashsem);
  sem_destroy(& _startclient);
  if (! ((unsigned int )_fp == (unsigned int )stdout)) {
    if (! ((unsigned int )_fp == (unsigned int )stderr)) {
      fclose(_fp);
    }
  }
  _initialised = 0;
  return;
}
}
int trc_file(cchar_t *file ) 
{ 

  {
  if (_fp) {
    if (! ((unsigned int )_fp == (unsigned int )stdout)) {
      if (! ((unsigned int )_fp == (unsigned int )stderr)) {
        fclose(_fp);
      }
    }
  }
  if (! file) {
    _fp = stdout;
  } else {
    _fp = fopen((char const   * __restrict  )file, (char const   * __restrict  )"w");
    if (! _fp) {
      return (1);
    }
  }
  return (0);
}
}
tthread_t *trc_thread(tid_t id ) 
{ tthread_t *t ;

  {
  t = (tthread_t *)((void *)0);
  t = _thread[(int )id % 307];
  while ((unsigned int )t != (unsigned int )((void *)0)) {
    if (t->id == id) {
      break;
    }
    t = t->next;
  }
  return (t);
}
}
void trc_print_threads(void) 
{ int i ;
  tthread_t *t ;

  {
  t = (tthread_t *)((void *)0);
  sem_wait(& _hashsem);
  i = 0;
  while (i < 307) {
    t = _thread[i];
    while (1) {
      if (_thread[i]) {
        if (! ((unsigned int )t != (unsigned int )((void *)0))) {
          break;
        }
      } else {
        break;
      }
      printf((char const   * __restrict  )"t->id: %d\t t->name: %s\t t->level: %d\tt->on: %d\n",
             t->id, t->name, t->level, t->on);
      t = t->next;
    }
    i ++;
  }
  sem_post(& _hashsem);
  return;
}
}
extern int ( /* missing proto */  memset)() ;
int trc_add_thread(cchar_t *tname , tid_t id ) 
{ uint_t i ;
  tthread_t *t ;
  int tmp ;

  {
  t = (tthread_t *)((void *)0);
  if (id == 0UL) {
    id = pthread_self();
  }
  sem_wait(& _hashsem);
  t = trc_thread(id);
  if (t) {
    if (tname) {
      sprintf((char * __restrict  )(t->name), (char const   * __restrict  )"%s", tname);
    } else {
      sprintf((char * __restrict  )(t->name), (char const   * __restrict  )"%d", id);
    }
  } else {
    tmp = malloc(sizeof(tthread_t ));
    t = (tthread_t *)tmp;
    if (! t) {
      sem_post(& _hashsem);
      return (1);
    }
    i = (unsigned int )((int )id % 307);
    t->id = id;
    if (tname) {
      sprintf((char * __restrict  )(t->name), (char const   * __restrict  )"%s", tname);
    } else {
      sprintf((char * __restrict  )(t->name), (char const   * __restrict  )"%d", id);
    }
    t->on = (int )_on;
    t->level = _tlevel;
    memset(t->wspace, ' ', 44);
    t->next = _thread[i];
    _thread[i] = t;
    _numthreads ++;
  }
  sem_post(& _hashsem);
  return (0);
}
}
int trc_remove_thread(tid_t id ) 
{ int i ;
  int ret ;
  tthread_t *cur ;
  tthread_t *next ;

  {
  ret = 1;
  if (id == 0UL) {
    id = pthread_self();
  }
  sem_wait(& _hashsem);
  i = (int )id % 307;
  if (_thread[i]) {
    if ((_thread[i])->id == id) {
      cur = _thread[i];
      _thread[i] = cur->next;
      free(cur);
      _numthreads --;
      ret = 0;
    } else {
      goto _L;
    }
  } else {
    _L: /* CIL Label */ 
    cur = _thread[i];
    while ((unsigned int )cur != (unsigned int )((void *)0)) {
      next = cur->next;
      if (next) {
        if (next->id == id) {
          cur->next = next->next;
          free(next);
          _numthreads --;
          ret = 0;
        }
      }
      cur = cur->next;
    }
  }
  sem_post(& _hashsem);
  return (ret);
}
}
void trc_turn_on(void) 
{ uint_t i ;
  tthread_t *t ;

  {
  t = (tthread_t *)((void *)0);
  sem_wait(& _hashsem);
  _on = 1U;
  i = 0U;
  while (i < 307U) {
    t = _thread[i];
    while (1) {
      if (_thread[i]) {
        if (! ((unsigned int )t != (unsigned int )((void *)0))) {
          break;
        }
      } else {
        break;
      }
      t->on = 1;
      t = t->next;
    }
    i ++;
  }
  sem_post(& _hashsem);
  return;
}
}
void trc_turn_off(void) 
{ uint_t i ;
  tthread_t *t ;

  {
  t = (tthread_t *)((void *)0);
  sem_wait(& _hashsem);
  _on = 0U;
  i = 0U;
  while (i < 307U) {
    t = _thread[i];
    while (1) {
      if (_thread[i]) {
        if (! ((unsigned int )t != (unsigned int )((void *)0))) {
          break;
        }
      } else {
        break;
      }
      t->on = 0;
      t = t->next;
    }
    i ++;
  }
  sem_post(& _hashsem);
  return;
}
}
int trc_turn_thread_on(tid_t id ) 
{ int ret ;
  tthread_t *t ;

  {
  ret = 1;
  t = (tthread_t *)((void *)0);
  if (id == 0UL) {
    id = pthread_self();
  }
  pthread_mutex_lock(& _hashmutex);
  if (! _hashreads) {
    sem_wait(& _hashsem);
  }
  _hashreads ++;
  pthread_mutex_unlock(& _hashmutex);
  t = trc_thread(id);
  if (t) {
    t->on = 1;
    ret = 0;
  }
  pthread_mutex_lock(& _hashmutex);
  _hashreads --;
  if (! _hashreads) {
    sem_post(& _hashsem);
  }
  pthread_mutex_unlock(& _hashmutex);
  return (ret);
}
}
int trc_turn_thread_off(tid_t id ) 
{ int ret ;
  tthread_t *t ;

  {
  ret = 1;
  t = (tthread_t *)((void *)0);
  if (id == 0UL) {
    id = pthread_self();
  }
  pthread_mutex_lock(& _hashmutex);
  if (! _hashreads) {
    sem_wait(& _hashsem);
  }
  _hashreads ++;
  pthread_mutex_unlock(& _hashmutex);
  t = trc_thread(id);
  if (t) {
    t->on = 0;
    ret = 0;
  }
  pthread_mutex_lock(& _hashmutex);
  _hashreads --;
  if (! _hashreads) {
    sem_post(& _hashsem);
  }
  pthread_mutex_unlock(& _hashmutex);
  return (ret);
}
}
int trc_turn_unit_on(uint_t i ) 
{ int ret ;

  {
  ret = 1;
  if (_unitmax == 0U) {
    return (ret);
  } else {
    if (i < 0U) {
      return (ret);
    } else {
      if (i >= _unitmax) {
        return (ret);
      }
    }
  }
  sem_wait(& _hashsem);
  if (i < 1000U) {
    (_unit + i)->on = 1;
    ret = 0;
  }
  sem_post(& _hashsem);
  return (ret);
}
}
int trc_turn_unit_off(uint_t i ) 
{ int ret ;

  {
  ret = 1;
  if (_unitmax == 0U) {
    return (ret);
  } else {
    if (i < 0U) {
      return (ret);
    } else {
      if (i >= _unitmax) {
        return (ret);
      }
    }
  }
  sem_wait(& _hashsem);
  if (i < 1000U) {
    (_unit + i)->on = 0;
    ret = 0;
  }
  sem_post(& _hashsem);
  return (ret);
}
}
int trc_valid_level(tlevel_t tlevel ) 
{ 

  {
  return ((tlevel & 4294967168U) == 0U);
}
}
int trc_set_level(tlevel_t level ) 
{ uint_t i ;
  tthread_t *t ;
  int tmp ;

  {
  t = (tthread_t *)((void *)0);
  tmp = trc_valid_level(level);
  if (! tmp) {
    return (1);
  }
  sem_wait(& _hashsem);
  _tlevel = level;
  i = 0U;
  while (i < 307U) {
    t = _thread[i];
    while (1) {
      if (_thread[i]) {
        if (! ((unsigned int )t != (unsigned int )((void *)0))) {
          break;
        }
      } else {
        break;
      }
      t->level = level;
      t = t->next;
    }
    i ++;
  }
  sem_post(& _hashsem);
  return (0);
}
}
int trc_add_level(tlevel_t level ) 
{ uint_t i ;
  tthread_t *t ;
  int tmp ;

  {
  t = (tthread_t *)((void *)0);
  tmp = trc_valid_level(level);
  if (! tmp) {
    return (1);
  }
  sem_wait(& _hashsem);
  _tlevel |= level;
  i = 0U;
  while (i < 307U) {
    t = _thread[i];
    while (1) {
      if (_thread[i]) {
        if (! ((unsigned int )t != (unsigned int )((void *)0))) {
          break;
        }
      } else {
        break;
      }
      t->level |= level;
      t = t->next;
    }
    i ++;
  }
  sem_post(& _hashsem);
  return (0);
}
}
int trc_remove_level(tlevel_t level ) 
{ uint_t i ;
  tthread_t *t ;
  int tmp ;

  {
  t = (tthread_t *)((void *)0);
  tmp = trc_valid_level(level);
  if (! tmp) {
    return (1);
  }
  sem_wait(& _hashsem);
  _tlevel &= ~ level;
  i = 0U;
  while (i < 307U) {
    t = _thread[i];
    while (1) {
      if (_thread[i]) {
        if (! ((unsigned int )t != (unsigned int )((void *)0))) {
          break;
        }
      } else {
        break;
      }
      t->level &= ~ level;
      t = t->next;
    }
    i ++;
  }
  sem_post(& _hashsem);
  return (0);
}
}
int trc_set_thread_level(tlevel_t level , tid_t id ) 
{ int ret ;
  tthread_t *t ;
  int tmp ;

  {
  ret = 1;
  t = (tthread_t *)((void *)0);
  if (id == 0UL) {
    id = pthread_self();
  }
  sem_wait(& _hashsem);
  t = trc_thread(id);
  if (t) {
    tmp = trc_valid_level(level);
    if (tmp) {
      t->level = level;
      ret = 0;
    }
  }
  sem_post(& _hashsem);
  return (ret);
}
}
int trc_add_thread_level(tlevel_t level , tid_t id ) 
{ int ret ;
  tthread_t *t ;
  int tmp ;

  {
  ret = 1;
  t = (tthread_t *)((void *)0);
  if (id == 0UL) {
    id = pthread_self();
  }
  sem_wait(& _hashsem);
  t = trc_thread(id);
  if (t) {
    tmp = trc_valid_level(level);
    if (tmp) {
      t->level |= level;
      ret = 0;
    }
  }
  sem_post(& _hashsem);
  return (ret);
}
}
int trc_remove_thread_level(tlevel_t level , tid_t id ) 
{ int ret ;
  tthread_t *t ;
  int tmp ;

  {
  ret = 1;
  t = (tthread_t *)((void *)0);
  if (id == 0UL) {
    id = pthread_self();
  }
  sem_wait(& _hashsem);
  t = trc_thread(id);
  if (t) {
    tmp = trc_valid_level(level);
    if (tmp) {
      t->level &= ~ level;
      ret = 0;
    }
  }
  sem_post(& _hashsem);
  return (ret);
}
}
int trc_set_unit_level(uint_t i , tlevel_t level ) 
{ int ret ;
  int tmp ;

  {
  ret = 1;
  if (_unitmax == 0U) {
    return (ret);
  } else {
    if (i < 0U) {
      return (ret);
    } else {
      if (i >= _unitmax) {
        return (ret);
      }
    }
  }
  sem_wait(& _hashsem);
  if (i < 1000U) {
    tmp = trc_valid_level(level);
    if (tmp) {
      (_unit + i)->level = level;
      ret = 0;
    }
  }
  sem_post(& _hashsem);
  return (ret);
}
}
int trc_add_unit_level(uint_t i , tlevel_t level ) 
{ int ret ;
  int tmp ;

  {
  ret = 1;
  if (_unitmax == 0U) {
    return (ret);
  } else {
    if (i < 0U) {
      return (ret);
    } else {
      if (i >= _unitmax) {
        return (ret);
      }
    }
  }
  sem_wait(& _hashsem);
  if (i < 1000U) {
    tmp = trc_valid_level(level);
    if (tmp) {
      (_unit + i)->level |= level;
      ret = 0;
    }
  }
  sem_post(& _hashsem);
  return (ret);
}
}
int trc_remove_unit_level(uint_t i , tlevel_t level ) 
{ int ret ;
  int tmp ;

  {
  ret = 1;
  if (_unitmax == 0U) {
    return (ret);
  } else {
    if (i < 0U) {
      return (ret);
    } else {
      if (i >= _unitmax) {
        return (ret);
      }
    }
  }
  sem_wait(& _hashsem);
  if (i < 1000U) {
    tmp = trc_valid_level(level);
    if (tmp) {
      (_unit + i)->level &= ~ level;
      ret = 0;
    }
  }
  sem_post(& _hashsem);
  return (ret);
}
}
void trc_state(void) 
{ 

  {
  printf((char const   * __restrict  )"_trc: %d\t_level: %d\t_t: %d\t", _trc, _tlevel,
         _server);
  if ((unsigned int )_fp == (unsigned int )stdout) {
    printf((char const   * __restrict  )"_fp: _STDOUT");
  } else {
    if (_fp) {
      printf((char const   * __restrict  )"_fp: user file");
    } else {
      printf((char const   * __restrict  )"_fp: NULL");
    }
  }
  printf((char const   * __restrict  )"\n");
  return;
}
}
char *trc_varargs(char const   *fmt  , ...) 
{ va_list args ;
  tthread_t *t ;
  pthread_t tmp ;
  char *tmp___0 ;

  {
  t = (tthread_t *)((void *)0);
  pthread_mutex_lock(& _hashmutex);
  if (! _hashreads) {
    sem_wait(& _hashsem);
  }
  _hashreads ++;
  pthread_mutex_unlock(& _hashmutex);
  tmp = pthread_self();
  t = trc_thread(tmp);
  if (t) {
    if (fmt) {
      __builtin_va_start(args, fmt);
      vsprintf((char * __restrict  )(t->fmt), (char const   * __restrict  )fmt, args);
      __builtin_va_end(args);
    } else {
      t->fmt[0] = (char )((void *)0);
    }
  }
  pthread_mutex_lock(& _hashmutex);
  _hashreads --;
  if (! _hashreads) {
    sem_post(& _hashsem);
  }
  pthread_mutex_unlock(& _hashmutex);
  if (t) {
    tmp___0 = t->fmt;
  } else {
    tmp___0 = (char *)((void *)0);
  }
  return (tmp___0);
}
}
extern int ( /* missing proto */  write)() ;
void trc_trace(taction_t a , uint_t i , tlevel_t level , cchar_t *file , uint_t line ,
               cchar_t *fn , cchar_t *kword , cchar_t *s ) 
{ int n ;
  tthread_t *t ;
  int num ;
  int bytesWritten ;
  int unit ;
  int thread ;
  time_t tim ;
  struct tm *timeptr ;
  char buf[64] ;
  pthread_t tmp ;
  int tmp___0 ;
  int tmp___1 ;

  {
  pthread_mutex_lock(& _hashmutex);
  if (! _hashreads) {
    sem_wait(& _hashsem);
  }
  _hashreads ++;
  pthread_mutex_unlock(& _hashmutex);
  if (! _fp) {
    goto _L;
  } else {
    tmp = pthread_self();
    t = trc_thread(tmp);
    if (! t) {
      _L: /* CIL Label */ 
      pthread_mutex_lock(& _hashmutex);
      _hashreads --;
      if (! _hashreads) {
        sem_post(& _hashsem);
      }
      pthread_mutex_unlock(& _hashmutex);
      return;
    }
  }
  if (_unitmax > 0U) {
    if (i >= 0U) {
      if (i < _unitmax) {
        if ((_unit + i)->on) {
          if (((_unit + i)->level & level) != 0U) {
            tmp___0 = 1;
          } else {
            tmp___0 = 0;
          }
        } else {
          tmp___0 = 0;
        }
      } else {
        tmp___0 = 0;
      }
    } else {
      tmp___0 = 0;
    }
  } else {
    tmp___0 = 0;
  }
  unit = tmp___0;
  if (t->on) {
    if ((t->level & level) != 0U) {
      tmp___1 = 1;
    } else {
      tmp___1 = 0;
    }
  } else {
    tmp___1 = 0;
  }
  thread = tmp___1;
  if (! unit) {
    if (! thread) {
      pthread_mutex_lock(& _hashmutex);
      _hashreads --;
      if (! _hashreads) {
        sem_post(& _hashsem);
      }
      pthread_mutex_unlock(& _hashmutex);
      return;
    }
  }
  time(& tim);
  timeptr = localtime((time_t const   *)(& tim));
  strftime((char * __restrict  )(buf), 64U, (char const   * __restrict  )"%D-%T",
           (struct tm  const  * __restrict  )timeptr);
  sprintf((char * __restrict  )(t->trace), (char const   * __restrict  )"%s:%s:%d:%s:%n",
          buf, file, line, t->name, & n);
  t->wspace[44 - n] = (char )'\000';
  switch ((int )a) {
  case 0: 
  sprintf((char * __restrict  )(t->trace + n), (char const   * __restrict  )"%senter %s(%s)\n",
          t->wspace, fn, s);
  break;
  case 1: 
  sprintf((char * __restrict  )(t->trace + n), (char const   * __restrict  )"%sreturn %s(%s)\n",
          t->wspace, fn, s);
  break;
  case 2: 
  sprintf((char * __restrict  )(t->trace + n), (char const   * __restrict  )"%s%s: return\n",
          t->wspace, fn);
  break;
  case 3: 
  sprintf((char * __restrict  )(t->trace + n), (char const   * __restrict  )"%s%s\n",
          t->wspace, s);
  break;
  case 4: 
  sprintf((char * __restrict  )(t->trace + n), (char const   * __restrict  )"%sERROR in fn %s: %s\n",
          t->wspace, fn, s);
  break;
  }
  t->wspace[44 - n] = (char )' ';
  if (_server) {
    num = 0;
    bytesWritten = 0;
    while (bytesWritten < 1098) {
      num = write(_serv_sockfd, (void *)(t->trace + bytesWritten), 1098 - bytesWritten);
      bytesWritten += num;
    }
    if (bytesWritten == 1098) {
      _msgs ++;
    }
  } else {
    fprintf((FILE * __restrict  )_fp, (char const   * __restrict  )"%s", t->trace);
  }
  pthread_mutex_lock(& _hashmutex);
  _hashreads --;
  if (! _hashreads) {
    sem_post(& _hashsem);
  }
  pthread_mutex_unlock(& _hashmutex);
  return;
}
}
extern int ( /* missing proto */  gethostname)() ;
extern int ( /* missing proto */  memcpy)() ;
int trc_start_client(void) 
{ struct sockaddr_in serv_addr ;
  char name[1024] ;
  struct hostent *hostptr ;
  int tmp ;

  {
  serv_addr.sin_family = (sa_family_t )0;
  serv_addr.sin_port = (unsigned short)0;
  serv_addr.sin_addr.s_addr = 0U;
  serv_addr.sin_zero[0] = (unsigned char)0;
  serv_addr.sin_zero[1] = (unsigned char)0;
  serv_addr.sin_zero[2] = (unsigned char)0;
  serv_addr.sin_zero[3] = (unsigned char)0;
  serv_addr.sin_zero[4] = (unsigned char)0;
  serv_addr.sin_zero[5] = (unsigned char)0;
  serv_addr.sin_zero[6] = (unsigned char)0;
  serv_addr.sin_zero[7] = (unsigned char)0;
  hostptr = (struct hostent *)((void *)0);
  sem_wait(& _startclient);
  _serv_sockfd = socket(2, 1, 0);
  if (_serv_sockfd < 0) {
    perror((char const   *)((void *)0));
    return (1);
  }
  gethostname(name, 1024);
  hostptr = gethostbyname((char const   *)(name));
  memset(& serv_addr, 0, sizeof(serv_addr));
  memcpy(& serv_addr.sin_addr, *(hostptr->h_addr_list + 0), hostptr->h_length);
  serv_addr.sin_family = (unsigned short)2;
  serv_addr.sin_port = htons((unsigned short)2013);
  tmp = connect(_serv_sockfd, (struct sockaddr  const  *)((struct sockaddr *)(& serv_addr)),
                sizeof(serv_addr));
  if (tmp < 0) {
    printf((char const   * __restrict  )"connect error\n");
    perror((char const   *)((void *)0));
    return (1);
  }
  return (0);
}
}
extern int ( /* missing proto */  close)() ;
int trc_stop_client(void) 
{ 

  {
  close(_serv_sockfd);
  return (0);
}
}
extern int ( /* missing proto */  read)() ;
void *trc_start_server(void) 
{ char buf[1098] ;
  int sockfd ;
  int client_sockfd ;
  int status ;
  int on ;
  int nread ;
  int len ;
  struct sockaddr_in serv_addr ;
  struct sockaddr_in client_addr ;
  int tmp ;
  int tmp___0 ;

  {
  status = 0;
  on = 1;
  sockfd = socket(2, 1, 0);
  if (sockfd < 0) {
    perror((char const   *)((void *)0));
    return ((void *)0);
  }
  status = setsockopt(sockfd, 1, 2, (void const   *)((char const   *)(& on)), sizeof(on));
  if (status == -1) {
    perror("setsockopt(..., SO_REUSEADDR,...)");
    return ((void *)0);
  }
  serv_addr.sin_family = (unsigned short)2;
  serv_addr.sin_addr.s_addr = htonl(0U);
  serv_addr.sin_port = htons((unsigned short)2013);
  tmp = bind(sockfd, (struct sockaddr  const  *)(& serv_addr), sizeof(serv_addr));
  if (tmp < 0) {
    perror((char const   *)((void *)0));
    return ((void *)0);
  }
  listen(sockfd, 1);
  sem_post(& _startclient);
  len = (int )sizeof(client_addr);
  client_sockfd = accept(sockfd, (struct sockaddr * __restrict  )(& client_addr),
                         (socklen_t * __restrict  )(& len));
  while (1) {
    if (_server) {
      if (! (client_sockfd != -1)) {
        goto _L;
      }
    } else {
      _L: /* CIL Label */ 
      if (! _msgs) {
        break;
      }
    }
    nread = 0;
    while (1) {
      tmp___0 = read(client_sockfd, buf, 1098);
      nread += tmp___0;
      if (! (nread < 1098)) {
        break;
      }
    }
    _msgs --;
    fprintf((FILE * __restrict  )_fp, (char const   * __restrict  )"%s", buf);
  }
  close(client_sockfd);
  return ((void *)0);
}
}
int trc_stop_server(void) 
{ 

  {
  _server = 0U;
  return ((int )_server);
}
}
