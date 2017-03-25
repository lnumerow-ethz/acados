include(ExternalProject)

if(NOT DEFINED HPMPC_TARGET)
#	set(HPMPC_TARGET X64_AVX2)
#	set(HPMPC_TARGET X64_AVX)
	set(HPMPC_TARGET C99_4X4)
endif()
if(NOT DEFINED HPMPC_BLASFEO_PATH)
	set(HPMPC_BLASFEO_PATH ${PROJECT_SOURCE_DIR}/external/blasfeo)
endif()

ExternalProject_Add(
    hpmpc_project
    DEPENDS blasfeo
    CONFIGURE_COMMAND ""
    SOURCE_DIR "${PROJECT_SOURCE_DIR}/external/hpmpc"
    BUILD_IN_SOURCE 1
    BUILD_COMMAND make clean shared_library -j 2 TARGET=${HPMPC_TARGET} BLASFEO_PATH=${HPMPC_BLASFEO_PATH}
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
		STEP_TARGETS build install
		EXCLUDE_FROM_ALL TRUE
#		INSTALL_COMMAND make install PREFIX=${CMAKE_INSTALL_PREFIX}
#		INSTALL_COMMAND ""
)

ExternalProject_Get_Property(hpmpc_project source_dir)
add_library(hpmpc SHARED IMPORTED)
#add_dependencies(hpmpc hpmpc_project-build blasfeo_project-build)
#set_property(TARGET hpmpc PROPERTY IMPORTED_LOCATION "${source_dir}/libhpmpc.so")
