`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/28/2023 06:12:01 PM
// Design Name: 
// Module Name: parallel_load_register_16b
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


module parallel_load_register_16b(out, reset, clk, enable, in);

    output reg [15:0] out;
    input [15:0] in;
    input reset, clk, enable;
    
    always @(posedge clk & enable) begin
        if (reset) begin
            out = 0;
        end
        else begin
            out = in;
        end 
    end
endmodule
