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
  #define CASADI_PREFIX(ID) ls_res_quadcopter_ ## ID
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

static const int CASADI_PREFIX(s0)[15] = {11, 1, 0, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
#define s0 CASADI_PREFIX(s0)
static const int CASADI_PREFIX(s1)[8] = {4, 1, 0, 4, 0, 1, 2, 3};
#define s1 CASADI_PREFIX(s1)
static const int CASADI_PREFIX(s2)[19] = {15, 1, 0, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
#define s2 CASADI_PREFIX(s2)
static const int CASADI_PREFIX(s3)[243] = {15, 15, 0, 15, 30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 180, 195, 210, 225, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
#define s3 CASADI_PREFIX(s3)
/* jac_res */
int jac_res(const real_t** arg, real_t** res, int* iw, real_t* w, int mem) {
  real_t a0=arg[0] ? arg[0][0] : 0;
  if (res[0]!=0) res[0][0]=a0;
  a0=arg[0] ? arg[0][1] : 0;
  if (res[0]!=0) res[0][1]=a0;
  a0=arg[0] ? arg[0][2] : 0;
  if (res[0]!=0) res[0][2]=a0;
  a0=arg[0] ? arg[0][3] : 0;
  if (res[0]!=0) res[0][3]=a0;
  a0=arg[0] ? arg[0][4] : 0;
  if (res[0]!=0) res[0][4]=a0;
  a0=arg[0] ? arg[0][5] : 0;
  if (res[0]!=0) res[0][5]=a0;
  a0=arg[0] ? arg[0][6] : 0;
  if (res[0]!=0) res[0][6]=a0;
  a0=arg[0] ? arg[0][7] : 0;
  if (res[0]!=0) res[0][7]=a0;
  a0=arg[0] ? arg[0][8] : 0;
  if (res[0]!=0) res[0][8]=a0;
  a0=arg[0] ? arg[0][9] : 0;
  if (res[0]!=0) res[0][9]=a0;
  a0=arg[0] ? arg[0][10] : 0;
  if (res[0]!=0) res[0][10]=a0;
  a0=arg[1] ? arg[1][0] : 0;
  if (res[0]!=0) res[0][11]=a0;
  a0=arg[1] ? arg[1][1] : 0;
  if (res[0]!=0) res[0][12]=a0;
  a0=arg[1] ? arg[1][2] : 0;
  if (res[0]!=0) res[0][13]=a0;
  a0=arg[1] ? arg[1][3] : 0;
  if (res[0]!=0) res[0][14]=a0;
  a0=1.;
  if (res[1]!=0) res[1][0]=a0;
  real_t a1=0.;
  if (res[1]!=0) res[1][1]=a1;
  if (res[1]!=0) res[1][2]=a1;
  if (res[1]!=0) res[1][3]=a1;
  if (res[1]!=0) res[1][4]=a1;
  if (res[1]!=0) res[1][5]=a1;
  if (res[1]!=0) res[1][6]=a1;
  if (res[1]!=0) res[1][7]=a1;
  if (res[1]!=0) res[1][8]=a1;
  if (res[1]!=0) res[1][9]=a1;
  if (res[1]!=0) res[1][10]=a1;
  if (res[1]!=0) res[1][11]=a1;
  if (res[1]!=0) res[1][12]=a1;
  if (res[1]!=0) res[1][13]=a1;
  if (res[1]!=0) res[1][14]=a1;
  if (res[1]!=0) res[1][15]=a1;
  if (res[1]!=0) res[1][16]=a0;
  if (res[1]!=0) res[1][17]=a1;
  if (res[1]!=0) res[1][18]=a1;
  if (res[1]!=0) res[1][19]=a1;
  if (res[1]!=0) res[1][20]=a1;
  if (res[1]!=0) res[1][21]=a1;
  if (res[1]!=0) res[1][22]=a1;
  if (res[1]!=0) res[1][23]=a1;
  if (res[1]!=0) res[1][24]=a1;
  if (res[1]!=0) res[1][25]=a1;
  if (res[1]!=0) res[1][26]=a1;
  if (res[1]!=0) res[1][27]=a1;
  if (res[1]!=0) res[1][28]=a1;
  if (res[1]!=0) res[1][29]=a1;
  if (res[1]!=0) res[1][30]=a1;
  if (res[1]!=0) res[1][31]=a1;
  if (res[1]!=0) res[1][32]=a0;
  if (res[1]!=0) res[1][33]=a1;
  if (res[1]!=0) res[1][34]=a1;
  if (res[1]!=0) res[1][35]=a1;
  if (res[1]!=0) res[1][36]=a1;
  if (res[1]!=0) res[1][37]=a1;
  if (res[1]!=0) res[1][38]=a1;
  if (res[1]!=0) res[1][39]=a1;
  if (res[1]!=0) res[1][40]=a1;
  if (res[1]!=0) res[1][41]=a1;
  if (res[1]!=0) res[1][42]=a1;
  if (res[1]!=0) res[1][43]=a1;
  if (res[1]!=0) res[1][44]=a1;
  if (res[1]!=0) res[1][45]=a1;
  if (res[1]!=0) res[1][46]=a1;
  if (res[1]!=0) res[1][47]=a1;
  if (res[1]!=0) res[1][48]=a0;
  if (res[1]!=0) res[1][49]=a1;
  if (res[1]!=0) res[1][50]=a1;
  if (res[1]!=0) res[1][51]=a1;
  if (res[1]!=0) res[1][52]=a1;
  if (res[1]!=0) res[1][53]=a1;
  if (res[1]!=0) res[1][54]=a1;
  if (res[1]!=0) res[1][55]=a1;
  if (res[1]!=0) res[1][56]=a1;
  if (res[1]!=0) res[1][57]=a1;
  if (res[1]!=0) res[1][58]=a1;
  if (res[1]!=0) res[1][59]=a1;
  if (res[1]!=0) res[1][60]=a1;
  if (res[1]!=0) res[1][61]=a1;
  if (res[1]!=0) res[1][62]=a1;
  if (res[1]!=0) res[1][63]=a1;
  if (res[1]!=0) res[1][64]=a0;
  if (res[1]!=0) res[1][65]=a1;
  if (res[1]!=0) res[1][66]=a1;
  if (res[1]!=0) res[1][67]=a1;
  if (res[1]!=0) res[1][68]=a1;
  if (res[1]!=0) res[1][69]=a1;
  if (res[1]!=0) res[1][70]=a1;
  if (res[1]!=0) res[1][71]=a1;
  if (res[1]!=0) res[1][72]=a1;
  if (res[1]!=0) res[1][73]=a1;
  if (res[1]!=0) res[1][74]=a1;
  if (res[1]!=0) res[1][75]=a1;
  if (res[1]!=0) res[1][76]=a1;
  if (res[1]!=0) res[1][77]=a1;
  if (res[1]!=0) res[1][78]=a1;
  if (res[1]!=0) res[1][79]=a1;
  if (res[1]!=0) res[1][80]=a0;
  if (res[1]!=0) res[1][81]=a1;
  if (res[1]!=0) res[1][82]=a1;
  if (res[1]!=0) res[1][83]=a1;
  if (res[1]!=0) res[1][84]=a1;
  if (res[1]!=0) res[1][85]=a1;
  if (res[1]!=0) res[1][86]=a1;
  if (res[1]!=0) res[1][87]=a1;
  if (res[1]!=0) res[1][88]=a1;
  if (res[1]!=0) res[1][89]=a1;
  if (res[1]!=0) res[1][90]=a1;
  if (res[1]!=0) res[1][91]=a1;
  if (res[1]!=0) res[1][92]=a1;
  if (res[1]!=0) res[1][93]=a1;
  if (res[1]!=0) res[1][94]=a1;
  if (res[1]!=0) res[1][95]=a1;
  if (res[1]!=0) res[1][96]=a0;
  if (res[1]!=0) res[1][97]=a1;
  if (res[1]!=0) res[1][98]=a1;
  if (res[1]!=0) res[1][99]=a1;
  if (res[1]!=0) res[1][100]=a1;
  if (res[1]!=0) res[1][101]=a1;
  if (res[1]!=0) res[1][102]=a1;
  if (res[1]!=0) res[1][103]=a1;
  if (res[1]!=0) res[1][104]=a1;
  if (res[1]!=0) res[1][105]=a1;
  if (res[1]!=0) res[1][106]=a1;
  if (res[1]!=0) res[1][107]=a1;
  if (res[1]!=0) res[1][108]=a1;
  if (res[1]!=0) res[1][109]=a1;
  if (res[1]!=0) res[1][110]=a1;
  if (res[1]!=0) res[1][111]=a1;
  if (res[1]!=0) res[1][112]=a0;
  if (res[1]!=0) res[1][113]=a1;
  if (res[1]!=0) res[1][114]=a1;
  if (res[1]!=0) res[1][115]=a1;
  if (res[1]!=0) res[1][116]=a1;
  if (res[1]!=0) res[1][117]=a1;
  if (res[1]!=0) res[1][118]=a1;
  if (res[1]!=0) res[1][119]=a1;
  if (res[1]!=0) res[1][120]=a1;
  if (res[1]!=0) res[1][121]=a1;
  if (res[1]!=0) res[1][122]=a1;
  if (res[1]!=0) res[1][123]=a1;
  if (res[1]!=0) res[1][124]=a1;
  if (res[1]!=0) res[1][125]=a1;
  if (res[1]!=0) res[1][126]=a1;
  if (res[1]!=0) res[1][127]=a1;
  if (res[1]!=0) res[1][128]=a0;
  if (res[1]!=0) res[1][129]=a1;
  if (res[1]!=0) res[1][130]=a1;
  if (res[1]!=0) res[1][131]=a1;
  if (res[1]!=0) res[1][132]=a1;
  if (res[1]!=0) res[1][133]=a1;
  if (res[1]!=0) res[1][134]=a1;
  if (res[1]!=0) res[1][135]=a1;
  if (res[1]!=0) res[1][136]=a1;
  if (res[1]!=0) res[1][137]=a1;
  if (res[1]!=0) res[1][138]=a1;
  if (res[1]!=0) res[1][139]=a1;
  if (res[1]!=0) res[1][140]=a1;
  if (res[1]!=0) res[1][141]=a1;
  if (res[1]!=0) res[1][142]=a1;
  if (res[1]!=0) res[1][143]=a1;
  if (res[1]!=0) res[1][144]=a0;
  if (res[1]!=0) res[1][145]=a1;
  if (res[1]!=0) res[1][146]=a1;
  if (res[1]!=0) res[1][147]=a1;
  if (res[1]!=0) res[1][148]=a1;
  if (res[1]!=0) res[1][149]=a1;
  if (res[1]!=0) res[1][150]=a1;
  if (res[1]!=0) res[1][151]=a1;
  if (res[1]!=0) res[1][152]=a1;
  if (res[1]!=0) res[1][153]=a1;
  if (res[1]!=0) res[1][154]=a1;
  if (res[1]!=0) res[1][155]=a1;
  if (res[1]!=0) res[1][156]=a1;
  if (res[1]!=0) res[1][157]=a1;
  if (res[1]!=0) res[1][158]=a1;
  if (res[1]!=0) res[1][159]=a1;
  if (res[1]!=0) res[1][160]=a0;
  if (res[1]!=0) res[1][161]=a1;
  if (res[1]!=0) res[1][162]=a1;
  if (res[1]!=0) res[1][163]=a1;
  if (res[1]!=0) res[1][164]=a1;
  if (res[1]!=0) res[1][165]=a1;
  if (res[1]!=0) res[1][166]=a1;
  if (res[1]!=0) res[1][167]=a1;
  if (res[1]!=0) res[1][168]=a1;
  if (res[1]!=0) res[1][169]=a1;
  if (res[1]!=0) res[1][170]=a1;
  if (res[1]!=0) res[1][171]=a1;
  if (res[1]!=0) res[1][172]=a1;
  if (res[1]!=0) res[1][173]=a1;
  if (res[1]!=0) res[1][174]=a1;
  if (res[1]!=0) res[1][175]=a1;
  if (res[1]!=0) res[1][176]=a0;
  if (res[1]!=0) res[1][177]=a1;
  if (res[1]!=0) res[1][178]=a1;
  if (res[1]!=0) res[1][179]=a1;
  if (res[1]!=0) res[1][180]=a1;
  if (res[1]!=0) res[1][181]=a1;
  if (res[1]!=0) res[1][182]=a1;
  if (res[1]!=0) res[1][183]=a1;
  if (res[1]!=0) res[1][184]=a1;
  if (res[1]!=0) res[1][185]=a1;
  if (res[1]!=0) res[1][186]=a1;
  if (res[1]!=0) res[1][187]=a1;
  if (res[1]!=0) res[1][188]=a1;
  if (res[1]!=0) res[1][189]=a1;
  if (res[1]!=0) res[1][190]=a1;
  if (res[1]!=0) res[1][191]=a1;
  if (res[1]!=0) res[1][192]=a0;
  if (res[1]!=0) res[1][193]=a1;
  if (res[1]!=0) res[1][194]=a1;
  if (res[1]!=0) res[1][195]=a1;
  if (res[1]!=0) res[1][196]=a1;
  if (res[1]!=0) res[1][197]=a1;
  if (res[1]!=0) res[1][198]=a1;
  if (res[1]!=0) res[1][199]=a1;
  if (res[1]!=0) res[1][200]=a1;
  if (res[1]!=0) res[1][201]=a1;
  if (res[1]!=0) res[1][202]=a1;
  if (res[1]!=0) res[1][203]=a1;
  if (res[1]!=0) res[1][204]=a1;
  if (res[1]!=0) res[1][205]=a1;
  if (res[1]!=0) res[1][206]=a1;
  if (res[1]!=0) res[1][207]=a1;
  if (res[1]!=0) res[1][208]=a0;
  if (res[1]!=0) res[1][209]=a1;
  if (res[1]!=0) res[1][210]=a1;
  if (res[1]!=0) res[1][211]=a1;
  if (res[1]!=0) res[1][212]=a1;
  if (res[1]!=0) res[1][213]=a1;
  if (res[1]!=0) res[1][214]=a1;
  if (res[1]!=0) res[1][215]=a1;
  if (res[1]!=0) res[1][216]=a1;
  if (res[1]!=0) res[1][217]=a1;
  if (res[1]!=0) res[1][218]=a1;
  if (res[1]!=0) res[1][219]=a1;
  if (res[1]!=0) res[1][220]=a1;
  if (res[1]!=0) res[1][221]=a1;
  if (res[1]!=0) res[1][222]=a1;
  if (res[1]!=0) res[1][223]=a1;
  if (res[1]!=0) res[1][224]=a0;
  return 0;
}

void jac_res_incref(void) {
}

void jac_res_decref(void) {
}

int jac_res_n_in(void) { return 2;}

int jac_res_n_out(void) { return 2;}

const char* jac_res_name_in(int i){
  switch (i) {
    case 0: return "i0";
    case 1: return "i1";
    default: return 0;
  }
}

const char* jac_res_name_out(int i){
  switch (i) {
    case 0: return "o0";
    case 1: return "o1";
    default: return 0;
  }
}

const int* jac_res_sparsity_in(int i) {
  switch (i) {
    case 0: return s0;
    case 1: return s1;
    default: return 0;
  }
}

const int* jac_res_sparsity_out(int i) {
  switch (i) {
    case 0: return s2;
    case 1: return s3;
    default: return 0;
  }
}

int jac_res_work(int *sz_arg, int* sz_res, int *sz_iw, int *sz_w) {
  if (sz_arg) *sz_arg = 2;
  if (sz_res) *sz_res = 2;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 2;
  return 0;
}


#ifdef __cplusplus
} /* extern "C" */
#endif
