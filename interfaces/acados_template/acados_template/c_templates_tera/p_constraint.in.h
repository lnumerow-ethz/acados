/*
 * Copyright 2019 Gianluca Frison, Dimitris Kouzoupis, Robin Verschueren,
 * Andrea Zanelli, Niels van Duijkeren, Jonathan Frey, Tommaso Sartor,
 * Branimir Novoselnik, Rien Quirynen, Rezart Qelibari, Dang Doan,
 * Jonas Koenemann, Yutao Chen, Tobias Schöls, Jonas Schlagenhauf, Moritz Diehl
 *
 * This file is part of acados.
 *
 * The 2-Clause BSD License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.;
 */

#ifndef {{ con_p.name }}_P_CONSTRAINT
#define {{ con_p.name }}_P_CONSTRAINT

#ifdef __cplusplus
extern "C" {
#endif

{% if dims.npd > 0 %}
// implicit ODE
int {{ con_p.name }}_p_constraint(const real_t** arg, real_t** res, int* iw, real_t* w, void *mem);
int {{ con_p.name }}_p_constraint_work(int *, int *, int *, int *);
const int *{{ con_p.name }}_p_constraint_sparsity_in(int);
const int *{{ con_p.name }}_p_constraint_sparsity_out(int);
int {{ con_p.name }}_p_constraint_n_in();
int {{ con_p.name }}_p_constraint_n_out();
{% endif %}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  // {{ con_p.name }}_P_CONSTRAINT
