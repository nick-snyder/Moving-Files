// Testbench for BCD_counter_4b module
`timescale 1ns / 1ps

module BCD_counter_4b_tb;

    // Inputs
    reg clk = 0;
    reg enable;
    reg reset;

    // Outputs
    wire [3:0] out;
    wire carryOut;

    // Instantiate the module
    BCD_counter_4b dut(
        .out(out),
        .carryOut(carryOut),
        .clk(clk),
        .enable(enable),
        .reset(reset)
    );

    // Generate clock signal
    always #5 clk = ~clk;
    
    integer i;

    // Stimulus
    initial begin
        // Initialize inputs
        reset = 1;
        enable = 1;

        // Reset the counter
        #10 reset = 0;
//        #10 reset = 1;

        // Test counting up from 0 to 9
        for (i = 0; i < 100; i = i + 1) begin
            #10 enable = 0;
            #10 enable = 1;
        end
        
        #10 $finish;
    end

    // Monitor output
    always @(posedge clk) begin
        $display("out: %d carryOut: %d", out, carryOut);
    end

endmodule
