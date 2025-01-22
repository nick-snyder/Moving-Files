%==========================================================
%
% Nicholas (Nick) Snyder
% ECE 401
% Section 5
% 10/29/20
%
% Homework 7
% 
%==========================================================

% Define constants
batteryVoltage = 100;
resistance = 1000;
capacitance1 = 0.000008;
capacitance2 = 0.000005;
capacitance3 = 0.000002;

% Define the Time Constant. Also known as tau
timeConstant1 = resistance * capacitance1;
timeConstant2 = resistance * capacitance2;
timeConstant3 = resistance * capacitance3;

% Peak of each function
% For this example, the capacitor discharges at 90% capacitance
peak1 = -timeConstant1 * log(0.1);
peak2 = -timeConstant2 * log(0.1);
peak3 = -timeConstant3 * log(0.1);

% Define the domain of the charging function
time11 = linspace(0, peak1, 50);
time21 = linspace(0, peak2, 50);
time31 = linspace(0, peak3, 50);

% Use both time and tau to calculate voltage across charging capacitor
voltageAcrossChargingCapacitor1 = batteryVoltage * (1 - exp(-time11/timeConstant1));
voltageAcrossChargingCapacitor2 = batteryVoltage * (1 - exp(-time21/timeConstant2));
voltageAcrossChargingCapacitor3 = batteryVoltage * (1 - exp(-time31/timeConstant3));

% Define the domain of the discharging function
time12 = linspace(peak1, 0.08, 50);
time22 = linspace(peak2, 0.08, 50);
time32 = linspace(peak3, 0.08, 50);

% This is used to ensure the discharging function starts at the peak of the
% charging function
peakVoltage1 = voltageAcrossChargingCapacitor1(end) * 10;
peakVoltage2 = voltageAcrossChargingCapacitor2(end) * 10;
peakVoltage3 = voltageAcrossChargingCapacitor3(end) * 10;

% Use both time and tau to calculate voltage across discharging capacitor
voltageAcrossDischargingCapacitor1 = peakVoltage1 * exp(-time12/timeConstant1);
voltageAcrossDischargingCapacitor2 = peakVoltage2 * exp(-time22/timeConstant2);
voltageAcrossDischargingCapacitor3 = peakVoltage3 * exp(-time32/timeConstant3);

% Combine the domains of the charging and discharging functions
time1 = [time11, time12];
time2 = [time21, time22];
time3 = [time31, time32];

% Combine both ranges of the charging and discharging functions
voltageAcrossCapacitor1 = [voltageAcrossChargingCapacitor1, voltageAcrossDischargingCapacitor1];
voltageAcrossCapacitor2 = [voltageAcrossChargingCapacitor2, voltageAcrossDischargingCapacitor2];
voltageAcrossCapacitor3 = [voltageAcrossChargingCapacitor3, voltageAcrossDischargingCapacitor3];

% Plot 8 Microfarrad Capacitor with red line
% Plot 5 Microfarrad Capacitor with green line
% Plot 2 Microfarrad Capacitor with blue line
% Columns 117 through 123 serve purpose of ensure vertical axis spans from 0
% to 110
plot(time1, voltageAcrossCapacitor1, 'r', time2, voltageAcrossCapacitor2, 'g', time3, voltageAcrossCapacitor3, 'b', 0, 110)
grid on

% Add titles and legend
xlabel('Time in seconds')
ylabel('Capacitor Voltage')
title('Capacitor Charging')
legend('8 Microfarrad Capacitor', '5 Microfarrad Capacitor', '2 Microfarrad Capacitor')
