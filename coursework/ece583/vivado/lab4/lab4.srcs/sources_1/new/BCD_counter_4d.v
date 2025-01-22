`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/28/2023 06:12:01 PM
// Design Name: 
// Module Name: BCD_counter_4d
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


module BCD_counter_4d(out, clk, enable, reset);

    output [15:0] out;
    input clk, enable, reset;
    
//    wire [3:0] out0_3, out4_7, out8_11, out12_15;
    wire CO_0, CO_1, CO_2, CO_3;
    
//    reg [19:0] timing = 5'h00000;
    
    // BCD_counter             (      out,  carryOut, clk,                      enable, reset);
    BCD_counter_4b counter_4b_0(  out[3:0],     CO_0, clk,                      enable, reset);
    BCD_counter_4b counter_4b_1(  out[7:4],     CO_1, clk,               CO_0 & enable, reset);
    BCD_counter_4b counter_4b_2( out[11:8],     CO_2, clk,        CO_0 & CO_1 & enable, reset);
    BCD_counter_4b counter_4b_3(out[15:12],     CO_3, clk, CO_0 & CO_1 & CO_2 & enable, reset);
    
//    always @(posedge clk) timing = timing + 1;
    
//    always @(*) out = {out12_15, out8_11, out4_7, out0_3};
    
endmodule