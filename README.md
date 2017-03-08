cnix - C API to the nix package manager

# Brief

cnix provides a stable C API and ABI to the Nix package manager.   

cnix makes easier the creation of langage bindings ( Python, Ruby, Golang, Rust ) for the Nix package manager 


# Usage

```c

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

```


# License
LGPLv3


