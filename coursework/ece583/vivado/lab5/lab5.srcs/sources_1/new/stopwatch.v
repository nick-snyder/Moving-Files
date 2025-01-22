`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/25/2023 04:45:22 PM
// Design Name: 
// Module Name: stopwatch
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module stopwatch(
    input start,
    input stop,
    input store,
    input reset,
    input clk,
    output [3:0] anode,
    output [6:0] segment, 
    output led_start,
    output led_stop,
    output led_store,
    output led_reset
    );
    
    reg newRecordFlag;
    reg [15:0] r0, r1;
    reg [19:0] timing = 5'h00000;
    wire [15:0] bcd_out, w0;
    
    stopwatch_control_unit scu(
        .start(start), 
        .stop(stop), 
        .store(store), 
        .reset(reset), 
        .newRecordFlag(newRecordFlag), 
        .clk(timing[19]), 
        .displayInputSel(displayInputSel), 
        .registerEN(registerEN), 
        .registerInputSel(registerInputSel), 
        .counterEN(counterEN), 
        .counterReset(counterReset)
    );
    
    four_digit_binary_coded_decimal_counter bcd(
        .clk(timing[19]),
        .enable(counterEN),
        .reset(counterReset),
        .out(bcd_out)
    );

    display_control dc(
        .clk(clk),
        .in(r2),
        .segment(segment),
        .anode(anode)
    );
    
    sixteen_bit_parallel_load_register plr(
        .clk(timing[19]),
        .enable(registerEN),
        .reset(),
        .in(r0),
        .out(w0)
    );
    
    always @(posedge clk)
    begin
        // 16-bit mux
        if (registerInputSel == 1) r0 = 16'h9999;
        else if (registerInputSel == 0) r0 = bcd_out;
        
        // 16-bit mux
        if (displayInputSel == 1) r1 = w0;
        else if (displayInputSel == 0) r1 = bcd_out;
        
        // 16-bit comparator
        if (bcd_out < w0) newRecordFlag = 1;
        
        // clock
        timing = timing + 1;
    end
    
    assign led_start = start;
    assign led_stop = stop;
    assign led_store = store;
    assign led_reset = reset;
    
endmodule
