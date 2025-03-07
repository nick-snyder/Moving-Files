% Create and plot a sphere with radius r.
[x,y,z] = sphere;       % Create a unit sphere.
r = 2;
surf(x*r,y*r,z*r)       % Adjust each dimension and plot.
axis equal              % Use the same scale for each axis.

% Find the surface area and volume.
A = 4*pi*r^2;
V = (4/3)*pi*r^3;