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


function generate_c_code_disc_dyn( model, opts )

%% import casadi
import casadi.*

casadi_version = CasadiMeta.version();
if strcmp(casadi_version(1:3),'3.4') % require casadi 3.4.x
    casadi_opts = struct('mex', false, 'casadi_int', 'int', 'casadi_real', 'double');
else % old casadi versions
    error('Please download and install CasADi version 3.4.x to ensure compatibility with acados')
end

%% load model
% x
x = model.sym_x;
nx = length(x);
% check type
if class(x(1)) == 'casadi.SX'
    isSX = true;
else
    isSX = false;
end
% u
u = model.sym_u;
nu = length(u);
% p
if isfield(model, 'sym_p')
    p = model.sym_p;
    np = length(p);
else
    if isSX
        p = SX.sym('p',0, 0);
    else
        p = MX.sym('p',0, 0);
    end
    np = 0;
end

model_name = model.name;

if isfield(model, 'dyn_expr_phi')
    phi = model.dyn_expr_phi;
    % assume nx1 = nx !!!
    % multipliers for hessian
    if isSX
        lam = SX.sym('lam', nx, 1);
    else
        lam = MX.sym('lam', nx, 1);
    end
    % generate jacobians
    jac_ux = jacobian(phi, [u; x]);
    % generate adjoint
    adj_ux = jtimes(phi, [u; x], lam, true);
    % generate hessian
    hess_ux = jacobian(adj_ux, [u; x]);
    % Set up functions
    phi_fun_jac_ut_xt = Function([model_name,'_dyn_disc_phi_fun_jac'], {x, u, p}, {phi, jac_ux'});
    phi_fun_jac_ut_xt_hess = Function([model_name,'_dyn_disc_phi_fun_jac_hess'], {x, u, lam, p}, {phi, jac_ux', hess_ux});
    % generate C code
    phi_fun_jac_ut_xt.generate([model_name,'_dyn_disc_phi_fun_jac'], casadi_opts);
    phi_fun_jac_ut_xt_hess.generate([model_name,'_dyn_disc_phi_fun_jac_hess'], casadi_opts);
end
