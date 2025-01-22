`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/21/2023 03:55:12 PM
// Design Name: 
// Module Name: CarryLookaheadAdder_32b
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


module CarryLookaheadAdder_32b(s, c32, c31, a, b, c0);

    output [31:0]s;
    output c32, c31;
    input [31:0]a, b;
    input c0;
    
    wire c16;
    
    // CarryLookaheadAdder_16b       (s,        c16, c15, G, P, a,        b,        c0);
    CarryLookaheadAdder_16b bit0_15  (s[15:0],  c16,    ,  ,  , a[15:0],  b[15:0],  c0);
    CarryLookaheadAdder_16b bit16_31 (s[31:16], c32, c31,  ,  , a[31:16], b[31:16], c16);

endmodule
