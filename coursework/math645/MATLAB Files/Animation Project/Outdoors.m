
% Write-up (Outdoors.m)
% My animation uses shifting, morphing, rescaling, and rotating to show 
% Ash walk around in some tall grass outside professor Oak's house. Each 
% move is a shift in a specified direction. Each turn is a morph from a 
% charater facing one direction to one facing another. When Ash encounters 
% a wild pokemon, alternating frames of the background image are drawn to 
% the screen. The background is then sliced up and shifted to either side 
% of the visible screen. Ash then seemingly flies away with the help of a 
% gradual scale and rotation (not around the origin). The Nintendo 
% watermark is passed through each members animation and in my case, is 
% present in the upper-left corner of the screen. More in-depth 
% descriptions of each function are found in the comments above each 
% respective function.  
%                                                   - Nick Snyder

function out = Outdoors(watermark)

    % setup
    % read in scene
    scene = read('Scene.jpg');
    scene_inverted = read('Scene_inverted.jpg');
    ash_left = read('Ash_Left.jpg');
%     ash_right = read('Ash_Right.jpg');
    ash_up = read('Ash_Up.jpg');
    ash_down = read('Ash_Down.jpg');
    
    % add extra points to all matrices
    % all ash copies should have 100 points
    ash_left = addPoints(ash_left, 30);
%     ash_right = addPoints(ash_right, 30);
    ash_up = addPoints(ash_up, 5);
    ash_down = addPoints(ash_down, 15);
    scene = addPoints(scene, 266);
    
    
    % start of animation
    % display ash_down at 108,96
    ash = ash_down;
    ash = move(scene, ash, 108, 0, 0, 0, watermark);
    ash = move(scene, ash, 0, 96, 0, 0, watermark);
    frame(scene, ash, 0.5, 1, watermark);
    
    % ash turns west
    ash = turn(ash, ash_left);
    
    % ash move west to 76,96 (-32, 0)
    ash = move(scene, ash, -32, 0, 0.125, 1, watermark);
    frame(scene, ash, 0.5, 1, watermark);
    
    % ash turns south
    ash = turn(ash, ash_down);
    
    % ash moves south to 76,64 (0, -32)
    ash = move(scene, ash, 0, -32, 0.125, 1, watermark);
    frame(scene, ash, 0.5, 1, watermark);
    
    % ash turns west
    ash = turn(ash, ash_left);
    
    % ash moves west to 8,64 (-64, 0)
    ash = move(scene, ash, -64, 0, 0.125, 1, watermark);
    frame(scene, ash, 0.5, 1, watermark);
    
    % ash turns north
    ash = turn(ash, ash_up);
    
    % ash moves north to 8,72 (0, +8)
    ash = move(scene, ash, 0, 8, 0.125, 1, watermark);
    frame(scene, ash, 0.5, 1, watermark);
    
    
    % wild pokemon appears
    % invert scene colors
    for i=1:10
        if (mod(i, 2) == 1)
            frame(scene_inverted, ash, 0, 1, watermark);
        else
            frame(scene, ash, 0, 1, watermark);
        end
    end
    
    % slice scene
    scene = slice(scene, ash, watermark);
    
    % scale ash up and rotate
    for i=1:30
        % scale
        scale_factor = [1.05 0; 0 1.05];
        ash = scale_factor * ash;
    
        % rotate once around self
        rotation = [cos(pi/6), sin(pi/6); -sin(pi/6), cos(pi/6)];
        ash = rotate_around_self(ash, rotation);
    
        % draw frame
        frame(scene, ash, 0, 1, watermark);
    end

    out = watermark;
end

% functions

% turn
% transformations:
%     shifts  
%     morphs
% summary:    
%     to turn, first turned image matrix need to return to the origin from 
%     wherever it was before the function call. Then turned image matrix is 
%     moved to where the original image matrix is located. Original image 
%     matrix is morphed into the turned image matrix.
% parameters:
%     ash             original image matrix
%     ash_direction   turned image matrix
% outputs:
%     out             original now-turned image matrix
function out = turn(ash, ash_direction)

    % move based on point 1, (5,15)
    offset = [5; 15];

    % move wherever ash_direction is back to origin
    vector = [-1; 0];
    shift = vector * ones(1, 100);
    while ash_direction(1:1) ~= offset(1:1)
        ash_direction = ash_direction + shift;
    end
    vector = [0; -1];
    shift = vector * ones(1, 100);
    while ash_direction(1:2) ~= offset(1:2)
        ash_direction = ash_direction + shift;
    end

    % move ash_direction to where ash is
    vector = [1; 0];
    shift = vector * ones(1, 100);
    while ash_direction(1, 1) ~= ash(1, 1)
        ash_direction = ash_direction + shift;
    end
    vector = [0; 1];
    shift = vector * ones(1, 100);
    while ash_direction(2, 1) ~= ash(2, 1)
        ash_direction = ash_direction + shift;
    end

    for i = 0:1/8:1
	    ash = (1 - i) * ash + i * ash_direction;
    end

    out = ash;
end

% move
% transformations:
%     shifts
% summary:
%     moves character by specified amount in either x or y direction
% parameters:
%     scene       background image matrix. Used to draw frames
%     ash         character image matrix  
%     x           distance in x-direction to move
%     y           distance in y-direction to move
%     time        wait time after frame. Used to draw frames
%     display     boolean value to draw frame. Used to draw frames
% outputs:
%     out         moved character image matrix
function out = move(scene, ash, x, y, time, display, watermark)
        
    % for x and y direction, determine desired shift vector
    if (x < 0)
        vector = [-1; 0];
        i_end = abs(x);
    elseif (x > 0)
        vector = [1; 0];
        i_end = abs(x);
    elseif (y < 0)
        vector = [0; -1];
        i_end = abs(y);
    elseif (y > 0)
        vector = [0; 1];
        i_end = abs(y);
    else
        out = ash;
        return;
    end

    shift = vector * ones(1, 100);
    for i = 1:(i_end/2)
        for j = 1:2
            ash = ash + shift;
        end
        frame(scene, ash, time, display, watermark);
    end
    out = ash;
end

% slice
% transformations:
%     shifting
% summary:
%     shifts 'slices' or blocks of 250 pixels to alternating sides of 
%     background in four pixel increments. This implementation shifts said 
%     slices 41 times to remove all visible pixels from background
% paramerters:
%     scene       background image matrix
%     ash         character image matrix. Used for drawing frames
% outputs:
%     out         now off-screen scene. Ouptut scene is used for later frames
function out = slice(scene, ash, watermark)

    % block size
    n = 250;

    % iterate all blocks 16 times
    for i=1:41

        % for each block of pixels
        for j=1:16
            
            % determine if block should shift left or right
            if (mod(j, 2) == 1)
                % even blocks are shifted to the right
                vector = [1; 0];
            else
                % odd block are shift to the left
                vector = [-1; 0];
            end

            % create shift vector
            shift_vector = vector * ones(1, n);

            % shift each block by 1 pixel, 4 times. For smooth motion
            for k=1:4
                scene(:, n*(j-1)+1:n*(j)) = scene(:, n*(j-1)+1:n*(j)) + shift_vector; 
            end
        end
        frame(scene, ash, 0, 1, watermark);
    end
    out = scene;
end

% rotate_around_self
% transformations:
%     rotation
% summary:
%     rotates chracter around itself (center) by moving image to origin and
%     then rotating said image and placing image back to origional location
% parameters:
%     charater    image getting rotated
%     rotation    how much image will be rotated
% outputs:
%     out         character once rotated
function out = rotate_around_self(character, rotation)

    value = (character(2, 76) - character(2, 62)) / 2;

    % remember coordinates
    xcoord = character(1, 1); 
    ycoord = character(2, 1);

    % send to origin(shift in x and y directions)
    xcoords = character(1, :);
    ycoords = character(2, :);
    character(1, :) = xcoords - xcoord + value;
    character(2, :) = ycoords - ycoord + value;

    % rotate
    character = rotation * character;

    % move back to coordinates
    character(1, :) = character(1, :) + xcoord - value;
    character(2, :) = character(2, :) + ycoord - value;

    % return
    out = character;
end

% frame
% transformations:   
%     none
% summary:    
%     draws frame by combining character and scene. 
%       Simple fill command and axis specifications
% parameters: 
%     scene       background image
%     ash         character image
%     time        wait time after frame. Used for initial placement of ash
%     display     boolean value to draw frame. Used for initial placement of ash
% outputs:
%     none
function frame(scene, ash, time, display, watermark)
    if (display == 1)
        frame = [scene ash watermark];
        fill(frame(1, :), frame(2, :), 'white.')
        axis([0 160 16 160]);
        pause(time);
    end
end

% read 
% transformations:
%     none
% summary:
%     repeated code for reading in image
% parameters:
%     filename    string of filename
% outputs:
%     out         newly created matrix representation of image
function out = read(filename)
    out = imread(filename);
    out = Jpeg2pointsConverter(out, 200);
end

% addPoints
% transformations:
%     none
% summary:
%     repeated code for adding extra points to image matrix used for morphing
% parameters:
%     ash         character matrix
%     extra       number of extra points to be added to image matrix
% outputs:   
%     out         character matrix with added points
function out = addPoints(ash, extra)
    vector = [8; 8];    % arbitrary point in image
    extraPoints = vector * ones(1, extra);
    out = [ash(:, 1:extra), extraPoints, ash(:, (extra + 1):end)];
end
