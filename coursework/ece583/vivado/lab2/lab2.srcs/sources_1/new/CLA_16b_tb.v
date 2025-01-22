`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/06/2023 10:17:43 PM
// Design Name: 
// Module Name: CLA_16b_tb
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


module CLA_16b_tb;

        // Inputs
    reg [15:0] a, b;
    reg c0;
    
    // Outputs
    wire [15:0] s;
    wire c16, c15, G, P;
    
    // Instantiate the module
    CarryLookaheadAdder_16b uut(s, c16, c15, G, P, a, b, c0);
    
    // Clock
    reg clk;
    initial clk = 0;
    always #5 clk = ~clk;
    
    // Testcase 1
    initial begin
        a = 16'b0000000000000000;
        b = 16'b0000000000000000;
        c0 = 0;
        #10;
        if (s !== 16'b0000000000000000) $display("Testcase 1 failed!");
        if (c16 !== 0) $display("Testcase 1 failed!");
        if (c15 !== 0) $display("Testcase 1 failed!");
        if (G !== 0) $display("Testcase 1 failed!");
        if (P !== 1) $display("Testcase 1 failed!");
    end
    
    // Testcase 2
    initial begin
        a = 16'b0111111111111111;
        b = 16'b0000000000000001;
        c0 = 0;
        #10;
        if (s !== 16'b1000000000000000) $display("Testcase 2 failed!");
        if (c16 !== 0) $display("Testcase 2 failed!");
        if (c15 !== 1) $display("Testcase 2 failed!");
        if (G !== 1) $display("Testcase 2 failed!");
        if (P !== 0) $display("Testcase 2 failed!");
    end
    
    // Testcase 3
    initial begin
        a = 16'b0111111111111111;
        b = 16'b0000000000000001;
        c0 = 1;
        #10;
        if (s !== 16'b1000000000000001) $display("Testcase 3 failed!");
        if (c16 !== 0) $display("Testcase 3 failed!");
        if (c15 !== 1) $display("Testcase 3 failed!");
        if (G !== 1) $display("Testcase 3 failed!");
        if (P !== 0) $display("Testcase 3 failed!");
    end
    
    // Testcase 4
    initial begin
        a = 16'b0111111111111111;
        b = 16'b1111111111111111;
        c0 = 0;
        #10;
        if (s !== 16'b1111111111111110) $display("Testcase 4 failed!");
        if (c16 !== 1) $display("Testcase 4 failed!");
        if (c15 !== 0) $display("Testcase 4 failed!");
        if (G !== 0) $display("Testcase 4 failed!");
        if (P !== 1) $display("Testcase 4 failed!");
    end

endmodule
