`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/06/2023 10:20:02 PM
// Design Name: 
// Module Name: FA_1b_tb
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


module FA_1b_tb;

    parameter N = 8; //size of the test set 
    reg a; // create the 4-bit a variable A 
    reg b; // create a 4-bit b variable to hold B 
    reg carryIn; // carry in 
    wire sum; // a net to route sum as ouptut 
    wire carryOut; // carry out 
    reg a_array [1:N]; 
    reg carryIn_array [1:N]; 
    reg b_array [1:N]; 
    reg sum_array [1:N]; 
    reg carryOut_array [1:N]; 
    
    initial 
        begin 
            //initialization of a_array 
            a_array[1] =  1'b0; 
            a_array[2] =  1'b0; 
            a_array[3] =  1'b0; 
            a_array[4] =  1'b0; 
            a_array[5] =  1'b1; 
            a_array[6] =  1'b1; 
            a_array[7] =  1'b1; 
            a_array[8] =  1'b1; 
 
            //initialization of carryIn_array 
            carryIn_array[1] =  1'b0; 
            carryIn_array[2] =  1'b1; 
            carryIn_array[3] =  1'b0; 
            carryIn_array[4] =  1'b1; 
            carryIn_array[5] =  1'b0; 
            carryIn_array[6] =  1'b1; 
            carryIn_array[7] =  1'b0; 
            carryIn_array[8] =  1'b1; 
 
            //initialization of b_array 
            b_array[1] =  1'b0; 
            b_array[2] =  1'b0; 
            b_array[3] =  1'b1; 
            b_array[4] =  1'b1; 
            b_array[5] =  1'b0; 
            b_array[6] =  1'b0; 
            b_array[7] =  1'b1; 
            b_array[8] =  1'b1; 
 
            //initialization of sum_array (expected sum outputs) 
            sum_array[1] =  1'b0; 
            sum_array[2] =  1'b1; 
            sum_array[3] =  1'b1; 
            sum_array[4] =  1'b0; 
            sum_array[5] =  1'b1; 
            sum_array[6] =  1'b0; 
            sum_array[7] =  1'b0; 
            sum_array[8] =  1'b1; 
 
            //initialization of carryOut_array (expected carry output) 
            carryOut_array[1] =  1'b0; 
            carryOut_array[2] =  1'b0; 
            carryOut_array[3] =  1'b0; 
            carryOut_array[4] =  1'b1; 
            carryOut_array[5] =  1'b0; 
            carryOut_array[6] =  1'b1; 
            carryOut_array[7] =  1'b1; 
            carryOut_array[8] =  1'b1; 
        end 
    integer i; 
    always 
        begin 
            for (i = 1; i <= N; i = i + 1) 
                begin 
                    $display(i); 
                    a <= a_array[i]; // assign test data to the a vector 
                    b <= b_array[i]; // assign test data to the b vector 
                    carryIn    <=    carryIn_array[i]; // assign carry in 
 
                    #40; // delay for 40 time units 
 
                    if (!(sum == sum_array[i] & carryOut == carryOut_array[i])) 
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
    FullAdder_1b fullAdder(sum, carryOut, carryIn, a, b); // instantiate one-bit adder module 

endmodule