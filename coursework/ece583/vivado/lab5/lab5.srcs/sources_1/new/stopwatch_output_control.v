`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/02/2023 04:31:32 PM
// Design Name: 
// Module Name: stopwatch_output_control
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


module stopwatch_output_control(
    input wire [2:0] s,
    output wire displayInputSel,
    output wire counterEN,
    output wire registerEN,
    output wire counterReset,
    output wire registerInputSel
    );
    
    reg [4:0] out;
    
    always @(*)
    begin
        case(s)
            3'b000: out = 5'b10010;
            3'b001: out = 5'b11010;
            3'b010: out = 5'b11000;
            3'b011: out = 5'b10000;
            3'b100: out = 5'b10101;
            3'b101: out = 5'b00001;
            3'b110: out = 5'b10010;
            3'b111: out = 5'b10110;
        endcase
    end
    
    assign displayInputSel = out[4];
    assign counterEN = out[3];
    assign registerEN = out[2];
    assign counterReset = out[1];
    assign registerInputSel = out[0];
    
endmodule
