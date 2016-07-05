
#ifndef MACROS_H
#define MACROS_H

// Append two preprocessor arguments together
#define _APPEND(a,b) a##b
#define APPEND(a,b) _APPEND(a,b)

// Count number of arguments
#define _NARGS(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,N,...) N
#define NARGS(...) APPEND(_NARGS(__VA_ARGS__,10,9,8,7,6,5,4,3,2,1),)

// Stringize Token
#define _STR(x) #x
#define STR(x) _STR(x)

// Get specific value from __VA_ARGS__
#define PGET_0(e0,...) e0
#define PGET_1(e0,e1,...) e1
#define PGET_2(e0,e1,e2,...) e2
#define PGET_3(e0,e1,e2,e3,...) e3
#define PGET_4(e0,e1,e2,e3,e4,...) e4
#define PGET_5(e0,e1,e2,e3,e4,e5,...) e5
#define PGET_6(e0,e1,e2,e3,e4,e5,e6,...) e6
#define PGET_7(e0,e1,e2,e3,e4,e5,e6,e7,...) e7
#define PGET_8(e0,e1,e2,e3,e4,e5,e6,e7,e8,...) e8
#define PGET_9(e0,e1,e2,e3,e4,e5,e6,e7,e8,e9,...) e9
#ifdef WIN32
# define PGET_N(n,...) PGET_I(n,__VA_ARGS__)
# define PGET_I(n,...) APPEND(APPEND(PGET_,n)(__VA_ARGS__),)
#else
# define PGET_N(n,...) APPEND(PGET_,n)(__VA_ARGS__)
#endif

// Declare variables using comma separator
#define PDECL_1(e0,...) e0 v0
#define PDECL_2(e0,e1,...) e0 v0, e1 v1
#define PDECL_3(e0,e1,e2,...) e0 v0, e1 v1, e2 v2
#define PDECL_4(e0,e1,e2,e3,...) e0 v0, e1 v1, e2 v2, e3 v3
#define PDECL_5(e0,e1,e2,e3,e4,...) e0 v0, e1 v1, e2 v2, e3 v3, e4 v4
#define PDECL_6(e0,e1,e2,e3,e4,e5,...) e0 v0, e1 v1, e2 v2, e3 v3, e4 v4, e5 v5
#define PDECL_7(e0,e1,e2,e3,e4,e5,e6,...) e0 v0, e1 v1, e2 v2, e3 v3, e4 v4, e5 v5, e6 v6
#define PDECL_8(e0,e1,e2,e3,e4,e5,e6,e7,...) e0 v0, e1 v1, e2 v2, e3 v3, e4 v4, e5 v5, e6 v6, e7 v7
#define PDECL_9(e0,e1,e2,e3,e4,e5,e6,e7,e8,...) e0 v0, e1 v1, e2 v2, e3 v3, e4 v4, e5 v5, e6 v6, e7 v7, e8 v8
#define PDECL_10(e0,e1,e2,e3,e4,e5,e6,e7,e8,e9,...) e0 v0, e1 v1, e2 v2, e3 v3, e4 v4, e5 v5, e6 v6, e7 v7, e8 v8, e9 v9
#ifdef WIN32
# define PDECL_N(n,...) PDECL_I(n,__VA_ARGS__)
# define PDECL_I(n,...) APPEND(APPEND(PDECL_,n)(__VA_ARGS__),)
#else
# define PDECL_N(n,...) APPEND(PDECL_,n)(__VA_ARGS__)
#endif

// Pass variables using comma separator
#define PCALL_1(...) v0
#define PCALL_2(...) v0, v1
#define PCALL_3(...) v0, v1, v2
#define PCALL_4(...) v0, v1, v2, v3
#define PCALL_5(...) v0, v1, v2, v3, v4
#define PCALL_6(...) v0, v1, v2, v3, v4, v5
#define PCALL_7(...) v0, v1, v2, v3, v4, v5, v6
#define PCALL_8(...) v0, v1, v2, v3, v4, v5, v6, v7
#define PCALL_9(...) v0, v1, v2, v3, v4, v5, v6, v7, v8
#define PCALL_10(...) v0, v1, v2, v3, v4, v5, v6, v7, v8, v9
#ifdef WIN32
# define PCALL_N(n,...) PCALL_I(n,__VA_ARGS__)
# define PCALL_I(n,...) APPEND(APPEND(PCALL_,n)(__VA_ARGS__),)
#else
# define PCALL_N(n,...) APPEND(PCALL_,n)(__VA_ARGS__)
#endif

#include "openglerror.h"

#define GL_REPORT_STMT(type,func,...) { OpenGLError ev(STR(type), STR(func), OpenGLError::type, OpenGLError::func); OpenGLError::sendEvent(&ev); }
#ifdef WIN32
# define GL_REPORT(type,func,...) APPEND(GL_REPORT_STMT(type,func,__VA_ARGS__),)
#else
# define GL_REPORT(type,func,...) GL_REPORT_STMT(type,func,__VA_ARGS__)
#endif

// Accept declarations
#define GL_DECL_1(fn) inline bool fn()
#define GL_DECL_2(fn,t0,...) inline bool fn(PDECL_1(t0))
#define GL_DECL_3(fn,t0,t1,...) inline bool fn(PDECL_2(t0,t1))
#define GL_DECL_4(fn,t0,t1,t2,...) inline bool fn(PDECL_3(t0,t1,t2))
#define GL_DECL_5(fn,t0,t1,t2,t3,...) inline bool fn(PDECL_4(t0,t1,t2,t3))
#define GL_DECL_6(fn,t0,t1,t2,t3,t4,...) inline bool fn(PDECL_5(t0,t1,t2,t3,t4))
#define GL_DECL_7(fn,t0,t1,t2,t3,t4,t5,...) inline bool fn(PDECL_6(t0,t1,t2,t3,t4,t5))
#define GL_DECL_8(fn,t0,t1,t2,t3,t4,t5,t6,...) inline bool fn(PDECL_7(t0,t1,t2,t3,t4,t5,t6))
#define GL_DECL_9(fn,t0,t1,t2,t3,t4,t5,t6,t7,...) inline bool fn(PDECL_8(t0,t1,t2,t3,t4,t5,t6,t7))
#define GL_DECL_10(fn,t0,t1,t2,t3,t4,t5,t6,t7,t8,...) inline bool fn(PDECL_9(t0,t1,t2,t3,t4,t5,t6,t7,t8))
#define GL_DECL_11(fn,t0,t1,t2,t3,t4,t5,t6,t7,t8,t9,...) inline bool fn(PDECL_10(t0,t1,t2,t3,t4,t5,t6,t7,t8,t9))

// Accept callings
#define GL_CALL_1(caller,fn) caller::fn()
#define GL_CALL_2(caller,fn,...) caller::fn(PCALL_1())
#define GL_CALL_3(caller,fn,...) caller::fn(PCALL_2())
#define GL_CALL_4(caller,fn,...) caller::fn(PCALL_3())
#define GL_CALL_5(caller,fn,...) caller::fn(PCALL_4())
#define GL_CALL_6(caller,fn,...) caller::fn(PCALL_5())
#define GL_CALL_7(caller,fn,...) caller::fn(PCALL_6())
#define GL_CALL_8(caller,fn,...) caller::fn(PCALL_7())
#define GL_CALL_9(caller,fn,...) caller::fn(PCALL_8())
#define GL_CALL_10(caller,fn,...) caller::fn(PCALL_9())
#define GL_CALL_11(caller,fn,...) caller::fn(PCALL_10())

// Platform-specific entry points
#ifdef WIN32
# define GL_DECL(...) GL_DECL_I(NARGS(__VA_ARGS__),__VA_ARGS__)
# define GL_DECL_I(n,...) APPEND(APPEND(GL_DECL_,n)(__VA_ARGS__),)
# define GL_CALL(caller,...) GL_CALL_I(NARGS(__VA_ARGS__),caller,__VA_ARGS__)
# define GL_CALL_I(n,caller,...) APPEND(APPEND(GL_CALL_,n)(caller,__VA_ARGS__),)
#else
# define GL_DECL(...) APPEND(GL_DECL_,NARGS(__VA_ARGS__)(__VA_ARGS__))
# define GL_CALL(caller,...) APPEND(GL_CALL_,NARGS(__VA_ARGS__)(caller,__VA_ARGS__))
#endif

// Entry points
#ifdef    GL_DEBUG
# define GL_CHECK(caller,...) GL_DECL(__VA_ARGS__) { if(!GL_CALL(caller,__VA_ARGS__)) { GL_REPORT(caller,__VA_ARGS__); return false; } return true; }
#else
# define GL_CHECK(caller,...)
#endif // GL_DEBUG

#endif // MACROS_H
