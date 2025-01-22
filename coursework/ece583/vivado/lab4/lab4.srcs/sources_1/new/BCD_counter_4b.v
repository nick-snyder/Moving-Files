`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/28/2023 06:12:01 PM
// Design Name: 
// Module Name: BCD_counter_4b
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


module BCD_counter_4b(out, carryOut, clk, enable, reset);

    output reg [3:0] out;
    output reg carryOut;
    input clk, enable, reset;
    
    always @(posedge clk) 
    begin
        
        if (reset) out = 0;
        
        else 
        begin
            if (enable) 
            begin
                case (out)
                    4'b0000: out = 4'b0001;
                    4'b0001: out = 4'b0010;
                    4'b0010: out = 4'b0011;
                    4'b0011: out = 4'b0100;
                    4'b0100: out = 4'b0101;
                    4'b0101: out = 4'b0110;
                    4'b0110: out = 4'b0111;
                    4'b0111: out = 4'b1000;
                    4'b1000: out = 4'b1001;
                    4'b1001: out = 4'b0000;
                endcase
                
                if (out == 4'b1001) carryOut = 1;
                else carryOut = 0;
            end
        end
    end
endmodule
