`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: UNH ECE
// Engineer: Nick Snyder
// 
// Create Date: 02/02/2023 11:23:31 PM
// Design Name: 2-1 mux
// Module Name: mux_behavioral
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


module mux_behavioral(out, s, a, b);

    output reg out;
    input s, a, b;
    
    always @(*)begin
    if (s)
        out = b;
    else
        out = a;
    end
    
endmodule
