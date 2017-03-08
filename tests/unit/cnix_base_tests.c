




#include <cnix/cnix.h>

#include <check.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


START_TEST(cnix_base_instanciate)
{
    cnix_handle_t h = cnix_handle_new();
    fail_unless(h != NULL);

    cnix_handle_delete(h);
}
END_TEST



START_TEST(cnix_base_store_path)
{
    cnix_handle_t h = cnix_handle_new();
    fail_unless(h != NULL);

    char* store_path = cnix_store_path(h);
    fail_unless(h != NULL);

    struct stat st;
    int err = stat(store_path, &st);
    fail_if(err != 0)   ;
    fail_if( S_ISDIR(st.st_mode) == 0);
    printf("nix store %s \n", store_path);

    free(store_path);

    cnix_handle_delete(h);
}
END_TEST



START_TEST(cnix_store_mass_query)
{
    // test with invalid handle
    cnix_handle_t h = NULL;

    int mass_query = cnix_store_want_mass_query(h);
    fail_unless(mass_query == -1);

    int code = cnix_error_code();
    fail_unless(code == CNIX_ERROR_INVALID_HANDLE);

    h = cnix_handle_new();

    mass_query = cnix_store_want_mass_query(h);
    fail_unless(mass_query == 0 || mass_query == 1);

    cnix_handle_delete(h);
}
END_TEST


START_TEST(cnix_error_simple)
{
    int code = cnix_error_code();

    fail_unless(code == CNIX_ERROR_OK);

    const char* p = cnix_error_string();

    char* pos = strstr(p, "OK");

    fail_unless( pos != NULL);

    cnix_error_set(CNIX_ERROR_OTHER, "major failure");

    code = cnix_error_code();
    fail_unless(code == CNIX_ERROR_OTHER);

    const char* p2 = cnix_error_string();

    fail_unless(strcmp(p2, "major failure") == 0);

    cnix_error_reset();

    code = cnix_error_code();
    fail_unless(code == CNIX_ERROR_OK);

}
END_TEST


int main(void){


    Suite *s1 = suite_create("base");
    TCase *tc1_1 = tcase_create("base");

    int nf;

    SRunner *sr = srunner_create(s1);
    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, cnix_base_instanciate);
    tcase_add_test(tc1_1, cnix_base_store_path);
    tcase_add_test(tc1_1, cnix_store_mass_query);
    tcase_add_test(tc1_1, cnix_error_simple);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;

}
