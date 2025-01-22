%ECE717/817 - Introduction to Digital Image Processing 
%Copyright ECE Department University of New Hampshire 2008
%ALL RIGHTS RESERVED
%
%                     Median filtering
%


% Read image from file
I = imread('peppers.png');
% Convert color image to grayscale
Ii = rgb2gray(I);

% Apply "salt and pepper" noise to the image
 Ii = imnoise(Ii,'salt & pepper',0.02);

 % Display
figure(4), imshow(Ii)
title('Image with "Salt and Pepper" noise') 

% -------------------- MEDIAN FILTERING ---------------------------
Io =  medfilt2(Ii,[3 3]);

% Display
figure(5), imshow(Io)
title('Image after median filtering')

