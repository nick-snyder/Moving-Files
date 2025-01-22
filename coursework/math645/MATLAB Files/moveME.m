% This script will move the letter N about the screen using
% homogeneous coordinate transformations common to computer graphics

p1=[0;0]; p2=[1;2]; p3=[0;4]; p4=[2;3]; p5=[4;4]; p6=[3;2]; p7=[4;0]; p8=[2;1];
star2dMatrix = [p1, p2, p3, p4, p5, p6, p7, p8]

hold on

star3dMatrix = [star2dMatrix;ones(1,8)]

color = str2mat('y','m','c','r','g','b','k');

x=0; y=0;

while true

    for x=1:4
    
        for y=1:4
    
            shift = [ 1 0 x; 0 1 y; 0 0 1]
            star3dAfterTransformation = shift * star3dMatrix
            star2dAfterTransformation = star3dAfterTransformation(1:2,:);
       
        end
    
    end

    fill(star2dAfterTransformation(1,:),star2dAfterTransformation(2,:),color(rem(x,7)+1))
        
    pause(0.15);

end

hold off
