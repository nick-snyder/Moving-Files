`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/25/2023 03:57:55 PM
// Design Name: 
// Module Name: stopwatch_control_unit
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


module stopwatch_control_unit(
    input start,
    input stop,
    input store,
    input reset,
    input newRecordFlag,
    input clk,
    output displayInputSel,
    output registerEN,
    output registerInputSel,
    output counterEN,
    output counterReset
    );
    
    reg [2:0] s;
    wire [2:0] n;
   
    stopwatch_state_transition_control sstc(
        .start(start),
        .stop(stop),
        .store(store),
        .reset(reset),
        .newRecordFlag(newRecordFlag),
        .s(s),
        .n(n)
     );
     
     stopwatch_output_control soc(
        .s(s),
        .displayInputSel(displayInputSel),
        .counterEN(counterEN),
        .registerEN(registerEN),
        .counterReset(counterReset),
        .registerInputSel(registerInputSel)
     );
     
    always @(posedge clk) s = n;
    
endmodule
