`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/14/2023 01:01:31 AM
// Design Name: 
// Module Name: PWM_generator
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


module PWM_generator(
    input [1:0] position,
    input clk,
    output reg modulated_signal
    );
    
    clk_divider clk_div(clk, clk_out);
    
    reg [15:0] width;
    reg [15:0] time_v;
    
    // set signal high at t=0
    initial begin
        modulated_signal = 1;
        time_v = 0;
    end
    
    always @(posedge clk_out)
    begin

        // determine width from switch position
        case (position)
            2'b00: width <= 1500;//3
            2'b01: width <= 2200; //4
            2'b10: width <= 800; //2
            2'b11: width <= 1500; //3
        endcase
        
        if(time_v < width) 
        begin
            modulated_signal <= 1;
        end 
        else 
        begin
            modulated_signal <= 0;
        end
        
        if(time_v > 20000) 
        begin
            time_v <= 0;
        end
    end
endmodule
