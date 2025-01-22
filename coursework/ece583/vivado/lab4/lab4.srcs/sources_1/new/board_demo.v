`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/11/2023 04:23:06 PM
// Design Name: 
// Module Name: board_demo
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


// Define a function to get the segment value for a given switch value
function [6:0] get_segment_value;
    input [3:0] switches;
    reg [6:0] segment;
    
    // Define named constants for anode select values
    parameter ANODE_SELECT_DIGIT_0 = 4'b1110;
    parameter ANODE_SELECT_DIGIT_1 = 4'b1101;
    parameter ANODE_SELECT_DIGIT_2 = 4'b1011;
    parameter ANODE_SELECT_DIGIT_3 = 4'b0111;
    
    // Define named constants for switch values
    parameter SWITCH_VALUE_ZERO  = 4'b0000;
    parameter SWITCH_VALUE_ONE   = 4'b0001;
    parameter SWITCH_VALUE_TWO   = 4'b0010;
    parameter SWITCH_VALUE_THREE = 4'b0011;
    parameter SWITCH_VALUE_FOUR  = 4'b0100;
    parameter SWITCH_VALUE_FIVE  = 4'b0101;
    parameter SWITCH_VALUE_SIX   = 4'b0110;
    parameter SWITCH_VALUE_SEVEN = 4'b0111;
    parameter SWITCH_VALUE_EIGHT = 4'b1000;
    parameter SWITCH_VALUE_NINE  = 4'b1001;
    
    // Define named constants for segment values
    parameter SEGMENT_VALUE_ZERO  = 7'b1000000;
    parameter SEGMENT_VALUE_ONE   = 7'b1111001;
    parameter SEGMENT_VALUE_TWO   = 7'b0100100;
    parameter SEGMENT_VALUE_THREE = 7'b0110000;
    parameter SEGMENT_VALUE_FOUR  = 7'b0011001;
    parameter SEGMENT_VALUE_FIVE  = 7'b0010010;
    parameter SEGMENT_VALUE_SIX   = 7'b0000010; 
    parameter SEGMENT_VALUE_SEVEN = 7'b1111000;
    parameter SEGMENT_VALUE_EIGHT = 7'b0000000;
    parameter SEGMENT_VALUE_NINE  = 7'b0010000;
    
    begin
	  // Use a case statement to determine the segment value for the 
	  // given switch value
        case (switches[3:0])
            SWITCH_VALUE_ZERO:  segment = SEGMENT_VALUE_ZERO; 
            SWITCH_VALUE_ONE:   segment = SEGMENT_VALUE_ONE;  
            SWITCH_VALUE_TWO:   segment = SEGMENT_VALUE_TWO;  
            SWITCH_VALUE_THREE: segment = SEGMENT_VALUE_THREE;
            SWITCH_VALUE_FOUR:  segment = SEGMENT_VALUE_FOUR; 
            SWITCH_VALUE_FIVE:  segment = SEGMENT_VALUE_FIVE; 
            SWITCH_VALUE_SIX:   segment = SEGMENT_VALUE_SIX;  
            SWITCH_VALUE_SEVEN: segment = SEGMENT_VALUE_SEVEN;
            SWITCH_VALUE_EIGHT: segment = SEGMENT_VALUE_EIGHT;
            SWITCH_VALUE_NINE:  segment = SEGMENT_VALUE_NINE; 
            default:            segment = SEGMENT_VALUE_ZERO;
        endcase
        // Return the segment value
        get_segment_value = segment;
    end
endfunction

module board_demo(
    input clk, enable, reset,
    output reg [6:0] segment,
    output reg [3:0] anode
    );
    
    wire [15:0] out;
    
    // BCD_counter_4d(out, clk, enable, reset);
    BCD_counter_4d counter(out, clk, enable, reset);
    
    // Selecting between which digit/anode to refresh
//    wire [1:0] digit_select;
    reg [1:0] refresh = 2'b00;
    
    // Clock signal
    always @(posedge clk) begin
        refresh <= refresh + 1;
    end
    
    // Essentially a delay
//    assign digit_select = refresh[19:18];
    
    // For the length of the program, the digit_select will direct 
    // flow to refresh a digit/anode
    always @(posedge clk) begin
        case (refresh)
            2'b00: 
            begin
                // Refresh digit 0
                anode = 4'b1110;
                // Update segments
                // Digit 0 will be refreshed to reflect the positions 
                // of the first four switches as encoded into decimal 
                // numbers
                segment = get_segment_value(out[3:0]);
            end
            2'b01: 
            begin
                // Refresh digit 1
                anode = 4'b1101;
                // Update segments
		        // Digit 1 will be refreshed to reflect the positions 
                // of the second four switches as encoded into decimal 
                // numbers
                segment = get_segment_value(out[7:4]);
            end
            2'b10: 
            begin
                // Refresh digit 2
                anode = 4'b1011;
                // Update segments
		        // Digit 2 will be refreshed to reflect the positions 
                // of the third four switches as encoded into decimal 
                // numbers
                segment = get_segment_value(out[11:8]);
            end 
            2'b11: 
            begin
                // Refresh digit 3
                anode = 4'b0111;
                // Update segments
		        // Digit 3 will be refreshed to reflect the positions 
                // of the fourth four switches as encoded into decimal 
                // numbers
                segment = get_segment_value(out[15:12]);
            end    
        endcase            
    end
endmodule
