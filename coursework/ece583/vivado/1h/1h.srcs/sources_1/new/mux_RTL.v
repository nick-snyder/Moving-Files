`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: UNH ECE
// Engineer: Nick Snyder
// 
// Create Date: 02/02/2023 11:23:31 PM
// Design Name: 2-1 mux
// Module Name: mux_RTL
// Project Name: homework1
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


module mux_RTL(out, s, a, b);

    output out;
    input s, a, b;
    
    wire t1, t2, sbar;
    
    assign sbar = ~s;
    assign t1 = b & s;
    assign t2 = a & sbar;
    assign out = t1 | t2;
    
endmodule
