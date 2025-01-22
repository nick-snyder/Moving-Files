`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/03/2023 10:43:48 PM
// Design Name: 
// Module Name: testbench_display_control
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


module testbench_display_control;

    // Declare signals for testbench
    reg clk = 0;
    reg [15:0] in;
    wire [6:0] segment;
    wire [3:0] anode;
    
    // Instantiate the module to be tested
    display_control dut(clk, in, segment, anode);
    
    always #10 clk = ~clk;
    
    // Provide input values to the module for testing
    initial
    begin
//        clk = 0;
        // Test case 1: Input value 1234
        in = 16'd1234;
        #100;
        // Expected output:
        // Segment = 7'b0110000
        // Anode = 4'b1110 (displaying digit 4)
        
        // Test case 2: Input value 9876
        in = 16'd9876;
        #100;
        // Expected output:
        // Segment = 7'b0011111
        // Anode = 4'b0111 (displaying digit 1)
        
        // Test case 3: Input value 0
        in = 16'd0;
        #100;
        // Expected output:
        // Segment = 7'b1111110
        // Anode = 4'b1110 (displaying digit 0)
        
        // Add more test cases here as needed
        
        $finish; // End simulation
    end

endmodule
