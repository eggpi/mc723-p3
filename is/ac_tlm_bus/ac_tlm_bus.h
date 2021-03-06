#ifndef AC_TLM_BUS_H_
#define AC_TLM_BUS_H_

#include <systemc>
#include "ac_tlm_protocol.H"
#include "ac_tlm_port.H"
#include "ac_memport.H"

// using statements
using tlm::tlm_transport_if;

//#define DEBUG

/// Namespace to isolate bus from ArchC
namespace user
{

/// A TLM bus
class ac_tlm_bus :
  public sc_module,
  public ac_tlm_transport_if // Using ArchC TLM protocol
{
public:
  // Memory communication port
  ac_tlm_port DM_port;

  // Software offloading communication port
  ac_tlm_port offloading_port;
  
  /// Exposed port with ArchC interface
  sc_export< ac_tlm_transport_if > target_export[8];

  ac_tlm_rsp (*mem_access_callback)(const ac_tlm_req &);
  
  
  /**
   * Implementation of TLM transport method that
   * handle packets of the protocol doing apropriate actions.
   * This method must be implemented (required by SystemC TLM).
   * @param request is a received request packet
   * @return A response packet to be send
  */
  ac_tlm_rsp transport( const ac_tlm_req &request ) {
    ac_tlm_rsp response = mem_access_callback(request);
    if (response.status == SUCCESS) return response;
    
    if(request.addr == 0xEEEEEEEE)
      return offloading_port->transport(request);
        
    else
      return DM_port->transport(request);
  }


  /**
   * Default constructor.
   */
  ac_tlm_bus(sc_module_name module_name, ac_tlm_rsp (*mem_access_callback)(const ac_tlm_req &));

  /**
   * Default destructor.
   */
  ~ac_tlm_bus();
};

};

#endif //AC_TLM_BUS_H_
