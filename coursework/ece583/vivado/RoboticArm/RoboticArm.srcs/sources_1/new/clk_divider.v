`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/25/2023 07:46:18 PM
// Design Name: 
// Module Name: clk_divider
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


module clk_divider(
    input wire clk_in,
    output reg clk_out
    );
    
    reg [22:0] counter = 0;
    parameter div = 30;
    
    initial clk_out = 1;
    
    always @(posedge clk_in)
    begin
        if (counter == div)
        begin
            counter <= 0;
            clk_out <= ~clk_out;
        end
        else
        begin
            counter <= counter + 1;
        end
    end
endmodule
