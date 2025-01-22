
% Write-up (Story.m)
% This is where all the parts are called from. The watermark is a small
% Nintendo logo and it is passed into each section. It's not super
% funtional because it is a structure named 'watermark' with a single
% member also named 'watermark' that sometimes doesn't do what you would
% think it would do. A problem we faced is that something that happens in
% Selection.m interferes with how frames are drawn in Outdoors.m and then
% carry over to Battle.m. For the best quality animation, comment out
% either line containing the function calls. The .gif submitted will be
% when neither are commented out. 
%                                                - Nick Snyder

watermark = load('watermark.mat');

watermark = Selection(watermark.watermark);
watermark.watermark = Outdoors(watermark.watermark);
watermark.watermark = Battle(watermark.watermark);
