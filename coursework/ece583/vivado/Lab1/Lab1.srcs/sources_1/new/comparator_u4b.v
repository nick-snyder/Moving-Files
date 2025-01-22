`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/06/2023 07:41:17 PM
// Design Name: 
// Module Name: comparator_u4b
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


module comparator_u4b(greater, equal, less, a, b);

    output greater, equal, less;
    input[0:3] a, b;
    
    wire g0, g1, g2, g3, e0, e1, e2, e3, l0, l1, l2, l3;
    
    comparator_u1b_dataflow bit0(g0, e0, l0, a[0], b[0]);
    comparator_u1b_dataflow bit1(g1, e1, l1, a[1], b[1]);
    comparator_u1b_dataflow bit2(g2, e2, l2, a[2], b[2]);
    comparator_u1b_dataflow bit3(g3, e3, l3, a[3], b[3]);
    
    wire i1, i2, i3, i4, i5, i6;
    
    assign i1 = e3 & g2;
    assign i2 = e3 & l2;
    assign i3 = e3 & e2 & g1;
    assign i4 = e3 & e2 & l1;
    assign i5 = e3 & e2 & e1 & g0;
    assign i6 = e3 & e2 & e1 & l0;
    
    assign greater = g0 | i1 | i3 | i5;
    assign equal = e0 & e1 & e2 & e3;
    assign less = l3 | i2 | i4 | i6;

endmodule
