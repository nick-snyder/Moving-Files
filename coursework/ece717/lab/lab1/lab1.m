I = imread('prescription.jpg');
Ii = rgb2gray(I);
QF = 2;
imshow(Ii)
title('Input image, Ii')
Itemp = imresize(Ii,1/QF);
imshow(Itemp)
title('Temporaty image, Itemp')
Io = imresize(Itemp, QF, 'nearest');
imshow(Io)
title('QF = 2')
QF = 8;
Itemp = imresize(Ii,1/QF);
Io = imresize(Itemp, QF, 'nearest');
imshow(Io)
title('QF = 8')
QF = 32;
Itemp = imresize(Ii,1/QF);
Io = imresize(Itemp, QF, 'nearest');
imshow(Io)
title('QF = 32')
I = imread('prescription.jpg');
Ii = rgb2gray(I);
[Height, Width] = size(Ii) % Display the image height and width
imshow(Ii)
title('Input image, Ii')
DF = 8; 
IoD = Ii(1:DF:Height, 1:DF:Width); % True Decimation
IoNN = imresize(IoD, [Height, Width], 'nearest'); %  Horizontal expanding
imshow(IoNN)
title('DF = 8')DF = 32; 
IoD = Ii(1:DF:Height, 1:DF:Width); % True Decimation
IoNN = imresize(IoD, [Height, Width], 'nearest'); %  Horizontal expanding
imshow(IoNN)
title('DF = 32')
I = imread('capsule.jpg');
Ii = rgb2gray(I);
imshow(Ii)
title('Input image')
N = 8;
NumberOfIntensityLevels = 2^N;
[Io, map] = gray2ind(Ii, NumberOfIntensityLevels); 
imshow(Io, map);
title(['Same image after intensity quantization, ',num2str(2^N), ' gray levels'])
N = 6;
NumberOfIntensityLevels = 2^N;
[Io, map] = gray2ind(Ii, NumberOfIntensityLevels); 
imshow(Io, map);
title(['Same image after intensity quantization, ',num2str(2^N), ' gray levels'])N = 1;
NumberOfIntensityLevels = 2^N;
[Io, map] = gray2ind(Ii, NumberOfIntensityLevels); 
imshow(Io, map);
title(['Same image after intensity quantization, ',num2str(2^N), ' gray levels'])