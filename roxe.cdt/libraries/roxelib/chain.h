/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#pragma once

#include "types.h"

#warning "<roxelib/chain.h> is deprecated use <roxe/chain.h>. If you are using C++ the .h header files will be removed from inclusion entirely in v1.7.0"
/**
 *  @addtogroup chain
 *  @ingroup c_api
 *  @brief Defines %C API for querying internal chain state
 *  @{
 */

extern "C" {
    /**
     *  Gets the set of active producers.
     *
     *  @param producers - Pointer to a buffer of account names
     *  @param datalen - Byte length of buffer, when passed 0 will return the size required to store full output.
     *
     *  @return uint32_t - Number of bytes actually populated
     *  @pre `producers` is a pointer to a range of memory at least `datalen` bytes long
     *  @post the passed in `producers` pointer gets the array of active producers.
     *
     *  Example:
     *
     *  @code
     *  capi_name producers[21];
     *  uint32_t bytes_populated = get_active_producers(producers, sizeof(capi_name)*21);
     *  @endcode
     */
   __attribute__((roxe_wasm_import))
   uint32_t get_active_producers( capi_name* producers, uint32_t datalen );
}

/// @}
