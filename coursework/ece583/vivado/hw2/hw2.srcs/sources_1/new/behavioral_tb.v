`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/23/2023 05:21:20 PM
// Design Name: 
// Module Name: behavioral_tb
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


module behavioral_tb;

  // Instantiate the behavioral module
  dataflow dut(
    .in(in),
    .out(out)
  );

  // Declare the inputs and outputs
  reg [1:9] in;
  wire [3:0] out;

  // Create a clock generator
  parameter CLK_PERIOD = 10;
  reg clk = 0;
  always #CLK_PERIOD clk = ~clk;

  // Create a stimulus block to provide test inputs
  initial begin
    // Test case 1
    in = 9'b111111111;
    #10;
    // Expected output: 4'b1111
    
    // Test case 2
    in = 9'b000000000;
    #10;
    // Expected output: 4'b0000
    
    // Test case 3
    in = 9'b000000001;
    #10;
    // Expected output: 4'b0110
    
    // Add more test cases here
    
    $finish;
  end

  // Create an expected output block to store the expected results
//  always @(posedge clk) begin
//    casez(in)
//      9'b111111111: assert(out === 4'b1111);
//      9'b000000000: assert(out === 4'b0000);
//      9'b000000001: assert(out === 4'b0110);
//      // Add more expected outputs here
//    endcase
//  end

endmodule
