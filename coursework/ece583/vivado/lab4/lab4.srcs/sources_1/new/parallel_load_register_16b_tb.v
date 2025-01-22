// Testbench for parallel_load_register_16b module

`timescale 1ns / 1ps

module parallel_load_register_16b_tb;

  // Inputs
  reg clk = 0;
  reg enable;
  reg reset;
  reg [15:0] in;

  // Outputs
  wire [15:0] out;

  // Instantiate the module
  parallel_load_register_16b dut (
    .out(out),
    .reset(reset),
    .clk(clk),
    .enable(enable),
    .in(in)
  );

  // Clock generator
  always #5 clk = ~clk;

  // Stimulus
  initial begin
    // Initialize inputs
    enable = 1;
    reset = 1;
    in = 16'b0000_0000_0000_0001;

    // Reset sequence
    #10 reset = 0;
    #10 reset = 1;
    #10 reset = 0;

    // Load input value
    #10 in = 16'b1111_1111_1111_1111;
    #10 enable = 0;
    #10 enable = 1;

    // Wait for a few more clock cycles to observe the outputs
    #100 $finish;
  end

  // Monitor
  always @(posedge clk) begin
    $display("out = %d", out);
  end

endmodule
