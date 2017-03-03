# Build list with all source files to go into the acados library
file(GLOB_RECURSE ACADOS_SRC ${PROJECT_SOURCE_DIR}/acados/*.c)
# Exclude helper files
list(REMOVE_ITEM ACADOS_SRC ${PROJECT_SOURCE_DIR}/acados/ocp_qp/condensing_helper_functions.c)

if (NOT EXISTS ${PROJECT_SOURCE_DIR}/external/OOQP)
    list(REMOVE_ITEM ACADOS_SRC ${PROJECT_SOURCE_DIR}/acados/ocp_qp/ocp_qp_ooqp.c)
endif()

# Sources for examples
set(HPMPC_EXAMPLE_SRC ${PROJECT_SOURCE_DIR}/examples/test_ocp_qp_hpmpc.c)
set(CONDENSING_QPOASES_EXAMPLE_SRC ${PROJECT_SOURCE_DIR}/examples/test_ocp_qp_condensing_qpoases.c)
set(CHEN_MODEL_SRC ${PROJECT_SOURCE_DIR}/examples/Chen/Chen_model.c)
set(NMPC_EXAMPLE_SRC ${PROJECT_SOURCE_DIR}/examples/test_nmpc.c)
file(GLOB CHAIN_EXAMPLE_SRC ${PROJECT_SOURCE_DIR}/examples/casadi_chain/Chain_model.c

    ${PROJECT_SOURCE_DIR}/examples/casadi_chain/vde*.c
    ${PROJECT_SOURCE_DIR}/examples/casadi_chain/jac*.c
    ${PROJECT_SOURCE_DIR}/examples/test_chain.c
)

file(GLOB PENDULUM_EXAMPLE_SRC ${PROJECT_SOURCE_DIR}/examples/casadi_pendulum/pendulum_model.c

    ${PROJECT_SOURCE_DIR}/examples/casadi_pendulum/vde_forw_pendulum.c
    ${PROJECT_SOURCE_DIR}/examples/casadi_pendulum/jac_pendulum.c
    ${PROJECT_SOURCE_DIR}/examples/test_nmpc_pendulum_hpmpc_libstr.c
)

file(GLOB ACADOS_CONTROLLER_MEM_SRC

    ${PROJECT_SOURCE_DIR}/experimental/andrea/modular_interface/ocps/acados_kitty_interface.c
    ${PROJECT_SOURCE_DIR}/experimental/andrea/modular_interface/ocps/plotting.c
    ${PROJECT_SOURCE_DIR}/experimental/andrea/modular_interface/utils/eispack.c
    ${PROJECT_SOURCE_DIR}/experimental/andrea/modular_interface/models/aircraft_integrator.c
    ${PROJECT_SOURCE_DIR}/experimental/andrea/modular_interface/autogen/ocp_xtracking_banana1_casadi.c
    ${PROJECT_SOURCE_DIR}/experimental/andrea/modular_interface/autogen/ocp_utracking_banana1_casadi.c
    ${PROJECT_SOURCE_DIR}/experimental/andrea/modular_interface/autogen/ocp_integrate_ode_banana1_casadi.c
    ${PROJECT_SOURCE_DIR}/experimental/andrea/modular_interface/ocps/residual_x_eval_wrapper.c
    ${PROJECT_SOURCE_DIR}/experimental/andrea/modular_interface/ocps/residual_u_eval_wrapper.c

)

file(GLOB PENDULUM_EXAMPLE_PT_SRC ${PROJECT_SOURCE_DIR}/examples/casadi_pendulum/pendulum_model.c

    ${PROJECT_SOURCE_DIR}/examples/casadi_pendulum/vde_forw_pendulum.c
    ${PROJECT_SOURCE_DIR}/examples/casadi_pendulum/jac_pendulum.c
    ${PROJECT_SOURCE_DIR}/examples/test_nmpc_pendulum_hpmpc_libstr_pt.c
)
