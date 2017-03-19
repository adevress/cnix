

file(GLOB src_cnix "*.cpp")

file(GLOB headers_nix "${CMAKE_CURRENT_SOURCE_DIR}/../include/cnix/*.h")

include_directories(${NIX_INCLUDE_DIRS} )

add_library(cnix SHARED ${src_cnix} ${headers_nix} )

target_link_libraries(cnix ${NIX_LIB_MAIN} ${NIX_LIB_STORE} ${NIX_LIB_UTIL})


install(TARGETS cnix
             DESTINATION ${LIB_INSTALL_DIR} )


