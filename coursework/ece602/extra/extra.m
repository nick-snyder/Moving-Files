% ECE 602 EC
% 
% Consider an electric dipole in free space on the x-y plane with a positive charge Q 
% located at +b on y-axis and a negative charge Q located at -b on y-axis. 
% 
% Derive the Electric Field for a general point on the x-y plane (E(x, y, 0)). 
% Submit your derivation as a pdf file in Canvas. 
% 
% Plot the Electric Field in Matlab using Q = 4πε Coulombs and b = 1 meter. 
% Submit your Matlab file (*.m) in Canvas. 


% Only simulates dipole with equal an opposite charge at each end. 
% Only works when -2 < x, y < 2

% epsilon = 1;    % permittivity
% Q = 4 * pi * epsilon;   % Coulomb
% b = 1;  % meter

% counter variable keeping track of next matrix position to be filled
i = 1;

A=0;    % x-coordinate of negative end of dipole
C=0;    % x-coordinate of positive end of dipole
B=1;    % y-coordinate of either end of dipole (0, 1)+, (0, -1)-

% empty matrix of every possible data point at a resolution (21x21)
Field = zeros(4, 441);  

% for every position in the x-direction
for D=-2:0.2:2

    % for every position in the y- direction
    for E=-2:0.2:2
        
        F=((D-A)^2+(E+B)^2)^1.5;
        G=((D-C)^2+(E-B)^2)^1.5;
        H=(D-A)/F;
        I=(E+B)/F;
        J=(D-C)/G;
        K=(E-B)/G;

        L=J-H;  % a-x-hat
        M=K-I;  % a-y-hat

        % add data point to matrix
        vector = [D; E; L; M];
        Field(:, i) = vector;

        % increment counter
        i = i + 1;
    end
end

% The first two rows of the matrix are the x and y of the data point.
% The last two rows are the vectors of each induvidual data point.
quiver(Field(1, :), Field(2, :), Field(3, :), Field(4, :));

axis([-2.2 2.2 -2.2 2.2]);
title('Electric Field');
xlabel('x');
ylabel('y');