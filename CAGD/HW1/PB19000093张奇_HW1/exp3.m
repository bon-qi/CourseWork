%% 实现用径向基函数数逼近

%% 准备交互界面
figure('Units', 'pixel', 'Position', [100,100,1000,700], 'toolbar', 'none');
h = drawpolyline();
h.set('InteractionsAllowed');
title("interactive plot, please pts")
global p;
p = h.Position;
axis([0 1 0 1])
hold on;

%% 逼近并画出
f = mk_approx(p, 1000);
global plt;
plt = plot(f(1,:),f(2,:));
axis([0 1 0 1]);

%% 实现交互
addlistener(h, 'ROIMoved', @draw);

function f = mk_approx(p, npts)
 % assert p = n x 2 mat
 x = p(:,1) ;
 y = p(:,2) ;
 n = size(x,1) ;
 
  %% 构造矩阵，并解方程
 mat = zeros(n,n) ;
 for i = 1:n
     for j = 1:n
        mat(j,i) = f_basis(x(j), p, i);
     end
 end
 b = mat \ y;
 
  %% 将画图数据构造出来
 x_max = max(x);
 x_min = min(x);
 d = (x_max - x_min) / npts;
 x = x_min : d : x_max;
 f = zeros(2,size(x,2));
 f(1,:) = x;
 for i = 1:size(f,2)
    f(2,i) = f_approx(x(i),b, p);
 end
end

 
 %% 实现逼近函数的带入
function ret=f_approx(x, b, p)
% %  b(1)
%  size(b) 
%  size(p)
%  ret = f_basis(x,p,0);
ret = 0;
 n = size(p,1); 
 for i = 1:n
     ret = ret + b(i) * f_basis(x,p,i);
 end
end

%% 实现基函数族
function ret = f_basis(x,p,i)
    d = 4;
    if i == 0
        ret = 1;
    else
        ret = 1/((x - p(i,2))^2 + d);
    end
end

%% 支持交互画图
function draw(varargin)
    h = evalin('base', 'h');
    global plt;
    global p;
    delete(plt);
    p = h(1).Position();
    f = mk_approx(p, 1000);
    plt = plot(f(1,:),f(2,:),'b');
    axis([0 1 0 1]);
end
