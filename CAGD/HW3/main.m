%% 作业：完成递归Beizer曲线生成

%% 首先将做图的画板给出
figure('Units', 'pixel', 'Position', [100,100,1000,700], 'toolbar', 'none');

%% 准备工作：交互式多边形生成
hp = drawpolyline;
hp.set('InteractionsAllowed');
title("beizer curve, please pts")
hold on;
pos = hp.Position;

%% 画出Beizer曲线
curve = mk_curve(pos);
global h;
h = plot(curve(:,1),curve(:,2),'b');
axis([0 1 0 1]);

%% 增加监听事件 实现实时交互
addlistener(hp, 'ROIMoved', @draw);

%% 给监听事件对应的画图
function ret = draw(varargin)
    hp = evalin('base', 'hp');
    global h;
    delete(h);
    pos = hp(1).Position();
    curve = mk_curve(pos);
    h = plot(curve(:,1),curve(:,2),'b');
    axis([0 1 0 1]);
end

function ret = B(t, n , i)
    %assert(t >= 0 and t <= 1);
    ret = nchoosek(n,i) * t^(n-i) * (1-t)^i;
end

%% 构造曲线的函数
function curve=mk_curve(pos)
    curve = zeros(1000,2);
    n_pts = size(pos,1);
    pos
    %% process: 递归基于的数据， 第一个参数为递归的次数
%    process = zeros(size(pos,1),size(pos,1),2);
%    process(:,1,:) = pos;
    for i = 1:1000,
        temp = zeros(1,2);
        for k = 0:n_pts-1,
            temp = temp + pos(k+1,:) *  B(i/1000.0, n_pts-1, k); 
        end
        curve(i,:) = temp;
    end
end