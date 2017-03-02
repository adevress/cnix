

if(UNIT_TESTS)


find_package(Check REQUIRED)


add_executable(cnix_base_test_c_bin "cnix_base_tests.c")
target_link_libraries(cnix_base_test_c_bin ${CHECK_LIBRARIES} cnix m rt ${CMAKE_THREAD_LIBS_INIT})

add_test(cnix_base_test cnix_base_test_c_bin)

endif()
