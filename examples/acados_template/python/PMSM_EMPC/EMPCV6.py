from acados_template import *
import acados_template as at
import numpy as nmp
from ctypes import *
import matplotlib
import matplotlib.pyplot as plt
import scipy.linalg
import json

CODE_GEN = 1
COMPILE = 1

FORMULATION = 4         # 0 for hexagon | 1  for torque control with Hexagon | 2  Pos definite Constraint + Hexagon | 3 pure nonlinear | 4 Pos definite Constraint + terminal set

i_d_ref =  -100         # Setpoints only valid for Formulation 0, for Formulation 1 and 2 the setpoints are setting to 0 => like a E-MPC  
i_q_ref =  50       
w_val = 2000.0          # do not change in this script, sometimes the values below calculate with a fix w_val = 2000 1/S

# constants
L_d = 107e-6 
L_q = 150e-6
R_m = 18.15e-3
K_m = 13.8e-3
N_P = 5.0
u_max = 48
i_max = 155.0     # only for simulation

alpha = R_m**2 + w_val**2*L_d**2
beta  = R_m**2 + w_val**2*L_q**2
gamma = 2*R_m*w_val*(L_d-L_q)
delta = 2*w_val**2*L_d*K_m
epsilon = 2*R_m*w_val*K_m
rho = w_val**2*K_m**2

phi = 0

x0Start = nmp.array([-25, -10])

SLACK_TUNING   =  1e2
SLACK_E_TUNING =  10e3

Weight_TUNING = 1e-7
Weight_E_TUNING = 1e-7

INPUT_REG = 1e-9
SLACK_TUNINGHessian = 0

TAU = 3

# set sample time
Ts = 0.000125

N = 6       # N=6 and N=8

# Model of the PMSM
#====================================================================
def export_ode_model():

    model_name = 'rsm'

    # set up states 
    i_d = SX.sym('i_d')
    i_q = SX.sym('i_q')
    x = vertcat(i_d, i_q)

    # set up controls 
    u_d = SX.sym('u_d')
    u_q = SX.sym('u_q')
    u = vertcat(u_d, u_q)

    # set up xdot 
    i_d_dot = SX.sym('i_d_dot')
    i_q_dot = SX.sym('i_q_dot')
    xdot = vertcat(i_d_dot, i_q_dot)

    # set up parameters
    omega  = SX.sym('omega')    # speed
    dist_d = SX.sym('dist_d')   # d disturbance
    dist_q = SX.sym('dist_q')   # q disturbance
    p = vertcat(omega, dist_d, dist_q)

    # dynamics     
    fexpl = vertcat(-(R_m/L_d)*i_d + (L_q/L_d)*omega*i_q + u_d/L_d, \
                    -(L_d/L_q)*omega*i_d - (R_m/L_q)*i_q + u_q/L_q - (omega*K_m)/L_q)

    fimpl = vertcat(-i_d_dot-(R_m/L_d)*i_d + (L_q/L_d)*omega*i_q + u_d/L_d, \
                    -i_q_dot-(L_d/L_q)*omega*i_d - (R_m/L_q)*i_q + u_q/L_q - (omega*K_m)/L_q)

    model = acados_dae()

    model.f_impl_expr = []
    model.f_expl_expr = fexpl
    model.x = x
    model.xdot = xdot
    model.u = u
    model.z = []
    model.p = p
    model.name = model_name

    return model 

# Hexagon Voltage Constraints
#====================================================================
def get_general_constraints_DC(phi,u_max,w_val):

    # polytopic constraint on the input
    s3 = sqrt(3)
    cphi = cos(phi)
    sphi = sin(phi)
    
    h1 = s3*cphi + sphi
    h2 = sphi
    h3 = -s3*cphi + sphi
    h7 = -s3*sphi + cphi
    h8 = cphi
    h9 = s3*sphi + cphi

    # form D and C matrices
    # (acados C interface works with column major format)
    D = nmp.array([[h1, h7],[h2, h8],[h3, h9]])
    C = nmp.array([[0, 0],[0, 0],[0, 0]])

    g1 = 2.0/s3*u_max
    g2 = 1.0/s3*u_max

    lg = nmp.array([-g1, -g2, -g1])
    ug = nmp.array([g1, g2, g1])
 
    res = dict()
    res["D"] = D
    res["C"] = C
    res["lg"] = lg
    res["ug"] = ug

    return res

# Hexagon Terminal Constraints
#====================================================================
def get_general_terminal_constraints_DC(phi):

    # polytopic constraint on the input
    s3 = sqrt(3)
    cphi = cos(phi)
    sphi = sin(phi)
    
    h1 = s3*cphi + sphi
    h2 = sphi
    h3 = -s3*cphi + sphi
    h7 = -s3*sphi + cphi
    h8 = cphi
    h9 = s3*sphi + cphi

    # form D and C matrices
    # (acados C interface works with column major format)
    D = nmp.array([[h1, h7],[h2, h8],[h3, h9]])

    A = nmp.array([[-R_m/L_d, w_val*L_q/L_d],[-w_val*L_d/L_q, -R_m/L_q]])
    invB = nmp.array([[L_d,0],[0,L_q]])
    f = nmp.array([[0],[-K_m*w_val/L_q]])
    
    invBA = invB.dot(A)
    Ce = D.dot(invBA)

    g1 = 2.0/s3*u_max
    g2 = 1.0/s3*u_max

    invBf = invB.dot(f)
    lge = -nmp.array([[g1], [g2], [g1]]) - D.dot(invBf)
    uge = +nmp.array([[g1], [g2], [g1]]) - D.dot(invBf)
    
    res = dict()
    res["Ce"] = Ce
    res["lge"] = lge
    res["uge"] = uge

    return res

# Torque Constraints
#====================================================================
def export_torqueline():

    con_name = 'torqueline'

    # set up states 
    i_d = SX.sym('i_d')
    i_q = SX.sym('i_q')
    x = vertcat(i_d, i_q)

    # set up controls
    u_d = SX.sym('u_d')
    u_q = SX.sym('u_q')
    u = vertcat(u_d, u_q)

    # set up parameters
    omega  = SX.sym('omega')    # speed
    dist_d = SX.sym('dist_d')   # d disturbance
    dist_q = SX.sym('dist_q')   # q disturbance
    p = vertcat(omega, dist_d, dist_q)

    # torque and voltage constraints
    constraint = acados_constraint()

    r = SX.sym('r', 1, 1)
    constraint.con_h_expr = r[0]
    constraint.con_r_expr = TAU - 1.5*N_P*(K_m*i_q)
    # constraint.con_r_expr = TAU - 1.5*N_P*((L_d-L_q)*i_d*i_q + K_m*i_q)
    constraint.x = x
    constraint.u = u 
    constraint.r = r
    constraint.nr = 1
    constraint.nh = 1
    constraint.name = con_name

    return constraint  

# Torque Constraints --> pd
#====================================================================
def export_torqueline_pd():

    con_name = 'torqueline'

    # set up states 
    i_d = SX.sym('i_d')
    i_q = SX.sym('i_q')
    x = vertcat(i_d, i_q)

    # set up controls
    u_d = SX.sym('u_d')
    u_q = SX.sym('u_q')
    u = vertcat(u_d, u_q)

    # set up parameters
    omega  = SX.sym('omega')    # speed
    dist_d = SX.sym('dist_d')   # d disturbance
    dist_q = SX.sym('dist_q')   # q disturbance
    p = vertcat(omega, dist_d, dist_q)

    # torque and voltage constraints
    constraint = acados_constraint()

    r = SX.sym('r', 3, 1)
    constraint.con_h_expr = vertcat(r[0], r[1]**2 + r[2]**2)
    constraint.con_r_expr = vertcat(TAU - 1.5*N_P*(K_m*i_q), u_d, u_q)
    # constraint.con_r_expr =  vertcat(TAU - 1.5*N_P*((L_d-L_q)*i_d*i_q + K_m*i_q), u_d, u_q)
    constraint.x = x
    constraint.u = u 
    constraint.r = r
    constraint.nr = 3
    constraint.nh = 2
    constraint.name = con_name

    return constraint 

# torque Constraints --> nl
#====================================================================
def export_torqueline_nl():

    con_name = 'torqueline'

    # set up states 
    i_d = SX.sym('i_d')
    i_q = SX.sym('i_q')
    x = vertcat(i_d, i_q)

    # set up controls
    u_d = SX.sym('u_d')
    u_q = SX.sym('u_q')
    u = vertcat(u_d, u_q)

    # set up parameters
    omega  = SX.sym('omega')    # speed
    dist_d = SX.sym('dist_d')   # d disturbance
    dist_q = SX.sym('dist_q')   # q disturbance
    p = vertcat(omega, dist_d, dist_q)

    # torque and voltage constraints
    constraint = acados_constraint()

    constraint.con_h_expr = TAU - 1.5*N_P*(K_m*i_q)
    # constraint.con_h_expr = TAU - 1.5*N_P*((L_d-L_q)*i_d*i_q + K_m*i_q)
    constraint.x = x
    constraint.u = u 
    constraint.nh = 1
    constraint.name = con_name

    return constraint  

# torque End-Constraints
#====================================================================
def export_torquelineEnd():

    con_name = 'torquelineEnd'

    # set up states 
    i_d = SX.sym('i_d')
    i_q = SX.sym('i_q')
    x = vertcat(i_d, i_q)

    # set up controls
    u_d = SX.sym('u_d')
    u_q = SX.sym('u_q') 
    u = vertcat(u_d, u_q)

    # set up parameters
    omega  = SX.sym('omega')    # speed
    dist_d = SX.sym('dist_d')   # d disturbance
    dist_q = SX.sym('dist_q')   # q disturbance
    p = vertcat(omega, dist_d, dist_q)
    
    # torque and voltage constraints
    constraint = acados_constraint()

    r = SX.sym('r', 1, 1)
    constraint.con_h_expr = r[0]
    constraint.con_r_expr = TAU - 1.5*N_P*(K_m*i_q)
    # constraint.con_r_expr = TAU - 1.5*N_P*((L_d-L_q)*i_d*i_q + K_m*i_q)
    constraint.x = x
    constraint.u = u 
    constraint.r = r
    constraint.nr = 1
    constraint.nh = 1
    constraint.name = con_name

    return constraint

# torque End-Constraints --> pd
#====================================================================
def export_torquelineEnd_pd():

    con_name = 'torquelineEnd'

    # set up states 
    i_d = SX.sym('i_d')
    i_q = SX.sym('i_q')
    x = vertcat(i_d, i_q)

    # set up controls
    u_d = SX.sym('u_d')
    u_q = SX.sym('u_q') 
    u = vertcat(u_d, u_q)

    # set up parameters
    omega  = SX.sym('omega')    # speed
    dist_d = SX.sym('dist_d')   # d disturbance
    dist_q = SX.sym('dist_q')   # q disturbance
    p = vertcat(omega, dist_d, dist_q)
    
    # torque and voltage constraints
    constraint = acados_constraint()

    r = SX.sym('r', 3, 1)
    constraint.con_h_expr = vertcat(r[0], alpha*r[1]**2 + beta*r[2]**2 + gamma*r[1]*r[2] + delta*r[1] + epsilon*r[2] + rho)
    constraint.con_r_expr = vertcat(TAU - 1.5*N_P*(K_m*i_q), i_d, i_q)
    # constraint.con_r_expr = vertcat(TAU - 1.5*N_P*((L_d-L_q)*i_d*i_q + K_m*i_q), i_d, i_q)
    constraint.x = x
    constraint.u = u 
    constraint.r = r
    constraint.nr = 3
    constraint.nh = 2
    constraint.name = con_name

    return constraint

# torque End-Constraints --> nl
#====================================================================
def export_torquelineEnd_nl():

    con_name = 'torquelineEnd'

    # set up states 
    i_d = SX.sym('i_d')
    i_q = SX.sym('i_q')
    x = vertcat(i_d, i_q)

    # set up controls
    u_d = SX.sym('u_d')
    u_q = SX.sym('u_q') 
    u = vertcat(u_d, u_q)

    # set up parameters
    omega  = SX.sym('omega')    # speed
    dist_d = SX.sym('dist_d')   # d disturbance
    dist_q = SX.sym('dist_q')   # q disturbance
    p = vertcat(omega, dist_d, dist_q)
    
    # torque and voltage constraints
    constraint = acados_constraint()

    constraint.con_h_expr = nmp.array([TAU - 1.5*N_P*(K_m*i_q)])
    # constraint.con_h_expr = TAU - 1.5*N_P*((L_d-L_q)*i_d*i_q + K_m*i_q)
    constraint.x = x
    constraint.u = u
    constraint.nh = 1
    constraint.name = con_name

    return constraint

# create render arguments
ra = acados_ocp_nlp()

# export model
model = export_ode_model()

# set model_name
ra.model = model

# export constraint description
if FORMULATION == 1:
    constraint_nltorqueline = export_torqueline()
    constraint_nltorquelineEnd = export_torquelineEnd()
if FORMULATION == 2:
    constraint_nltorqueline = export_torqueline_pd()
    constraint_nltorquelineEnd = export_torquelineEnd()
if FORMULATION == 3:
    constraint_nltorqueline = export_torqueline_nl()
    constraint_nltorquelineEnd = export_torquelineEnd_nl()
if FORMULATION == 4:
    constraint_nltorqueline = export_torqueline_pd()
    constraint_nltorquelineEnd = export_torquelineEnd_pd()

# set model dims
nx = model.x.size()[0]
nu = model.u.size()[0]
np = model.p.size()[0]
ny = nu + nx
ny_e = nx
Tf = N*Ts

# set ocp_nlp_dimensions
nlp_dims = ra.dims
nlp_dims.nx = nx
nlp_dims.nu = nu
nlp_dims.np = np
nlp_dims.ny = ny
nlp_dims.ny_e = ny_e

if FORMULATION == 0:
    nlp_dims.nbu = 0
    nlp_dims.ng = 3
    nlp_dims.ng_e = 3

if FORMULATION == 1:        
    nlp_dims.nbu = 0
    nlp_dims.ng = 3
    nlp_dims.ng_e = 3
    nlp_dims.nh  = 1                    # 1st torque constraint 
    nlp_dims.npd  = 1                   # 1st torque constraint 
    nlp_dims.nh_e = 1                   # 1st torque constraint 
    nlp_dims.npd_e = 1                  # 1st torque constraint 
    nlp_dims.ns = 1
    nlp_dims.ns_e = 1 
    nlp_dims.nsh = 1
    nlp_dims.nsh_e = 1 

if FORMULATION == 2:        
    nlp_dims.nbu = 0
    nlp_dims.ng = 3
    nlp_dims.ng_e = 3
    nlp_dims.nh  = 2                    # 1st torque constraint | 2nd voltage constraint
    nlp_dims.npd  = 2         # 1st torque constraint | 2nd voltage constraint
    nlp_dims.nh_e = 1                   # 1st torque constraint | 2nd terminal set
    nlp_dims.npd_e = 1      # 1st torque constraint | 2nd terminal set
    nlp_dims.ns = 1
    nlp_dims.ns_e = 1 
    nlp_dims.nsh = 1
    nlp_dims.nsh_e = 1 

if FORMULATION == 3:        
    nlp_dims.nbu = 0
    nlp_dims.ng = 3
    nlp_dims.ng_e = 3
    nlp_dims.nh  = 1        # 1st torque constraint | 2nd voltage constraints
    nlp_dims.nh_e = 1       # 1st torque constraint | 2nd terminal set
    nlp_dims.ns = 1
    nlp_dims.ns_e = 1 
    nlp_dims.nsh = 1
    nlp_dims.nsh_e = 1 

if FORMULATION == 4:        
    nlp_dims.nbu = 0
    nlp_dims.ng = 3
    nlp_dims.ng_e = 3
    nlp_dims.nh  = 2            # 1st torque constraint | 2nd voltage constraint
    nlp_dims.npd  = 3           # 1st torque constraint | 2nd voltage constraint
    nlp_dims.nh_e = 2           # 1st torque constraint | 2nd terminal set
    nlp_dims.npd_e = 3          # 1st torque constraint | 2nd terminal set
    nlp_dims.ns = 1
    nlp_dims.ns_e = 1 
    nlp_dims.nsh = 1
    nlp_dims.nsh_e = 1 

nlp_dims.nbx = 0
nlp_dims.nbx_e = 0
nlp_dims.N = N

# set weighting matrices
nlp_cost = ra.cost

Q = nmp.eye(nx)
Q[0,0] = Weight_TUNING*Tf/N
Q[1,1] = Weight_TUNING*Tf/N

Q_e = nmp.eye(nx)
Q_e[0,0] = Weight_E_TUNING*Tf/N
Q_e[1,1] = Weight_E_TUNING*Tf/N

R = nmp.eye(nu)
R[0,0] = INPUT_REG*Tf/N
R[1,1] = INPUT_REG*Tf/N

nlp_cost.W = scipy.linalg.block_diag(Q, R)   # weight matrix
nlp_cost.W_e = Q_e                           # weight matrix for Mayer term

Vu = nmp.zeros((ny, nu))
Vu[2,0] = 1.0
Vu[3,1] = 1.0
nlp_cost.Vu = Vu

Vx = nmp.zeros((ny, nx))
Vx[0,0] = 1.0
Vx[1,1] = 1.0
nlp_cost.Vx = Vx

Vx_e = nmp.zeros((ny_e, nx))
Vx_e[0,0] = 1.0
Vx_e[1,1] = 1.0
nlp_cost.Vx_e = Vx_e

if FORMULATION == 0: 
    nlp_cost.yref  = nmp.zeros((ny, ))
    nlp_cost.yref[0] = i_d_ref
    nlp_cost.yref[1] = i_q_ref
    nlp_cost.yref[2] = 0
    nlp_cost.yref[3] = 0
    nlp_cost.yref_e = nmp.zeros((ny_e, ))
    nlp_cost.yref_e[0] = i_d_ref
    nlp_cost.yref_e[1] = i_q_ref
else: 
    nlp_cost.yref  = nmp.zeros((ny, ))
    nlp_cost.yref[0] = 0
    nlp_cost.yref[1] = 0
    nlp_cost.yref[2] = 0
    nlp_cost.yref[3] = 0
    nlp_cost.yref_e = nmp.zeros((ny_e, ))
    nlp_cost.yref_e[0] = 0
    nlp_cost.yref_e[1] = 0

# get D and C
res = get_general_constraints_DC(phi,u_max,w_val)
D = res["D"]
C = res["C"]
lg = res["lg"]
ug = res["ug"]

res = get_general_terminal_constraints_DC(phi)
Ce = res["Ce"]
lge = res["lge"]
uge = res["uge"]

# setting bounds
nlp_con = ra.constraints

if FORMULATION == 0: 
    # setting general constraints --> lg <= D*u + C*u <= ug
    nlp_con.D   = D
    nlp_con.C   = C
    nlp_con.lg  = lg
    nlp_con.ug  = ug
    nlp_con.C_e  = Ce
    nlp_con.lg_e = lge
    nlp_con.ug_e = uge

    nlp_con.x0 = x0Start

if FORMULATION == 1 or FORMULATION == 3: 
    # setting general constraints --> lg <= D*u + C*u <= ug
    nlp_con.D   = D
    nlp_con.C   = C
    nlp_con.lg  = lg
    nlp_con.ug  = ug
    nlp_con.C_e  = Ce
    nlp_con.lg_e = lge
    nlp_con.ug_e = uge

    # lower gradient/hessian wrt lower slack
    nlp_cost.zl = SLACK_TUNING*nmp.array([1])
    nlp_cost.Zl = SLACK_TUNINGHessian*nmp.ones((1,1))                # hessian
    nlp_cost.zu = SLACK_TUNING*nmp.array([1])
    nlp_cost.Zu = SLACK_TUNINGHessian*nmp.ones((1,1))                # hessian
    #_e
    nlp_cost.zl_e = SLACK_E_TUNING*nmp.array([1])           
    nlp_cost.Zl_e = SLACK_TUNINGHessian*nmp.ones((1,1))              # hessian   
    nlp_cost.zu_e = SLACK_E_TUNING*nmp.array([1])     
    nlp_cost.Zu_e = SLACK_TUNINGHessian*nmp.ones((1,1))              # hessian   

    nlp_con.lh = nmp.array([0])                  # 1st torque constraint 
    nlp_con.uh = nmp.array([0])
    nlp_con.lsh = nmp.array([0])                        # soft lower bounds --> greater than 0
    nlp_con.ush = nmp.array([0])                        # soft upper bounds --> greater than 0
    #_e
    nlp_con.lh_e = nmp.array([0])                # 1st torque constraint 
    nlp_con.uh_e = nmp.array([0])
    nlp_con.lsh_e = nmp.array([0])      
    nlp_con.ush_e = nmp.array([0])      

    nlp_con.idxsh = nmp.array([0])
    nlp_con.idxsh_e = nmp.array([0])  

    nlp_con.x0 = x0Start

if FORMULATION == 2: 
    # setting general constraints --> lg <= D*u + C*u <= ug
    nlp_con.D   = D
    nlp_con.C   = C
    nlp_con.lg  = lg
    nlp_con.ug  = ug
    nlp_con.C_e  = Ce
    nlp_con.lg_e = lge
    nlp_con.ug_e = uge

    # lower gradient/hessian wrt lower slack
    nlp_cost.zl = SLACK_TUNING*nmp.array([1])
    nlp_cost.Zl = SLACK_TUNINGHessian*nmp.ones((1,1))                # hessian
    nlp_cost.zu = SLACK_TUNING*nmp.array([1])
    nlp_cost.Zu = SLACK_TUNINGHessian*nmp.ones((1,1))                # hessian
    #_e
    nlp_cost.zl_e = SLACK_E_TUNING*nmp.array([1])           
    nlp_cost.Zl_e = SLACK_TUNINGHessian*nmp.ones((1,1))              # hessian   
    nlp_cost.zu_e = SLACK_E_TUNING*nmp.array([1])     
    nlp_cost.Zu_e = SLACK_TUNINGHessian*nmp.ones((1,1))              # hessian   

    nlp_con.lh = nmp.array([0, -1e9])                   # 1st torque constraint | 2nd voltage constraint 
    nlp_con.uh = nmp.array([0, u_max**2/3])
    nlp_con.lsh = nmp.array([0])                        # soft lower bounds --> greater than 0
    nlp_con.ush = nmp.array([0])                        # soft upper bounds --> greater than 0
    #_e
    nlp_con.lh_e = nmp.array([0])                       # 1st torque constraint | 2nd terminal set 
    nlp_con.uh_e = nmp.array([0])
    nlp_con.lsh_e = nmp.array([0])      
    nlp_con.ush_e = nmp.array([0])      

    nlp_con.idxsh = nmp.array([0])
    nlp_con.idxsh_e = nmp.array([0])  

    nlp_con.x0 = x0Start

if FORMULATION == 4: 
    # setting general constraints --> lg <= D*u + C*u <= ug
    nlp_con.D   = D
    nlp_con.C   = C
    nlp_con.lg  = lg
    nlp_con.ug  = ug
    nlp_con.C_e  = Ce
    nlp_con.lg_e = lge
    nlp_con.ug_e = uge

    # lower gradient/hessian wrt lower slack
    nlp_cost.zl = SLACK_TUNING*nmp.array([1])
    nlp_cost.Zl = SLACK_TUNINGHessian*nmp.ones((1,1))                # hessian
    nlp_cost.zu = SLACK_TUNING*nmp.array([1])
    nlp_cost.Zu = SLACK_TUNINGHessian*nmp.ones((1,1))                # hessian
    #_e
    nlp_cost.zl_e = SLACK_E_TUNING*nmp.array([1])           
    nlp_cost.Zl_e = SLACK_TUNINGHessian*nmp.ones((1,1))              # hessian   
    nlp_cost.zu_e = SLACK_E_TUNING*nmp.array([1])     
    nlp_cost.Zu_e = SLACK_TUNINGHessian*nmp.ones((1,1))              # hessian   

    nlp_con.lh = nmp.array([0, -1e9])                   # 1st torque constraint | 2nd voltage constraint 
    nlp_con.uh = nmp.array([0, u_max**2/3])
    nlp_con.lsh = nmp.array([0])                        # soft lower bounds --> greater than 0
    nlp_con.ush = nmp.array([0])                        # soft upper bounds --> greater than 0
    #_e
    nlp_con.lh_e = nmp.array([0, -1e9])                       # 1st torque constraint | 2nd terminal set 
    nlp_con.uh_e = nmp.array([0, u_max**2/3])
    nlp_con.lsh_e = nmp.array([0])      
    nlp_con.ush_e = nmp.array([0])      

    nlp_con.idxsh = nmp.array([0])
    nlp_con.idxsh_e = nmp.array([0])  

    nlp_con.x0 = x0Start

# setting parameters
# nlp_con.p = nmp.array([w_val, 0.0, 0.0, tau_des])
nlp_con.p = nmp.array([w_val, 0.0, 0.0])

# set QP solver
ra.solver_config.qp_solver = 'PARTIAL_CONDENSING_HPIPM'
# ra.solver_config.qp_solver = 'FULL_CONDENSING_HPIPM'
# ra.solver_config.qp_solver = 'FULL_CONDENSING_QPOASES'
ra.solver_config.hessian_approx = 'GAUSS_NEWTON'
ra.solver_config.integrator_type = 'ERK'
ra.solver_config.sim_method_num_stages = 2   # 1: RK1, 2: RK2, 4: RK4    
# ra.solver_config.integrator_type = 'IRK'

# set prediction horizon
ra.solver_config.tf = Tf
ra.solver_config.nlp_solver_type = 'SQP_RTI'
# ra.solver_config.nlp_solver_type = 'SQP'

# set header path
ra.acados_include_path = '/mnt/c/Austauch/projects/SCQPAndrea/acados/include'
ra.acados_lib_path = '/mnt/c/Austauch/projects/SCQPAndrea/acados/lib'

file_name = 'acados_ocp.json'

# import pdb; pdb.set_trace()

if CODE_GEN == 1:
    if FORMULATION == 0:
        acados_solver = generate_solver(ra, json_file = file_name)
    if FORMULATION == 1:
        ra.con_h = constraint_nltorqueline
        ra.con_h_e = constraint_nltorquelineEnd
        acados_solver = generate_solver(ra, json_file = file_name)
    if FORMULATION == 2:
        ra.con_h = constraint_nltorqueline
        ra.con_h_e = constraint_nltorquelineEnd
        acados_solver = generate_solver(ra, json_file = file_name)
    if FORMULATION == 3:
        ra.con_h = constraint_nltorqueline
        ra.con_h_e = constraint_nltorquelineEnd
        acados_solver = generate_solver(ra, json_file = file_name)
    if FORMULATION == 4:
        ra.con_h = constraint_nltorqueline
        ra.con_h_e = constraint_nltorquelineEnd
        acados_solver = generate_solver(ra, json_file = file_name)

if COMPILE == 1:
    # make 
    os.chdir('c_generated_code')
    os.system('make')
    os.system('make shared_lib')
    os.chdir('..')

# closed loop simulation
Nsim = 100

simX = nmp.ndarray((Nsim, nx))
simU = nmp.ndarray((Nsim, nu))
simXR = nmp.ndarray((Nsim+1, nx))
simXR1 = nmp.ndarray((Nsim, nx))
simXRN = nmp.ndarray((Nsim, nx))

print("============================================================================================")
print("Mode = ", FORMULATION)
print("speed_el = ", w_val)
print("============================================================================================")
print("Initial Condition")
print("id0 = ", x0Start[0])
print("iq0 = ", x0Start[1])

# get initial condition for real simulation
simXR[0,0] = x0Start[0]
simXR[0,1] = x0Start[1]

xvec = nmp.matrix([[x0Start[0]],[x0Start[1]]])

for i in range(Nsim):
    print("\n")
    print("SimulationStep = ", i)
    print("=================")
    status = acados_solver.solve()

    if status != 0:
        print('acados returned status {}. Exiting.'.format(status))
        # import pdb; pdb.set_trace()
    # get solution
    x0 = acados_solver.get(0, "x")
    x1 = acados_solver.get(1, "x")
    xN = acados_solver.get(N, "x")
    u0 = acados_solver.get(0, "u")
    
    for j in range(nx):
        simX[i,j] = x0[j]
        simXR1[i,j] = x1[j]
        simXRN[i,j] = xN[j]

    for j in range(nu):
        simU[i,j] = u0[j]

    #print("controller predicted id= ", x0[0])
    #print("controller predicted iq= ", x0[1])

    uvec = nmp.matrix([[u0[0]],[u0[1]]])

    # real Simulation (RK2 method)
    A = nmp.matrix([[-R_m/L_d, w_val*L_q/L_d],[-w_val*L_d/L_q, -R_m/L_q]],dtype=float)
    B = nmp.matrix([[1.0/L_d,0.0],[0.0,1.0/L_q]],dtype=float)
    f = nmp.matrix([[0.0],[-K_m*w_val/L_q]],dtype=float)

    xvec = xvec + Ts*A*xvec + Ts*B*uvec + Ts*f + 0.5*Ts*Ts*A*A*xvec + 0.5*Ts*Ts*A*B*uvec + 0.5*Ts*Ts*A*f

    print("States= ", xvec)
    print("Controls= ", uvec)
    print("\n")

    # update initial condition xk+1
    acados_solver.set(0, "lbx",  xvec)
    acados_solver.set(0, "ubx",  xvec)

    # update initial condition
    # x0 = acados_solver.get(1, "x")
    # acados_solver.set(0, "lbx",  x0)
    # acados_solver.set(0, "ubx",  x0)

    simXR[i+1,0] = xvec[0]
    simXR[i+1,1] = xvec[1]

# plot results
t = nmp.linspace(0.0, Ts*Nsim, Nsim)
plt.subplot(4, 1, 1)
plt.step(t, simU[:,0], 'r')
plt.plot([0, Ts*Nsim], [nlp_cost.yref[2], nlp_cost.yref[2]], '--')
plt.title('closed-loop simulation')
plt.ylabel('u_d')
plt.xlabel('t')
plt.grid(True)
plt.subplot(4, 1, 2)
plt.step(t, simU[:,1], 'r')
plt.plot([0, Ts*Nsim], [nlp_cost.yref[3], nlp_cost.yref[3]], '--')
plt.ylabel('u_q')
plt.xlabel('t')
plt.grid(True)
plt.subplot(4, 1, 3)
plt.plot(t, simX[:,0])
plt.ylabel('x_d')
plt.xlabel('t')
plt.grid(True)
plt.subplot(4, 1, 4)
plt.plot(t, simX[:,1])
plt.ylabel('x_q')
plt.xlabel('t')
plt.grid(True)

# plot hexagon
r = 2/3*u_max

x1 = r
y1 = 0
x2 = r*cos(pi/3)
y2 = r*sin(pi/3)

q1 = -(y2 - y1/x1*x2)/(1-x2/x1)
m1 = -(y1 + q1)/x1

# box constraints
m2 = 0
q2 = r*sin(pi/3)
# -q2 <= uq  <= q2

plt.figure()
plt.plot(simU[:,0], simU[:,1], 'o')
plt.xlabel('ud')
plt.ylabel('uq')
ud = nmp.linspace(-1.5*u_max, 1.5*u_max, 100)
plt.plot(ud, -m1*ud -q1)
plt.plot(ud, -m1*ud +q1)
plt.plot(ud, +m1*ud -q1)
plt.plot(ud, +m1*ud +q1)
plt.plot(ud, -q2*nmp.ones((100, 1)))
plt.plot(ud, q2*nmp.ones((100, 1)))
plt.grid(True)
ax = plt.gca()
ax.set_xlim([-u_max, u_max])
ax.set_ylim([-u_max, u_max])
circle = plt.Circle((0, 0), u_max/nmp.sqrt(3), color='red', fill=False)
ax.add_artist(circle)

delta = 100
x = nmp.linspace(-i_max, i_max/3, delta)
y = nmp.linspace(-i_max, i_max, delta)
XV, YV = nmp.meshgrid(x,y)

alpha = R_m**2 + w_val**2*L_d**2
beta  = R_m**2 + w_val**2*L_q**2
gamma = 2*R_m*w_val*(L_d-L_q)
delta = 2*w_val**2*L_d*K_m
epsilon = 2*R_m*w_val*K_m
rho = w_val**2*K_m**2 - (48)**2/3

FeaSetV = alpha*XV**2 + beta*YV**2 + gamma*XV*YV + delta*XV + epsilon*YV + rho
# TauV = 1.5*N_P*((L_d-L_q)*XV*YV + K_m*YV)
TauV = 1.5*N_P*(K_m*YV)

S1 = -0.24543672*XV + 0.50146524*YV
S2 = -0.214*XV      - 0.01815*YV
S3 = -0.18256328*XV -0.53776524*YV

# trajectory in the dq-plane
plt.figure()
plt.plot(simXR[:,0], simXR[:,1],'bo')
plt.plot(simXR[:,0], simXR[:,1],'b')
plt.plot(simX[:,0], simX[:,1],'r')
plt.plot(simX[:,0], simX[:,1],'r*')
plt.contour(XV, YV, FeaSetV,[0],colors='r')
plt.contour(XV, YV, S1,[-27.82562584,83.02562584],colors='k')
plt.contour(XV, YV, S2,[-0.11281292,55.31281292], colors='k')
plt.contour(XV, YV, S3,[-27.82562584,83.02562584],colors='k')
plt.contour(XV, YV, TauV,[TAU],colors='g')
plt.xlabel('x_d')
plt.ylabel('x_q')
plt.grid(True)

# plt.figure()
# plt.plot(simXR1[:,0], simXR1[:,1],'bo')
# plt.plot(simXR1[:,0], simXR1[:,1],'b')
# plt.contour(XV, YV, FeaSetV,[0],colors='r')
# plt.contour(XV, YV, S1,[-27.82562584,83.02562584],colors='k')
# plt.contour(XV, YV, S2,[-0.11281292,55.31281292], colors='k')
# plt.contour(XV, YV, S3,[-27.82562584,83.02562584],colors='k')
# plt.contour(XV, YV, TauV,[TAU],colors='g')
# plt.xlabel('x_d')
# plt.ylabel('x_q')
# plt.grid(True)

# plt.figure()
# plt.plot(simXRN[:,0], simXRN[:,1],'bo')
# plt.plot(simXRN[:,0], simXRN[:,1],'b')
# plt.contour(XV, YV, FeaSetV,[0],colors='r')
# plt.contour(XV, YV, S1,[-27.82562584,83.02562584],colors='k')
# plt.contour(XV, YV, S2,[-0.11281292,55.31281292], colors='k')
# plt.contour(XV, YV, S3,[-27.82562584,83.02562584],colors='k')
# plt.contour(XV, YV, TauV,[TAU],colors='g')
# plt.xlabel('x_d')
# plt.ylabel('x_q')
# plt.grid(True)

plt.show()