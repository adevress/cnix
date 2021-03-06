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
#include <cnix/cnix.h>

#include "cnix_def.hpp"
#include "cnix_utils.hpp"

#include <sstream>
#include <iostream>
#include <memory>
#include <cstring>
#include <set>
#include <string>

// all internal nix handle
#include <nix/store-api.hh>


#ifdef NIX_1_11_VERSION

struct cnix_struct_internal{
    cnix_struct_internal(): _store(nix::openStore()){

    }

    virtual ~cnix_struct_internal(){}

    const std::string get_store() const{
		auto s = _store->queryAllValidPaths();
		return *(s.begin());
    }

    bool want_mass_query() const{
        return true;
    }

    std::shared_ptr<nix::StoreAPI> _store;
};




#else 

struct cnix_struct_internal{
    cnix_struct_internal(): _store(nix::openStore()){

    }

    virtual ~cnix_struct_internal(){}

    const std::string get_store() const{
        return _store->storeDir;
    }

    bool want_mass_query() const{
        return _store->wantMassQuery();
    }

    std::set<std::string> all_path() const{
        return _store->queryAllValidPaths();
    }

    std::string query_path_from_hash(const std::string & hash) const{
        return _store->queryPathFromHashPart(hash);
    }

    std::shared_ptr<nix::Store> _store;
};


#endif 


cnix_struct_internal* unwrap_handle(cnix_handle_t h){
    if(!h){
        throw cnix_invalid_handle("Invalid cnix handle NULL");
    }
    return h;
}



CNIX_CDEF cnix_handle_t cnix_handle_new(){

    auto res = error_handler<cnix_handle_t>([]{

        return new cnix_struct_internal();

    }, CNIX_ERROR_STORE_INIT);

    return (res) ? res.value() : nullptr;
}


CNIX_CDEF void cnix_handle_delete(cnix_handle_t handle){
    delete static_cast<cnix_struct_internal*>(handle);
}


CNIX_CDEF char* cnix_store_path(cnix_handle_t handle){
    auto res = error_handler<char*>([&]{

        const std::string store = unwrap_handle(handle)->get_store();
        return strdup(store.c_str());

    }, CNIX_ERROR_OTHER);


    return (res) ? res.value() : nullptr;
}


CNIX_CDEF int cnix_store_want_mass_query(cnix_handle_t handle){
    auto res = error_handler<bool>([&]{

        return unwrap_handle(handle)->want_mass_query();

    }, CNIX_ERROR_OTHER);

    if(!res)
        return -1;

    return (res) ? 1 : 0;
}


CNIX_CDEF char** cnix_all_paths(cnix_handle_t handle){
    auto res = error_handler<char**>([&]{

        auto set_string =  unwrap_handle(handle)->all_path();

        char ** arr = (char**) malloc(sizeof(char*) * (set_string.size()+1));
        if(arr == nullptr) throw std::bad_alloc();

        std::size_t nelem =0;
        for( auto & str : set_string){
            arr[nelem] = strdup(str.c_str()) ;
            nelem += 1;
        }
        arr[nelem] = nullptr;
        return arr;

    }, CNIX_ERROR_OTHER);

    if(!res)
        return NULL;

    return res.value();
}


CNIX_CDEF char* cnix_hash_to_path(cnix_handle_t handle, const char* hash){

    auto res = error_handler<char*>([&]{

        auto res =  unwrap_handle(handle)->query_path_from_hash(hash);
        return strdup(res.c_str());

    }, CNIX_ERROR_OTHER);

    if(!res)
        return NULL;

    return res.value();
}

