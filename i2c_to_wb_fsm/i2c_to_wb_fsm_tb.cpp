#include <systemc.h>
#include "i2c_to_wb_fsm.h"

/*void applyInputSignals(int inputVector)
{
    int inputBit = 0;

    for (int i = 0; i < 5; i++) 
    {
        inputBit = inputVector %10;
        inputVector = inputVector / 10;
        
        switch(i)
        {
            case 0:
            {
                i2c_data_rise = inputBit;
                break;
            }
            case 1:
            {
                i2c_data_fall = inputBit;
                break;
            }
            case 2:
            {
                i2c_data = inputBit;
                break;
            }
            case 3:
            {
                i2c_clk_rise = inputBit;
                break;
            }
            case 4:
            {
                i2c_clk_fall = inputBit;
                break;
            }
            case 5:
            {
                i2c_r_w_bit = inputBit;
                break;
            }
            case 6:
            {
                i2c_ack_out = inputBit;
                break;
            }
            case 7:
            {
                wb_rst_i = inputBit;
                break;
            }
            case 8:
            {
                i2c_clk = inputBit;
                break;
            }
            case 9:
            {
                wb_clk_i = inputBit;
                break;
            }
        }

    }
}*/

int sc_main (int argc, char* argv[]) {
    sc_signal<bool>   i2c_data_rise;
    sc_signal<bool>   i2c_data_fall;
    sc_signal<bool>   i2c_clk_rise;
    sc_signal<bool>   i2c_clk_fall;    
    sc_signal<bool>   i2c_clk;
    //sc_signal<bool>   start_detected;
   // sc_signal<bool>   stop_detected;
    sc_signal<bool>   wb_rst_i;
    //sc_signal<bool>   xmt_byte_done;
    sc_signal<sc_bv<8>> state_out;
    //sc_signal<fsm_state> nxt_st;
    //sc_signal<sc_int<4>> bit_count;
    //sc_signal<bool> tip_ack;
    sc_signal<bool> i2c_ack_done;
    sc_signal<bool> i2c_ack_out;
    sc_signal<bool>  i2c_data;
    sc_signal<bool> i2c_r_w_bit;
    sc_signal<bool>  tip_addr_ack;
    sc_signal<bool> tip_addr_byte;
    sc_signal<bool> tip_read_byte;
    sc_signal<bool> tip_write_byte;
    sc_signal<bool> tip_wr_ack;
    sc_signal<bool> tip_rd_ack;
    sc_signal<bool> i2c_error;

    //sc_clock clock("clock", 10, 0.5, 1, false);
    sc_clock wb_clk_i("wb_clk_i", 2, SC_NS ,0.5);
    //sc_clock i2c_clk("i2c_clk", 2, SC_NS ,0.5);

    // DUT connections
    i2c_to_wb_fsm i2c("I2C");
        i2c.i2c_data_rise(i2c_data_rise);
        i2c.i2c_data_fall(i2c_data_fall);
        i2c.i2c_clk(i2c_clk);
       // i2c.start_detected(start_detected);
       // i2c.stop_detected(stop_detected);
        i2c.wb_rst_i(wb_rst_i);
        i2c.wb_clk_i(wb_clk_i);
        //i2c.nxt_st(nxt_st);
        i2c.state_out(state_out);
        i2c.i2c_clk_rise(i2c_clk_rise);
        i2c.i2c_clk_fall(i2c_clk_fall);
        //i2c.xmt_byte_done(xmt_byte_done);
        //i2c.bit_count(bit_count);
        //i2c.tip_ack(tip_ack);
        i2c.i2c_ack_done(i2c_ack_done);
        i2c.i2c_ack_out(i2c_ack_out);
        i2c.i2c_data(i2c_data);
        i2c.i2c_r_w_bit(i2c_r_w_bit);
        i2c.tip_addr_byte(tip_addr_byte);
        i2c.tip_addr_ack(tip_addr_ack);
        i2c.tip_read_byte(tip_read_byte);
        i2c.tip_write_byte(tip_write_byte);  
        i2c.tip_wr_ack(tip_wr_ack);      
        i2c.tip_rd_ack(tip_rd_ack);
        i2c.i2c_error(i2c_error);

    // Open VCD file
    sc_trace_file *wf = sc_create_vcd_trace_file("fsm");
    wf->set_time_unit(1, SC_NS);

    // Dump signals
    i2c.tracing(wf);

    // ***start sim @ 0s
    sc_start(0,SC_NS);
    cout << "@" << sc_time_stamp;

    // Initialize all variables
    i2c_data_rise = 0;
    i2c_data_fall = 0;
    i2c_data = 0;
    i2c_clk_rise = 0;
    i2c_clk_fall = 0;
    i2c_r_w_bit = 0;
    i2c_ack_out = 0;
    wb_rst_i = 1;
    i2c_clk = 0; 

    // expected outputs
    /* 
    i2c_ack_done = 0
    tip_addr_byte = 0
    tip_read_byte = 0
    tip_write_byte = 0
    tip_wr_ack = 0
    tip_rd_ack = 0
    tip_addr_ack = 0
    i2c_error = 0
    state_out = 00000001 (idle)
    */

    // ***sim @ 10s
    sc_start(10,SC_NS);

    // apply signals
    i2c_data_rise = 0;
    i2c_data_fall = 1;      
    i2c_data = 0;
    i2c_clk_rise = 0;
    i2c_clk_fall = 0;
    i2c_r_w_bit = 0;
    i2c_ack_out = 0;
    wb_rst_i = 0;
    i2c_clk = 1;        // start_detected=1

    // expected outputs
    /* 
    i2c_ack_done = 0
    tip_addr_byte = 1
    tip_read_byte = 0
    tip_write_byte = 1
    tip_wr_ack = 0
    tip_rd_ack = 0
    tip_addr_ack = 0
    i2c_error = 0
    state_out = 00000010 (addr_byte)
    */

    // ***sim @ 30s
    sc_start(20,SC_NS);

    // apply signals
    i2c_data_rise = 0;
    i2c_data_fall = 0;      
    i2c_data = 0;
    i2c_clk_rise = 1;
    i2c_clk_fall = 0;
    i2c_r_w_bit = 0;
    i2c_ack_out = 0;
    wb_rst_i = 0;
    i2c_clk = 1;        

    // expected outputs
    /* 
    i2c_ack_done = 0
    tip_addr_byte = 0
    tip_read_byte = 0
    tip_write_byte = 0
    tip_wr_ack = 1
    tip_rd_ack = 0
    tip_addr_ack = 1
    i2c_error = 0
    state_out = 00000100 (addr_ack)
    */

    // ***sim @ 50ns
    sc_start(20,SC_NS);

   // apply signals
    i2c_data_rise = 0;
    i2c_data_fall = 0;      
    i2c_data = 0;
    i2c_clk_rise = 1;
    i2c_clk_fall = 1;
    i2c_r_w_bit = 0;
    i2c_ack_out = 0;
    wb_rst_i = 0;
    i2c_clk = 1;        

    // expected outputs
    /* 
    i2c_ack_done = 1
    tip_addr_byte = 0
    tip_read_byte = 0
    tip_write_byte = 1
    tip_wr_ack = 0
    tip_rd_ack = 0
    tip_addr_ack = 0
    i2c_error = 0
    state_out = 00001000 (write)
    */

    // ***sim @ 90ns
    sc_start(40,SC_NS);

   // apply signals
    /*i2c_data_rise = 0;
    i2c_data_fall = 1;      
    i2c_data = 0;
    i2c_clk_rise = 1;
    i2c_clk_fall = 1;
    i2c_r_w_bit = 0;
    i2c_ack_out = 0;
    wb_rst_i = 0;
    i2c_clk = 1; */       

    // expected outputs
    /* 
    i2c_ack_done = 1
    tip_addr_byte = 1
    tip_read_byte = 0
    tip_write_byte = 1
    tip_wr_ack = 0
    tip_rd_ack = 0
    tip_addr_ack = 0
    i2c_error = 0
    state_out = 00000010 (addr_byte)
    */    



    sc_start(20,SC_NS);
    
    i2c_ack_done=0;
    i2c_clk_rise=1;
    // ->state=wr_ack, -> tip_wr_ack=1

    sc_start(20,SC_NS);

    i2c_ack_done=1;
    // -> state = write - > tip_write_byte=1

    sc_start(20,SC_NS);
    i2c_data_rise = 1;  // stop_detected=1
    i2c_data_fall = 0;
    i2c_clk_rise=0;
    // -> state = idle

    sc_start(20,SC_NS);

    cout << "@" << sc_time_stamp() <<" Terminating simulation\n" << endl;
    sc_close_vcd_trace_file(wf);
    return 0;// Terminate simulation
}