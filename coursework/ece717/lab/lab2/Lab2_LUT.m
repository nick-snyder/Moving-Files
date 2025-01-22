% ECE717 Introduction to Digital Image Processing
%
%Copyright Richard A. Messner 2020
%ALL RIGHTS RESERVED
%
%=======================================================================
% Lab 2  LUT - "look-up tables"
%=======================================================================
% Updated by RAM 17 Feb 2015
% Updated by RAM 13 Feb 2018
% Updated by RAM 13 Feb 2020
% Updated by RAM 18 Feb 2024
% 
%=======================================================================
%  Clean up enviornment
%======================================================================= 
close all; % close all opened graphs
clear all; % clear all variables
clc        % Clear Command Windwo
%=======================================================================
%=======================================================================
%  Read in image rose256.tif , display image, title image
%=======================================================================
InputImage = imread('gress.jpg');
InputImage = rgb2gray(InputImage);
%=======================================================================
% Other Images to work with, please choose more of your own to explore
%=======================================================================
% InputImage = imread('saturn.png');
% InputImage = rgb2gray(InputImage);
% 
% InputImage = imread('saturn2.png');
% InputImage = rgb2gray(InputImage);
% 
% InputImage = imread('gramp.jpg');
% InputImage = rgb2gray(InputImage);

% InputImage = imread('WindPoint.tif');
% InputImage = rgb2gray(InputImage);

%=======================================================================
% Define input intensity
%=======================================================================
Ii = 0:255;
%=======================================================================
% Generate Some Standard LUTs for output intensity
%=======================================================================
% Io = Ii;                                            % Normal transform
Io = 255 - Ii;                                      % Negative transform
%Io(1:128) = Ii(1:128)*2;  Io(129:256)=255;          % Stretch x2
%Io = floor(Ii/2);                                   % Shrink x2
%Io(1:128)=0;Io(129:256)=255;                        % Hard Threshold
%=======================================================================
% User defined LUT's = Example given, Student should make more user
% defined LUTS.   Be Creative!
%=======================================================================
%Io = Ii;   Io(150:180) = 230;

% Add more here
% Io(1:128)=Ii(1:128)+128; Io(129:256)=Ii(129:256)-128;    % 2's Complement

%=======================================================================
% Display inital image
%=======================================================================
figure; % Create a new figure
imshow(InputImage); % Display the input image
title('Initial Input Image'); % Title the figure
%=======================================================================
% Display LUT Mapping
%=======================================================================
figure; % Create new figure
plot(Ii,Io); %plot the input vs output LUT
% stem(Ii,Io); % Stem plot the input vs output LUT
axis([ 1 256 1 256 ]); % Place Axis
title('LUT Applied'); % Title Figure
xlabel('Input intensity'); % X Label
ylabel('Output intensity'); % Y Label
%=======================================================================
% Display transformed image
%=======================================================================
figure; % Create new figure
colormap = [Io' Io' Io']/255;  % Produce Colormap for Gray Scale
imshow(InputImage, colormap); % Display with Colormap
title('Transformed image'); % Title figure
Io1=uint8(Io); % Change Io to integer
B=intlut(InputImage,Io1); % Produce uint8 image from LUT
%=======================================================================
% Perform Two's complement using INTLUT
%=======================================================================

%      LUT=uint8(zeros([1 256]));
%      LUT(1:128)=Ii(1:128)+128;
%      LUT(129:256)=Ii(129:256)-128;
%      OutputImage=intlut(InputImage,LUT);
% Displays
%      figure;
%      imshow(InputImage);
%      title('Initial Input Image');
%         
%      figure;
%      imshow(OutputImage);
%      title('2s Complement Image');
%=======================================================================
% Two's Complement applied twice
%=======================================================================
     LUT=uint8(zeros([1 256]));
     LUT(1:128)=Ii(1:128)+128;
     LUT(129:256)=Ii(129:256)-128;
     MiddleImage=intlut(InputImage,LUT);
     OutputImage=intlut(MiddleImage,LUT);
     %Displays
        figure
        imshow(InputImage)
        title('Initial Input Image')
        
        figure
        imshow(MiddleImage)
        title('After One 2s Complement Image')
        
        figure
        imshow(OutputImage)
        title('After Two 2s Complement Image')
%=======================================================================




