`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/02/2023 05:23:11 PM
// Design Name: 
// Module Name: testbench_stopwatch
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


module testbench_stopwatch;

    reg start, stop, store, reset, clk;
    wire [3:0] anode;
    wire [6:0] segment;
    wire led_start, led_stop, led_store, led_reset;
    
    stopwatch dut(
        .start(start),
        .stop(stop),
        .store(store),
        .reset(reset),
        .clk(clk),
        .anode(anode),
        .segment(segment),
        .led_start(led_start),
        .led_stop(led_stop),
        .led_store(led_store),
        .led_reset(led_reset)
    );
    
    always #10 clk = ~clk;
    
    initial begin
        clk = 0;
        start = 0;
        stop = 0;
        store = 0;
        reset = 0;
    
        // Start stopwatch
        #100 start = 1;
        #100000 start = 0;
    
        // Stop stopwatch
        #1000000000 stop = 1;
        #100000000 stop = 0;
    
        // Store time
        #1000000 store = 1;
        #1000000 store = 0;
    
        // Reset stopwatch
        #1000000 reset = 1;
        #1000000 reset = 0;
        
        // Start stopwatch
        #1000000 start = 1;
        #1000000000 start = 0;
    
        // Stop stopwatch
        #200000000 stop = 1;
        #100000 stop = 0;
    
        // Store time
        #100000 store = 1;
        #100000 store = 0;
    
        // Reset stopwatch
        #100000 reset = 1;
        #100000 reset = 0;
    
        $finish;
    end

endmodule

