`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/21/2023 03:55:12 PM
// Design Name: 
// Module Name: RippleCarryAdderSubtractor_8b
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


module RippleCarryAdderSubtractor_8b(s, carryOut, overflow, sub, a, b);

    output [7:0]s;
    output carryOut, overflow;
    input [7:0]a, b;
    input sub;
    
    wire in0, in1, in2, in3, in4, in5, in6, in7;
    wire carry0, carry1, carry2, carry3, carry4, carry5, carry6, carry7;
    
    assign in0 = b[0] ^ sub;
    assign in1 = b[1] ^ sub;
    assign in2 = b[2] ^ sub;
    assign in3 = b[3] ^ sub;
    assign in4 = b[4] ^ sub;
    assign in5 = b[5] ^ sub;
    assign in6 = b[6] ^ sub;
    assign in7 = b[7] ^ sub;
    
    assign carry0 = 1'b0 ^ sub;
    
    FullAdder_1b bit0(s[0], carry1, carry0, a[0], in0);
    FullAdder_1b bit1(s[1], carry2, carry1, a[1], in1);
    FullAdder_1b bit2(s[2], carry3, carry2, a[2], in2);
    FullAdder_1b bit3(s[3], carry4, carry3, a[3], in3);
    FullAdder_1b bit4(s[4], carry5, carry4, a[4], in4);
    FullAdder_1b bit5(s[5], carry6, carry5, a[5], in5);
    FullAdder_1b bit6(s[6], carry7, carry6, a[6], in6);
    FullAdder_1b bit7(s[7], carry8, carry7, a[7], in7);
    
    assign carryOut = carry8;
    assign overflow = carry7 ^ carry8;
    
endmodule
