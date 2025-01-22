% ECE717 Introduction to Digital Image Processing
%
% Copyright Richard A. Messner 2020
% ALL RIGHTS RESERVED
%
%=======================================================================
% Lab 1
%=======================================================================
% Initial Create Date: 2/10/08
% Updated by RAM Date: 2/4/2020
%
% 
%=======================================================================
%                    Intensity Quantization
%=======================================================================
%
% In this section, the effects of varying the intensity quantization of the
% image will be explored.  In practical terms, the intensity quantization
% is related to the number of bits used to store each pixel value.  Using
% fewer bits means allowing a smaller number of discrete gray levels.  This
% can have undesirable effects such as false contouring     

%=======================================================================
%  Clean up enviornment
%======================================================================= 
close all; % close all opened graphs
clear all; % clear all variables
clc        % Clear Command Windwo
%=======================================================================%

% Number of bits per color
N = 8; % N = 1 ... 8  bits

% Read image from file
I = imread('peppers.png');

% Convert color image to grayscale
Ii = rgb2gray(I);

% Intensity Quantization in MATLAB is done via color map reindexing
NumberOfIntensityLevels = 2^N;
[Io, map] = gray2ind(Ii, NumberOfIntensityLevels); 


% Display
figure(1)
imshow(Ii)
title('Input image')

figure(2)
imshow(Io, map);
title(['Same image after intensity quantization, N=',num2str(N)])
