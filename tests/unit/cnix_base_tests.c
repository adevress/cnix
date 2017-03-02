




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



int main(void){


    Suite *s1 = suite_create("base");
    TCase *tc1_1 = tcase_create("base");

    int nf;

    SRunner *sr = srunner_create(s1);
    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, cnix_base_instanciate);
    tcase_add_test(tc1_1, cnix_base_store_path);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;

}
