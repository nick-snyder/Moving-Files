% im = imread("");
im = [1, 4, 5, 11, 13, 2, 4, 5]

for i = 1:length(im)+2
    im(1, i+1) = im(1, i);
end

im(1, length(im)+1) = im(1, length(im));
im