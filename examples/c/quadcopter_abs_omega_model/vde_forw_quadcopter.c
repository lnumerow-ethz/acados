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
  #define CASADI_PREFIX(ID) vde_forw_quadcopter_ ## ID
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
static const int CASADI_PREFIX(s1)[59] = {7, 7, 0, 7, 14, 21, 28, 35, 42, 49, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6};
#define s1 CASADI_PREFIX(s1)
static const int CASADI_PREFIX(s2)[35] = {7, 4, 0, 7, 14, 21, 28, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6};
#define s2 CASADI_PREFIX(s2)
static const int CASADI_PREFIX(s3)[8] = {4, 1, 0, 4, 0, 1, 2, 3};
#define s3 CASADI_PREFIX(s3)
/* vdeFun */
int vdeFun(const real_t** arg, real_t** res, int* iw, real_t* w, int mem) {
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
  a11=arg[3] ? arg[3][1] : 0;
  real_t a12=sq(a11);
  real_t a13=arg[3] ? arg[3][3] : 0;
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
  a15=arg[3] ? arg[3][0] : 0;
  real_t a16=sq(a15);
  real_t a17=arg[3] ? arg[3][2] : 0;
  real_t a18=sq(a17);
  a16=(a16-a18);
  a16=(a14*a16);
  a16=(a16/a3);
  a8=(a8+a16);
  a8=(a8/a9);
  a8=(-a8);
  if (res[0]!=0) res[0][5]=a8;
  a8=(a9*a0);
  a16=(a8*a4);
  a18=(a9*a0);
  real_t a19=(a18*a4);
  a16=(a16-a19);
  a19=sq(a15);
  real_t a20=sq(a11);
  a19=(a19-a20);
  a20=sq(a17);
  a19=(a19+a20);
  a20=sq(a13);
  a19=(a19-a20);
  a20=9.2249999999999988e-03;
  a19=(a20*a19);
  a19=(a19/a3);
  a16=(a16+a19);
  if (res[0]!=0) res[0][6]=a16;
  a16=arg[1] ? arg[1][4] : 0;
  a19=(a1*a16);
  a3=arg[1] ? arg[1][1] : 0;
  real_t a21=(a0*a3);
  a19=(a19+a21);
  a21=5.0000000000000000e-01;
  a19=(a21*a19);
  real_t a22=arg[1] ? arg[1][5] : 0;
  real_t a23=(a5*a22);
  real_t a24=arg[1] ? arg[1][2] : 0;
  real_t a25=(a4*a24);
  a23=(a23+a25);
  a23=(a21*a23);
  a19=(a19+a23);
  a23=arg[1] ? arg[1][6] : 0;
  a25=(a7*a23);
  real_t a26=arg[1] ? arg[1][3] : 0;
  real_t a27=(a6*a26);
  a25=(a25+a27);
  a25=(a21*a25);
  a19=(a19+a25);
  a19=(-a19);
  if (res[1]!=0) res[1][0]=a19;
  a19=(a2*a16);
  a25=arg[1] ? arg[1][0] : 0;
  a27=(a0*a25);
  a19=(a19+a27);
  a19=(a21*a19);
  a27=(a5*a23);
  real_t a28=(a6*a24);
  a27=(a27+a28);
  a27=(a21*a27);
  a19=(a19-a27);
  a27=(a7*a22);
  a28=(a4*a26);
  a27=(a27+a28);
  a27=(a21*a27);
  a19=(a19+a27);
  if (res[1]!=0) res[1][1]=a19;
  a19=(a2*a22);
  a27=(a4*a25);
  a19=(a19+a27);
  a19=(a21*a19);
  a27=(a1*a23);
  a28=(a6*a3);
  a27=(a27+a28);
  a27=(a21*a27);
  a19=(a19+a27);
  a27=(a7*a16);
  a26=(a0*a26);
  a27=(a27+a26);
  a27=(a21*a27);
  a19=(a19-a27);
  if (res[1]!=0) res[1][2]=a19;
  a19=(a2*a23);
  a25=(a6*a25);
  a19=(a19+a25);
  a19=(a21*a19);
  a25=(a1*a22);
  a3=(a4*a3);
  a25=(a25+a3);
  a25=(a21*a25);
  a19=(a19-a25);
  a25=(a5*a16);
  a24=(a0*a24);
  a25=(a25+a24);
  a25=(a21*a25);
  a19=(a19+a25);
  if (res[1]!=0) res[1][3]=a19;
  a19=(a6*a22);
  a25=(a4*a23);
  a19=(a19+a25);
  a25=(a9*a22);
  a25=(a6*a25);
  a24=(a10*a23);
  a25=(a25+a24);
  a19=(a19-a25);
  a25=4.;
  a19=(a25*a19);
  if (res[1]!=0) res[1][4]=a19;
  a19=(a6*a16);
  a24=(a0*a23);
  a19=(a19+a24);
  a24=(a9*a16);
  a24=(a6*a24);
  a23=(a12*a23);
  a24=(a24+a23);
  a19=(a19-a24);
  a19=(a25*a19);
  a19=(-a19);
  if (res[1]!=0) res[1][5]=a19;
  a19=(a9*a16);
  a19=(a4*a19);
  a24=(a8*a22);
  a19=(a19+a24);
  a16=(a9*a16);
  a16=(a4*a16);
  a22=(a18*a22);
  a16=(a16+a22);
  a19=(a19-a16);
  if (res[1]!=0) res[1][6]=a19;
  a19=arg[1] ? arg[1][11] : 0;
  a16=(a1*a19);
  a22=arg[1] ? arg[1][8] : 0;
  a24=(a0*a22);
  a16=(a16+a24);
  a16=(a21*a16);
  a24=arg[1] ? arg[1][12] : 0;
  a23=(a5*a24);
  a3=arg[1] ? arg[1][9] : 0;
  a27=(a4*a3);
  a23=(a23+a27);
  a23=(a21*a23);
  a16=(a16+a23);
  a23=arg[1] ? arg[1][13] : 0;
  a27=(a7*a23);
  a26=arg[1] ? arg[1][10] : 0;
  a28=(a6*a26);
  a27=(a27+a28);
  a27=(a21*a27);
  a16=(a16+a27);
  a16=(-a16);
  if (res[1]!=0) res[1][7]=a16;
  a16=(a2*a19);
  a27=arg[1] ? arg[1][7] : 0;
  a28=(a0*a27);
  a16=(a16+a28);
  a16=(a21*a16);
  a28=(a5*a23);
  real_t a29=(a6*a3);
  a28=(a28+a29);
  a28=(a21*a28);
  a16=(a16-a28);
  a28=(a7*a24);
  a29=(a4*a26);
  a28=(a28+a29);
  a28=(a21*a28);
  a16=(a16+a28);
  if (res[1]!=0) res[1][8]=a16;
  a16=(a2*a24);
  a28=(a4*a27);
  a16=(a16+a28);
  a16=(a21*a16);
  a28=(a1*a23);
  a29=(a6*a22);
  a28=(a28+a29);
  a28=(a21*a28);
  a16=(a16+a28);
  a28=(a7*a19);
  a26=(a0*a26);
  a28=(a28+a26);
  a28=(a21*a28);
  a16=(a16-a28);
  if (res[1]!=0) res[1][9]=a16;
  a16=(a2*a23);
  a27=(a6*a27);
  a16=(a16+a27);
  a16=(a21*a16);
  a27=(a1*a24);
  a22=(a4*a22);
  a27=(a27+a22);
  a27=(a21*a27);
  a16=(a16-a27);
  a27=(a5*a19);
  a3=(a0*a3);
  a27=(a27+a3);
  a27=(a21*a27);
  a16=(a16+a27);
  if (res[1]!=0) res[1][10]=a16;
  a16=(a6*a24);
  a27=(a4*a23);
  a16=(a16+a27);
  a27=(a9*a24);
  a27=(a6*a27);
  a3=(a10*a23);
  a27=(a27+a3);
  a16=(a16-a27);
  a16=(a25*a16);
  if (res[1]!=0) res[1][11]=a16;
  a16=(a6*a19);
  a27=(a0*a23);
  a16=(a16+a27);
  a27=(a9*a19);
  a27=(a6*a27);
  a23=(a12*a23);
  a27=(a27+a23);
  a16=(a16-a27);
  a16=(a25*a16);
  a16=(-a16);
  if (res[1]!=0) res[1][12]=a16;
  a16=(a9*a19);
  a16=(a4*a16);
  a27=(a8*a24);
  a16=(a16+a27);
  a19=(a9*a19);
  a19=(a4*a19);
  a24=(a18*a24);
  a19=(a19+a24);
  a16=(a16-a19);
  if (res[1]!=0) res[1][13]=a16;
  a16=arg[1] ? arg[1][18] : 0;
  a19=(a1*a16);
  a24=arg[1] ? arg[1][15] : 0;
  a27=(a0*a24);
  a19=(a19+a27);
  a19=(a21*a19);
  a27=arg[1] ? arg[1][19] : 0;
  a23=(a5*a27);
  a3=arg[1] ? arg[1][16] : 0;
  a22=(a4*a3);
  a23=(a23+a22);
  a23=(a21*a23);
  a19=(a19+a23);
  a23=arg[1] ? arg[1][20] : 0;
  a22=(a7*a23);
  a28=arg[1] ? arg[1][17] : 0;
  a26=(a6*a28);
  a22=(a22+a26);
  a22=(a21*a22);
  a19=(a19+a22);
  a19=(-a19);
  if (res[1]!=0) res[1][14]=a19;
  a19=(a2*a16);
  a22=arg[1] ? arg[1][14] : 0;
  a26=(a0*a22);
  a19=(a19+a26);
  a19=(a21*a19);
  a26=(a5*a23);
  a29=(a6*a3);
  a26=(a26+a29);
  a26=(a21*a26);
  a19=(a19-a26);
  a26=(a7*a27);
  a29=(a4*a28);
  a26=(a26+a29);
  a26=(a21*a26);
  a19=(a19+a26);
  if (res[1]!=0) res[1][15]=a19;
  a19=(a2*a27);
  a26=(a4*a22);
  a19=(a19+a26);
  a19=(a21*a19);
  a26=(a1*a23);
  a29=(a6*a24);
  a26=(a26+a29);
  a26=(a21*a26);
  a19=(a19+a26);
  a26=(a7*a16);
  a28=(a0*a28);
  a26=(a26+a28);
  a26=(a21*a26);
  a19=(a19-a26);
  if (res[1]!=0) res[1][16]=a19;
  a19=(a2*a23);
  a22=(a6*a22);
  a19=(a19+a22);
  a19=(a21*a19);
  a22=(a1*a27);
  a24=(a4*a24);
  a22=(a22+a24);
  a22=(a21*a22);
  a19=(a19-a22);
  a22=(a5*a16);
  a3=(a0*a3);
  a22=(a22+a3);
  a22=(a21*a22);
  a19=(a19+a22);
  if (res[1]!=0) res[1][17]=a19;
  a19=(a6*a27);
  a22=(a4*a23);
  a19=(a19+a22);
  a22=(a9*a27);
  a22=(a6*a22);
  a3=(a10*a23);
  a22=(a22+a3);
  a19=(a19-a22);
  a19=(a25*a19);
  if (res[1]!=0) res[1][18]=a19;
  a19=(a6*a16);
  a22=(a0*a23);
  a19=(a19+a22);
  a22=(a9*a16);
  a22=(a6*a22);
  a23=(a12*a23);
  a22=(a22+a23);
  a19=(a19-a22);
  a19=(a25*a19);
  a19=(-a19);
  if (res[1]!=0) res[1][19]=a19;
  a19=(a9*a16);
  a19=(a4*a19);
  a22=(a8*a27);
  a19=(a19+a22);
  a16=(a9*a16);
  a16=(a4*a16);
  a27=(a18*a27);
  a16=(a16+a27);
  a19=(a19-a16);
  if (res[1]!=0) res[1][20]=a19;
  a19=arg[1] ? arg[1][25] : 0;
  a16=(a1*a19);
  a27=arg[1] ? arg[1][22] : 0;
  a22=(a0*a27);
  a16=(a16+a22);
  a16=(a21*a16);
  a22=arg[1] ? arg[1][26] : 0;
  a23=(a5*a22);
  a3=arg[1] ? arg[1][23] : 0;
  a24=(a4*a3);
  a23=(a23+a24);
  a23=(a21*a23);
  a16=(a16+a23);
  a23=arg[1] ? arg[1][27] : 0;
  a24=(a7*a23);
  a26=arg[1] ? arg[1][24] : 0;
  a28=(a6*a26);
  a24=(a24+a28);
  a24=(a21*a24);
  a16=(a16+a24);
  a16=(-a16);
  if (res[1]!=0) res[1][21]=a16;
  a16=(a2*a19);
  a24=arg[1] ? arg[1][21] : 0;
  a28=(a0*a24);
  a16=(a16+a28);
  a16=(a21*a16);
  a28=(a5*a23);
  a29=(a6*a3);
  a28=(a28+a29);
  a28=(a21*a28);
  a16=(a16-a28);
  a28=(a7*a22);
  a29=(a4*a26);
  a28=(a28+a29);
  a28=(a21*a28);
  a16=(a16+a28);
  if (res[1]!=0) res[1][22]=a16;
  a16=(a2*a22);
  a28=(a4*a24);
  a16=(a16+a28);
  a16=(a21*a16);
  a28=(a1*a23);
  a29=(a6*a27);
  a28=(a28+a29);
  a28=(a21*a28);
  a16=(a16+a28);
  a28=(a7*a19);
  a26=(a0*a26);
  a28=(a28+a26);
  a28=(a21*a28);
  a16=(a16-a28);
  if (res[1]!=0) res[1][23]=a16;
  a16=(a2*a23);
  a24=(a6*a24);
  a16=(a16+a24);
  a16=(a21*a16);
  a24=(a1*a22);
  a27=(a4*a27);
  a24=(a24+a27);
  a24=(a21*a24);
  a16=(a16-a24);
  a24=(a5*a19);
  a3=(a0*a3);
  a24=(a24+a3);
  a24=(a21*a24);
  a16=(a16+a24);
  if (res[1]!=0) res[1][24]=a16;
  a16=(a6*a22);
  a24=(a4*a23);
  a16=(a16+a24);
  a24=(a9*a22);
  a24=(a6*a24);
  a3=(a10*a23);
  a24=(a24+a3);
  a16=(a16-a24);
  a16=(a25*a16);
  if (res[1]!=0) res[1][25]=a16;
  a16=(a6*a19);
  a24=(a0*a23);
  a16=(a16+a24);
  a24=(a9*a19);
  a24=(a6*a24);
  a23=(a12*a23);
  a24=(a24+a23);
  a16=(a16-a24);
  a16=(a25*a16);
  a16=(-a16);
  if (res[1]!=0) res[1][26]=a16;
  a16=(a9*a19);
  a16=(a4*a16);
  a24=(a8*a22);
  a16=(a16+a24);
  a19=(a9*a19);
  a19=(a4*a19);
  a22=(a18*a22);
  a19=(a19+a22);
  a16=(a16-a19);
  if (res[1]!=0) res[1][27]=a16;
  a16=arg[1] ? arg[1][32] : 0;
  a19=(a1*a16);
  a22=arg[1] ? arg[1][29] : 0;
  a24=(a0*a22);
  a19=(a19+a24);
  a19=(a21*a19);
  a24=arg[1] ? arg[1][33] : 0;
  a23=(a5*a24);
  a3=arg[1] ? arg[1][30] : 0;
  a27=(a4*a3);
  a23=(a23+a27);
  a23=(a21*a23);
  a19=(a19+a23);
  a23=arg[1] ? arg[1][34] : 0;
  a27=(a7*a23);
  a28=arg[1] ? arg[1][31] : 0;
  a26=(a6*a28);
  a27=(a27+a26);
  a27=(a21*a27);
  a19=(a19+a27);
  a19=(-a19);
  if (res[1]!=0) res[1][28]=a19;
  a19=(a2*a16);
  a27=arg[1] ? arg[1][28] : 0;
  a26=(a0*a27);
  a19=(a19+a26);
  a19=(a21*a19);
  a26=(a5*a23);
  a29=(a6*a3);
  a26=(a26+a29);
  a26=(a21*a26);
  a19=(a19-a26);
  a26=(a7*a24);
  a29=(a4*a28);
  a26=(a26+a29);
  a26=(a21*a26);
  a19=(a19+a26);
  if (res[1]!=0) res[1][29]=a19;
  a19=(a2*a24);
  a26=(a4*a27);
  a19=(a19+a26);
  a19=(a21*a19);
  a26=(a1*a23);
  a29=(a6*a22);
  a26=(a26+a29);
  a26=(a21*a26);
  a19=(a19+a26);
  a26=(a7*a16);
  a28=(a0*a28);
  a26=(a26+a28);
  a26=(a21*a26);
  a19=(a19-a26);
  if (res[1]!=0) res[1][30]=a19;
  a19=(a2*a23);
  a27=(a6*a27);
  a19=(a19+a27);
  a19=(a21*a19);
  a27=(a1*a24);
  a22=(a4*a22);
  a27=(a27+a22);
  a27=(a21*a27);
  a19=(a19-a27);
  a27=(a5*a16);
  a3=(a0*a3);
  a27=(a27+a3);
  a27=(a21*a27);
  a19=(a19+a27);
  if (res[1]!=0) res[1][31]=a19;
  a19=(a6*a24);
  a27=(a4*a23);
  a19=(a19+a27);
  a27=(a9*a24);
  a27=(a6*a27);
  a3=(a10*a23);
  a27=(a27+a3);
  a19=(a19-a27);
  a19=(a25*a19);
  if (res[1]!=0) res[1][32]=a19;
  a19=(a6*a16);
  a27=(a0*a23);
  a19=(a19+a27);
  a27=(a9*a16);
  a27=(a6*a27);
  a23=(a12*a23);
  a27=(a27+a23);
  a19=(a19-a27);
  a19=(a25*a19);
  a19=(-a19);
  if (res[1]!=0) res[1][33]=a19;
  a19=(a9*a16);
  a19=(a4*a19);
  a27=(a8*a24);
  a19=(a19+a27);
  a16=(a9*a16);
  a16=(a4*a16);
  a24=(a18*a24);
  a16=(a16+a24);
  a19=(a19-a16);
  if (res[1]!=0) res[1][34]=a19;
  a19=arg[1] ? arg[1][39] : 0;
  a16=(a1*a19);
  a24=arg[1] ? arg[1][36] : 0;
  a27=(a0*a24);
  a16=(a16+a27);
  a16=(a21*a16);
  a27=arg[1] ? arg[1][40] : 0;
  a23=(a5*a27);
  a3=arg[1] ? arg[1][37] : 0;
  a22=(a4*a3);
  a23=(a23+a22);
  a23=(a21*a23);
  a16=(a16+a23);
  a23=arg[1] ? arg[1][41] : 0;
  a22=(a7*a23);
  a26=arg[1] ? arg[1][38] : 0;
  a28=(a6*a26);
  a22=(a22+a28);
  a22=(a21*a22);
  a16=(a16+a22);
  a16=(-a16);
  if (res[1]!=0) res[1][35]=a16;
  a16=(a2*a19);
  a22=arg[1] ? arg[1][35] : 0;
  a28=(a0*a22);
  a16=(a16+a28);
  a16=(a21*a16);
  a28=(a5*a23);
  a29=(a6*a3);
  a28=(a28+a29);
  a28=(a21*a28);
  a16=(a16-a28);
  a28=(a7*a27);
  a29=(a4*a26);
  a28=(a28+a29);
  a28=(a21*a28);
  a16=(a16+a28);
  if (res[1]!=0) res[1][36]=a16;
  a16=(a2*a27);
  a28=(a4*a22);
  a16=(a16+a28);
  a16=(a21*a16);
  a28=(a1*a23);
  a29=(a6*a24);
  a28=(a28+a29);
  a28=(a21*a28);
  a16=(a16+a28);
  a28=(a7*a19);
  a26=(a0*a26);
  a28=(a28+a26);
  a28=(a21*a28);
  a16=(a16-a28);
  if (res[1]!=0) res[1][37]=a16;
  a16=(a2*a23);
  a22=(a6*a22);
  a16=(a16+a22);
  a16=(a21*a16);
  a22=(a1*a27);
  a24=(a4*a24);
  a22=(a22+a24);
  a22=(a21*a22);
  a16=(a16-a22);
  a22=(a5*a19);
  a3=(a0*a3);
  a22=(a22+a3);
  a22=(a21*a22);
  a16=(a16+a22);
  if (res[1]!=0) res[1][38]=a16;
  a16=(a6*a27);
  a22=(a4*a23);
  a16=(a16+a22);
  a22=(a9*a27);
  a22=(a6*a22);
  a3=(a10*a23);
  a22=(a22+a3);
  a16=(a16-a22);
  a16=(a25*a16);
  if (res[1]!=0) res[1][39]=a16;
  a16=(a6*a19);
  a22=(a0*a23);
  a16=(a16+a22);
  a22=(a9*a19);
  a22=(a6*a22);
  a23=(a12*a23);
  a22=(a22+a23);
  a16=(a16-a22);
  a16=(a25*a16);
  a16=(-a16);
  if (res[1]!=0) res[1][40]=a16;
  a16=(a9*a19);
  a16=(a4*a16);
  a22=(a8*a27);
  a16=(a16+a22);
  a19=(a9*a19);
  a19=(a4*a19);
  a27=(a18*a27);
  a19=(a19+a27);
  a16=(a16-a19);
  if (res[1]!=0) res[1][41]=a16;
  a16=arg[1] ? arg[1][46] : 0;
  a19=(a1*a16);
  a27=arg[1] ? arg[1][43] : 0;
  a22=(a0*a27);
  a19=(a19+a22);
  a19=(a21*a19);
  a22=arg[1] ? arg[1][47] : 0;
  a23=(a5*a22);
  a3=arg[1] ? arg[1][44] : 0;
  a24=(a4*a3);
  a23=(a23+a24);
  a23=(a21*a23);
  a19=(a19+a23);
  a23=arg[1] ? arg[1][48] : 0;
  a24=(a7*a23);
  a28=arg[1] ? arg[1][45] : 0;
  a26=(a6*a28);
  a24=(a24+a26);
  a24=(a21*a24);
  a19=(a19+a24);
  a19=(-a19);
  if (res[1]!=0) res[1][42]=a19;
  a19=(a2*a16);
  a24=arg[1] ? arg[1][42] : 0;
  a26=(a0*a24);
  a19=(a19+a26);
  a19=(a21*a19);
  a26=(a5*a23);
  a29=(a6*a3);
  a26=(a26+a29);
  a26=(a21*a26);
  a19=(a19-a26);
  a26=(a7*a22);
  a29=(a4*a28);
  a26=(a26+a29);
  a26=(a21*a26);
  a19=(a19+a26);
  if (res[1]!=0) res[1][43]=a19;
  a19=(a2*a22);
  a26=(a4*a24);
  a19=(a19+a26);
  a19=(a21*a19);
  a26=(a1*a23);
  a29=(a6*a27);
  a26=(a26+a29);
  a26=(a21*a26);
  a19=(a19+a26);
  a26=(a7*a16);
  a28=(a0*a28);
  a26=(a26+a28);
  a26=(a21*a26);
  a19=(a19-a26);
  if (res[1]!=0) res[1][44]=a19;
  a19=(a2*a23);
  a24=(a6*a24);
  a19=(a19+a24);
  a19=(a21*a19);
  a24=(a1*a22);
  a27=(a4*a27);
  a24=(a24+a27);
  a24=(a21*a24);
  a19=(a19-a24);
  a24=(a5*a16);
  a3=(a0*a3);
  a24=(a24+a3);
  a24=(a21*a24);
  a19=(a19+a24);
  if (res[1]!=0) res[1][45]=a19;
  a19=(a6*a22);
  a24=(a4*a23);
  a19=(a19+a24);
  a24=(a9*a22);
  a24=(a6*a24);
  a3=(a10*a23);
  a24=(a24+a3);
  a19=(a19-a24);
  a19=(a25*a19);
  if (res[1]!=0) res[1][46]=a19;
  a19=(a6*a16);
  a24=(a0*a23);
  a19=(a19+a24);
  a24=(a9*a16);
  a24=(a6*a24);
  a23=(a12*a23);
  a24=(a24+a23);
  a19=(a19-a24);
  a19=(a25*a19);
  a19=(-a19);
  if (res[1]!=0) res[1][47]=a19;
  a19=(a9*a16);
  a19=(a4*a19);
  a24=(a8*a22);
  a19=(a19+a24);
  a16=(a9*a16);
  a16=(a4*a16);
  a22=(a18*a22);
  a16=(a16+a22);
  a19=(a19-a16);
  if (res[1]!=0) res[1][48]=a19;
  a19=arg[2] ? arg[2][4] : 0;
  a16=(a1*a19);
  a22=arg[2] ? arg[2][1] : 0;
  a24=(a0*a22);
  a16=(a16+a24);
  a16=(a21*a16);
  a24=arg[2] ? arg[2][5] : 0;
  a23=(a5*a24);
  a3=arg[2] ? arg[2][2] : 0;
  a27=(a4*a3);
  a23=(a23+a27);
  a23=(a21*a23);
  a16=(a16+a23);
  a23=arg[2] ? arg[2][6] : 0;
  a27=(a7*a23);
  a26=arg[2] ? arg[2][3] : 0;
  a28=(a6*a26);
  a27=(a27+a28);
  a27=(a21*a27);
  a16=(a16+a27);
  a16=(-a16);
  if (res[2]!=0) res[2][0]=a16;
  a16=(a2*a19);
  a27=arg[2] ? arg[2][0] : 0;
  a28=(a0*a27);
  a16=(a16+a28);
  a16=(a21*a16);
  a28=(a5*a23);
  a29=(a6*a3);
  a28=(a28+a29);
  a28=(a21*a28);
  a16=(a16-a28);
  a28=(a7*a24);
  a29=(a4*a26);
  a28=(a28+a29);
  a28=(a21*a28);
  a16=(a16+a28);
  if (res[2]!=0) res[2][1]=a16;
  a16=(a2*a24);
  a28=(a4*a27);
  a16=(a16+a28);
  a16=(a21*a16);
  a28=(a1*a23);
  a29=(a6*a22);
  a28=(a28+a29);
  a28=(a21*a28);
  a16=(a16+a28);
  a28=(a7*a19);
  a26=(a0*a26);
  a28=(a28+a26);
  a28=(a21*a28);
  a16=(a16-a28);
  if (res[2]!=0) res[2][2]=a16;
  a16=(a2*a23);
  a27=(a6*a27);
  a16=(a16+a27);
  a16=(a21*a16);
  a27=(a1*a24);
  a22=(a4*a22);
  a27=(a27+a22);
  a27=(a21*a27);
  a16=(a16-a27);
  a27=(a5*a19);
  a3=(a0*a3);
  a27=(a27+a3);
  a27=(a21*a27);
  a16=(a16+a27);
  if (res[2]!=0) res[2][3]=a16;
  a16=(a6*a24);
  a27=(a4*a23);
  a16=(a16+a27);
  a27=(a9*a24);
  a27=(a6*a27);
  a3=(a10*a23);
  a27=(a27+a3);
  a16=(a16-a27);
  a16=(a25*a16);
  if (res[2]!=0) res[2][4]=a16;
  a16=(a15+a15);
  a16=(a14*a16);
  a16=(a21*a16);
  a16=(a25*a16);
  a27=(a6*a19);
  a3=(a0*a23);
  a27=(a27+a3);
  a3=(a9*a19);
  a3=(a6*a3);
  a23=(a12*a23);
  a3=(a3+a23);
  a27=(a27-a3);
  a27=(a25*a27);
  a16=(a16+a27);
  a16=(-a16);
  if (res[2]!=0) res[2][5]=a16;
  a15=(a15+a15);
  a15=(a20*a15);
  a15=(a21*a15);
  a16=(a9*a19);
  a16=(a4*a16);
  a27=(a8*a24);
  a16=(a16+a27);
  a19=(a9*a19);
  a19=(a4*a19);
  a24=(a18*a24);
  a19=(a19+a24);
  a16=(a16-a19);
  a15=(a15+a16);
  if (res[2]!=0) res[2][6]=a15;
  a15=arg[2] ? arg[2][11] : 0;
  a16=(a1*a15);
  a19=arg[2] ? arg[2][8] : 0;
  a24=(a0*a19);
  a16=(a16+a24);
  a16=(a21*a16);
  a24=arg[2] ? arg[2][12] : 0;
  a27=(a5*a24);
  a3=arg[2] ? arg[2][9] : 0;
  a23=(a4*a3);
  a27=(a27+a23);
  a27=(a21*a27);
  a16=(a16+a27);
  a27=arg[2] ? arg[2][13] : 0;
  a23=(a7*a27);
  a22=arg[2] ? arg[2][10] : 0;
  a28=(a6*a22);
  a23=(a23+a28);
  a23=(a21*a23);
  a16=(a16+a23);
  a16=(-a16);
  if (res[2]!=0) res[2][7]=a16;
  a16=(a2*a15);
  a23=arg[2] ? arg[2][7] : 0;
  a28=(a0*a23);
  a16=(a16+a28);
  a16=(a21*a16);
  a28=(a5*a27);
  a26=(a6*a3);
  a28=(a28+a26);
  a28=(a21*a28);
  a16=(a16-a28);
  a28=(a7*a24);
  a26=(a4*a22);
  a28=(a28+a26);
  a28=(a21*a28);
  a16=(a16+a28);
  if (res[2]!=0) res[2][8]=a16;
  a16=(a2*a24);
  a28=(a4*a23);
  a16=(a16+a28);
  a16=(a21*a16);
  a28=(a1*a27);
  a26=(a6*a19);
  a28=(a28+a26);
  a28=(a21*a28);
  a16=(a16+a28);
  a28=(a7*a15);
  a22=(a0*a22);
  a28=(a28+a22);
  a28=(a21*a28);
  a16=(a16-a28);
  if (res[2]!=0) res[2][9]=a16;
  a16=(a2*a27);
  a23=(a6*a23);
  a16=(a16+a23);
  a16=(a21*a16);
  a23=(a1*a24);
  a19=(a4*a19);
  a23=(a23+a19);
  a23=(a21*a23);
  a16=(a16-a23);
  a23=(a5*a15);
  a3=(a0*a3);
  a23=(a23+a3);
  a23=(a21*a23);
  a16=(a16+a23);
  if (res[2]!=0) res[2][10]=a16;
  a16=(a11+a11);
  a16=(a14*a16);
  a16=(a21*a16);
  a16=(a25*a16);
  a23=(a6*a24);
  a3=(a4*a27);
  a23=(a23+a3);
  a3=(a9*a24);
  a3=(a6*a3);
  a19=(a10*a27);
  a3=(a3+a19);
  a23=(a23-a3);
  a23=(a25*a23);
  a16=(a16+a23);
  if (res[2]!=0) res[2][11]=a16;
  a16=(a6*a15);
  a23=(a0*a27);
  a16=(a16+a23);
  a23=(a9*a15);
  a23=(a6*a23);
  a27=(a12*a27);
  a23=(a23+a27);
  a16=(a16-a23);
  a16=(a25*a16);
  a16=(-a16);
  if (res[2]!=0) res[2][12]=a16;
  a16=(a9*a15);
  a16=(a4*a16);
  a23=(a8*a24);
  a16=(a16+a23);
  a15=(a9*a15);
  a15=(a4*a15);
  a24=(a18*a24);
  a15=(a15+a24);
  a16=(a16-a15);
  a11=(a11+a11);
  a11=(a20*a11);
  a11=(a21*a11);
  a16=(a16-a11);
  if (res[2]!=0) res[2][13]=a16;
  a16=arg[2] ? arg[2][18] : 0;
  a11=(a1*a16);
  a15=arg[2] ? arg[2][15] : 0;
  a24=(a0*a15);
  a11=(a11+a24);
  a11=(a21*a11);
  a24=arg[2] ? arg[2][19] : 0;
  a23=(a5*a24);
  a27=arg[2] ? arg[2][16] : 0;
  a3=(a4*a27);
  a23=(a23+a3);
  a23=(a21*a23);
  a11=(a11+a23);
  a23=arg[2] ? arg[2][20] : 0;
  a3=(a7*a23);
  a19=arg[2] ? arg[2][17] : 0;
  a28=(a6*a19);
  a3=(a3+a28);
  a3=(a21*a3);
  a11=(a11+a3);
  a11=(-a11);
  if (res[2]!=0) res[2][14]=a11;
  a11=(a2*a16);
  a3=arg[2] ? arg[2][14] : 0;
  a28=(a0*a3);
  a11=(a11+a28);
  a11=(a21*a11);
  a28=(a5*a23);
  a22=(a6*a27);
  a28=(a28+a22);
  a28=(a21*a28);
  a11=(a11-a28);
  a28=(a7*a24);
  a22=(a4*a19);
  a28=(a28+a22);
  a28=(a21*a28);
  a11=(a11+a28);
  if (res[2]!=0) res[2][15]=a11;
  a11=(a2*a24);
  a28=(a4*a3);
  a11=(a11+a28);
  a11=(a21*a11);
  a28=(a1*a23);
  a22=(a6*a15);
  a28=(a28+a22);
  a28=(a21*a28);
  a11=(a11+a28);
  a28=(a7*a16);
  a19=(a0*a19);
  a28=(a28+a19);
  a28=(a21*a28);
  a11=(a11-a28);
  if (res[2]!=0) res[2][16]=a11;
  a11=(a2*a23);
  a3=(a6*a3);
  a11=(a11+a3);
  a11=(a21*a11);
  a3=(a1*a24);
  a15=(a4*a15);
  a3=(a3+a15);
  a3=(a21*a3);
  a11=(a11-a3);
  a3=(a5*a16);
  a27=(a0*a27);
  a3=(a3+a27);
  a3=(a21*a3);
  a11=(a11+a3);
  if (res[2]!=0) res[2][17]=a11;
  a11=(a6*a24);
  a3=(a4*a23);
  a11=(a11+a3);
  a3=(a9*a24);
  a3=(a6*a3);
  a27=(a10*a23);
  a3=(a3+a27);
  a11=(a11-a3);
  a11=(a25*a11);
  if (res[2]!=0) res[2][18]=a11;
  a11=(a17+a17);
  a11=(a14*a11);
  a11=(a21*a11);
  a11=(a25*a11);
  a3=(a6*a16);
  a27=(a0*a23);
  a3=(a3+a27);
  a27=(a9*a16);
  a27=(a6*a27);
  a23=(a12*a23);
  a27=(a27+a23);
  a3=(a3-a27);
  a3=(a25*a3);
  a11=(a11-a3);
  if (res[2]!=0) res[2][19]=a11;
  a17=(a17+a17);
  a17=(a20*a17);
  a17=(a21*a17);
  a11=(a9*a16);
  a11=(a4*a11);
  a3=(a8*a24);
  a11=(a11+a3);
  a16=(a9*a16);
  a16=(a4*a16);
  a24=(a18*a24);
  a16=(a16+a24);
  a11=(a11-a16);
  a17=(a17+a11);
  if (res[2]!=0) res[2][20]=a17;
  a17=arg[2] ? arg[2][25] : 0;
  a11=(a1*a17);
  a16=arg[2] ? arg[2][22] : 0;
  a24=(a0*a16);
  a11=(a11+a24);
  a11=(a21*a11);
  a24=arg[2] ? arg[2][26] : 0;
  a3=(a5*a24);
  a27=arg[2] ? arg[2][23] : 0;
  a23=(a4*a27);
  a3=(a3+a23);
  a3=(a21*a3);
  a11=(a11+a3);
  a3=arg[2] ? arg[2][27] : 0;
  a23=(a7*a3);
  a15=arg[2] ? arg[2][24] : 0;
  a28=(a6*a15);
  a23=(a23+a28);
  a23=(a21*a23);
  a11=(a11+a23);
  a11=(-a11);
  if (res[2]!=0) res[2][21]=a11;
  a11=(a2*a17);
  a23=arg[2] ? arg[2][21] : 0;
  a28=(a0*a23);
  a11=(a11+a28);
  a11=(a21*a11);
  a28=(a5*a3);
  a19=(a6*a27);
  a28=(a28+a19);
  a28=(a21*a28);
  a11=(a11-a28);
  a28=(a7*a24);
  a19=(a4*a15);
  a28=(a28+a19);
  a28=(a21*a28);
  a11=(a11+a28);
  if (res[2]!=0) res[2][22]=a11;
  a11=(a2*a24);
  a28=(a4*a23);
  a11=(a11+a28);
  a11=(a21*a11);
  a28=(a1*a3);
  a19=(a6*a16);
  a28=(a28+a19);
  a28=(a21*a28);
  a11=(a11+a28);
  a7=(a7*a17);
  a15=(a0*a15);
  a7=(a7+a15);
  a7=(a21*a7);
  a11=(a11-a7);
  if (res[2]!=0) res[2][23]=a11;
  a2=(a2*a3);
  a23=(a6*a23);
  a2=(a2+a23);
  a2=(a21*a2);
  a1=(a1*a24);
  a16=(a4*a16);
  a1=(a1+a16);
  a1=(a21*a1);
  a2=(a2-a1);
  a5=(a5*a17);
  a27=(a0*a27);
  a5=(a5+a27);
  a5=(a21*a5);
  a2=(a2+a5);
  if (res[2]!=0) res[2][24]=a2;
  a2=(a6*a24);
  a5=(a4*a3);
  a2=(a2+a5);
  a5=(a9*a24);
  a5=(a6*a5);
  a10=(a10*a3);
  a5=(a5+a10);
  a2=(a2-a5);
  a2=(a25*a2);
  a5=(a13+a13);
  a14=(a14*a5);
  a14=(a21*a14);
  a14=(a25*a14);
  a2=(a2-a14);
  if (res[2]!=0) res[2][25]=a2;
  a2=(a6*a17);
  a0=(a0*a3);
  a2=(a2+a0);
  a0=(a9*a17);
  a6=(a6*a0);
  a12=(a12*a3);
  a6=(a6+a12);
  a2=(a2-a6);
  a25=(a25*a2);
  a25=(-a25);
  if (res[2]!=0) res[2][26]=a25;
  a25=(a9*a17);
  a25=(a4*a25);
  a8=(a8*a24);
  a25=(a25+a8);
  a9=(a9*a17);
  a4=(a4*a9);
  a18=(a18*a24);
  a4=(a4+a18);
  a25=(a25-a4);
  a13=(a13+a13);
  a20=(a20*a13);
  a21=(a21*a20);
  a25=(a25-a21);
  if (res[2]!=0) res[2][27]=a25;
  return 0;
}

void vdeFun_incref(void) {
}

void vdeFun_decref(void) {
}

int vdeFun_n_in(void) { return 4;}

int vdeFun_n_out(void) { return 3;}

const char* vdeFun_name_in(int i){
  switch (i) {
    case 0: return "i0";
    case 1: return "i1";
    case 2: return "i2";
    case 3: return "i3";
    default: return 0;
  }
}

const char* vdeFun_name_out(int i){
  switch (i) {
    case 0: return "o0";
    case 1: return "o1";
    case 2: return "o2";
    default: return 0;
  }
}

const int* vdeFun_sparsity_in(int i) {
  switch (i) {
    case 0: return s0;
    case 1: return s1;
    case 2: return s2;
    case 3: return s3;
    default: return 0;
  }
}

const int* vdeFun_sparsity_out(int i) {
  switch (i) {
    case 0: return s0;
    case 1: return s1;
    case 2: return s2;
    default: return 0;
  }
}

int vdeFun_work(int *sz_arg, int* sz_res, int *sz_iw, int *sz_w) {
  if (sz_arg) *sz_arg = 4;
  if (sz_res) *sz_res = 3;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 30;
  return 0;
}


#ifdef __cplusplus
} /* extern "C" */
#endif
