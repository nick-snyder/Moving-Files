% ECE717 Introduction to Digital Image Processing
%
%Copyright Richard A. Messner 2020
%ALL RIGHTS RESERVED
%
%=======================================================================
% Lab 1
%=======================================================================
% Inital Create Date 2/10/08
% Updated by RAM March 2014
% Modified by JG 2/19/2015
% Updated by RAM Feb 2020
%=======================================================================
%
%=======================================================================
%                             Decimation
%=======================================================================
% Decimation is another way of reducing image resolution.  Decimation works
% by essentially throwing away rows and columns of pixels.  For example,
% decimation by a factor of 2 in the vertical dimension would mean that
% every two rows of pixels in the source image becomes one row in the
% destination image.  Decimation in the horizontal direction would decrease
% the number of columns in the destination image in a similar way.

% In general, decimation by a factor n means that for every N rows in the
% source image, 1 row is placed in the result image and N-1 rows are thrown
% away (the same holds true for columns).  Since pixels are being thrown
% away, the dimensions of the resultant image are smaller than the source.
% In order to expand the image back to its original size, nearest-neighbor
% interpolation can be used.  Nearest-neighbor is one of the simplest forms
% of expanding the number of pixels in an image, as it simply involves
% replicating adjacent rows and columns of pixels.  For example, expanding
% the image by a factor of N along the vertical direction simply involves
% taking every row in the source image and making n copies of it in the
% result image.          

%=======================================================================
%  Clean up enviornment
%======================================================================= 
close all; % close all opened graphs
clear all; % clear all variables
clc        % Clear Command Windwo
%=======================================================================
%=======================================================================

%=======================================================================
% Set Decimation Factor
%=======================================================================
% DF = 1; 
DF=input("Type in Decimation Factor (integer from 1 to 64)")

%=======================================================================
% Read Image From File
%=======================================================================
I = imread('peppers.png');

%=======================================================================
% Convert Color Image to Grayscale
%=======================================================================
Ii = rgb2gray(I);


%=======================================================================
% Implementation of Horizontal Decimation
%=======================================================================
[Height, Width] = size(Ii) % Display the image height and width
IoD = Ii(1:DF:Height, 1:DF:Width); % True Decimation
IoNN = imresize(IoD, [Height, Width], 'nearest'); %  Horizontal expanding

%=======================================================================
% Display
%=======================================================================
figure(1)
imshow(Ii)
title('Input image, Ii')
impixelinfo

figure(2)
imshow(IoD)
title('Same image after decimation, IoD')
impixelinfo

figure(3)
imshow(IoNN)
title('Nearest neighbor expanded image, IoNN')
impixelinfo


