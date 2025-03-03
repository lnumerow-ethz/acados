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


#include "acados/ocp_nlp/ocp_nlp_constraints_bgh.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

// blasfeo
#include "blasfeo/include/blasfeo_d_aux.h"
#include "blasfeo/include/blasfeo_d_blas.h"
// acados
#include "acados/ocp_qp/ocp_qp_common.h"
#include "acados/utils/mem.h"



/************************************************
 * dims
 ************************************************/

int ocp_nlp_constraints_bgh_dims_calculate_size(void *config_)
{
    int size = sizeof(ocp_nlp_constraints_bgh_dims);

    return size;
}



void *ocp_nlp_constraints_bgh_dims_assign(void *config_, void *raw_memory)
{
    char *c_ptr = (char *) raw_memory;

    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) c_ptr;
    c_ptr += sizeof(ocp_nlp_constraints_bgh_dims);

    assert((char *) raw_memory + ocp_nlp_constraints_bgh_dims_calculate_size(config_) >= c_ptr);

    // initialize to zero
    dims->nx = 0;
    dims->nu = 0;
    dims->nz = 0;
    dims->nb = 0;
    dims->nbx = 0;
    dims->nbu = 0;
    dims->ng = 0;
    dims->nh = 0;
    dims->ns = 0;
    dims->nsbu = 0;
    dims->nsbx = 0;
    dims->nsg = 0;
    dims->nsh = 0;

    return dims;
}



void ocp_nlp_constraints_bgh_dims_initialize(void *config_, void *dims_, int nx, int nu, int nz, int nbx,
                                             int nbu, int ng, int nh, int dummy0, int ns)
{
    ocp_nlp_constraints_bgh_dims *dims = dims_;

    dims->nx = nx;
    dims->nu = nu;
    dims->nz = nz;
    dims->nbx = nbx;
    dims->nbu = nbu;
    dims->nb = nbx + nbu;
    dims->ng = ng;
    dims->nh = nh;
    dims->ns = ns;

    return;
}


/* dimension setters */
static void ocp_nlp_constraints_bgh_set_nx(void *config_, void *dims_, const int *nx)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    dims->nx = *nx;
}



static void ocp_nlp_constraints_bgh_set_nu(void *config_, void *dims_, const int *nu)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    dims->nu = *nu;
}



static void ocp_nlp_constraints_bgh_set_nz(void *config_, void *dims_, const int *nz)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    dims->nz = *nz;
}



static void ocp_nlp_constraints_bgh_set_nbx(void *config_, void *dims_, const int *nbx)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    dims->nbx = *nbx;
    dims->nb = dims->nbu + dims->nbx;
}



static void ocp_nlp_constraints_bgh_set_nbu(void *config_, void *dims_, const int *nbu)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    dims->nbu = *nbu;
    dims->nb = dims->nbu + dims->nbx;
}



static void ocp_nlp_constraints_bgh_set_ng(void *config_, void *dims_, const int *ng)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    dims->ng = *ng;
}



static void ocp_nlp_constraints_bgh_set_nh(void *config_, void *dims_, const int *nh)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    dims->nh = *nh;
}



static void ocp_nlp_constraints_bgh_set_nsbu(void *config_, void *dims_, const int *nsbu)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    dims->nsbu = *nsbu;
    dims->ns = dims->nsbu + dims->nsbx + dims->nsg + dims->nsh;
}



static void ocp_nlp_constraints_bgh_set_nsbx(void *config_, void *dims_, const int *nsbx)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    dims->nsbx = *nsbx;
    dims->ns = dims->nsbu + dims->nsbx + dims->nsg + dims->nsh;
}



static void ocp_nlp_constraints_bgh_set_nsg(void *config_, void *dims_, const int *nsg)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    dims->nsg = *nsg;
    dims->ns = dims->nsbu + dims->nsbx + dims->nsg + dims->nsh;
}



static void ocp_nlp_constraints_bgh_set_nsh(void *config_, void *dims_, const int *nsh)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    dims->nsh = *nsh;
    dims->ns = dims->nsbu + dims->nsbx + dims->nsg + dims->nsh;
}



void ocp_nlp_constraints_bgh_dims_set(void *config_, void *dims_, const char *field,
                                             const int* value)
{
    if (!strcmp(field, "nx"))
    {
        ocp_nlp_constraints_bgh_set_nx(config_, dims_, value);
    }
    else if (!strcmp(field, "nu"))
    {
        ocp_nlp_constraints_bgh_set_nu(config_, dims_, value);
    }
    else if (!strcmp(field, "nz"))
    {
        ocp_nlp_constraints_bgh_set_nz(config_, dims_, value);
    }
    else if (!strcmp(field, "nbx"))
    {
        ocp_nlp_constraints_bgh_set_nbx(config_, dims_, value);
    }
    else if (!strcmp(field, "nbu"))
    {
        ocp_nlp_constraints_bgh_set_nbu(config_, dims_, value);
    }
    else if (!strcmp(field, "ng"))
    {
        ocp_nlp_constraints_bgh_set_ng(config_, dims_, value);
    }
    else if (!strcmp(field, "nh"))
    {
        ocp_nlp_constraints_bgh_set_nh(config_, dims_, value);
    }
    else if (!strcmp(field, "nsbu"))
    {
        ocp_nlp_constraints_bgh_set_nsbu(config_, dims_, value);
    }
    else if (!strcmp(field, "nsbx"))
    {
        ocp_nlp_constraints_bgh_set_nsbx(config_, dims_, value);
    }
    else if (!strcmp(field, "nsg"))
    {
        ocp_nlp_constraints_bgh_set_nsg(config_, dims_, value);
    }
    else if (!strcmp(field, "nsh"))
    {
        ocp_nlp_constraints_bgh_set_nsh(config_, dims_, value);
    }
    else
    {
        printf("\nerror: ocp_nlp_constraints_bgh_dims_get: field %s not available in module\n", field);
        exit(1);
    }
}



/* dimension getters */
static void ocp_nlp_constraints_bgh_get_ni(void *config_, void *dims_, int* value)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    *value = dims->nbx + dims->nbu + dims->ng + dims->nh + dims->ns;
}



static void ocp_nlp_constraints_bgh_get_nb(void *config_, void *dims_, int* value)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    *value = dims->nb;
}



static void ocp_nlp_constraints_bgh_get_nbx(void *config_, void *dims_, int* value)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    *value = dims->nbx;
}



static void ocp_nlp_constraints_bgh_get_nbu(void *config_, void *dims_, int* value)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    *value = dims->nbu;
}



static void ocp_nlp_constraints_bgh_get_ng(void *config_, void *dims_, int* value)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    *value = dims->ng;
}



static void ocp_nlp_constraints_bgh_get_nh(void *config_, void *dims_, int* value)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    *value = dims->nh;
}



static void ocp_nlp_constraints_bgh_get_ns(void *config_, void *dims_, int* value)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    *value = dims->ns;
}



static void ocp_nlp_constraints_bgh_get_nsbx(void *config_, void *dims_, int* value)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    *value = dims->nsbx;
}



static void ocp_nlp_constraints_bgh_get_nsbu(void *config_, void *dims_, int* value)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    *value = dims->nsbu;
}



static void ocp_nlp_constraints_bgh_get_nsg(void *config_, void *dims_, int* value)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    *value = dims->nsg;
}



static void ocp_nlp_constraints_bgh_get_nsh(void *config_, void *dims_, int* value)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    *value = dims->nsh;
}



void ocp_nlp_constraints_bgh_dims_get(void *config_, void *dims_, const char *field, int* value)
{
    if (!strcmp(field, "ni"))
    {
        ocp_nlp_constraints_bgh_get_ni(config_, dims_, value);
    }
    else if (!strcmp(field, "nb"))
    {
        ocp_nlp_constraints_bgh_get_nb(config_, dims_, value);
    }
    else if (!strcmp(field, "nbx"))
    {
        ocp_nlp_constraints_bgh_get_nbx(config_, dims_, value);
    }
    else if (!strcmp(field, "nbu"))
    {
        ocp_nlp_constraints_bgh_get_nbu(config_, dims_, value);
    }
    else if (!strcmp(field, "ng"))
    {
        ocp_nlp_constraints_bgh_get_ng(config_, dims_, value);
    }
    else if (!strcmp(field, "nh"))
    {
        ocp_nlp_constraints_bgh_get_nh(config_, dims_, value);
    }
    else if (!strcmp(field, "ns"))
    {
        ocp_nlp_constraints_bgh_get_ns(config_, dims_, value);
    }
    else if (!strcmp(field, "nsbu"))
    {
        ocp_nlp_constraints_bgh_get_nsbu(config_, dims_, value);
    }
    else if (!strcmp(field, "nsbx"))
    {
        ocp_nlp_constraints_bgh_get_nsbx(config_, dims_, value);
    }
    else if (!strcmp(field, "nsg"))
    {
        ocp_nlp_constraints_bgh_get_nsg(config_, dims_, value);
    }
    else if (!strcmp(field, "nsh"))
    {
        ocp_nlp_constraints_bgh_get_nsh(config_, dims_, value);
    }
    else
    {
        printf("\nerror: ocp_nlp_constraints_bgh_dims_get: field %s not available in module\n", field);
        exit(1);
    }
}



/************************************************
 * model
 ************************************************/

int ocp_nlp_constraints_bgh_model_calculate_size(void *config, void *dims_)
{
    ocp_nlp_constraints_bgh_dims *dims = dims_;

    // extract dims
    int nx = dims->nx;
    int nu = dims->nu;
    int nb = dims->nb;
    int ng = dims->ng;
    int nh = dims->nh;
    int ns = dims->ns;

    int size = 0;

    size += sizeof(ocp_nlp_constraints_bgh_model);

    size += sizeof(int) * nb;                                         // idxb
    size += sizeof(int) * ns;                                         // idxs
    size += blasfeo_memsize_dvec(2 * nb + 2 * ng + 2 * nh + 2 * ns);  // d
    size += blasfeo_memsize_dmat(nu + nx, ng);                        // DCt

    size += 64;  // blasfeo_mem align

    return size;
}



void *ocp_nlp_constraints_bgh_model_assign(void *config, void *dims_, void *raw_memory)
{
    ocp_nlp_constraints_bgh_dims *dims = dims_;

    char *c_ptr = (char *) raw_memory;

    // extract sizes
    int nx = dims->nx;
    int nu = dims->nu;
    int nb = dims->nb;
    int ng = dims->ng;
    int nh = dims->nh;
    int ns = dims->ns;

    // struct
    ocp_nlp_constraints_bgh_model *model = (ocp_nlp_constraints_bgh_model *) c_ptr;
    c_ptr += sizeof(ocp_nlp_constraints_bgh_model);

    // dims
    //  model->dims = dims;

    // blasfeo_mem align
    align_char_to(64, &c_ptr);

    // blasfeo_dmat
    // DCt
    assign_and_advance_blasfeo_dmat_mem(nu + nx, ng, &model->DCt, &c_ptr);

    // blasfeo_dvec
    // d
    assign_and_advance_blasfeo_dvec_mem(2 * nb + 2 * ng + 2 * nh + 2 * ns, &model->d, &c_ptr);
    // default initialization to zero
    blasfeo_dvecse(2*nb+2*ng+2*nh+2*ns, 0.0, &model->d, 0);

    // int
    // idxb
    assign_and_advance_int(nb, &model->idxb, &c_ptr);
    // idxs
    assign_and_advance_int(ns, &model->idxs, &c_ptr);

    // assert
    assert((char *) raw_memory + ocp_nlp_constraints_bgh_model_calculate_size(config, dims) >=
           c_ptr);

    return model;
}



int ocp_nlp_constraints_bgh_model_set(void *config_, void *dims_,
                         void *model_, const char *field, void *value)
{
    ocp_nlp_constraints_bgh_dims *dims = (ocp_nlp_constraints_bgh_dims *) dims_;
    ocp_nlp_constraints_bgh_model *model = (ocp_nlp_constraints_bgh_model *) model_;

    int ii;
    int *ptr_i;

    if (!dims || !model || !field || !value)
    {
        printf("ocp_nlp_constraints_bgh_model_set: got Null pointer \n");
        exit(1);
    }

    int nu = dims->nu;
    int nx = dims->nx;
    int nb = dims->nb;
    int ng = dims->ng;
    int nh = dims->nh;
    int ns = dims->ns;
    int nsbu = dims->nsbu;
    int nsbx = dims->nsbx;
    int nsg = dims->nsg;
    int nsh = dims->nsh;
    int nbx = dims->nbx;
    int nbu = dims->nbu;

    // TODO(oj): document which strings mean what! - adapted from prev implementation..
    if (!strcmp(field, "lb")) // TODO(fuck_lint) remove !!!
    {
        blasfeo_pack_dvec(nb, value, &model->d, 0);
    }
    else if (!strcmp(field, "ub")) // TODO(fuck_lint) remove !!!
    {
        blasfeo_pack_dvec(nb, value, &model->d, nb+ng+nh);
    }
    else if (!strcmp(field, "idxbx"))
    {
        ptr_i = (int *) value;
        for (ii=0; ii < nbx; ii++)
            model->idxb[nbu+ii] = nu+ptr_i[ii];
    }
    else if (!strcmp(field, "lbx"))
    {
        blasfeo_pack_dvec(nbx, value, &model->d, nbu);
    }
    else if (!strcmp(field, "ubx"))
    {
        blasfeo_pack_dvec(nbx, value, &model->d, nb + ng + nh + nbu);
    }
    else if (!strcmp(field, "idxbu"))
    {
        ptr_i = (int *) value;
        for (ii=0; ii < nbu; ii++)
            model->idxb[ii] = ptr_i[ii];
    }
    else if (!strcmp(field, "lbu"))
    {
        blasfeo_pack_dvec(nbu, value, &model->d, 0);
    }
    else if (!strcmp(field, "ubu"))
    {
        blasfeo_pack_dvec(nbu, value, &model->d, nb + ng + nh);
    }
    else if (!strcmp(field, "C"))
    {
        blasfeo_pack_tran_dmat(ng, nx, value, ng, &model->DCt, nu, 0);
    }
    else if (!strcmp(field, "D"))
    {
        blasfeo_pack_tran_dmat(ng, nu, value, ng, &model->DCt, 0, 0);
    }
    else if (!strcmp(field, "lg"))
    {
        blasfeo_pack_dvec(ng, value, &model->d, nb);
    }
    else if (!strcmp(field, "ug"))
    {
        blasfeo_pack_dvec(ng, value, &model->d, 2*nb+ng+nh);
    }
    else if (!strcmp(field, "nl_constr_h_fun_jac"))
    {
        model->nl_constr_h_fun_jac = value;
    }
    else if (!strcmp(field, "nl_constr_h_fun_jac_hess"))
    {
        model->nl_constr_h_fun_jac_hess = value;
    }
    else if (!strcmp(field, "lh"))
    {
        blasfeo_pack_dvec(nh, value, &model->d, nb+ng);
    }
    else if (!strcmp(field, "uh"))
    {
        blasfeo_pack_dvec(nh, value, &model->d, 2*nb+2*ng+nh);
    }
    else if (!strcmp(field, "idxsbu"))
    {
        ptr_i = (int *) value;
        for (ii=0; ii < nsbu; ii++)
            model->idxs[ii] = ptr_i[ii];
    }
    else if (!strcmp(field, "lsbu"))
    {
        blasfeo_pack_dvec(nsbu, value, &model->d, 2*nb+2*ng+2*nh);
    }
    else if (!strcmp(field, "usbu"))
    {
        blasfeo_pack_dvec(nsbu, value, &model->d, 2*nb+2*ng+2*nh+ns);
    }
    else if (!strcmp(field, "idxsbx"))
    {
        ptr_i = (int *) value;
        for (ii=0; ii < nsbx; ii++)
            model->idxs[nsbu+ii] = nbu+ptr_i[ii];
    }
    else if (!strcmp(field, "lsbx"))
    {
        blasfeo_pack_dvec(nsbx, value, &model->d, 2*nb+2*ng+2*nh+nsbu);
    }
    else if (!strcmp(field, "usbx"))
    {
        blasfeo_pack_dvec(nsbx, value, &model->d, 2*nb+2*ng+2*nh+ns+nsbu);
    }
    else if (!strcmp(field, "idxsg"))
    {
        ptr_i = (int *) value;
        for (ii=0; ii < nsg; ii++)
            model->idxs[nsbu+nsbx+ii] = nbu+nbx+ptr_i[ii];
    }
    else if (!strcmp(field, "lsg"))
    {
        blasfeo_pack_dvec(nsg, value, &model->d, 2*nb+2*ng+2*nh+nsbu+nsbx);
    }
    else if (!strcmp(field, "usg"))
    {
        blasfeo_pack_dvec(nsg, value, &model->d, 2*nb+2*ng+2*nh+ns+nsbu+nsbx);
    }
    else if (!strcmp(field, "idxsh"))
    {
        ptr_i = (int *) value;
        for (ii=0; ii < nsh; ii++)
            model->idxs[nsbu+nsbx+nsg+ii] = nbu+nbx+ng+ptr_i[ii];
    }
    else if (!strcmp(field, "lsh"))
    {
        blasfeo_pack_dvec(nsh, value, &model->d, 2*nb+2*ng+2*nh+nsbu+nsbx+nsg);
    }
    else if (!strcmp(field, "ush"))
    {
        blasfeo_pack_dvec(nsh, value, &model->d, 2*nb+2*ng+2*nh+ns+nsbu+nsbx+nsg);
    }
    else
    {
        printf("\nerror: model field not available in module ocp_nlp_constraints_bgh: %s\n", field);
        exit(1);
    }

    return ACADOS_SUCCESS;
}


/************************************************
 * options
 ************************************************/

int ocp_nlp_constraints_bgh_opts_calculate_size(void *config_, void *dims_)
{
    int size = 0;

    size += sizeof(ocp_nlp_constraints_bgh_opts);

    return size;
}



void *ocp_nlp_constraints_bgh_opts_assign(void *config_, void *dims_, void *raw_memory)
{
    char *c_ptr = (char *) raw_memory;

    ocp_nlp_constraints_bgh_opts *opts = (ocp_nlp_constraints_bgh_opts *) c_ptr;
    c_ptr += sizeof(ocp_nlp_constraints_bgh_opts);

    assert((char *) raw_memory + ocp_nlp_constraints_bgh_opts_calculate_size(config_, dims_) >=
           c_ptr);

    return opts;
}



void ocp_nlp_constraints_bgh_opts_initialize_default(void *config_, void *dims_, void *opts_)
{
    ocp_nlp_constraints_bgh_opts *opts = opts_;

    opts->compute_adj = 1;
    opts->compute_hess = 0;

    return;
}



void ocp_nlp_constraints_bgh_opts_update(void *config_, void *dims_, void *opts_)
{
    //  ocp_nlp_constraints_bgh_opts *opts = opts_;

    return;
}



void ocp_nlp_constraints_bgh_opts_set(void *config_, void *opts_, char *field, void *value)
{

    ocp_nlp_constraints_bgh_opts *opts = opts_;

    if(!strcmp(field, "compute_adj"))
    {
        int *compute_adj = value;
        opts->compute_adj = *compute_adj;
    }
    else if(!strcmp(field, "compute_hess"))
    {
        int *compute_hess = value;
        opts->compute_hess = *compute_hess;
    }
    else
    {
        printf("\nerror: field %s not available in ocp_nlp_constraints_bgh_opts_set\n", field);
        exit(1);
    }

    return;

}



/************************************************
 * memory
 ************************************************/

int ocp_nlp_constraints_bgh_memory_calculate_size(void *config_, void *dims_, void *opts_)
{
    ocp_nlp_constraints_bgh_dims *dims = dims_;

    // extract dims
    int nx = dims->nx;
    int nu = dims->nu;
    int nb = dims->nb;
    int ng = dims->ng;
    int nh = dims->nh;
    int ns = dims->ns;

    int size = 0;

    size += sizeof(ocp_nlp_constraints_bgh_memory);

    size += 1 * blasfeo_memsize_dvec(2 * nb + 2 * ng + 2 * nh + 2 * ns);  // fun
    size += 1 * blasfeo_memsize_dvec(nu + nx + 2 * ns);                   // adj

    size += 1 * 64;  // blasfeo_mem align

    return size;
}



void *ocp_nlp_constraints_bgh_memory_assign(void *config_, void *dims_, void *opts_,
                                            void *raw_memory)
{
    ocp_nlp_constraints_bgh_dims *dims = dims_;

    char *c_ptr = (char *) raw_memory;

    // extract dims
    int nx = dims->nx;
    int nu = dims->nu;
    int nb = dims->nb;
    int ng = dims->ng;
    int nh = dims->nh;
    int ns = dims->ns;

    // struct
    ocp_nlp_constraints_bgh_memory *memory = (ocp_nlp_constraints_bgh_memory *) c_ptr;
    c_ptr += sizeof(ocp_nlp_constraints_bgh_memory);

    // blasfeo_mem align
    align_char_to(64, &c_ptr);

    // fun
    assign_and_advance_blasfeo_dvec_mem(2 * nb + 2 * ng + 2 * nh + 2 * ns, &memory->fun, &c_ptr);
    // adj
    assign_and_advance_blasfeo_dvec_mem(nu + nx + 2 * ns, &memory->adj, &c_ptr);

    assert((char *) raw_memory +
               ocp_nlp_constraints_bgh_memory_calculate_size(config_, dims, opts_) >=
           c_ptr);

    return memory;
}



struct blasfeo_dvec *ocp_nlp_constraints_bgh_memory_get_fun_ptr(void *memory_)
{
    ocp_nlp_constraints_bgh_memory *memory = memory_;

    return &memory->fun;
}



struct blasfeo_dvec *ocp_nlp_constraints_bgh_memory_get_adj_ptr(void *memory_)
{
    ocp_nlp_constraints_bgh_memory *memory = memory_;

    return &memory->adj;
}



void ocp_nlp_constraints_bgh_memory_set_ux_ptr(struct blasfeo_dvec *ux, void *memory_)
{
    ocp_nlp_constraints_bgh_memory *memory = memory_;

    memory->ux = ux;
}



void ocp_nlp_constraints_bgh_memory_set_lam_ptr(struct blasfeo_dvec *lam, void *memory_)
{
    ocp_nlp_constraints_bgh_memory *memory = memory_;

    memory->lam = lam;
}



void ocp_nlp_constraints_bgh_memory_set_DCt_ptr(struct blasfeo_dmat *DCt, void *memory_)
{
    ocp_nlp_constraints_bgh_memory *memory = memory_;

    memory->DCt = DCt;
}



void ocp_nlp_constraints_bgh_memory_set_RSQrq_ptr(struct blasfeo_dmat *RSQrq, void *memory_)
{
    ocp_nlp_constraints_bgh_memory *memory = memory_;

    memory->RSQrq = RSQrq;
}




void ocp_nlp_constraints_bgh_memory_set_z_alg_ptr(struct blasfeo_dvec *z_alg, void *memory_)
{
    ocp_nlp_constraints_bgh_memory *memory = memory_;

    memory->z_alg = z_alg;
}



void ocp_nlp_constraints_bgh_memory_set_dzduxt_ptr(struct blasfeo_dmat *dzduxt, void *memory_)
{
    ocp_nlp_constraints_bgh_memory *memory = memory_;

    memory->dzduxt = dzduxt;
}



void ocp_nlp_constraints_bgh_memory_set_idxb_ptr(int *idxb, void *memory_)
{
    ocp_nlp_constraints_bgh_memory *memory = memory_;

    memory->idxb = idxb;
}



void ocp_nlp_constraints_bgh_memory_set_idxs_ptr(int *idxs, void *memory_)
{
    ocp_nlp_constraints_bgh_memory *memory = memory_;

    memory->idxs = idxs;
}



/************************************************
 * workspace
 ************************************************/

int ocp_nlp_constraints_bgh_workspace_calculate_size(void *config_, void *dims_, void *opts_)
{
    ocp_nlp_constraints_bgh_dims *dims = dims_;

    // extract dims
    int nx = dims->nx;
    int nu = dims->nu;
    int nz = dims->nz;
    int nb = dims->nb;
    int ng = dims->ng;
    int nh = dims->nh;
    int ns = dims->ns;

    int size = 0;

    size += sizeof(ocp_nlp_constraints_bgh_workspace);

    size += 1 * blasfeo_memsize_dmat(nu+nx, nu+nx); // tmp_nv_nv
    size += 1 * blasfeo_memsize_dmat(nz, nh);       // tmp_nz_nh
    size += 1 * blasfeo_memsize_dmat(nx+nu, nh);    // tmp_nv_nh
    size += 1 * blasfeo_memsize_dvec(nb+ng+nh+ns);  // tmp_ni
    size += 1 * blasfeo_memsize_dvec(nh);           // tmp_nh

    size += 1 * 64;                                 // blasfeo_mem align

    return size;
}



static void ocp_nlp_constraints_bgh_cast_workspace(void *config_, void *dims_, void *opts_, void *work_)
{
    ocp_nlp_constraints_bgh_dims *dims = dims_;
    ocp_nlp_constraints_bgh_workspace *work = work_;

    // extract dims
    int nx = dims->nx;
    int nu = dims->nu;
    int nz = dims->nz;
    int nb = dims->nb;
    int ng = dims->ng;
    int nh = dims->nh;
    int ns = dims->ns;

    char *c_ptr = (char *) work_;
    c_ptr += sizeof(ocp_nlp_constraints_bgh_workspace);

    // blasfeo_mem align
    align_char_to(64, &c_ptr);

    // tmp_nv_nv
    assign_and_advance_blasfeo_dmat_mem(nu+nx, nu+nx, &work->tmp_nv_nv, &c_ptr);
    
    // tmp_nz_nh
    assign_and_advance_blasfeo_dmat_mem(nz, nh, &work->tmp_nz_nh, &c_ptr);

    // tmp_nv_nh
    assign_and_advance_blasfeo_dmat_mem(nx + nu, nh, &work->tmp_nv_nh, &c_ptr);

    // tmp_ni
    assign_and_advance_blasfeo_dvec_mem(nb+ng+nh+ns, &work->tmp_ni, &c_ptr);

    // tmp_nh
    assign_and_advance_blasfeo_dvec_mem(nh, &work->tmp_nh, &c_ptr);

    assert((char *) work + ocp_nlp_constraints_bgh_workspace_calculate_size(config_, dims, opts_) >= c_ptr);

    return;
}



/************************************************
 * functions
 ************************************************/

void ocp_nlp_constraints_bgh_initialize(void *config_, void *dims_, void *model_, void *opts,
                                        void *memory_, void *work_)
{
    ocp_nlp_constraints_bgh_dims *dims = dims_;
    ocp_nlp_constraints_bgh_model *model = model_;
    ocp_nlp_constraints_bgh_memory *memory = memory_;

    // loop index
    int j;

    // extract dims
    int nx = dims->nx;
    int nu = dims->nu;
    int nb = dims->nb;
    int ng = dims->ng;
    int ns = dims->ns;

    // initialize idxb
    for (j = 0; j < nb; j++)
    {
        memory->idxb[j] = model->idxb[j];
    }

    // initialize idxs
    for (j = 0; j < ns; j++)
    {
        memory->idxs[j] = model->idxs[j];
    }

    // initialize general constraints matrix
    blasfeo_dgecp(nu + nx, ng, &model->DCt, 0, 0, memory->DCt, 0, 0);

    return;
}



void ocp_nlp_constraints_bgh_update_qp_matrices(void *config_, void *dims_, void *model_,
                                                void *opts_, void *memory_, void *work_)
{
    ocp_nlp_constraints_bgh_dims *dims = dims_;
    ocp_nlp_constraints_bgh_model *model = model_;
    ocp_nlp_constraints_bgh_opts *opts = opts_;
    ocp_nlp_constraints_bgh_memory *memory = memory_;
    ocp_nlp_constraints_bgh_workspace *work = work_;

    ocp_nlp_constraints_bgh_cast_workspace(config_, dims, opts_, work_);

    // extract dims
    int nx = dims->nx;
    int nu = dims->nu;
    int nz = dims->nz;
    int nb = dims->nb;
    int ng = dims->ng;
    int nh = dims->nh;
    int ns = dims->ns;

    ext_fun_arg_t ext_fun_type_in[3];
    void *ext_fun_in[3];
    ext_fun_arg_t ext_fun_type_out[3];
    void *ext_fun_out[3];

    // box
    blasfeo_dvecex_sp(nb, 1.0, model->idxb, memory->ux, 0, &work->tmp_ni, 0);

    // general linear
    blasfeo_dgemv_t(nu+nx, ng, 1.0, memory->DCt, 0, 0, memory->ux, 0, 0.0, &work->tmp_ni, nb, &work->tmp_ni, nb);

    // nonlinear
    if (nh > 0)
    {
        struct blasfeo_dvec_args x_in;  // input x of external fun;
        x_in.x = memory->ux;
        x_in.xi = nu;

        struct blasfeo_dvec_args u_in;  // input u of external fun;
        u_in.x = memory->ux;
        u_in.xi = 0;

        struct blasfeo_dvec_args z_in;  // input z of external fun;
        z_in.x = memory->z_alg;
        z_in.xi = 0;

        struct blasfeo_dvec_args fun_out;
        fun_out.x = &work->tmp_ni;
        fun_out.xi = nb + ng;

        struct blasfeo_dmat_args jac_out;
        jac_out.A = memory->DCt;
        jac_out.ai = 0;
        jac_out.aj = ng;

        struct blasfeo_dmat_args jac_z_out; // Jacobian dhdz treated separately
        if (nz > 0)
        { 
            jac_z_out.A = &work->tmp_nz_nh;
            jac_z_out.ai = 0;
            jac_z_out.aj = 0;
        }

		// TODO check that it is correct, as it prevents convergence !!!!!
        if (opts->compute_hess)
        {
            if (nz > 0) {
                printf("ocp_nlp_constraints_bgh: opts->compute_hess is set to 1, but exact Hessians are not available (yet) when nz > 0. Exiting.\n");
                exit(1);
            }

            struct blasfeo_dvec_args mult_in;  // multipliers of external fun;
            mult_in.x = &work->tmp_nh;
            mult_in.xi = 0;
            // TODO check that it is (upper - lower) and  not the other way around
            blasfeo_daxpy(nh, -1.0, memory->lam, nb+ng, memory->lam, 2*nb+2*ng+nh, &work->tmp_nh, 0);
//            blasfeo_daxpy(nh, -1.0, memory->lam, 2*nb+2*ng+nh, memory->lam, nb+ng, &work->tmp_nh, 0);
//            blasfeo_daxpy(nh, 1.0, memory->lam, nb+ng, memory->lam, 2*nb+2*ng+nh, &work->tmp_nh, 0);

            struct blasfeo_dmat_args hess_out;
            hess_out.A = &work->tmp_nv_nv;
            hess_out.ai = 0;
            hess_out.aj = 0;

            ext_fun_type_in[0] = BLASFEO_DVEC_ARGS;
            ext_fun_in[0] = &x_in;
            ext_fun_type_in[1] = BLASFEO_DVEC_ARGS;
            ext_fun_in[1] = &u_in;
            ext_fun_type_in[2] = BLASFEO_DVEC_ARGS;
            ext_fun_in[2] = &mult_in;

            ext_fun_type_out[0] = BLASFEO_DVEC_ARGS;
            ext_fun_out[0] = &fun_out;  // fun: nh
            ext_fun_type_out[1] = BLASFEO_DMAT_ARGS;
            ext_fun_out[1] = &jac_out;  // jac': (nu+nx) * nh
            ext_fun_type_out[2] = BLASFEO_DMAT_ARGS;
            ext_fun_out[2] = &hess_out;  // hess*mult: (nu+nx) * (nu+nx)

            model->nl_constr_h_fun_jac_hess->evaluate(model->nl_constr_h_fun_jac_hess,
					ext_fun_type_in, ext_fun_in, ext_fun_type_out, ext_fun_out);

            blasfeo_dgead(nu+nx, nu+nx, 1.0, &work->tmp_nv_nv, 0, 0, memory->RSQrq, 0, 0);

        }
        else
        {
            ext_fun_type_in[0] = BLASFEO_DVEC_ARGS;
            ext_fun_in[0] = &x_in;
            ext_fun_type_in[1] = BLASFEO_DVEC_ARGS;
            ext_fun_in[1] = &u_in;
			ext_fun_type_in[2] = BLASFEO_DVEC_ARGS;
			ext_fun_in[2] = &z_in;

            ext_fun_type_out[0] = BLASFEO_DVEC_ARGS;
            ext_fun_out[0] = &fun_out;  // fun: nh
            ext_fun_type_out[1] = BLASFEO_DMAT_ARGS;
            ext_fun_out[1] = &jac_out;  // jac': (nu+nx) * nh
			ext_fun_type_out[2] = BLASFEO_DMAT_ARGS;
			ext_fun_out[2] = &jac_z_out;  // jac': nz * nh
			
            model->nl_constr_h_fun_jac->evaluate(model->nl_constr_h_fun_jac, ext_fun_type_in, ext_fun_in, ext_fun_type_out, ext_fun_out);

			// expand h:
			// h(x, u, z) ~
			// h(\bar{x}, \bar{u}, \bar{z}) + 
			// dhdx*(x - \bar{x}) + 
			// dhdu*(u - \bar{u}) + 
			// dhdz*(z - \bar{z}) =
			//
			// h(\bar{x}, \bar{u}, \bar{z}) - dhdz*dzdx*\bar{x} - dhdz*dzdu*\bar{u} + 
			// (dhdx + dhdz*dzdx)*(x - \bar{x}) +  
			// (dhdu + dhdz*dzdu)*(u - \bar{u})  
			
			// TODO(andrea): check residual computation
			// update DCt
			// printf("memory->dzduxt=n");
			// blasfeo_print_dmat(nu+nx, nh, memory->dzduxt, 0, 0);
			blasfeo_dgemm_nn(nu+nx, nh, nz, 1.0, memory->dzduxt, 0, 0,
					&work->tmp_nz_nh, 0, 0, 0.0, &work->tmp_nv_nh, 0, 0, &work->tmp_nv_nh, 0, 0);
		    blasfeo_dgead(nu+nx, nh, 1.0, &work->tmp_nv_nh, 0, 0, memory->DCt, ng, 0);	
			// printf("tmp_nv_nh=\n");
			// blasfeo_print_dmat(nu+nx, nh, &work->tmp_nv_nh, 0, 0);
			// update memory->fun	
			blasfeo_dgemv_t(nu+nx, nh, -1.0, &work->tmp_nz_nh, 0, 0, memory->ux,
					0, 1.0, &memory->fun, 0, &memory->fun, 0);
        }
    }

    blasfeo_daxpy(nb+ng+nh, -1.0, &work->tmp_ni, 0, &model->d, 0, &memory->fun, 0);
    blasfeo_daxpy(nb+ng+nh, -1.0, &model->d, nb+ng+nh, &work->tmp_ni, 0, &memory->fun, nb+ng+nh);

    // soft
    blasfeo_dvecad_sp(ns, -1.0, memory->ux, nu+nx, model->idxs, &memory->fun, 0);
    blasfeo_dvecad_sp(ns, -1.0, memory->ux, nu+nx+ns, model->idxs, &memory->fun, nb+ng+nh);

    blasfeo_daxpy(2*ns, -1.0, memory->ux, nu+nx, &model->d, 2*nb+2*ng+2*nh, &memory->fun, 2*nb+2*ng+2*nh);

    // nlp_mem: ineq_adj
    if (opts->compute_adj)
    {
        blasfeo_dvecse(nu+nx+2*ns, 0.0, &memory->adj, 0);
        blasfeo_daxpy(nb+ng+nh, -1.0, memory->lam, nb+ng+nh, memory->lam, 0, &work->tmp_ni, 0);
        blasfeo_dvecad_sp(nb, 1.0, &work->tmp_ni, 0, model->idxb, &memory->adj, 0);
        blasfeo_dgemv_n(nu+nx, ng+nh, 1.0, memory->DCt, 0, 0, &work->tmp_ni, nb, 1.0, &memory->adj, 0, &memory->adj, 0);
        // soft
        blasfeo_dvecex_sp(ns, 1.0, model->idxs, memory->lam, 0, &memory->adj, nu+nx);
        blasfeo_dvecex_sp(ns, 1.0, model->idxs, memory->lam, nb+ng+nh, &memory->adj, nu+nx+ns);
        blasfeo_daxpy(2*ns, 1.0, memory->lam, 2*nb+2*ng+2*nh, &memory->adj, nu+nx, &memory->adj, nu+nx);
    }

    return;
}



void ocp_nlp_constraints_bgh_config_initialize_default(void *config_)
{
    ocp_nlp_constraints_config *config = config_;

    config->dims_calculate_size = &ocp_nlp_constraints_bgh_dims_calculate_size;
    config->dims_assign = &ocp_nlp_constraints_bgh_dims_assign;
    config->dims_initialize = &ocp_nlp_constraints_bgh_dims_initialize;
    config->dims_set = &ocp_nlp_constraints_bgh_dims_set;
    config->dims_get = &ocp_nlp_constraints_bgh_dims_get;
    config->model_calculate_size = &ocp_nlp_constraints_bgh_model_calculate_size;
    config->model_assign = &ocp_nlp_constraints_bgh_model_assign;
    config->model_set = &ocp_nlp_constraints_bgh_model_set;
    config->opts_calculate_size = &ocp_nlp_constraints_bgh_opts_calculate_size;
    config->opts_assign = &ocp_nlp_constraints_bgh_opts_assign;
    config->opts_initialize_default = &ocp_nlp_constraints_bgh_opts_initialize_default;
    config->opts_update = &ocp_nlp_constraints_bgh_opts_update;
    config->opts_set = &ocp_nlp_constraints_bgh_opts_set;
    config->memory_calculate_size = &ocp_nlp_constraints_bgh_memory_calculate_size;
    config->memory_assign = &ocp_nlp_constraints_bgh_memory_assign;
    config->memory_get_fun_ptr = &ocp_nlp_constraints_bgh_memory_get_fun_ptr;
    config->memory_get_adj_ptr = &ocp_nlp_constraints_bgh_memory_get_adj_ptr;
    config->memory_set_ux_ptr = &ocp_nlp_constraints_bgh_memory_set_ux_ptr;
    config->memory_set_lam_ptr = &ocp_nlp_constraints_bgh_memory_set_lam_ptr;
    config->memory_set_DCt_ptr = &ocp_nlp_constraints_bgh_memory_set_DCt_ptr;
    config->memory_set_RSQrq_ptr = &ocp_nlp_constraints_bgh_memory_set_RSQrq_ptr;
    config->memory_set_z_alg_ptr = &ocp_nlp_constraints_bgh_memory_set_z_alg_ptr;
    config->memory_set_dzdux_tran_ptr = &ocp_nlp_constraints_bgh_memory_set_dzduxt_ptr;
    config->memory_set_idxb_ptr = &ocp_nlp_constraints_bgh_memory_set_idxb_ptr;
    config->memory_set_idxs_ptr = &ocp_nlp_constraints_bgh_memory_set_idxs_ptr;
    config->workspace_calculate_size = &ocp_nlp_constraints_bgh_workspace_calculate_size;
    config->initialize = &ocp_nlp_constraints_bgh_initialize;
    config->update_qp_matrices = &ocp_nlp_constraints_bgh_update_qp_matrices;
    config->config_initialize_default = &ocp_nlp_constraints_bgh_config_initialize_default;

    return;
}
