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

%% test of native matlab interface
clear VARIABLES

addpath('../linear_mass_spring_model/');

%% arguments
compile_interface = 'false';
codgen_model = 'true';
method = 'irk';
% method = 'IRK';
sens_forw = 'true';
num_stages = 4;
num_steps = 4;
gnsf_detect_struct = 'true';

Ts = 0.1;
FD_epsilon = 1e-6;

%% model
model = linear_mass_spring_model;

model_name = ['lin_mass_' method];
nx = model.nx;
nu = model.nu;

% x0 = [1e-1; 1e0; 2e-1; 2e0]; % pendulum
% u = 0;

% linear_mass_spring_
x0 = ones(nx,1);
u = ones(nu,1);

%% acados sim model
sim_model = acados_sim_model();
sim_model.set('T', Ts);
sim_model.set('name', model_name);

sim_model.set('sym_x', model.sym_x);
if isfield(model, 'sym_u')
    sim_model.set('sym_u', model.sym_u);
end
if isfield(model, 'sym_p')
    sim_model.set('sym_p', model.sym_p);
end
sim_model.set('dim_nx', model.nx);
sim_model.set('dim_nu', model.nu);


if (strcmp(method, 'erk'))
    sim_model.set('dyn_type', 'explicit');
    sim_model.set('dyn_expr_f', model.expr_f_expl);
else % irk irk_gnsf
    sim_model.set('dyn_type', 'implicit');
    sim_model.set('dyn_expr_f', model.expr_f_impl);
    sim_model.set('sym_xdot', model.sym_xdot);
end


%% acados sim opts
sim_opts = acados_sim_opts();
sim_opts.set('compile_interface', compile_interface);
sim_opts.set('codgen_model', codgen_model);
sim_opts.set('num_stages', num_stages);
sim_opts.set('num_steps', num_steps);
sim_opts.set('method', method);
sim_opts.set('sens_forw', sens_forw);
if (strcmp(method, 'irk_gnsf'))
    sim_opts.set('gnsf_detect_struct', gnsf_detect_struct);
end

%% acados sim
% create sim
sim = acados_sim(sim_model, sim_opts);

% Note: this does not work with gnsf, because it needs to be available
% in the precomputation phase
% 	sim.set('T', Ts);

% set initial state
sim.set('x', zeros(nx+1, 1));
sim.set('u', u);

% solve
sim.solve();

xn = sim.get('xn');
S_forw_ind = sim.get('S_forw');
