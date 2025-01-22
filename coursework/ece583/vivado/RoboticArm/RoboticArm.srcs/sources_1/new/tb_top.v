module tb_top;
    // Declare inputs and outputs for the testbench
    reg clk;
    reg [5:0] switches;
    wire [2:0] out;

    // Instantiate the top module
    top dut(
        .clk(clk),
        .sw(switches),
        .JB(out)
    );

    // Clock generation
    initial clk = 0;
    always #10 clk = ~clk; // Generate a 100MHz clock

    // Stimulus generation
    initial begin
    
        // Move servos to 0 degrees
        switches = 8'b111111; // set all servos to 1.5ms duty cycle
        #100000000;

        // Move servos to 90 degrees
        switches = 8'b101010; // set all servos to 2ms duty cycle
        #100000000;
        
         // Move servos to 0 degrees
        switches = 8'b010101; // set all servos to 1.5ms duty cycle
        #100000000;

        // Move servos to -90 degrees
        switches = 8'b000000; // set all servos to 1ms duty cycle
        #100000000;

        // Move servos to 0 degrees
        switches = 8'b111111; // set all servos to 1.5ms duty cycle
        #100000000;

        // End simulation
        $finish;
    end
endmodule
