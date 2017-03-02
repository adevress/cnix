#ifndef CNIX_H
#define CNIX_H



#ifdef __cplusplus
extern "C" {
#endif

struct cnix_struct_internal;

// main nix context
typedef struct cnix_struct_internal* cnix_handle_t;


/**
 * \brief create and initialize a default new nix handle
 *
 **/
cnix_handle_t cnix_handle_new();


/**
 * @brief cnix_store_path
 * @return path of the nix store
 */
char* cnix_store_path(cnix_handle_t handle);


/**
 * \brief destroy a nix handle
 *
 * */
void cnix_handle_delete(cnix_handle_t handle);




#ifdef __cplusplus
}
#endif

#endif // CNIX_H

