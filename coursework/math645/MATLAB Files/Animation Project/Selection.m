
% Write-up (Selection.m)
% For this project, I was in charge of selecting Pokemon in the first scene, 
% making Pokemon move left and right up and down, looking like dancing, 
% changing colors, rotating and sheaing and adding some subtitles. 
% Unfortunately, I didn't make it morphing work at the last. It was a great 
% teamwork experience, and we chose very interesting themes.
%                                                   - Hao Wang

function out = Selection(watermark)
    A =imread('Hao3.jpg'); 
    A = Jpeg2pointsConverter(A,100); %I use 220 but it is to vague to see it , so I use 100
    [Nr,Nc]=size(A); 
    plot(A(1,:),A(2,:),'.','color','k');% using color k
    B = imread('Hao2.jpg'); 
    B = Jpeg2pointsConverter(A,100);
    plot(B(1,:),B(2,:),'.','color','k')
    watermark = load('watermark.mat');
    
    
    axis([-300 300 -300 300]);% axis setting
    hold on 
    % (b) shifts
    x= [-230;240; 1];
    x2= [-230;200; 1];
    x3= [-230;180; 1];
    x1= [-230;220; 1];
    x4= [-230;160; 1];
    x5= [-230;140; 1];
    A = [A;ones(1,Nc)];
    
    for D=0:5% 10 times
        
        CC =[1 0 D; 0 1 0; 0 0 1]; % scale
        A = CC * A; 
        Q = A(1:2,:);
        plot(Q(1,:),Q(2,:),'.','color','k');% set the color to black
        hText = text(x(1),x(2) ,'Thanks for choosing me!');
        pause(0.1); 
        plot(Q(1,:),Q(2,:),'.','color','w');% make the back ground to white
        plot(x(1),x(2),'.','color','w')
       
        
        
    end
    
    for D=0:5% 10 times
        
        CC =[1 0 -2*D; 0 1 0; 0 0 1]; % scale
        A = CC * A; 
        x = CC * x;
        Q = A(1:2,:);
        plot(Q(1,:),Q(2,:),'.','color','k');% set the color to black
     
        hText = text(x1(1),x1(2) ,'Im your Pokemon');
        pause(0.1); 
        plot(Q(1,:),Q(2,:),'.','color','w');% make the back ground to white
    
        
    end
    
    for D=0:8% 10 times
        
        CC =[1 0 2*D; 0 1 0; 0 0 1]; % scale
        A = CC * A; 
        Q = A(1:2,:);
        plot(Q(1,:),Q(2,:),'.','color','k');% set the color to black
        pause(0.1); 
        plot(Q(1,:),Q(2,:),'.','color','w');% make the back ground to white
    end
    for D=0:8% 10 times
        
        CC =[1 0 -2*D; 0 1 0; 0 0 1]; % scale
        A = CC * A; 
        Q = A(1:2,:);
        plot(Q(1,:),Q(2,:),'.','color','k');% set the color to black
        pause(0.1); 
        plot(Q(1,:),Q(2,:),'.','color','w');% make the back ground to white
    end
    for D=0:7
        
        CC =[1 0 3*D; 0 1 0; 0 0 1]; % scale
        A = CC * A; 
        Q = A(1:2,:);
        plot(Q(1,:),Q(2,:),'.','color','k');% set the color to black
        pause(0.1); 
        plot(Q(1,:),Q(2,:),'.','color','w');% make the back ground to white
    end
    for D=0:7
        
        CC =[1 0 -3*D; 0 1 0; 0 0 1]; % scale
        A = CC * A; 
        Q = A(1:2,:);
        plot(Q(1,:),Q(2,:),'.','color','k');% set the color to black
        pause(0.1); 
        plot(Q(1,:),Q(2,:),'.','color','w');% make the back ground to white
    end
    for D=0:7
        
        CC =[1 0 3*D; 0 1 0; 0 0 1]; % scale
        A = CC * A; 
        Q = A(1:2,:);
        plot(Q(1,:),Q(2,:),'.','color','k');% set the color to black
        pause(0.1); 
        plot(Q(1,:),Q(2,:),'.','color','w');% make the back ground to white
    end
    for D=0:7
        
        CC =[1 0 -2*D; 0 1 0; 0 0 1]; % scale
        A = CC * A; 
        Q = A(1:2,:);
        plot(Q(1,:),Q(2,:),'.','color','k');% set the color to black
        pause(0.1); 
        plot(Q(1,:),Q(2,:),'.','color','w');% make the back ground to white
    end
    
    
    %up and down/////////////////////
     for D=1: 5
        cc=[1 0 0; 0 1 5*D; 0 0 1];
        A = cc * A;
        Q = A(1:2,:);
        hText = text(x2(1),x2(2) ,'Lets do dance!');
        plot(Q(1,:),Q(2,:),'.','color','k');
        pause(0.1);
        plot(Q(1,:),Q(2,:),'.','color','w');
    end
     for D=1: 5
        cc=[1 0 0; 0 1 -5*D; 0 0 1];
        A = cc * A;
        Q = A(1:2,:);
        plot(Q(1,:),Q(2,:),'.','color','k');
        pause(0.1);
        plot(Q(1,:),Q(2,:),'.','color','w');
     end
     for D=1: 5
        cc=[1 0 0; 0 1 5*D; 0 0 1];
        A = cc * A;
        Q = A(1:2,:);
        plot(Q(1,:),Q(2,:),'.','color','k');
        pause(0.1);
        plot(Q(1,:),Q(2,:),'.','color','w');
    end
     for D=1: 5
        cc=[1 0 0; 0 1 -5*D; 0 0 1];
        A = cc * A;
        Q = A(1:2,:);
        plot(Q(1,:),Q(2,:),'.','color','k');
        pause(0.1);
        plot(Q(1,:),Q(2,:),'.','color','w');
     end
     for D=1: 5
        cc=[1 0 0; 0 1 5*D; 0 0 1];
        A = cc * A;
        Q = A(1:2,:);
        plot(Q(1,:),Q(2,:),'.','color','k');
        pause(0.1);
        plot(Q(1,:),Q(2,:),'.','color','w');
    end
     for D=1: 5
        cc=[1 0 0; 0 1 -5*D; 0 0 1];
        A = cc * A;
        Q = A(1:2,:);
        plot(Q(1,:),Q(2,:),'.','color','k');
        pause(0.1);
        plot(Q(1,:),Q(2,:),'.','color','w');
    end
    
    % (a) rotations
    N = [Q;ones(1,Nc)];
    N1=N;
    R = [cos(pi/3) -sin(pi/3) 0; sin(pi/3) cos(pi/3) 0; 0 0 1];
    M = [ones(1,Nc)*15; ones(1,Nc)*15; zeros(1,Nc)];
    hText = text(x3(1),x3(2) ,'Sping move!');
    for i=0:1
        Shift = [1 0 i; 0 1 i; 0 0 1]; 
        N1 = Shift*N1;
    for j=1:30
        N1 = R*N1;
        N1 = N1 - M;%
        D1 = N1(1:2,:);
        plot(D1(1,:),D1(2,:),'.','color','r');
        pause(0.15);
        plot(D1(1,:),D1(2,:),'.','color','w');
    end
    end
    %(c)  shears, reflections, or rescalings
    for w=1:8
        P = (1/w).*A;% make the graph be smaller
        plot(P(1,:),P(2,:),'.','color','m'); 
        pause(0.2);
        plot(P(1,:),P(2,:),'.','color','w');
    end
    for z=1:15
        E = z.*P;%make the graph bigger
        hText = text(x4(1),x4(2) ,'Bigger');
        plot(E(1,:),E(2,:),'.','color','c');
        pause(0.3);
        plot(E(1,:),E(2,:),'.','color','w');
    end
    for w=1:5
        P = (1/w).*A;% make the graph be smaller
        plot(P(1,:),P(2,:),'.','color','r'); 
        hText = text(x5(1),x5(2) ,'Small!');
        pause(0.2);
        plot(P(1,:),P(2,:),'.','color','w');
    end
    for z=1:10
        E = z.*P;%make the graph bigger
        plot(E(1,:),E(2,:),'.','color','g');
        pause(0.2);
        plot(E(1,:),E(2,:),'.','color','w');
    end
    for w=1:5
        P = (1/w).*A;% make the graph be smaller
        plot(P(1,:),P(2,:),'.','color','r'); 
        pause(0.1);
        plot(P(1,:),P(2,:),'.','color','w');
    end
    for z=1:5
        E = z.*P;%make the graph bigger
        plot(E(1,:),E(2,:),'.','color','k');
        pause(0.1);
        plot(E(1,:),E(2,:),'.','color','w');
    end
    for w=1:5
        P = (1/w).*A;% make the graph be smaller
        plot(P(1,:),P(2,:),'.','color','k'); 
        pause(0.1);
        plot(P(1,:),P(2,:),'.','color','w');
    end
    %///////////
    out = watermark;
end

%Morphing

