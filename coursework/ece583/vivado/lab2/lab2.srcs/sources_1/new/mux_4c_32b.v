`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/06/2023 08:31:54 PM
// Design Name: 
// Module Name: mux_4c_32b
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


module mux_4c_32b(out, s, a, b, c, d);

    output reg [31:0]out;
    input [31:0] a, b, c, d;
    input [1:0]s;
    
    always @(*) begin
        case (s)
            2'b00: out = a;
            2'b01: out = b;
            2'b10: out = c;
            2'b11: out = d;
        endcase
    end

endmodule
