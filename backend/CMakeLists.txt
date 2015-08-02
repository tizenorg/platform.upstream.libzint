# (c) 2008 by BogDan Vatra < bogdan@licentia.eu >

project(zint)

set(zint_COMMON_SRCS common.c library.c render.c ps.c large.c reedsol.c gs1.c png.c)
set(zint_ONEDIM_SRCS code.c code128.c 2of5.c upcean.c)
set(zint_TWODIM_SRCS qr.c)
set(zint_SRCS ${zint_COMMON_SRCS} ${zint_ONEDIM_SRCS} ${zint_TWODIM_SRCS} )

add_definitions (-DNO_PNG)

add_library(zint SHARED ${zint_SRCS})

SET_TARGET_PROPERTIES(zint
     PROPERTIES
     VERSION ${FULLVER}
     SOVERSION ${MAJORVER}
     CLEAN_DIRECT_OUTPUT 1
)

target_link_libraries(zint -lm)

install(TARGETS zint  ${INSTALL_TARGETS_DEFAULT_ARGS} )
install(FILES zint.h DESTINATION ${INCLUDE_INSTALL_DIR} COMPONENT Devel)
install(FILES LICENSE DESTINATION ${SHARE_INSTALL_PREFIX}/zint)
