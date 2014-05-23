#include "ac_tlm_bus.h"

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate memory from ArchC
using user::ac_tlm_bus;

/// Constructor
ac_tlm_bus::ac_tlm_bus(sc_module_name module_name) :
  sc_module(module_name),
  DM_port("DM_port", 5242880U)
{
    /// Binds target_export to the memory
    for (int i = 0; i < sizeof(target_export) / sizeof(target_export[0]); i++) {
        target_export[i]( *this );
    }

}

/// Destructor
ac_tlm_bus::~ac_tlm_bus() {
}
