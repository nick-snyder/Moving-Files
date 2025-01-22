imshow('text.png')
imfinfo('text.png')
% imshow('')
% imfinfo('')
imshow('blobs.png')
imfinfo('blobs.png')
imshow('kobi.png')
imfinfo('kobi.png')
imshow('m83.tif')
imfinfo('m83.tif')
r = imread('rice256.tif');
imfinfo('rice256.tif')
imwrite(r, 'rice256.jpg', 'jpg');
imfinfo('rice256.jpg')
imwrite(b, 'rice256.png', 'png');
imfinfo('rice256.png')
imwrite(b, 'rice256.bmp', 'bmp');
imfinfo('rice256.bmp')
c = imread('canoe.tif');
imshow(c)
imfinfo('canoe.tif')
imwrite(c, 'canoe.jpg', 'jpg');
imfinfo('canoe.jpg')
imwrite(c, 'canoe.png', 'png');
imfinfo('canoe.png')
imwrite(c, 'canoe.bmp', 'bmp');
imfinfo('canoe.bmp')
a = imread('autumn.tif');
imshow('autumn.tif')
imfinfo('autumn.tif')
imwrite(a, 'autumn.jpg', 'jpg');
imfinfo('autumn.jpg')
imwrite(a, 'autumn.png', 'png');
imfinfo('autumn.png')
imwrite(a, 'autumn.bmp', 'bmp');
imfinfo('autumn.bmp')
B = zeros(2, 2);
for i = 0:1
    for j = 0:1
        for k = 0:1
            for l = 0:1
                B = [i j; k l]
            end
        end
    end
end
tiledlayout(1, 2);
nexttile;
x = linspace(0, 10, 6);
y1 = x;
figure;
stairs(x, y1, 'b-', 'LineWidth', 1); 
xlabel('x');
ylabel('y');
grid on;
tiledlayout(1, 3);
nexttile;
for K1 = 0:10
    Ii = linspace(0, 10, 100);
    Io = K1 * log10(K2 + K3 * Ii);
    plot(Ii, Io, 'b-', 'LineWidth', 2);
    axis([0 10 0 25])
    xlabel('Input (I_i)');
    ylabel('Output (I_o)');
    title('0 <= K1 <= 10');
    grid on;
    hold on;
end
nexttile;
for K2 = 0:10
    Ii = linspace(0, 10, 100);
    Io = K1 * log10(K2 + K3 * Ii);
    plot(Ii, Io, 'b-', 'LineWidth', 2);
    axis([0 10 0 25])
    xlabel('Input (I_i)');
    ylabel('Output (I_o)');
    title('0 <= K2 <= 10');
    grid on;
    hold on;
end
nexttile;
for K3 = 0:10
    Ii = linspace(0, 10, 100);
    Io = K1 * log10(K2 + K3 * Ii);
    plot(Ii, Io, 'b-', 'LineWidth', 2);
    axis([0 10 0 25])
    xlabel('Input (I_i)');
    ylabel('Output (I_o)');
    title('0 <= K3 <= 10');
    grid on;
    hold on;
end
r = imread('rice256.tif');
num_levels = 8
x = 0:pi/4:2*pi;
v = sin(x);
xq = 0:pi/16:2*pi;
vq1 = interp1(x, v, xq);
figure;
plot(x, v, 'o', xq, vq1, ':');
xlim([0 2*pi]);
title('(Default) Linear Interpolation');
vq2 = interp1(x, v, xq, 'spline');
figure;
plot(x, v, 'o', xq, vq2, ':');
xlim([0 2*pi]);
title('Spline Interpolation');
[X,Y] = meshgrid(-3:3);
V = peaks(X,Y);
figure
surf(X,Y,V)
title('Original Sampling');
[Xq,Yq] = meshgrid(-3:0.25:3);
Vq = interp2(X,Y,V,Xq,Yq,'cubic');
figure
surf(Xq,Yq,Vq);
title('Cubic Interpolation Over Finer Grid');