`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/14/2023 04:22:59 PM
// Design Name: 
// Module Name: mux_tb
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


module mux_tb;

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
            a_array[1] =  16'hA; 
            a_array[2] =  16'h7; 
            a_array[3] =  16'hA; 
            a_array[4] =  16'h7; 
            a_array[5] =  16'hA; 
            a_array[6] =  16'h7; 
            a_array[7] =  16'hA; 
            a_array[8] =  16'h7; 
 
            //initialization of b_array 
            b_array[1] =  16'hA; 
            b_array[2] =  16'hA; 
            b_array[3] =  16'h7; 
            b_array[4] =  16'h7; 
            b_array[5] =  16'hA; 
            b_array[6] =  16'hA; 
            b_array[7] =  16'h7; 
            b_array[8] =  16'h7; 
 
            //initialization of s_array
            s_array[1] =  16'hA; 
            s_array[2] =  16'hA; 
            s_array[3] =  16'hA; 
            s_array[4] =  16'hA; 
            s_array[5] =  16'h7; 
            s_array[6] =  16'h7; 
            s_array[7] =  16'h7; 
            s_array[8] =  16'h7; 
 
            //initialization of out_array (expected output) 
            out_array[1] =  16'hA; 
            out_array[2] =  16'h7; 
            out_array[3] =  16'hA; 
            out_array[4] =  16'h7; 
            out_array[5] =  16'hA; 
            out_array[6] =  16'hA; 
            out_array[7] =  16'h7; 
            out_array[8] =  16'h7; 
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
    mux_2c_16b test1(out, s, a, b); // test implentation 

endmodule

/*
a_array[0] = 4'b0000;
a_array[1] = 4'b0001;
*/

/*
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
            a_array[1] =  16'hA; 
            a_array[2] =  16'h7; 
            a_array[3] =  16'hA; 
            a_array[4] =  16'h7; 
            a_array[5] =  16'hA; 
            a_array[6] =  16'h7; 
            a_array[7] =  16'hA; 
            a_array[8] =  16'h7; 
 
            //initialization of b_array 
            b_array[1] =  16'hA; 
            b_array[2] =  16'hA; 
            b_array[3] =  16'h7; 
            b_array[4] =  16'h7; 
            b_array[5] =  16'hA; 
            b_array[6] =  16'hA; 
            b_array[7] =  16'h7; 
            b_array[8] =  16'h7; 
 
            //initialization of s_array
            s_array[1] =  16'hA; 
            s_array[2] =  16'hA; 
            s_array[3] =  16'hA; 
            s_array[4] =  16'hA; 
            s_array[5] =  16'h7; 
            s_array[6] =  16'h7; 
            s_array[7] =  16'h7; 
            s_array[8] =  16'h7; 
 
            //initialization of out_array (expected output) 
            out_array[1] =  16'hA; 
            out_array[2] =  16'h7; 
            out_array[3] =  16'hA; 
            out_array[4] =  16'h7; 
            out_array[5] =  16'hA; 
            out_array[6] =  16'hA; 
            out_array[7] =  16'h7; 
            out_array[8] =  16'h7; 
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

*/