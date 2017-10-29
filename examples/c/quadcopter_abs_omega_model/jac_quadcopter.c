/* This file was automatically generated by CasADi.
   The CasADi copyright holders make no ownership claim of its contents. */
#ifdef __cplusplus
extern "C" {
#endif

#ifdef CODEGEN_PREFIX
  #define NAMESPACE_CONCAT(NS, ID) _NAMESPACE_CONCAT(NS, ID)
  #define _NAMESPACE_CONCAT(NS, ID) NS ## ID
  #define CASADI_PREFIX(ID) NAMESPACE_CONCAT(CODEGEN_PREFIX, ID)
#else /* CODEGEN_PREFIX */
  #define CASADI_PREFIX(ID) jac_quadcopter_ ## ID
#endif /* CODEGEN_PREFIX */

#include <math.h>

#ifndef real_t
#define real_t double
#endif /* real_t */

#define to_double(x) (double) x
#define to_int(x) (int) x
#define CASADI_CAST(x,y) (x) y
/* Pre-c99 compatibility */
#if __STDC_VERSION__ < 199901L
real_t CASADI_PREFIX(fmin)(real_t x, real_t y) { return x<y ? x : y;}
#define fmin(x,y) CASADI_PREFIX(fmin)(x,y)
real_t CASADI_PREFIX(fmax)(real_t x, real_t y) { return x>y ? x : y;}
#define fmax(x,y) CASADI_PREFIX(fmax)(x,y)
#endif

#define PRINTF printf
real_t CASADI_PREFIX(sq)(real_t x) { return x*x;}
#define sq(x) CASADI_PREFIX(sq)(x)

real_t CASADI_PREFIX(sign)(real_t x) { return x<0 ? -1 : x>0 ? 1 : x;}
#define sign(x) CASADI_PREFIX(sign)(x)

static const int CASADI_PREFIX(s0)[11] = {7, 1, 0, 7, 0, 1, 2, 3, 4, 5, 6};
#define s0 CASADI_PREFIX(s0)
static const int CASADI_PREFIX(s1)[8] = {4, 1, 0, 4, 0, 1, 2, 3};
#define s1 CASADI_PREFIX(s1)
static const int CASADI_PREFIX(s2)[59] = {7, 7, 0, 7, 14, 21, 28, 35, 42, 49, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6};
#define s2 CASADI_PREFIX(s2)
/* jacFun */
int jacFun(const real_t** arg, real_t** res, int* iw, real_t* w, int mem) {
  real_t a0=arg[0] ? arg[0][4] : 0;
  real_t a1=arg[0] ? arg[0][1] : 0;
  real_t a2=(a0*a1);
  real_t a3=2.;
  a2=(a2/a3);
  real_t a4=arg[0] ? arg[0][5] : 0;
  real_t a5=arg[0] ? arg[0][2] : 0;
  real_t a6=(a4*a5);
  a6=(a6/a3);
  a2=(a2+a6);
  a6=arg[0] ? arg[0][6] : 0;
  real_t a7=arg[0] ? arg[0][3] : 0;
  real_t a8=(a6*a7);
  a8=(a8/a3);
  a2=(a2+a8);
  a2=(-a2);
  if (res[0]!=0) res[0][0]=a2;
  a2=arg[0] ? arg[0][0] : 0;
  a8=(a0*a2);
  a8=(a8/a3);
  real_t a9=(a6*a5);
  a9=(a9/a3);
  a8=(a8-a9);
  a9=(a4*a7);
  a9=(a9/a3);
  a8=(a8+a9);
  if (res[0]!=0) res[0][1]=a8;
  a8=(a4*a2);
  a8=(a8/a3);
  a9=(a6*a1);
  a9=(a9/a3);
  a8=(a8+a9);
  a9=(a0*a7);
  a9=(a9/a3);
  a8=(a8-a9);
  if (res[0]!=0) res[0][2]=a8;
  a8=(a6*a2);
  a8=(a8/a3);
  a9=(a4*a1);
  a9=(a9/a3);
  a8=(a8-a9);
  a9=(a0*a5);
  a9=(a9/a3);
  a8=(a8+a9);
  if (res[0]!=0) res[0][3]=a8;
  a8=(a4*a6);
  a9=2.5000000000000000e-01;
  real_t a10=(a9*a4);
  real_t a11=(a10*a6);
  a8=(a8-a11);
  a11=arg[1] ? arg[1][1] : 0;
  real_t a12=sq(a11);
  real_t a13=arg[1] ? arg[1][3] : 0;
  real_t a14=sq(a13);
  a12=(a12-a14);
  a14=1.5375000000000000e-02;
  a12=(a14*a12);
  a12=(a12/a3);
  a8=(a8+a12);
  a8=(a8/a9);
  if (res[0]!=0) res[0][4]=a8;
  a8=(a0*a6);
  a12=(a9*a0);
  real_t a15=(a12*a6);
  a8=(a8-a15);
  a15=arg[1] ? arg[1][0] : 0;
  real_t a16=sq(a15);
  real_t a17=arg[1] ? arg[1][2] : 0;
  real_t a18=sq(a17);
  a16=(a16-a18);
  a14=(a14*a16);
  a14=(a14/a3);
  a8=(a8+a14);
  a8=(a8/a9);
  a8=(-a8);
  if (res[0]!=0) res[0][5]=a8;
  a8=(a9*a0);
  a8=(a8*a4);
  a14=(a9*a0);
  a14=(a14*a4);
  a8=(a8-a14);
  a15=sq(a15);
  a11=sq(a11);
  a15=(a15-a11);
  a17=sq(a17);
  a15=(a15+a17);
  a13=sq(a13);
  a15=(a15-a13);
  a13=9.2249999999999988e-03;
  a13=(a13*a15);
  a13=(a13/a3);
  a8=(a8+a13);
  if (res[0]!=0) res[0][6]=a8;
  a8=0.;
  if (res[1]!=0) res[1][0]=a8;
  a13=5.0000000000000000e-01;
  a3=(a13*a0);
  if (res[1]!=0) res[1][1]=a3;
  a3=(a13*a4);
  if (res[1]!=0) res[1][2]=a3;
  a3=(a13*a6);
  if (res[1]!=0) res[1][3]=a3;
  if (res[1]!=0) res[1][4]=a8;
  if (res[1]!=0) res[1][5]=a8;
  if (res[1]!=0) res[1][6]=a8;
  a3=(a13*a0);
  a3=(-a3);
  if (res[1]!=0) res[1][7]=a3;
  if (res[1]!=0) res[1][8]=a8;
  a3=(a13*a6);
  if (res[1]!=0) res[1][9]=a3;
  a3=(a13*a4);
  a3=(-a3);
  if (res[1]!=0) res[1][10]=a3;
  if (res[1]!=0) res[1][11]=a8;
  if (res[1]!=0) res[1][12]=a8;
  if (res[1]!=0) res[1][13]=a8;
  a3=(a13*a4);
  a3=(-a3);
  if (res[1]!=0) res[1][14]=a3;
  a3=(a13*a6);
  a3=(-a3);
  if (res[1]!=0) res[1][15]=a3;
  if (res[1]!=0) res[1][16]=a8;
  a3=(a13*a0);
  if (res[1]!=0) res[1][17]=a3;
  if (res[1]!=0) res[1][18]=a8;
  if (res[1]!=0) res[1][19]=a8;
  if (res[1]!=0) res[1][20]=a8;
  a3=(a13*a6);
  a3=(-a3);
  if (res[1]!=0) res[1][21]=a3;
  a3=(a13*a4);
  if (res[1]!=0) res[1][22]=a3;
  a3=(a13*a0);
  a3=(-a3);
  if (res[1]!=0) res[1][23]=a3;
  if (res[1]!=0) res[1][24]=a8;
  if (res[1]!=0) res[1][25]=a8;
  if (res[1]!=0) res[1][26]=a8;
  if (res[1]!=0) res[1][27]=a8;
  a3=(a13*a1);
  a3=(-a3);
  if (res[1]!=0) res[1][28]=a3;
  a3=(a13*a2);
  if (res[1]!=0) res[1][29]=a3;
  a3=(a13*a7);
  a3=(-a3);
  if (res[1]!=0) res[1][30]=a3;
  a3=(a13*a5);
  if (res[1]!=0) res[1][31]=a3;
  if (res[1]!=0) res[1][32]=a8;
  a3=(a9*a6);
  a3=(a6-a3);
  a15=4.;
  a3=(a15*a3);
  a3=(-a3);
  if (res[1]!=0) res[1][33]=a3;
  if (res[1]!=0) res[1][34]=a8;
  a3=(a13*a5);
  a3=(-a3);
  if (res[1]!=0) res[1][35]=a3;
  a3=(a13*a7);
  if (res[1]!=0) res[1][36]=a3;
  a3=(a13*a2);
  if (res[1]!=0) res[1][37]=a3;
  a3=(a13*a1);
  a3=(-a3);
  if (res[1]!=0) res[1][38]=a3;
  a9=(a9*a6);
  a6=(a6-a9);
  a6=(a15*a6);
  if (res[1]!=0) res[1][39]=a6;
  if (res[1]!=0) res[1][40]=a8;
  if (res[1]!=0) res[1][41]=a8;
  a7=(a13*a7);
  a7=(-a7);
  if (res[1]!=0) res[1][42]=a7;
  a5=(a13*a5);
  a5=(-a5);
  if (res[1]!=0) res[1][43]=a5;
  a1=(a13*a1);
  if (res[1]!=0) res[1][44]=a1;
  a13=(a13*a2);
  if (res[1]!=0) res[1][45]=a13;
  a4=(a4-a10);
  a4=(a15*a4);
  if (res[1]!=0) res[1][46]=a4;
  a0=(a0-a12);
  a15=(a15*a0);
  a15=(-a15);
  if (res[1]!=0) res[1][47]=a15;
  if (res[1]!=0) res[1][48]=a8;
  return 0;
}

void jacFun_incref(void) {
}

void jacFun_decref(void) {
}

int jacFun_n_in(void) { return 2;}

int jacFun_n_out(void) { return 2;}

const char* jacFun_name_in(int i){
  switch (i) {
    case 0: return "i0";
    case 1: return "i1";
    default: return 0;
  }
}

const char* jacFun_name_out(int i){
  switch (i) {
    case 0: return "o0";
    case 1: return "o1";
    default: return 0;
  }
}

const int* jacFun_sparsity_in(int i) {
  switch (i) {
    case 0: return s0;
    case 1: return s1;
    default: return 0;
  }
}

const int* jacFun_sparsity_out(int i) {
  switch (i) {
    case 0: return s0;
    case 1: return s2;
    default: return 0;
  }
}

int jacFun_work(int *sz_arg, int* sz_res, int *sz_iw, int *sz_w) {
  if (sz_arg) *sz_arg = 2;
  if (sz_res) *sz_res = 2;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 19;
  return 0;
}


#ifdef __cplusplus
} /* extern "C" */
#endif
