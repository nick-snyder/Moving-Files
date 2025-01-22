`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/07/2023 11:17:10 PM
// Design Name: 
// Module Name: MUX_4c_32b_tb
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


module MUX_4c_32b_tb;
 
    reg [31:0] a, b, c, d;
    reg [1:0] s;
    wire [31:0] out;
    
    mux_4c_32b dut(out, s, a, b, c, d);
    
    initial begin
        // Test case 1
        a = 32'h12345678;
        b = 32'h9abcdef0;
        c = 32'hdeadbeef;
        d = 32'hfaceb00c;
        s = 2'b00;
        #10 $display("s = %d, out = %h", s, out);
        
        // Test case 2
        s = 2'b01;
        #10 $display("s = %d, out = %h", s, out);
        
        // Test case 3
        s = 2'b10;
        #10 $display("s = %d, out = %h", s, out);
        
        // Test case 4
        s = 2'b11;
        #10 $display("s = %d, out = %h", s, out);
        
        // End the simulation
        #10 $finish;
    end

endmodule
