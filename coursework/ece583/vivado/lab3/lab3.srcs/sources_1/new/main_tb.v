`timescale 1ns/1ps

module main_tb;
    // Inputs
    reg [15:0] switches;
    reg clk;
    
    // Outputs
    wire [6:0] segment;
    wire [3:0] anode;
    
    // Instantiate the Unit Under Test (UUT)
    main uut (
        .segment(segment), 
        .anode(anode), 
        .switches(switches), 
        .clk(clk)
    );
    
    initial begin
        // Initialize inputs
        switches = 16'b0;
        clk = 0;
        
        // Wait for the clock to start
        #5;
        
        // Set switches to a value to test display
        switches = 16'b0011000100100100;
        #50;
        
        // Toggle switches to test display update
        switches = 16'b0000111100001111;
        #50;
        switches = 16'b1111000011110000;
        #50;
        
        // Stop the clock and end the simulation
        clk = 0;
        #5;
        $finish;
    end
    
    always #10 clk = ~clk;
    
endmodule
