// ----------------------------------------------------------------------------
// SystemC Testbench Body
//
//    HLS version: 10.4b/841621 Production Release
//       HLS date: Thu Oct 24 17:20:07 PDT 2019
//  Flow Packages: HDL_Tcl 8.0a, SCVerify 10.4
//
//   Generated by: mdk@mdk-FX504
// Generated date: Fri Jan 03 06:36:57 PST 2020
//
// ----------------------------------------------------------------------------
// 
// -------------------------------------
// mc_testbench
// SCVerify mc_testbench SC_MODULE
// -------------------------------------
// 
#include "mc_testbench.h"
#include <mc_testbench_util.h>
#include <mc_simulator_extensions.h>

mc_testbench* mc_testbench::that;
bool testbench::enable_idle_sync_mode;
unsigned short testbench::idle_sync_stable_cycles;
void testbench::set_enable_stalls(bool flag) { mc_testbench::set_enable_stalls(flag); }
void testbench::reset_request() { mc_testbench::that->reset_request(); }
void mc_testbench_reset_request() { mc_testbench::that->reset_request(); }
bool testbench::dst_ignore;
void mc_testbench_dst_skip(bool v) { testbench::dst_skip = v; }
bool testbench::dst_skip;
bool testbench::dst_skip_quiet;
bool testbench::dst_skip_once;
bool testbench::dst_skip_noerr;
int  testbench::dst_array_comp_first;
int  testbench::dst_array_comp_last;
bool testbench::dst_use_mask;
ac_fixed<20, 8, true, AC_TRN, AC_WRAP > testbench::dst_output_mask;
mc_wait_ctrl testbench::dst_wait_ctrl;
bool testbench::src_ignore;
void mc_testbench_src_skip(bool v) { testbench::src_skip = v; }
bool testbench::src_skip;
bool testbench::src_skip_quiet;
bool testbench::src_skip_once;
bool testbench::src_skip_noerr;
int  testbench::src_array_comp_first;
int  testbench::src_array_comp_last;
mc_wait_ctrl testbench::src_wait_ctrl;
#ifndef CCS_SCVERIFY_USE_CCS_BLOCK
extern "C++" void DCT( ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > > &dst,  ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > > &src);
#endif
#ifndef CCS_SCVERIFY_USE_CCS_BLOCK
void testbench::exec_DCT( ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > > &dst,  ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > > &src) {
   return mc_testbench::exec_DCT(dst, src);
}
#endif

// ============================================
// Function: wait_for_idle_sync
// --------------------------------------------

void mc_testbench::wait_for_idle_sync()
{
   if (testbench::enable_idle_sync_mode) {
      std::cout << "mc_testbench STOPPING   @ " << sc_time_stamp() << std::endl;
      that->cpp_testbench_active.write(false);
      while (that->design_is_idle.read())  that->wait(that->design_is_idle.value_changed_event());
      while (!that->design_is_idle.read()) that->wait(that->design_is_idle.value_changed_event());
      that->cpp_testbench_active.write(true);
      std::cout << "mc_testbench CONTINUING @ " << sc_time_stamp() << std::endl;
   } else {
      that->cpp_testbench_active.write(true);
   }
}
// ============================================
// Function: set_enable_stalls
// --------------------------------------------

void mc_testbench::set_enable_stalls(bool flag)
{
   if (flag) {
     std::cout << "Enabling STALL_FLAG toggling" << std::endl;
     that->enable_stalls.write(sc_dt::Log_1);
   } else {
     std::cout << "Disabling STALL_FLAG toggling" << std::endl;
     that->enable_stalls.write(sc_dt::Log_0);
   }
}
// ============================================
// Function: reset_request
// --------------------------------------------

void mc_testbench::reset_request()
{
   reset_request_event.notify(0,SC_NS);
}
// ============================================
// Function: capture_dst
// --------------------------------------------

void mc_testbench::capture_dst( ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > > &dst)
{
   static mc_golden_info< ac_fixed<20, 8, true, AC_TRN, AC_WRAP >, ac_fixed<20, 8, true, AC_TRN, AC_WRAP > > dst_tmp(testbench::dst_ignore, false, dst_iteration_count);
   dst_tmp._ignore = testbench::dst_ignore;
   dst_tmp._iteration = dst_iteration_count;
   static int last_j_dst_out = 0;
   if (_capture_dst)
   {
      int cur_iter = dst_capture_count;
      ++dst_iteration_count;
      unsigned int chan_factor = 1;
      unsigned int ccs_scv_i,ccs_scv_j;
      ccs_scv_i = remaining_dst_golden;
      while (ccs_scv_i < dst.ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > >::debug_size()) {
         for (ccs_scv_j = last_j_dst_out; ccs_scv_j < chan_factor; ccs_scv_j++,ccs_scv_i++) {
            if (ccs_scv_i < dst.ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > >::debug_size()) {
               dst_tmp._data = dst.ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > >::chan[ccs_scv_i];
            } else {
               break;
            }
         }
         if (ccs_scv_j == chan_factor) {
            dst_golden.put(dst_tmp);
            last_j_dst_out = 0;
            dst_capture_count += chan_factor;
         } else {
            last_j_dst_out = ccs_scv_j;
         }
      }
      mc_testbench_util::process_wait_ctrl("dst",testbench::dst_wait_ctrl,ccs_wait_ctrl_dst.operator->(),cur_iter,dst_capture_count,1);
      testbench::dst_use_mask = false;
   }
   testbench::dst_ignore = false;
   testbench::dst_skip = false;
}
// ============================================
// Function: capture_src
// --------------------------------------------

void mc_testbench::capture_src( ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > > &src)
{
   static ac_fixed<20, 8, true, AC_TRN, AC_WRAP > src_tmp;
   static int last_j_src_in = 0;
   if (src_iteration_count == wait_cnt)
      wait_on_input_required();
   if (_capture_src && !testbench::src_ignore)
   {
      int cur_iter = src_capture_count;
      ++src_iteration_count;
      unsigned int chan_factor = 1;
      unsigned int ccs_scv_i,ccs_scv_j;
      ccs_scv_i = remaining_ccs_src;
      while (ccs_scv_i < src.ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > >::debug_size()) {
         for (ccs_scv_j = last_j_src_in; ccs_scv_j < chan_factor; ccs_scv_j++,ccs_scv_i++) {
            if (ccs_scv_i < src.ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > >::debug_size()) {
               src_tmp = src.ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > >::chan[ccs_scv_i];
            } else {
               break;
            }
         }
         if (ccs_scv_j == chan_factor) {
            ccs_src->put(src_tmp);
            last_j_src_in = 0;
            src_capture_count += chan_factor;
         } else {
            last_j_src_in = ccs_scv_j;
         }
      }
      mc_testbench_util::process_wait_ctrl("src",testbench::src_wait_ctrl,ccs_wait_ctrl_src.operator->(),cur_iter,src_capture_count,1);
   }
   testbench::src_ignore = false;
}
// ============================================
// Function: wait_on_input_required
// --------------------------------------------

void mc_testbench::wait_on_input_required()
{
   ++wait_cnt;
   wait(SC_ZERO_TIME); // get fifos a chance to update
   while (atleast_one_active_input) {
      if (_capture_src && ccs_src->used() == 0) return;
      that->cpp_testbench_active.write(false);
      wait(ccs_src->ok_to_put());
      that->cpp_testbench_active.write(true);
   }
}
// ============================================
// Function: capture_IN
// --------------------------------------------

void mc_testbench::capture_IN( ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > > &dst,  ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > > &src)
{
   that->remaining_dst_golden =  dst.ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > >::debug_size();
   that->capture_src(src);
}
// ============================================
// Function: capture_OUT
// --------------------------------------------

void mc_testbench::capture_OUT( ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > > &dst,  ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > > &src)
{
   that->capture_dst(dst);
   that->remaining_ccs_src =  src.ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > >::debug_size();
   if (testbench::enable_idle_sync_mode && that->remaining_ccs_src != 0) {
      cout << "Warning: Testbench input channel 'src' not empty. Remaining size: " << that->remaining_ccs_src << endl;
   }
}
// ============================================
// Function: exec_DCT
// --------------------------------------------

void mc_testbench::exec_DCT( ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > > &dst,  ac_channel<ac_fixed<20, 8, true, AC_TRN, AC_WRAP > > &src)
{
   #ifndef CCS_SCVERIFY_USE_CCS_BLOCK
   that->cpp_testbench_active.write(true);
   capture_IN(dst, src);
   DCT(dst, src);
   // throttle ac_channel based on number of calls to chan::size() or chan::empty() or chan::nb_read() (but not chan::available()) 
   if (1) {
      int cnt=0;
      if (cnt) std::cout << "mc_testbench.cpp: CONTINUES @ " << sc_time_stamp() << std::endl;
      if (cnt) that->cpp_testbench_active.write(true);
   }
   capture_OUT(dst, src);
   #else
   #endif
}
// ============================================
// Function: start_of_simulation
// --------------------------------------------

void mc_testbench::start_of_simulation()
{
   set_enable_stalls(false);
}
// ============================================
// Function: end_of_simulation
// --------------------------------------------

void mc_testbench::end_of_simulation()
{
   if (!_checked_results) {
      SC_REPORT_INFO(name(), "Simulation ran into deadlock");
      check_results();
   }
}
// ============================================
// Function: check_results
// --------------------------------------------

void mc_testbench::check_results()
{
   if (_checked_results) return;
   _checked_results = true;
   cout<<endl;
   cout<<"Checking results"<<endl;
   if (main_exit_code) _failed = true;
   int _num_outputs_checked = 0;
   bool _has_capture_counts = false;
   std::ostringstream mctb_msg;
   
   if (!_capture_dst) {
      cout<<"'dst' - warning, output was optimized away"<<endl;
   } else {
      _num_outputs_checked++;
      _failed |= dst_comp->check_results(dst_capture_count,testbench::dst_skip_noerr);
      _has_capture_counts |= !!(dst_capture_count);
   }
   cout<<endl;
   if (_num_outputs_checked == 0) {
      cout<<"Error: All outputs were optimized away. No output values were compared."<<endl;
      _failed = _failed || (_num_outputs_checked == 0);
   }
   if (!_has_capture_counts) {
      cout<<"Error: Nothing to compare, all output capture counts are zero."<<endl;
      _failed = true;
   }
   if (main_exit_code) cout << "Error: C++ Testbench 'main()' returned a non-zero exit code ("<<main_exit_code<<"). Check your testbench." <<endl;
   mctb_msg.clear();
   if (_failed) mctb_msg << "Simulation FAILED";
   else         mctb_msg << "Simulation PASSED";
   mctb_msg << " @ " << sc_time_stamp();
   SC_REPORT_INFO(this->name(), mctb_msg.str().c_str());
}
// ============================================
// Function: failed
// --------------------------------------------

bool mc_testbench::failed()
{
   return _failed;
}
// ============================================
// Function: set_failed
// --------------------------------------------

void mc_testbench::set_failed(bool fail)
{
   _failed = fail;
}
// ---------------------------------------------------------------
// Process: SC_METHOD wait_for_end
// Static sensitivity: sensitive << clk.pos() << testbench_end_event;

void mc_testbench::wait_for_end() {
   // If run() has not finished, we do nothing here
   if (!testbench_ended) return;
   // check for completed outputs
   if (dst_comp->get_compare_count() < dst_capture_count) {testbench_end_event.notify(1,SC_NS); return;}
   // If we made it here, all outputs have flushed. Check the results
   SC_REPORT_INFO(name(), "Simulation completed");
   check_results();
   sc_stop();
}
// ---------------------------------------------------------------
// Process: SC_THREAD run
// Static sensitivity: 

void mc_testbench::run() {
   testbench::enable_idle_sync_mode = false;
   testbench::idle_sync_stable_cycles = 1;
   testbench::dst_ignore = false;
   testbench::dst_skip = false;
   testbench::dst_skip_quiet = false;
   testbench::dst_skip_once = false;
   testbench::dst_skip_noerr = false;
   testbench::dst_array_comp_first = -1;
   testbench::dst_array_comp_last = -1;
   testbench::dst_use_mask = false;
   testbench::dst_output_mask = ~0;
   testbench::dst_wait_ctrl.clear();
   dst_capture_count = 0;
   dst_iteration_count = 0;
   testbench::src_ignore = false;
   testbench::src_skip = false;
   testbench::src_skip_quiet = false;
   testbench::src_skip_once = false;
   testbench::src_skip_noerr = false;
   testbench::src_array_comp_first = -1;
   testbench::src_array_comp_last = -1;
   testbench::src_wait_ctrl.clear();
   src_capture_count = 0;
   src_iteration_count = 0;
   testbench testbench_inst(sc_argc(), sc_argv());
   main_exit_code = testbench_inst.main();
   cout<<"Info: Execution of user-supplied C++ testbench 'main()' has completed with exit code = " << main_exit_code << endl;
   cout<<endl;
   cout<<"Info: Collecting data completed"<<endl;
   cout<<"   captured "<<dst_capture_count<<" values of dst"<<endl;
   cout<<"   captured "<<src_capture_count<<" values of src"<<endl;
   testbench_ended = true;
   testbench_end_event.notify(SC_ZERO_TIME);
}
#ifdef CCS_SCVERIFY_USE_CCS_BLOCK
#include "ccs_block_macros.cpp"
#endif