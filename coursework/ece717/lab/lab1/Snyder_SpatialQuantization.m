
% ECE717 Introduction to Digital Image Processing
%
% Copyright Richard A. Messner 2020
% ALL RIGHTS RESERVED
%
%=======================================================================
% Lab 1
%=======================================================================
% Initial Create Date: 2/10/08 RAM and PM
% Updated by RAM Date: 2/4/2020
%
% 
%=======================================================================
%                   Spatial Quantization
%=======================================================================
%
% The image you have loaded into MATLAB ("peppers.png") is composed
% of a matrix of samples (or pixels) 512 columns wide and 384 rows high.  
% The spatial resolution of this image would be the number of pixels per 
% unit area.  In this section, we will study the effects of reducing 
% spatial resolution through neighborhood averaging.
%
% The spatial quantization factor determines how big each square block will
% be.  For example, suppose a quantization factor (QF) of 4 is selected.  
% In this case, the input image should be divided up into square blocks of
% 4x4 pixels.

% The average (mean) value of the 16 pixels in each block will then be
% computed. Finally, the value of each of the 16 pixels in the block will
% replaced with this average value and written to the Result image.  
% Though the Result is still composed of a grid of 512x384 physical pixels,
% the effective spatial resolution has been reduced to 128x96.  
% This averaging approach is meant to approximate the way many real imaging
% sensor arrays, such as CCD's, operate.  
% 
% In short, a spatial quantization factor of 2 will halve the effective
% resolution, while a factor of three will decrease the effective 
% resolution to one third of the original, and so on.

%=======================================================================
%  Clean up enviornment
%======================================================================= 
close all; % close all opened graphs
clear all; % clear all variables
clc        % Clear Command Windwo
%=======================================================================%

% Quantization factor:
QF = 1; 

% Read image from file
I = imread('peppers.png');

% Convert color image to grayscale
Ii = rgb2gray(I);

%=======================================================================
% In order to perform spatial resampling MATLAB function 'imresize" is
% used. It is done in two steps: first to decrease image resolution (size),
% by Quantisation Factor; and then to return to original size using 
% the Nearest-neighbor interpolation. Nearest-neighbor is one of the
% simplest forms of expanding  the number of pixels in an image, as it
% simply involves replicating adjacent pixels.
% you may want to experiement with higher order interpolation in order
% to see their effects
%=======================================================================

Itemp = imresize(Ii,1/QF);
Io = imresize(Itemp, QF, 'nearest');

%=======================================================================
% Display
%=======================================================================
figure(1)
imshow(Ii)
title('Input image, Ii')

figure(2)
imshow(Itemp)
title('Temporaty image, Itemp')

figure(3)
imshow(Io)
title('Same image after spatial quantization, Io')
