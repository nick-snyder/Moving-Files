
�
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2$
create_project: 2default:default2
00:00:022default:default2
00:00:092default:default2
393.8242default:default2
67.4382default:defaultZ17-268h px� 
�
Command: %s
1870*	planAhead2�
�read_checkpoint -auto_incremental -incremental C:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/utils_1/imports/synth_1/stopwatch.dcp2default:defaultZ12-2866h px� 
�
;Read reference checkpoint from %s for incremental synthesis3154*	planAhead2~
jC:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/utils_1/imports/synth_1/stopwatch.dcp2default:defaultZ12-5825h px� 
T
-Please ensure there are no constraint changes3725*	planAheadZ12-7989h px� 
v
Command: %s
53*	vivadotcl2E
1synth_design -top stopwatch -part xc7a35tcpg236-12default:defaultZ4-113h px� 
:
Starting synth_design
149*	vivadotclZ4-321h px� 
�
@Attempting to get a license for feature '%s' and/or device '%s'
308*common2
	Synthesis2default:default2
xc7a35t2default:defaultZ17-347h px� 
�
0Got license for feature '%s' and/or device '%s'
310*common2
	Synthesis2default:default2
xc7a35t2default:defaultZ17-349h px� 
V
Loading part %s157*device2#
xc7a35tcpg236-12default:defaultZ21-403h px� 

VNo compile time benefit to using incremental synthesis; A full resynthesis will be run2353*designutilsZ20-5440h px� 
�
�Flow is switching to default flow due to incremental criteria not met. If you would like to alter this behaviour and have the flow terminate instead, please set the following parameter config_implementation {autoIncr.Synth.RejectBehavior Terminate}2229*designutilsZ20-4379h px� 
�
HMultithreading enabled for synth_design using a maximum of %s processes.4828*oasys2
22default:defaultZ8-7079h px� 
a
?Launching helper process for spawning children vivado processes4827*oasysZ8-7078h px� 
`
#Helper process launched with PID %s4824*oasys2
206842default:defaultZ8-7075h px� 
�
5undeclared symbol '%s', assumed default net type '%s'7502*oasys2
REGCCE2default:default2
wire2default:default2[
EC:/Xilinx/Vivado/2022.2/data/verilog/src/unimacro/BRAM_SINGLE_MACRO.v2default:default2
21702default:default8@Z8-11241h px� 
�
5undeclared symbol '%s', assumed default net type '%s'7502*oasys2#
displayInputSel2default:default2
wire2default:default2t
^C:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/stopwatch.v2default:default2
492default:default8@Z8-11241h px� 
�
5undeclared symbol '%s', assumed default net type '%s'7502*oasys2

registerEN2default:default2
wire2default:default2t
^C:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/stopwatch.v2default:default2
502default:default8@Z8-11241h px� 
�
5undeclared symbol '%s', assumed default net type '%s'7502*oasys2$
registerInputSel2default:default2
wire2default:default2t
^C:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/stopwatch.v2default:default2
512default:default8@Z8-11241h px� 
�
5undeclared symbol '%s', assumed default net type '%s'7502*oasys2
	counterEN2default:default2
wire2default:default2t
^C:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/stopwatch.v2default:default2
522default:default8@Z8-11241h px� 
�
5undeclared symbol '%s', assumed default net type '%s'7502*oasys2 
counterReset2default:default2
wire2default:default2t
^C:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/stopwatch.v2default:default2
532default:default8@Z8-11241h px� 
�
5undeclared symbol '%s', assumed default net type '%s'7502*oasys2
r22default:default2
wire2default:default2t
^C:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/stopwatch.v2default:default2
652default:default8@Z8-11241h px� 
�
%s*synth2�
yStarting RTL Elaboration : Time (s): cpu = 00:00:06 ; elapsed = 00:00:10 . Memory (MB): peak = 1205.844 ; gain = 408.797
2default:defaulth px� 
�
synthesizing module '%s'%s4497*oasys2
	stopwatch2default:default2
 2default:default2t
^C:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/stopwatch.v2default:default2
232default:default8@Z8-6157h px� 
�
synthesizing module '%s'%s4497*oasys2*
stopwatch_control_unit2default:default2
 2default:default2�
kC:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/stopwatch_control_unit.v2default:default2
232default:default8@Z8-6157h px� 
�
synthesizing module '%s'%s4497*oasys26
"stopwatch_state_transition_control2default:default2
 2default:default2�
wC:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/stopwatch_state_transition_control.v2default:default2
232default:default8@Z8-6157h px� 
�
'done synthesizing module '%s'%s (%s#%s)4495*oasys26
"stopwatch_state_transition_control2default:default2
 2default:default2
02default:default2
12default:default2�
wC:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/stopwatch_state_transition_control.v2default:default2
232default:default8@Z8-6155h px� 
�
synthesizing module '%s'%s4497*oasys2,
stopwatch_output_control2default:default2
 2default:default2�
mC:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/stopwatch_output_control.v2default:default2
232default:default8@Z8-6157h px� 
�
'done synthesizing module '%s'%s (%s#%s)4495*oasys2,
stopwatch_output_control2default:default2
 2default:default2
02default:default2
12default:default2�
mC:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/stopwatch_output_control.v2default:default2
232default:default8@Z8-6155h px� 
�
'done synthesizing module '%s'%s (%s#%s)4495*oasys2*
stopwatch_control_unit2default:default2
 2default:default2
02default:default2
12default:default2�
kC:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/stopwatch_control_unit.v2default:default2
232default:default8@Z8-6155h px� 
�
synthesizing module '%s'%s4497*oasys2;
'four_digit_binary_coded_decimal_counter2default:default2
 2default:default2�
|C:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/four_digit_binary_coded_decimal_counter.v2default:default2
232default:default8@Z8-6157h px� 
�
synthesizing module '%s'%s4497*oasys29
%four_bit_binary_coded_decimal_counter2default:default2
 2default:default2�
zC:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/four_bit_binary_coded_decimal_counter.v2default:default2
232default:default8@Z8-6157h px� 
�
-case statement is not full and has no default155*oasys2�
zC:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/four_bit_binary_coded_decimal_counter.v2default:default2
402default:default8@Z8-155h px� 
�
'done synthesizing module '%s'%s (%s#%s)4495*oasys29
%four_bit_binary_coded_decimal_counter2default:default2
 2default:default2
02default:default2
12default:default2�
zC:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/four_bit_binary_coded_decimal_counter.v2default:default2
232default:default8@Z8-6155h px� 
�
'done synthesizing module '%s'%s (%s#%s)4495*oasys2;
'four_digit_binary_coded_decimal_counter2default:default2
 2default:default2
02default:default2
12default:default2�
|C:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/four_digit_binary_coded_decimal_counter.v2default:default2
232default:default8@Z8-6155h px� 
�
synthesizing module '%s'%s4497*oasys2#
display_control2default:default2
 2default:default2z
dC:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/display_control.v2default:default2
232default:default8@Z8-6157h px� 
�
synthesizing module '%s'%s4497*oasys2%
get_segment_value2default:default2
 2default:default2|
fC:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/get_segment_value.v2default:default2
232default:default8@Z8-6157h px� 
�
'done synthesizing module '%s'%s (%s#%s)4495*oasys2%
get_segment_value2default:default2
 2default:default2
02default:default2
12default:default2|
fC:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/get_segment_value.v2default:default2
232default:default8@Z8-6155h px� 
�
'done synthesizing module '%s'%s (%s#%s)4495*oasys2#
display_control2default:default2
 2default:default2
02default:default2
12default:default2z
dC:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/display_control.v2default:default2
232default:default8@Z8-6155h px� 
�
:variable '%s' should not be used in output port connection685*oasys2
segment2default:default2t
^C:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/stopwatch.v2default:default2
662default:default8@Z8-685h px� 
�
!failed synthesizing module '%s'%s4496*oasys2
	stopwatch2default:default2
 2default:default2t
^C:/Users/no_kn/Documents/unh/coursework/ece583/vivado/lab5/lab5.srcs/sources_1/new/stopwatch.v2default:default2
232default:default8@Z8-6156h px� 
�
%s*synth2�
yFinished RTL Elaboration : Time (s): cpu = 00:00:07 ; elapsed = 00:00:13 . Memory (MB): peak = 1295.730 ; gain = 498.684
2default:defaulth px� 
U
Releasing license: %s
83*common2
	Synthesis2default:defaultZ17-83h px� 
�
G%s Infos, %s Warnings, %s Critical Warnings and %s Errors encountered.
28*	vivadotcl2
332default:default2
02default:default2
02default:default2
32default:defaultZ4-41h px� 
N

%s failed
30*	vivadotcl2 
synth_design2default:defaultZ4-43h px� 
�
Command failed: %s
69*common2Y
ESynthesis failed - please see the console or run log file for details2default:defaultZ17-69h px� 
�
Exiting %s at %s...
206*common2
Vivado2default:default2,
Thu May  4 14:55:40 20232default:defaultZ17-206h px� 


End Record