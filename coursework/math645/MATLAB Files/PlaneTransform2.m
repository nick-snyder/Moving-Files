function [Aout]=PlaneTransform2(A,NumIters)
% This is a MATLAB function which takes a 2x2 matrix
% and multiplies it by several unit length vectors.  
% It can be used to view matrix transformations
% of the plane.
% The matrix must be a 2 x 2 matrix in the workspace.
% NumIters is the number of iterations you want to use.
%USAGE: [Aout]=PlaneTransform(A,NumIters)


if size(A) ~= [2,2]
fprintf('A must be a 2 x 2 matrix\n');
return;
end

color = str2mat('b.','r.','g.','m.','c.','y.','k.');
cc1 = str2mat('b *','r *','g *','m *','c *','y *','k *');
cc2 = str2mat('b o','r o','g o','m o','c o','y o','k o');

% Creating unit vectors
figure;

it=0;
NN=64;
if it == 0
	
	V=zeros(2,NN);
    V = [cos(2*pi*[0:NN-1]/NN); sin(2*pi*[0:NN-1]/NN)];
    Vorig=V;

end

plot(V(1,:),V(2,:),'b.')

hold on
plot(V(1,1),V(2,1),'b*')
plot(V(1,NN/4+1),V(2,NN/4+1),'bo')
title('Original Vectors - notice the circled point and the starred point')
fprintf('Hit any key to continue.\n')
pause

for kk=1:NumIters
V=A*V;

plot(V(1,:),V(2,:),color(rem(kk,7)+1,:)) 
plot(V(1,1),V(2,1),cc1(rem(kk,7)+1,:))
plot(V(1,NN/4+1),V(2,NN/4+1),cc2(rem(kk,7)+1,:))


axis('equal')
fprintf('Hit any key to continue.\n')
pause
end
hold off
Aout=V;
