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

#ifndef CNIX_UTILS_HPP
#define CNIX_UTILS_HPP

#include <stdexcept>
#include <exception>

#include <boost/optional.hpp>

#include <cnix/cnix_error.h>


#include <nix/store-api.hh>


// invalid handle exception
class cnix_invalid_handle : public std::invalid_argument{
public:
    cnix_invalid_handle(const std::string & str) : std::invalid_argument(str){}
};


template<typename Res, typename Fun>
boost::optional<Res> error_handler(Fun && f, int default_error = CNIX_ERROR_OTHER){
    try{
        return f();
    }catch(cnix_invalid_handle & e){
        cnix_error_set(CNIX_ERROR_INVALID_HANDLE, e.what());
    } catch( nix::Error & e){
        if(std::string(e.what()) == "invalid hash part"){
            cnix_error_set(CNIX_ERROR_INVALID_HASH, e.what());
        }else{
            cnix_error_set(default_error, e.what());
        }
    } catch(std::exception & e){
        cnix_error_set(default_error, e.what());
    } catch(...){
        cnix_error_set(CNIX_ERROR_OTHER, " unknown error : not from std::exception");
    }
    return boost::optional<Res>();
}



#endif // CNIX_UTILS_HPP
