`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/02/2023 04:42:21 PM
// Design Name: 
// Module Name: stopwatch_state_transition_control
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


module stopwatch_state_transition_control(
    input start,
    input stop,
    input store,
    input reset,
    input newRecordFlag,
    input [2:0] s,
    output reg [2:0] n
    );
    
    always @(*)
    begin
        n[0] = (~start & ~reset & ~newRecordFlag & s[0]) | 
               (~start & ~reset & ~s[1] & s[0]) | 
               (~store & ~reset & s[1] & s[0]) | 
               (~reset & s[2] & s[0]) | 
               (reset & s[2] & s[1]) | 
               (~start & store & ~reset & ~s[0]) | 
               (stop & ~reset & ~newRecordFlag) | 
               (stop & ~reset & ~s[1]) | 
               (stop & ~reset & ~s[0]) | 
               (start & ~reset & ~s[1] & ~s[0]) | 
               (start & ~stop & ~reset & s[1] & s[0]) | 
               (start & ~reset & s[2]);
        n[1] = (~start & ~store & s[1]) | 
               reset | 
               (stop & ~store) | 
               (start & ~stop & ~s[2] & ~s[1] & s[0]) | 
               (start & ~stop & ~s[2] & s[1] & ~s[0]);
        n[2] = (~start & ~stop & s[2]) | 
               reset | 
               (~start & store) | 
               (stop & store);
    end   
endmodule
