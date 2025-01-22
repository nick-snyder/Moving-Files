f = imread('rose256.tif');
imshow(f)
imwrite(imrotate(f, 180), 'rose256_upside_down.tif')
figure, imshow(imrotate(f, 180))
imfinfo('rose256_upside_down.tif')
g = imread('rice256.png');
figure, imshow(g), colormap jet, figure, imshow(g)
impixelinfo
colorbar
figure, imshow(imabsdiff(f, g))
m = imread('moped.jpg');
M = [0.30, 0.59, 0.11];
gray = imapplymatrix(M, m);
figure
subplot(1,2,1), imshow(m), title('Original RGB')
subplot(1,2,2), imshow(gray), title('Grayscale conversion')
I = imread('mountain.jpg');
J = imcomplement(I);
figure
subplot(1,2,1), imshow(I), title('Original')
subplot(1,2,2), imshow(J), title('Complement')
I = imread('nighthawks.jpg');
J = imdivide(I, 2);
figure
subplot(1,2,1), imshow(I), title('Original')
subplot(1,2,2), imshow(J), title('Darkened')
I = imread('rivian.JPG');
J = imlincomb(2, I);
figure
subplot(1,2,1), imshow(I), title('Original')
subplot(1,2,2), imshow(J), title('brightened by factor of 2')
I = imread('crosskart.jpg');
J = immultiply(I, 2);
figure
subplot(1,2,1), imshow(I), title('Original')
subplot(1,2,2), imshow(J), title('brightened by factor of 2')
I = imread('cake.jpg');
Iq = imsubtract(I,50);
figure
subplot(1,2,1), imshow(I), title('Original')
subplot(1,2,2), imshow(Iq,[]), title('Image darkened by 50')
f = imread('rose256.tif');
g = imread('rice256.png');
figure, imshow(imadd(f, g))
f = imread('rose256.tif');
g = imread('rice256.png');
figure 
imshow(g)
impixelinfo
imshow(g), colormap summer
impixelinfo
imshow(g), colormap winter
impixelinfo 
figure
imwrite(imrotate(f, 45), 'f11c.tif')
subplot(1,2,1), imshow(f)
subplot(1,2,2), imshow(imrotate(f, 45))
f_small = imresize(f, 0.5);
f_big = imresize(f_small, 2);
figure
subplot(1,3,1), imshow(f)
subplot(1,3,2), imshow(f_small)
subplot(1,3,3), imshow(f_big) 
figure
subplot(1,5,1), imshow(f)
subplot(1,5,2), imshow(grayslice(f, 2), jet(2))
subplot(1,5,3), imshow(grayslice(f, 4), jet(4))
subplot(1,5,4), imshow(grayslice(f, 16), jet(16))
subplot(1,5,5), imshow(grayslice(f, 32), jet(32)) 
figure
subplot(1,5,1), imshow(g)
subplot(1,5,2), imshow(grayslice(g, 2), jet(2))
subplot(1,5,3), imshow(grayslice(g, 4), jet(4))
subplot(1,5,4), imshow(grayslice(g, 16), jet(16))
subplot(1,5,5), imshow(grayslice(g, 32), jet(32))
imwrite(f, 'rose256.tif', 'jpg');
imwrite(g, 'rice256.tif', 'jpg');
a = imsubtract(f, g);
b = imsubtract(g, f);
figure
subplot(1,2,1), imshow(a)
subplot(1,2,2), imshow(b)
% c = cast(imadd(f, g), "uint16");
c = imadd(cast(f, 'uint16'), cast(g, 'uint16'));
figure
subplot(1,3,1), imshow(imadd(f, g), jet(256)), title('uint8')
subplot(1,3,2), imshow(c, jet(256)), title('uint16') 
subplot(1,3,3), imshow(imabsdiff(cast(imadd(f, g), "uint16"), c), jet(256)), title('Absolute Difference')
d = imdivide(imadd(f, g), 2);
e = imlincomb(0.5,f,0.5,g);
figure
subplot(1,2,1), imshow(d)
subplot(1,2,2), imshow(e)
i = imcomplement(f);
figure
subplot(1,2,1), imshow(f)
subplot(1,2,2), imshow(i)
mask = false(256, 256);
mask(70:220, 70:190) = true;
figure
imshow(mask)
f_mask = immultiply(f, mask);
g_mask = immultiply(g, mask);
figure
subplot(1,2,1), imshow(f_mask)
subplot(1,2,2), imshow(g_mask)