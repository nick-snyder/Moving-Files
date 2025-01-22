`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/25/2023 09:35:52 PM
// Design Name: 
// Module Name: testbench_clk_divider
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


module testbench_clk_divider;

    reg clk_in = 0;
    wire clk_out;

    clk_divider cd(
        .clk_in(clk_in),
        .clk_out(clk_out)
    );
    
    always #10 clk_in = ~clk_in;
    initial
    begin
        #10000000;
        $finish;
    end

endmodule
