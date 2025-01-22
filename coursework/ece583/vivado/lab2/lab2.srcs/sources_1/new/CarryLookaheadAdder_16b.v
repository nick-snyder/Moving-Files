`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/21/2023 03:55:12 PM
// Design Name: 
// Module Name: CarryLookaheadAdder_16b
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


module CarryLookaheadAdder_16b(s, c16, c15, G, P, a, b, c0);

    output [15:0]s;
    output c16, c15, G, P;
    input [15:0]a, b;
    input c0;
    
    wire g3, g2, g1, g0, p3, p2, p1, p0, c3u, c2u, c1u;

    assign c15 = c3u;
    
    // CarryLookaheadUnit_4b   (c4,  c3,  c2,  c1,  G, P, g3, g2, g1, g0, p3, p2, p1, p0, c0);
    CarryLookaheadUnit_4b unit (c16, c3u, c2u, c1u, G, P, g3, g2, g1, g0, p3, p2, p1, p0, c0);
    
    // CarryLookaheadAdder_4b       (c4, c3, G,  P,  s,        c0,  a,        b);
    CarryLookaheadAdder_4b bit0_3   (  ,   , g0, p0, s[3:0],   c0,  a[3:0],   b[3:0]);
    CarryLookaheadAdder_4b bit4_7   (  ,   , g1, p1, s[7:4],   c1u, a[7:4],   b[7:4]);
    CarryLookaheadAdder_4b bit8_11  (  ,   , g2, p2, s[11:8],  c2u, a[11:8],  b[11:8]);
    CarryLookaheadAdder_4b bit12_15 (  ,   , g3, p3, s[15:12], c3u, a[15:12], b[15:12]);

endmodule
