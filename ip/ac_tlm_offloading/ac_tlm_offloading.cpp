/**
 * @file      ac_tlm_offloading.cpp
 * @author    Bruno de Carvalho Albertini
 *
 * @author    The ArchC Team
 *            http://www.archc.org/
 *
 *            Computer Systems Laboratory (LSC)
 *            IC-UNICAMP
 *            http://www.lsc.ic.unicamp.br/
 *
 * @version   0.1
 * @date      Sun, 02 Apr 2006 08:07:46 -0200
 *
 * @brief     Implements a ac_tlm memory.
 *
 * @attention Copyright (C) 2002-2005 --- The ArchC Team
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *
 */


//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes

#include "ac_tlm_offloading.h"

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate memory from ArchC
using user::ac_tlm_offloading;

/// Constructor
ac_tlm_offloading::ac_tlm_offloading( sc_module_name module_name ) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the memory
    target_export( *this );

}

/// Destructor
ac_tlm_offloading::~ac_tlm_offloading() {

}

/** Internal Write
  * Note: Always write 32 bits
  * @param a is the address to write
  * @param d id the data being write
  * @returns A TLM response packet with SUCCESS
*/

#define BITSPERLONG 32
#define TOP2BITS(x) ((x & (3L << (BITSPERLONG-2))) >> (BITSPERLONG-2))

ac_tlm_rsp_status ac_tlm_offloading::execute( const uint32_t &d )
{
  uint32_t input = be32toh(*((uint32_t *) &d));
  
  unsigned long a = 0L;                   /* accumulator      */
  unsigned long r = 0L;                   /* remainder        */
  unsigned long e = 0L;                   /* trial product    */

  int i;

  for (i = 0; i < BITSPERLONG; i++)   /* NOTE 1 */
  {
        r = (r << 2) + TOP2BITS(input); input <<= 2; /* NOTE 2 */
        a <<= 1;
        e = (a << 1) + 1;
        if (r >= e)
        {
              r -= e;
              a++;
        }
  }
  
  result = (uint32_t) a;
  
  return SUCCESS;
}
