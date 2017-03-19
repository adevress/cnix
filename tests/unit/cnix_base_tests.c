




#include <cnix/cnix.h>

#include <check.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


void free_array_str(char** array_str){
    char** p = array_str;
    while(*p != NULL){
        free(*p);
        p++;
    }
    free(array_str);
}


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



START_TEST(test_cnix_all_paths)
{

    cnix_handle_t h = cnix_handle_new();

    fail_unless(h != NULL);

    char ** paths = cnix_all_paths(h);


    fail_unless(paths != NULL);


    char** p = paths;
    while(*p != NULL){
        printf(" path: %s \n", *p);
        p++;
    }

    free_array_str(paths);

}
END_TEST



START_TEST(cnix_path_query)
{
    cnix_handle_t h = cnix_handle_new();

    fail_unless(h != NULL);

    char* inexisting_path = cnix_hash_to_path(h, "not-existing");

    fail_unless(inexisting_path == NULL);
    fail_unless(cnix_error_code() == CNIX_ERROR_INVALID_HASH);

    printf("report: %s\n", cnix_error_string());
    cnix_error_reset();


    char ** paths = cnix_all_paths(h);

    fail_unless(paths != NULL);

    char* path = paths[0];
    char* file_delim = strrchr(path, '/');

    fail_unless(file_delim != NULL);
    file_delim++;

    char* end_hash_delim = strchr(file_delim, '-');
    fail_unless(end_hash_delim != NULL);

    char* hash = strndup(file_delim, (end_hash_delim-file_delim));

    char* path_back = cnix_hash_to_path(h, hash);

    int diff = strcmp(path_back, path);

    fail_unless(diff == 0);

    free(path_back);
    free(hash);
    free_array_str(paths);

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
    tcase_add_test(tc1_1, test_cnix_all_paths);
    tcase_add_test(tc1_1, cnix_path_query);
    tcase_add_test(tc1_1, cnix_error_simple);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;

}
