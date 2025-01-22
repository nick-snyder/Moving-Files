`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/03/2023 12:19:38 AM
// Design Name: 
// Module Name: mux_gate_tb
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


module mux_gate_tb;
    parameter N = 8; 	// size of the test set 
    reg  a; 	
    reg  b; 	
    reg  s; 	
    wire out;
    reg  a_array [1:N]; 
    reg  b_array [1:N]; 
    reg  s_array [1:N]; 
    reg  out_array [1:N];
 
    initial 
        begin  
            //initialization of a_array 
            a_array[1] =  1'b0; 
            a_array[2] =  1'b1; 
            a_array[3] =  1'b0; 
            a_array[4] =  1'b1; 
            a_array[5] =  1'b0; 
            a_array[6] =  1'b1; 
            a_array[7] =  1'b0; 
            a_array[8] =  1'b1; 
 
            //initialization of b_array 
            b_array[1] =  1'b0; 
            b_array[2] =  1'b0; 
            b_array[3] =  1'b1; 
            b_array[4] =  1'b1; 
            b_array[5] =  1'b0; 
            b_array[6] =  1'b0; 
            b_array[7] =  1'b1; 
            b_array[8] =  1'b1; 
 
            //initialization of s_array
            s_array[1] =  1'b0; 
            s_array[2] =  1'b0; 
            s_array[3] =  1'b0; 
            s_array[4] =  1'b0; 
            s_array[5] =  1'b1; 
            s_array[6] =  1'b1; 
            s_array[7] =  1'b1; 
            s_array[8] =  1'b1; 
 
            //initialization of out_array (expected output) 
            out_array[1] =  1'b0; 
            out_array[2] =  1'b1; 
            out_array[3] =  1'b0; 
            out_array[4] =  1'b1; 
            out_array[5] =  1'b0; 
            out_array[6] =  1'b0; 
            out_array[7] =  1'b1; 
            out_array[8] =  1'b1; 
        end 
    integer i; 
    always 
        begin 
            for (i = 1; i <= N; i = i + 1) 
                begin 
                    $display(i); 
                    a <= a_array[i]; // assign test data to the a vector 
                    b <= b_array[i]; // assign test data to the b vector 
                    s <= s_array[i]; // assign s 
 
                    #40; // delay for 40 time units 
 
                    if (out != out_array[i]) 
                        begin 
                            $write("ERROR: "); 
                            $display("Wrong Answer "); 
                        end 
                     
                    else 
                        begin 
                          $display("Correct!!"); 
                        end 
                end 
            $display("Test Finished"); 
        end 
    mux_gate test1(out, s, a, b); // test implentation 
endmodule
