`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/06/2023 10:20:02 PM
// Design Name: 
// Module Name: CLA_32b_tb
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


module CLA_32b_tb();

        reg [31:0] a, b;
    reg c0;
    wire [31:0] s;
    wire c32, c31;
    
    CarryLookaheadAdder_32b dut(s, c32, c31, a, b, c0);
    
    initial begin
        // Test case 1: 0 + 0 = 0
        a = 32'b00000000000000000000000000000000;
        b = 32'b00000000000000000000000000000000;
        c0 = 1'b0;
        #10;
        $display("Test case 1: 0 + 0 = 0");
        $display("s = %b", s);
        $display("c32 = %b, c31 = %b", c32, c31);
        
        // Test case 2: 0 + 1 = 1
        a = 32'b00000000000000000000000000000000;
        b = 32'b00000000000000000000000000000001;
        c0 = 1'b0;
        #10;
        $display("Test case 2: 0 + 1 = 1");
        $display("s = %b", s);
        $display("c32 = %b, c31 = %b", c32, c31);
        
        // Test case 3: 1 + 1 = 10
        a = 32'b00000000000000000000000000000001;
        b = 32'b00000000000000000000000000000001;
        c0 = 1'b0;
        #10;
        $display("Test case 3: 1 + 1 = 10");
        $display("s = %b", s);
        $display("c32 = %b, c31 = %b", c32, c31);
        
        // Test case 4: Maximum value + 1 = 0 (with carry out)
        a = 32'hFFFFFFFF;
        b = 32'b00000000000000000000000000000001;
        c0 = 1'b0;
        #10;
        $display("Test case 4: Maximum value + 1 = 0 (with carry out)");
        $display("s = %b", s);
        $display("c32 = %b, c31 = %b", c32, c31);
        
        // Test case 5: Maximum value + 1 = 0 (without carry out)
        a = 32'hFFFFFFFF;
        b = 32'b00000000000000000000000000000001;
        c0 = 1'b1;
        #10;
        $display("Test case 5: Maximum value + 1 = 0 (without carry out)");
        $display("s = %b", s);
        $display("c32 = %b, c31 = %b", c32, c31);
        
        // Test case 6: Random values
        a = 32'hAABBCCDD;
        b = 32'h11223344;
        c0 = 1'b0;
        #10;
        $display("Test case 6: Random values");
        $display("s = %b", s);
        $display("c32 = %b, c31 = %b", c32, c31);

        #10;
        $finish;
    end

endmodule
