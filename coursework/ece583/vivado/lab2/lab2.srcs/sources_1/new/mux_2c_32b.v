`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/06/2023 08:29:35 PM
// Design Name: 
// Module Name: mux_2c_32b
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


module mux_2c_32b(out, s, a, b);

    output [31:0]out;
    input [31:0]a, b;
    input s;
    
    assign out = s ? b : a;

endmodule
