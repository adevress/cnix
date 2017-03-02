
#include <cnix/cnix.h>

#include "cnix_def.hpp"

#include <sstream>
#include <iostream>
#include <memory>
#include <cstring>

// all internal nix handle
#include <nix/store-api.hh>



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

    std::shared_ptr<nix::Store> _store;
};



cnix_struct_internal* unwrap_handle(cnix_handle_t h){
    return h;
}



CNIX_CDEF cnix_handle_t cnix_handle_new(){
    return new cnix_struct_internal();
}

CNIX_CDEF char* cnix_store_path(cnix_handle_t handle){
    const std::string store = unwrap_handle(handle)->get_store();
    return strdup(store.c_str());
}


CNIX_CDEF void cnix_handle_delete(cnix_handle_t handle){
    delete static_cast<cnix_struct_internal*>(handle);
}
