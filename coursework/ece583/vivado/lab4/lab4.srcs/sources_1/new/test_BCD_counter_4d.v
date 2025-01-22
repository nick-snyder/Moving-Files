// Testbench for BCD_counter_4d module

`timescale 1ns / 1ps

module test_BCD_counter_4d;

    // Inputs
    reg clk = 0;
    reg enable;
    reg reset;
    
    // Outputs
    wire [15:0] out;
    
    // Instantiate the module
    BCD_counter_4d dut (
        .out(out),
        .clk(clk),
        .enable(enable),
        .reset(reset)
    );
    
    // Clock generator
    always #5 clk = ~clk;
    
    integer i;
    
    // Stimulus
    initial begin
        // Initialize inputs
        enable = 1;
        reset = 1;
        
        // Reset sequence
        #10 reset = 0;
        
        // Count sequence
        for (i = 0; i < 9999; i = i + 1) begin
            #10 enable = 0;
            #10 enable = 1;
        end
        
        // Wait for a few more clock cycles to observe the outputs
        #10 $finish;
    end
    
    // Monitor
    always @(posedge clk) begin
        $display("out = %d", out);
    end

endmodule
