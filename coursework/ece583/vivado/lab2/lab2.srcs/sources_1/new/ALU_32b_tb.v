`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/06/2023 10:20:02 PM
// Design Name: 
// Module Name: ALU_32b_tb
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


module ALU_32b_tb();

    reg [31:0] a, b;
    reg [3:0] ALUop;
    wire [31:0] result;
    wire overflow, zero;
    
    ArithmaticLogicUnit_32b unit(result, overflow, zero, a, b, ALUop);
    
    initial begin
//        $dumpfile("alu.vcd");
//        $dumpvars(0, unit);
//        $monitor("a=%d, b=%d, ALUop=%d, result=%d, overflow=%d, zero=%d", 
//                 a, b, ALUop, result, overflow, zero);
                 
        // test case 1: addition of two positive numbers
        a = 12345678;
        b = 87654321;
        ALUop = 2'b00;  // addition
        #10;
        // expected result: 99999999, overflow: 0, zero: 0
         
        // test case 2: subtraction of two positive numbers
        a = 87654321;
        b = 12345678;
        ALUop = 2'b10;  // subtraction
        #10;
        // expected result: 75308643, overflow: 0, zero: 0
         
        // test case 3: addition of two negative numbers
        a = -12345678;
        b = -87654321;
        ALUop = 2'b00;  // addition
        #10;
        // expected result: -99999999, overflow: 0, zero: 0
         
        // test case 4: subtraction of two negative numbers
        a = -87654321;
        b = -12345678;
        ALUop = 2'b10;  // subtraction
        #10;
        // expected result: -75308643, overflow: 0, zero: 0
         
        // test case 5: addition of a positive and a negative number
        a = 12345678;
        b = -87654321;
        ALUop = 2'b00;  // addition
        #10;
        // expected result: -75308643, overflow: 0, zero: 0
         
        // test case 6: subtraction of a positive and a negative number
        a = 87654321;
        b = -12345678;
        ALUop = 2'b10;  // subtraction
        #10;
        // expected result: 99999999, overflow: 0, zero: 0
         
        // test case 7: AND operation
        a = 32'h55555555;
        b = 32'hAAAAAAAA;
        ALUop = 2'b01;  // AND
        #10;
        // expected result: 0x00000000, overflow: 0, zero: 1
         
        // test case 8: OR operation
        a = 32'h55555555;
        b = 32'hAAAAAAAA;
        ALUop = 2'b11;  // OR
        #10;
        // expected result: 0xFFFFFFFF, overflow: 0, zero: 0
         
        // test case 9: XOR operation
        a = 32'h55555555;
        b = 32'hAAAAAAAA;
        ALUop = 2'b10;  // XOR
        #10;
        // expected result: 0
        
        #10;
        $finish;
        
    end

endmodule
