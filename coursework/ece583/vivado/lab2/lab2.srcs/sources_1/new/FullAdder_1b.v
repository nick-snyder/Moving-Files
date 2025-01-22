`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/21/2023 03:55:12 PM
// Design Name: 
// Module Name: FullAdder_1b
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


module FullAdder_1b(s, carryOut, carryIn, a, b);

    output s, carryOut;
    input carryIn, a, b;
    
    assign s = a ^ b ^ carryIn;
    assign carryOut = a & b | carryIn & (a ^ b);

endmodule
