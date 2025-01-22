% ECE717 Introduction to Digital Image Processing
%
% Copyright Richard A. Messner 2020
%
% ALL RIGHTS RESERVED
%
%=======================================================================
% Lab 2
%=======================================================================%
% Inital Create Date 2/4/2020
% Updated by RAM 18 Feb 2024
%
% Copyright University of New Hampshire 
%
%                         Histogram Equalization
% 
% This laboratory involves the exploration of manipulation of image
% histograms.  The student should use this script a framework for 
% exploring the use of histogram equalization and histogram specification
% on various images in order to solidify how they are used and their
% limitations
%
% ---------------------------------------------------------------
close all       % Remove all figures
clear all       % Clear the work space, i.e. all stored variables
clc             % Clear command window
% ---------------------------------------------------------------

% ---------------------------------------------------------------
% Read image from file
% --------------------------------------------------------------- 
% InputImage = imread('pout.tif');
% ---------------------------------------------------------------
% Other Images to work with, please choose more of your own to explore
% ---------------------------------------------------------------
% InputImage = imread('saturn2.png');
% InputImage = rgb2gray(InputImage);

% InputImage = imread('saturn.png');
% InputImage = rgb2gray(InputImage);

% InputImage = imread('gramp.jpg');
% InputImage = rgb2gray(InputImage);

% InputImage = imread('TEST.png');
% InputImage = rgb2gray(InputImage);

InputImage = imread('WindPoint.tif');
InputImage = rgb2gray(InputImage); % Convert RGB to Gray
% ---------------------------------------------------------------

figure
imshow(InputImage), title('Original Image'); % Display Original Image

% Display input image and histogram using subplots
figure
subplot(2, 1, 1), imshow(InputImage), title('Original Input Image');
subplot(2, 1, 2), imhist(InputImage), title('Histogram');

% Histogram Equalization
HistEqImg = histeq(InputImage); % Perform Histogram Equalization

figure, imshow(HistEqImg); % Display Histogram Equalized Original Image
title('Histogram Equalized');

figure
subplot(2, 1, 1), imshow(HistEqImg); title('Equalized Input Image');
subplot(2, 1, 2), imhist(HistEqImg,64), title('Histogram equalization')

% Custom equalization
% ---------------------------------------------------------------
%  The vector 'hgram' is a 'pattern' for the desired histogram that will be
%  approximated to it. It should contain integer counts for equally spaced
%  bins with intensity values in the appropriate range: [0, 255] for images
%  of class uint8
% ---------------------------------------------------------------
n=64;

% Examples:
% ---------------------------------------------------------------
hgram =0:256/n:255;     % linear 'pattern' for desired histogram
% hgram = 255:-256/n:0;  % reversed slope linear 'pattern' for desired histogram
% ---------------------------------------------------------------

HistEqImg = histeq(InputImage,hgram);

figure
imshow(HistEqImg), title('Histogram Specified Input Image (Ramp)');

figure
subplot(3, 1, 1), imshow(HistEqImg), title('Custom Equalized Input Image');
subplot(3, 1, 2), imhist(HistEqImg,n);
title('Custom Histogram equalized Input Image')
subplot(3, 1, 3), plot(hgram), title('Histogram Specified')