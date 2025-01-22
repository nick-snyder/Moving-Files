`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/06/2023 10:20:02 PM
// Design Name: 
// Module Name: CLU_4b_tb
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


module CLU_4b_tb;

    reg g3, g2, g1, g0, p3, p2, p1, p0, c0;
    wire c4, c3, c2, c1, G, P;

    // Instantiate the DUT
    CarryLookaheadUnit_4b dut(.c4(c4), .c3(c3), .c2(c2), .c1(c1), .G(G), .P(P), .g3(g3), .g2(g2), .g1(g1), .g0(g0), .p3(p3), .p2(p2), .p1(p1), .p0(p0), .c0(c0));

    // Stimulus process
    initial begin
    
        // Initialize inputs
        g3 = 0;
        g2 = 0;
        g1 = 0;
        g0 = 0;
        p3 = 0;
        p2 = 0;
        p1 = 0;
        p0 = 0;
        c0 = 0;

        // Wait for the inputs to settle
        #20;

        // Test case 1: 0 + 0 = 0
        #5 g0 = 0; p0 = 1;
        #20 $display("Test case 1: g=%b, p=%b, c4=%b, c3=%b, c2=%b, c1=%b, G=%b, P=%b", {g3,g2,g1,g0}, {p3,p2,p1,p0}, c4, c3, c2, c1, G, P);

        // Test case 2: 3 + 5 = 8
        #5 g3 = 0; g2 = 0; g1 = 1; g0 = 1;
        #5 p3 = 1; p2 = 0; p1 = 1; p0 = 0;
        #20 $display("Test case 2: g=%b, p=%b, c4=%b, c3=%b, c2=%b, c1=%b, G=%b, P=%b", {g3,g2,g1,g0}, {p3,p2,p1,p0}, c4, c3, c2, c1, G, P);

        // Test case 3: 7 + 8 = 15
        #5 g3 = 1; g2 = 1; g1 = 1; g0 = 1;
        #5 p3 = 1; p2 = 0; p1 = 0; p0 = 0;
        #20 $display("Test case 3: g=%b, p=%b, c4=%b, c3=%b, c2=%b, c1=%b, G=%b, P=%b", {g3,g2,g1,g0}, {p3,p2,p1,p0}, c4, c3, c2, c1, G, P);

        // Stop the simulation
        #20 $finish;
    end
    
endmodule
