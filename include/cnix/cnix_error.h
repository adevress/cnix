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
#ifndef CNIX_ERROR_H
#define CNIX_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif


#define CNIX_ERROR_OK 0x00
#define CNIX_ERROR_STORE_INIT 0x01
#define CNIX_ERROR_INVALID_HANDLE 0x02
#define CNIX_ERROR_OTHER 0xff


/**
 * @brief cnix_error_string
 * @return string message associated with the last cnix error
 */
const char* cnix_error_string();

/**
 * @brief cnix_error_code
 * @return error code associated with the last cnix error ( e.g CNIX_ERROR_STORE_NOT_FOUND )
 */
int cnix_error_code();


/**
 * @brief cnix_error_reset
 *
 * reset internal error status to CNIX_ERROR_OK
 */
void cnix_error_reset();


// internal
void cnix_error_set(int code, const char* msg);



#ifdef __cplusplus
}
#endif

#endif // CNIX_ERROR_H
