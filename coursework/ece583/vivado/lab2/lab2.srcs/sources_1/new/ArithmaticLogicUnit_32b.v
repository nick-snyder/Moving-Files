`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/21/2023 03:55:12 PM
// Design Name: 
// Module Name: ArithmaticLogicUnit_32b
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


module ArithmaticLogicUnit_32b(result, overflow, zero, a, b, ALUop);

    output [31:0]result;
    output overflow, zero;
    input [31:0]a, b;
    input [3:0]ALUop;
    
    wire [31:0]out;
    wire c32, c31, o;
    
    // mux_2c_32b    (out,   s,        a, b);
    mux_2c_32b mux_a (a_mux, ALUop[3], a, ~a);
    mux_2c_32b mux_b (b_mux, ALUop[2], b, ~b);
    
    // CarryLookaheadAdder_32b   (s, c32, c31, a,     b,     c0);
    CarryLookaheadAdder_32b unit (o, c32, c31, a_mux, b_mux, ALUop[2]);
    
    // mux_4c_32b  (out, s,          a,             b,             c, d);
    mux_4c_32b mux (out, ALUop[1:0], a_mux & b_mux, a_mux | b_mux, o, b);
    
    assign result = out;
    assign overflow = c32 ^ c31;
    assign zero = ~(out[31] | out[30] | out[29] | out[28] | 
                    out[27] | out[26] | out[25] | out[24] | 
                    out[23] | out[22] | out[21] | out[20] | 
                    out[19] | out[18] | out[17] | out[16] | 
                    out[15] | out[14] | out[13] | out[12] | 
                    out[11] | out[10] | out[9]  | out[8]  | 
                    out[7]  | out[6]  | out[5]  | out[4]  | 
                    out[3]  | out[2]  | out[1]  | out[0]  );

endmodule
