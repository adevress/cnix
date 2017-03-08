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
#include <cnix/cnix_error.h>

#include "cnix_def.hpp"

#include <string>
#include <cstring>

// all internal nix handle
#include <nix/store-api.hh>

constexpr char default_message[] = "OK no error";


struct cnix_error{
   cnix_error() : code(CNIX_ERROR_OK), message(default_message){}

   int code;
   std::string message;

   void set(int mcode, const char* mmsg){
       code = mcode;
       message = mmsg;
   }
};


struct cnix_err_meyer_single{
    static cnix_error & get_error(){
        static thread_local cnix_error err;
        return err;
    }
};


CNIX_CDEF const char* cnix_error_string(){
    return cnix_err_meyer_single::get_error().message.c_str();
}

CNIX_CDEF int cnix_error_code(){
    return cnix_err_meyer_single::get_error().code;
}


CNIX_CDEF void cnix_error_set(int code, const char* msg){
    return cnix_err_meyer_single::get_error().set(code, msg);
}



CNIX_CDEF void cnix_error_reset(){
    cnix_error reset_err;

    std::swap(cnix_err_meyer_single::get_error(), reset_err);
}
