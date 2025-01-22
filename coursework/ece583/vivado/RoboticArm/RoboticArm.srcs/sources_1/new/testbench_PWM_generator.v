`timescale 1ns / 1ps

module testbench_PWM_generator;

    reg [1:0] position = 2'b00;
    reg clk = 0;
    
    PWM_generator dut1(
        .position(position),
        .clk(clk),
        .modulated_signal(modulated_signal)
    );
    
    always #10 clk = ~clk;

    initial
    begin
        position = 2'b00;
        #100000000;
        position = 2'b01;
        #100000000;
        position = 2'b10;
        #100000000;
        position = 2'b11;
        #100000000;
        $finish;
    end
endmodule
