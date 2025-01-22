`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/04/2023 12:04:04 AM
// Design Name: 
// Module Name: sixteen_bit_parallel_load_register
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


module sixteen_bit_parallel_load_register(
    input clk,
    input enable,
    input reset,
    input [15:0] in,
    output reg [15:0] out
    );
    
    always @(posedge clk & enable) 
    begin
        if (reset) out = 0;
        else out = in;
    end
endmodule
