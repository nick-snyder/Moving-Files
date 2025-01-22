`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/27/2023 10:16:49 PM
// Design Name: 
// Module Name: display_control
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


module display_control(
    input clk,
    input [15:0] in,
    output [6:0] segment,
    output reg [3:0] anode
    );
    
    // Selecting between which digit/anode to refresh
    reg [1:0] digit_select;
    reg [19:0] refresh = 20'h00000;
    reg [3:0] gsv_in;
    reg [6:0] gsv_segment;
    
    get_segment_value gsv(gsv_in, segment);
    
    always @(posedge clk) 
    begin
    
        refresh <= refresh + 1;
        digit_select <= refresh[19:18];
//        segment <= gsv_segment;
        
        case (digit_select)
            2'b00: 
            begin
                anode = 4'b1110;
                gsv_in = in[3:0];
            end
            2'b01: 
            begin
                anode = 4'b1101;
                gsv_in = in[7:4];
            end
            2'b10: 
            begin
                anode = 4'b1011;
                gsv_in = in[11:8];
            end 
            2'b11: 
            begin
                anode = 4'b0111;
                gsv_in = in[15:12];
            end    
        endcase            
    end
endmodule
