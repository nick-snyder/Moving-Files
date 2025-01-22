`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/14/2023 04:22:59 PM
// Design Name: 
// Module Name: comparator_tb
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


module comparator_tb;

    parameter N = 4; 	// size of the test set 
    reg  [3:0] a; 	
    reg  [3:0] b; 		
    wire greater;
    wire equal;
    wire less;
    reg  a_array [1:N]; 
    reg  b_array [1:N]; 
    reg  greater_array [1:N];
    reg  equal_array [1:N];
    reg  less_array [1:N];
    
    initial 
        begin  
            //initialization of a_array 
            a_array[1] =  16'hA; 
            a_array[2] =  16'h7; 
            a_array[3] =  16'hA; 
            a_array[4] =  16'h7; 
 
            //initialization of b_array 
            b_array[1] =  16'hA; 
            b_array[2] =  16'hA; 
            b_array[3] =  16'h7; 
            b_array[4] =  16'h7; 
 
            //initialization of greater_array (expected output)
            greater_array[1] =  1'b0; 
            greater_array[2] =  1'b1; 
            greater_array[3] =  1'b0; 
            greater_array[4] =  1'b0; 
 
            //initialization of equal_array (expected output) 
            equal_array[1] =  1'b1; 
            equal_array[2] =  1'b0; 
            equal_array[3] =  1'b0; 
            equal_array[4] =  1'b1; 
            
            //initialization of less_array (expected output) 
            less_array[1] =  1'b0; 
            less_array[2] =  1'b0; 
            less_array[3] =  1'b1; 
            less_array[4] =  1'b0; 
        end
    integer i; 
    always 
        begin 
            for (i = 1; i <= N; i = i + 1) 
                begin 
                    $display(i); 
                    a <= a_array[i]; // assign test data to the a vector 
                    b <= b_array[i]; // assign test data to the b vector 
 
                    #40; // delay for 40 time units 
 
                    if ((greater != greater_array[i]) && (equal != equal_array[i]) && (less != less_array[i])) 
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
    comparator_u4b test1(greater, equal, less, a, b); // test implentation 

endmodule
