/*
 * cnix
 * Copyright (C) 2017 - Adrien Devresse
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * */
#ifndef CNIX_H
#define CNIX_H

#include <cnix/cnix_error.h>


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
 * \brief destroy a nix handle
 *
 * */
void cnix_handle_delete(cnix_handle_t handle);


/**
 * @brief cnix_store_path
 * @return the path of the nix store. The returned string should be freed after usage.
 */
char* cnix_store_path(cnix_handle_t handle);

/**
 * @brief cnix_all_paths
 *
 * @param handle
 * @return all existing derivation paths in the nix store. The returned
 * array of string should be freed after usage
 */
char** cnix_all_paths(cnix_handle_t handle);

/**
 * @brief cnix_hash_to_path
 * @return path of a derivation for a given path. NULL if does not exist.
 *  The returned string should be freed after usage.
 */
char* cnix_hash_to_path(cnix_handle_t handle, const char* hash);

/**
 * @brief cnix_store_want_mass_query
 * @param handle
 * @return return 0 if wass query is not supported or 1 if supported, -1 if error
 */
int cnix_store_want_mass_query(cnix_handle_t handle);







#ifdef __cplusplus
}
#endif

#endif // CNIX_H

