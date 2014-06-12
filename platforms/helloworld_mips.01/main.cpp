/******************************************************
 * This is the main file for the mips1 ArchC model    *
 * This file is automatically generated by ArchC      *
 * WITHOUT WARRANTY OF ANY KIND, either express       *
 * or implied.                                        *
 * For more information on ArchC, please visit:       *
 * http://www.archc.org                               *
 *                                                    *
 * The ArchC Team                                     *
 * Computer Systems Laboratory (LSC)                  *
 * IC-UNICAMP                                         *
 * http://www.lsc.ic.unicamp.br                       *
 ******************************************************/
 
// Rodolfo editou aqui
//
const char *project_name="mips1";
const char *project_file="mips1.ac";
const char *archc_version="2.0beta1";
const char *archc_options="-abi -dy ";

#include  <systemc.h>
#include  "mips1.H"
#include  "ac_tlm_mem.h"
#include  "ac_tlm_bus.h"
#include  "ac_tlm_offloading.h"
#include  "ac_tlm_protocol.H"

using user::ac_tlm_mem;
using user::ac_tlm_bus;
using user::ac_tlm_offloading;

static mips1* mips1_proc1;
static mips1* mips1_proc2;
static mips1* mips1_proc3;
static mips1* mips1_proc4;
static mips1* mips1_proc5;
static mips1* mips1_proc6;
static mips1* mips1_proc7;
static mips1* mips1_proc8;


char **
duplicate_argv(int argc, char **argv) {
  char **new_argv = (char **) malloc(argc * sizeof(char *));
  for (int i = 0; i < argc; ++i) {
    new_argv[i] = strdup(argv[i]);
  }

  return new_argv;
}

ac_tlm_rsp wake_up_processor( const ac_tlm_req &request ) {
    ac_tlm_rsp response;

    if (request.addr != 0xFFFFFFFF) {
      response.status = ERROR;
      return response;
    }

    uint8_t mask = (request.data & 0xFF000000) >> 24;
    if (mask & 1) {// acordar processador 1
      mips1_proc1->ac_wait_sig = 0;
    }

    if (mask & (1 << 1)) {// acordar processador 2
      mips1_proc2->ac_wait_sig = 0;
    }
    
    if (mask & (1 << 2)) {// acordar processador 3
      mips1_proc3->ac_wait_sig = 0;
    }
    
    if (mask & (1 << 3)) {// acordar processador 4
      mips1_proc4->ac_wait_sig = 0;
    }
    
    if (mask & (1 << 4)) {// acordar processador 5
      mips1_proc5->ac_wait_sig = 0;
    }
    
    if (mask & (1 << 5)) {// acordar processador 6
      mips1_proc6->ac_wait_sig = 0;
    }
    
    if (mask & (1 << 6)) {// acordar processador 7
      mips1_proc7->ac_wait_sig = 0;
    }
    
    if (mask & (1 << 7)) {// acordar processador 8
      mips1_proc8->ac_wait_sig = 0;
    }

    response.status = SUCCESS;
    return response;
}

int sc_main(int ac, char *av[])
{

  //!  ISA simulator
  mips1_proc1 = new mips1("mips1");
  mips1_proc2 = new mips1("mips2");
  mips1_proc3 = new mips1("mips3");
  mips1_proc4 = new mips1("mips4");
  mips1_proc5 = new mips1("mips5");
  mips1_proc6 = new mips1("mips6");
  mips1_proc7 = new mips1("mips7");
  mips1_proc8 = new mips1("mips8");

  ac_tlm_mem mem("mem");
  ac_tlm_bus mem_bus("bus", wake_up_processor);
  ac_tlm_offloading offl("offloading");
  
#ifdef AC_DEBUG
  ac_trace("mips1_proc1.trace");
#endif 

  mips1_proc1->DM_port(mem_bus.target_export[0]);
  mips1_proc2->DM_port(mem_bus.target_export[1]);
  mips1_proc3->DM_port(mem_bus.target_export[2]);
  mips1_proc4->DM_port(mem_bus.target_export[3]);
  mips1_proc5->DM_port(mem_bus.target_export[4]);
  mips1_proc6->DM_port(mem_bus.target_export[5]);
  mips1_proc7->DM_port(mem_bus.target_export[6]);
  mips1_proc8->DM_port(mem_bus.target_export[7]);

  mem_bus.DM_port(mem.target_export);
  mem_bus.offloading_port(offl.target_export);
  
  mips1_proc1->init(ac, duplicate_argv(ac, av));
  mips1_proc2->init(ac, duplicate_argv(ac, av));
  mips1_proc3->init(ac, duplicate_argv(ac, av));
  mips1_proc4->init(ac, duplicate_argv(ac, av));
  mips1_proc5->init(ac, duplicate_argv(ac, av));
  mips1_proc6->init(ac, duplicate_argv(ac, av));
  mips1_proc7->init(ac, duplicate_argv(ac, av));
  mips1_proc8->init(ac, duplicate_argv(ac, av));
  cerr << endl;

  mips1_proc1->ac_wait_sig = 0; // bootstrap processor
  mips1_proc2->ac_wait_sig = 1;
  mips1_proc3->ac_wait_sig = 1;
  mips1_proc4->ac_wait_sig = 1;
  mips1_proc5->ac_wait_sig = 1;
  mips1_proc6->ac_wait_sig = 1;
  mips1_proc7->ac_wait_sig = 1;
  mips1_proc8->ac_wait_sig = 1;
  sc_start();

  mips1_proc1->PrintStat();
  cerr << endl;

#ifdef AC_STATS
  mips1_proc1->ac_sim_stats.time = sc_simulation_time();
  mips1_proc1->ac_sim_stats.print();
#endif 

#ifdef AC_DEBUG
  ac_close_trace();
#endif 

  int retval = mips1_proc1->ac_exit_status;
  delete mips1_proc1;
  delete mips1_proc2;
  delete mips1_proc3;
  delete mips1_proc4;
  delete mips1_proc5;
  delete mips1_proc6;
  delete mips1_proc7;
  delete mips1_proc8;

  return retval;
}
