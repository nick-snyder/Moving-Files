`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/21/2023 03:55:12 PM
// Design Name: 
// Module Name: CarryLookaheadUnit_4b
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


module CarryLookaheadUnit_4b(c4, c3, c2, c1, G, P, g3, g2, g1, g0, p3, p2, p1, p0, c0);

    output c4, c3, c2, c1, G, P;
    input g3, g2, g1, g0, p3, p2, p1, p0, c0;

    assign P = p3 & p2 & p1 & p0;
    assign G = g3 | (p3 & g2) | (p3 & p2 & g1) | (p3 & p2 & p1 & g0);
    assign c1 = g0 | (p0 & c0);
    assign c2 = g1 | (p1 & g0) | (p1 & p2 & c0);
    assign c3 = g2 | (p2 & g1) | (p2 & p1 & g0) | (p2 & p1 & p0 & c0);
    assign c4 = g3 | (p3 & g2) | (p3 & p2 & g1) | (p3 & p2 & p1 & g0) | (p3 & p2 & p1 & p0 & c0);

endmodule
