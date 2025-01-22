`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/21/2023 03:55:12 PM
// Design Name: 
// Module Name: CarryLookaheadAdder_4b
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


module CarryLookaheadAdder_4b(c4, c3, G, P, s, c0, a, b);

    output [3:0]s;
    output c4, c3, G, P;
    input [3:0]a, b;
    input c0;

    wire g3, g2, g1, g0, p3, p2, p1, p0, c3u, c2u, c1u;

    assign g0 = a[0] & b[0];
    assign p0 = a[0] | b[0];
    assign g1 = a[1] & b[1];
    assign p1 = a[1] | b[1];
    assign g2 = a[2] & b[2];
    assign p2 = a[2] | b[2];
    assign g3 = a[3] & b[3];
    assign p3 = a[3] | b[3];

    // CarryLookaheadUnit_4b   (c4, c3,  c2,  c1,  G, P, g3, g2, g1, g0, p3, p2, p1, p0, c0);
    CarryLookaheadUnit_4b unit (c4, c3u, c2u, c1u, G, P, g3, g2, g1, g0, p3, p2, p1, p0, c0);

    // FullAdder_1b   (s,   carryOut, carryIn, a,    b);
    FullAdder_1b bit0 (s[0],        , c0,      a[0], b[0]);
    FullAdder_1b bit1 (s[1],        , c1u,     a[1], b[1]);
    FullAdder_1b bit2 (s[2],        , c2u,     a[2], b[2]);
    FullAdder_1b bit3 (s[3],      c3, c3u,     a[3], b[3]);
    
endmodule
