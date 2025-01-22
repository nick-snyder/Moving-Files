`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/27/2023 10:28:28 PM
// Design Name: 
// Module Name: testbench_stopwatch_control_unit
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


module testbench_stopwatch_control_unit;

    /*
    input start,
    input stop,
    input store,
    input reset,
    input newRecordFlag,
    input clk,
    output displayInputSel,
    output registerEn,
    output registerInputSel,
    output counterEn,
    output counterReset
    */

//    reg start;
//    reg stop;
//    reg store;
//    reg reset;
//    reg newRecordFlag;
    reg clk = 0;
    
    wire displayInputSel;
    wire registerEN;
    wire registerInputSel;
    wire counterEN;
    wire counterReset;
    
    stopwatch_control_unit scu(
        .start(in[0]), 
        .stop(in[1]), 
        .store(in[2]), 
        .reset(in[3]), 
        .newRecordFlag(in[4]), 
        .clk(clk), 
        .displayInputSel(displayInputSel), 
        .registerEN(registerEN), 
        .registerInputSel(registerInputSel), 
        .counterEN(counterEN), 
        .counterReset(counterReset)
    );
    
    reg [4:0] in = 5'b00000;
    
    initial
    begin
        #50 in = in + 1;
        while (in != 0)
        begin
            #50 in = in + 1;
        end
        #50 in = in - 1;
        while (in != 0)
        begin
            #50 in = in - 1;
        end
        $finish;
    end
    
    always @(*)
    begin
        #10 clk <= ~clk;
//        in <= {start, stop, store, reset, newRecordFlag};
    end

endmodule
