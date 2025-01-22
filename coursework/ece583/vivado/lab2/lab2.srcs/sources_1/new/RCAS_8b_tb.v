`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/06/2023 10:20:02 PM
// Design Name: 
// Module Name: RCAS_8b_tb
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


module RCAS_8b_tb;

    reg [7:0] a, b;
    reg sub;
    wire [7:0] s;
    wire carryOut, overflow;
    
    RippleCarryAdderSubtractor_8b dut(s, carryOut, overflow, sub, a, b);
    
    initial begin
//        $dumpfile("dump.vcd");
//        $dumpvars(0, testbench_RippleCarryAdderSubtractor_8b);
        
        sub = 0;
        a = 8'b10101010;
        b = 8'b01010101;
        #10;
        
        sub = 1;
        a = 8'b01010101;
        b = 8'b10101010;
        #10;
        
        sub = 0;
        a = 8'b01111111;
        b = 8'b00000001;
        #10;
        
        sub = 1;
        a = 8'b10000000;
        b = 8'b11111111;
        #10;
        
        $finish;
    end
    
endmodule
