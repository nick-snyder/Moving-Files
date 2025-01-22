%Homework 13

% 3
syms x
f = log(x);

hold on

T1 = taylor(f, 'ExpansionPoint', 1, 'Order', 2);
T5 = taylor(f, 'ExpansionPoint', 1, 'Order', 6);
T10 = taylor(f, 'ExpansionPoint', 1, 'Order', 11);

fplot([T1 T5 T10 f])

xlim([0 2.2])
grid on 
xlabel('x')
ylabel('f(x)')
legend('approximation of ln(x) with order 1', ...
       'approximation of ln(x) with order 5', ...
       'approximation of ln(x) with order 10', ...
       'ln(x)','Location','Best')
title('Taylor Series Expansion')

% As x approaches 0 and 2, the approximations fall 
% away from ln(x)


% 4
threshold = 0.75   % check error at point here
feval = subs(f,x,threshold);

Teval = subs(T1,x,threshold);
err_T1=feval-Teval
stem(threshold, err_T1)

Teval = subs(T5,x,threshold);
err_T5=feval-Teval
stem(threshold, err_T5)

Teval = subs(T10,x,threshold);
err_T10=feval-Teval
stem(threshold, err_T10)


% 5
threshold = 2.5   % check error at point here
feval = subs(f,x,threshold);

Teval = subs(T1,x,threshold);
err_T1=feval-Teval
stem(threshold, err_T1)

Teval = subs(T5,x,threshold);
err_T5=feval-Teval
stem(threshold, err_T5)

Teval = subs(T10,x,threshold);
err_T10=feval-Teval
stem(threshold, err_T10)

hold off


% 6
% As the number of terms increase, the error decreases as the lines get
% closer to ln(x). The stem plot didn't really work for me


% 7
f = sin(x);

T1 = taylor(f, 'ExpansionPoint', 0, 'Order', 2);
T5 = taylor(f, 'ExpansionPoint', 0, 'Order', 6);
T10 = taylor(f, 'ExpansionPoint', 0, 'Order', 11);

fplot([T1 T5 T10 f])

xlim([-2*pi 2*pi])
grid on 
xlabel('x')
ylabel('f(x)')
legend('approximation of sin(x) with order 1', ...
       'approximation of sin(x) with order 5', ...
       'approximation of sin(x) with order 10', ...
       'sin(x)','Location','Best')
title('Taylor Series Expansion')

% As x approaches infinity, the errors also approache infinity

threshold = 1.5*pi   % check error at point here
feval = subs(f,x,threshold);

Teval = subs(T1,x,threshold);
err_T1=feval-Teval
%stem(threshold, err_T1)

Teval = subs(T5,x,threshold);
err_T5=feval-Teval
%stem(threshold, err_T5)

Teval = subs(T10,x,threshold);
err_T10=feval-Teval
%stem(threshold, err_T10)
