%
% Copyright 2019 Gianluca Frison, Dimitris Kouzoupis, Robin Verschueren,
% Andrea Zanelli, Niels van Duijkeren, Jonathan Frey, Tommaso Sartor,
% Branimir Novoselnik, Rien Quirynen, Rezart Qelibari, Dang Doan,
% Jonas Koenemann, Yutao Chen, Tobias Schöls, Jonas Schlagenhauf, Moritz Diehl
%
% This file is part of acados.
%
% The 2-Clause BSD License
%
% Redistribution and use in source and binary forms, with or without
% modification, are permitted provided that the following conditions are met:
%
% 1. Redistributions of source code must retain the above copyright notice,
% this list of conditions and the following disclaimer.
%
% 2. Redistributions in binary form must reproduce the above copyright notice,
% this list of conditions and the following disclaimer in the documentation
% and/or other materials provided with the distribution.
%
% THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
% AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
% IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
% ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
% LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
% CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
% SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
% INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
% CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
% ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
% POSSIBILITY OF SUCH DAMAGE.;
%

function check = check_reformulation(model, gnsf, print_info)

%% Description:
% this function takes the implicit ODE/ index-1 DAE and a gnsf structure
% to evaluate both models at num_eval random points x0, x0dot, z0, u0;
% if for all points the relative error is <= TOL, the function will return
% 1, otherwise it will give an error.

import casadi.*

TOL = 1e-14;
num_eval = 10;

% get dimensions
nx  = gnsf.nx;
nu  = gnsf.nu;
nz  = gnsf.nz;
nx1 = gnsf.nx1;
nx2 = gnsf.nx2;
nz1 = gnsf.nz1;
nz2 = gnsf.nz2;
n_out = gnsf.n_out;

% get model matrices
A  = gnsf.A;
B  = gnsf.B;
C  = gnsf.C;
E  = gnsf.E;
c  = gnsf.c;

L_x    = gnsf.L_x;
L_xdot = gnsf.L_xdot;
L_z    = gnsf.L_z;
L_u    = gnsf.L_u;

A_LO = gnsf.A_LO;
E_LO = gnsf.E_LO;
B_LO = gnsf.B_LO;
c_LO = gnsf.c_LO;

I_x1 = 1:nx1;
I_x2 = nx1+1:nx;

I_z1 = 1:nz1;
I_z2 = nz1+1:nz;

idx_perm_f = gnsf.idx_perm_f;


% get casadi variables
x = gnsf.x;
xdot = gnsf.xdot;
z = gnsf.z;
u = gnsf.u;
y = gnsf.y;
uhat = gnsf.uhat;
if isfield(model, 'sym_p')
    p = model.sym_p;
    np = length(p);
else
    if class(x(1)) == 'casadi.SX'
        p = SX.sym('p',0, 0);
    else
        p = MX.sym('p',0, 0);
    end
    np = 0;
end

% create functions
impl_ode_fun = Function('impl_ode_fun', {x, xdot, u, z, p}, {model.dyn_expr_f});
phi_fun = Function('phi_fun',{y, uhat, p}, {gnsf.phi_expr});
f_lo_fun = Function('f_lo_fun',{x(1:nx1), xdot(1:nx1), z, u, p}, {gnsf.f_lo_expr});

for i_check = 1:num_eval
    
    % generate random values
    x0    = rand(nx, 1);
    x0dot = rand(nx, 1);
    z0    = rand(nz, 1);
    u0    = rand(nu, 1);
    
    if gnsf.ny>0
        y0 = L_x * x0(I_x1) + L_xdot * x0dot(I_x1) + L_z * z0(I_z1);
    else
        y0 = [];
    end
    if gnsf.nuhat>0
        uhat0 = L_u * u0;
    else
        uhat0 = [];
    end


    % eval functions
    % if isparametric
        p0 = rand(np, 1);
        f_impl_val = full(impl_ode_fun(x0, x0dot, u0, z0, p0));
        phi_val = phi_fun( y0, uhat0, p0);
        f_lo_val = f_lo_fun(x0(I_x1), x0dot(I_x1), z0(I_z1), u0, p0);
    % else
    %     f_impl_val = full(impl_ode_fun(x0, x0dot, u0, z0));
    %     phi_val = phi_fun( y0, uhat0);
    %     f_lo_val = f_lo_fun(x0(I_x1), x0dot(I_x1), z0(I_z1), u0);
    % end
    f_impl_val = f_impl_val(idx_perm_f);
    

    
    % eval gnsf
    if n_out > 0
        C_phi = C * phi_val;
    else
        C_phi = zeros(nx1 + nz1, 1);
    end
    gnsf_val1 = A * x0(I_x1) + B * u0 + ...
        C_phi + c - E * [x0dot(I_x1); z0(I_z1)];


    if nx2 > 0 % eval LOS
        gnsf_val2 =  A_LO * x0(I_x2) + B_LO * u0 + c_LO + ...
            f_lo_val - E_LO * [x0dot(I_x2); z0(I_z2)];
        gnsf_val = full([gnsf_val1; gnsf_val2 ]);
    else
        gnsf_val = full(gnsf_val1);
    end
    
    % compute error and check
    rel_error = norm(f_impl_val - gnsf_val) / norm(f_impl_val);

    if rel_error > TOL
        disp('transcription failed; rel_error > TOL');
        disp('you are in debug mode now: keyboard');
        keyboard
        abs_error = gnsf_val - f_impl_val;
        T = table(f_impl_val, gnsf_val, abs_error);
        disp(T)
%         error('transcription failed; rel_error > TOL');
%         check = 0;


        lo_expr =  A_LO * x(I_x2) + B_LO * u + c_LO + ...
            gnsf.f_lo_expr - E_LO * [xdot(I_x2)];
        nsf_expr = (A * x(I_x1) + B * u + ...
            C * gnsf.phi_expr + c) - E * [xdot(I_x1); z(I_z1)];
    end            
end

if print_info
    disp(' ');
    disp(['model reformulation checked: relative error <= TOL = ', num2str(TOL)]);
    disp(' ');
end
check = 1;
    
%% helpful for debugging
% % use in calling function and compare
% % compare f_impl(i) with gnsf_val1(i);
% 

%     nx  = gnsf.nx;
%     nu  = gnsf.nu;
%     nz  = gnsf.nz;
%     nx1 = gnsf.nx1;
%     nx2 = gnsf.nx2;
%     
%         A  = gnsf.A;
%     B  = gnsf.B;
%     C  = gnsf.C;
%     E  = gnsf.E;
%     c  = gnsf.c;
% 
%     L_x    = gnsf.L_x;
%     L_z    = gnsf.L_z;
%     L_xdot = gnsf.L_xdot;
%     L_u    = gnsf.L_u;
%     
%     A_LO = gnsf.A_LO;
% 
%     x0 = rand(nx, 1);
%     x0dot = rand(nx, 1);
%     z0 = rand(nz, 1);
%     u0 = rand(nu, 1);
%     I_x1 = 1:nx1;
%     I_x2 = nx1+1:nx;
%         
%     y0 = L_x * x0(I_x1) + L_xdot * x0dot(I_x1) + L_z * z0;
%     uhat0 = L_u * u0;
% 
%     gnsf_val1 = (A * x(I_x1) + B * u + ...
%         C * phi_current + c) - E * [xdot(I_x1); z];
%     gnsf_val1 = gnsf_val1.simplify();
%     
% %     gnsf_val2 = A_LO * x(I_x2) + gnsf.f_lo_fun(x(I_x1), xdot(I_x1), z, u) - xdot(I_x2);
%     gnsf_val2 =  A_LO * x(I_x2) + gnsf.f_lo_fun(x(I_x1), xdot(I_x1), z, u) - xdot(I_x2);
% 
%         
%     gnsf_val = [gnsf_val1; gnsf_val2];
%     gnsf_val = gnsf_val.simplify();
%     dyn_expr_f = dyn_expr_f.simplify();
% keyboard


end
