`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: UNH
// Engineer: Nick Snyder
// 
// Create Date: 04/10/2023 01:35:29 AM
// Design Name: 
// Module Name: top
// Project Name: RoboticArm
// Target Devices: Basys 3
// Tool Versions: 
// Description: 
// Interface between switch positions to 4-degree servo-based robotic arm using PWM
// 
// Dependencies: 
// 
// Revision:
// Revision 1.0 - Fixed PWM_generator.v and clock_divider.v. Ready to test on hardware
// Additional Comments: Simulation results don't match actual performance
// 
//////////////////////////////////////////////////////////////////////////////////


module top(
    input clk,              // board clock
    input [5:0] sw,         // 2 switches per servo, 3 positions
    output [8:0] light,
    output [2:0] JB         // 3 servos in total, Pmod Jb pins 1-3
    );
    
    // standard board clock: 100,000,000Hz - 10ns
    // desired clock: 50Hz - 20ms
    // width range: 1-2ms
    // positions: 1ms, 1.5ms, 2ms
    // clock resolution: 0.25ms
    
    // Takes in switches and outputs a PWM signal to each of the corresponding servo motors.
    // Every clock cycle, each switch is checked to to update PWM signal sent to servo motor.
    // Servo motors use PWM to determine position, -90 -> 0 -> 90 degrees.
    
    // module PWM_generator(input [1:0] position, input clk, output reg modulated_signal);
    
    // update position of servo 0 
    PWM_generator pwm_0(sw[1:0], clk, JB[0]);
    
    // update position of servo 1 
    PWM_generator pwm_1(sw[3:2], clk, JB[1]);
    
    // update position of servo 2 
    PWM_generator pwm_2(sw[5:4], clk, JB[2]);
    
    assign light[0] = sw[0];
    assign light[1] = sw[1];
    assign light[2] = sw[2];
    assign light[3] = sw[3];
    assign light[4] = sw[4];
    assign light[5] = sw[5];
    
    assign light[6] = JB[0];
    assign light[7] = JB[1];
    assign light[8] = JB[2];
    
endmodule
