`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/06/2023 10:20:02 PM
// Design Name: 
// Module Name: CLA_4b_tb
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


module CLA_4b_tb;

    reg [3:0] a;
    reg [3:0] b;
    reg c0;
    wire [3:0] s;
    wire c3, c4, G, P;

    CarryLookaheadAdder_4b unit(c4, c3, G, P, s, c0, a, b);

    initial begin
//        #10;
        a = 4'b0000;
        b = 4'b0000;
        c0 = 0;

        #10;
        a = 4'b1111;
        b = 4'b1111;
        c0 = 0;

        #10;
        a = 4'b0001;
        b = 4'b0101;
        c0 = 1;

        #10;
        a = 4'b1100;
        b = 4'b0011;
        c0 = 1;
        
        #10;
        a = 4'b1010;
        b = 4'b1010;
        c0 = 0;
        
        #10;
        a = 4'b1010;
        b = 4'b1010;
        c0 = 1;
        
        #10;
        a = 4'b0110;
        b = 4'b0110;
        c0 = 0;
        
        #10;
        a = 4'b0110;
        b = 4'b0110;
        c0 = 1;
        
        #10;
        a = 4'b1101;
        b = 4'b0010;
        c0 = 0;
        
        #10;
        a = 4'b1101;
        b = 4'b0010;
        c0 = 1;
        
        #10;
        a = 4'b0101;
        b = 4'b0101;
        c0 = 0;
        
        #10;
        a = 4'b0101;
        b = 4'b0101;
        c0 = 1;
        
        #10;
        a = 4'b1001;
        b = 4'b0010;
        c0 = 0;
        
        #10;
        a = 4'b1001;
        b = 4'b0010;
        c0 = 1;
        
        #10;
        $finish;
    end

endmodule
