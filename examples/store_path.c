

    #include <assert.h>
	#include <stdio.h>
	#include <stdlib.h>


    #include <cnix/cnix.h>

    int main(){

        cnix_handle_t h = cnix_handle_new();
        assert(h != NULL);

        char* store_path = cnix_store_path(h);
        assert(h != NULL);

        printf("nix store %s \n", store_path);

        free(store_path);

        cnix_handle_delete(h);
    }

