% This script will morph a square into an octagon. 
%(add more points to make it look more like a circle).
 
%points arranged to easily show shape

p9B=[0;4];                       p0B=[4;4]; 
        p9C=[1;3.5];    p0A=[3;3.5];
    p9A=[.5;3];  p0=[2;3];   p0C=[3.5;3];

        p9=[1;2];       p3=[3;2]; 

    p6C=[.5;1];  p6=[2;1];  p3A=[3.5;1];
        p6A=[1;.5];     p3C=[3;.5];   
p6B=[0;0];                       p3B=[4;0]; 

star2dMatrix = [p0,p0A,p0B,p0C,p3,p3A,p3B,p3C,p6,p6A,p6B,p6C,p9,p9A,p9B,p9C];
fill(star2dMatrix(1,:),star2dMatrix(2,:),'r')
axis([-4 4 -4 4])
hold on;
%now define the "after", a circle-ish shape

                            a0=[0;1]; 
            a9C=[-.383;.924];           a0A=[.383;.924];
        a9B=[-1/sqrt(2);1/sqrt(2)];         a0B=[1/sqrt(2);1/sqrt(2)]; 
    a9A=[-.924;.383];                           a0C=[.924;.383];
a9=[-1;0];                                          a3=[1;0]; 
    a6C=[-.924;-.383];                          a3A=[.924;-.383];
        a6B=[-1/sqrt(2);-1/sqrt(2)];        a3B=[1/sqrt(2);-1/sqrt(2)]; 
            a6A=[-.383;-.924];          a3C=[.383;-.924];          
                            a6=[0;-1];

A=[a0,a0A,a0B,a0C,a3,a3A,a3B,a3C,a6,a6A,a6B,a6C,a9,a9A,a9B,a9C];
color = str2mat('y','m','c','r','g','b','k');
for k=0:1/6:1
	C = (1-k)*star2dMatrix + k*A;
	fill(C(1,:),C(2,:),color(k*6+1))
	pause(0.2);
end
hold off