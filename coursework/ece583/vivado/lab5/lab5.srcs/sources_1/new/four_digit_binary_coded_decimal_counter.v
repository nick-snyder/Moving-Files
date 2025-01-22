`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/03/2023 11:47:33 PM
// Design Name: 
// Module Name: four_digit_binary_coded_decimal_counter
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


module four_digit_binary_coded_decimal_counter(
    input clk,
    input enable,
    input reset,
    output [15:0] out
    );
    
    wire CO_0, CO_1, CO_2, CO_3;
    
    // four_bit_binary_coded_decimal_counter(clk,                      enable, reset, carryOut, out);
    four_bit_binary_coded_decimal_counter d0(clk,                      enable, reset,     CO_0, out[3:0]);
    four_bit_binary_coded_decimal_counter d1(clk,               CO_0 & enable, reset,     CO_1, out[7:4]);
    four_bit_binary_coded_decimal_counter d2(clk,        CO_0 & CO_1 & enable, reset,     CO_2, out[11:8]);
    four_bit_binary_coded_decimal_counter d3(clk, CO_0 & CO_1 & CO_2 & enable, reset,     CO_3, out[15:12]);
    
endmodule
