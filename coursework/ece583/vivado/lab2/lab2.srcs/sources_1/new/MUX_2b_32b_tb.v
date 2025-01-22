`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/07/2023 11:23:30 PM
// Design Name: 
// Module Name: MUX_2b_32b_tb
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


module MUX_2c_32b_tb;

  reg [31:0] a, b;
  reg s;
  wire [31:0] out;

  // Instantiate the DUT
  mux_2c_32b dut (.out(out), .s(s), .a(a), .b(b));

  // Stimulus process
  initial begin
    // Test case 1: select input a
    s = 0;
    a = 32'h12345678;
    b = 32'habcdef01;
    #5 $display("Test case 1: s=%b, a=%h, b=%h, out=%h", s, a, b, out);

    // Test case 2: select input b
    s = 1;
    #5 $display("Test case 2: s=%b, a=%h, b=%h, out=%h", s, a, b, out);
    b = 32'hfedcba98;
    #5 $display("Test case 2: s=%b, a=%h, b=%h, out=%h", s, a, b, out);

    // Stop the simulation
    #5 $finish;
  end

endmodule
