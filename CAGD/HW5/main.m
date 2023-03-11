
figure('Units', 'pixel', 'Position', [100,100,1000,700], 'toolbar', 'none');

hp = drawpolyline;
hp.set('InteractionsAllowed');
title("beizer curve, please pts")
hold on;
pos = hp.Position;
curve = mk_curve(pos);
global h;
global bg;
global bg_pts;
h = plot(curve(:,1),curve(:,2),'b');
axis([0 1 0 1]);
addlistener(hp, 'ROIMoved', @draw);

function draw(varargin)
    hp = evalin('base', 'hp');
    global h;
    global bg;
    global bg_pts;
    delete(h),delete(bg), delete(bg_pts);
    pos = hp(1).Position();
    curve = mk_curve(pos);
    h = plot(curve(:,1),curve(:,2),'b');
    axis([0 1 0 1]);
end

function curve=mk_curve(pos)
    n_pts = size(pos,1);
    curve = zeros(1000*(n_pts-1),2);
    A = zeros(2*n_pts-2,2*n_pts-2);
    b = zeros(2*n_pts-2,2);
    global bg;
    global bg_pts;

    %% 构造方程求解
    for i = 2:n_pts-1
        A(2*i-3, 2*i-2) = 1;
        A(2*i-3, 2*i-1) = 1;
        b(2*i-3,:) = 2*pos(i,:); 

        A(2*i-2,2*i-2) = 2;
        A(2*i-2,2*i-1) = -2; 
        A(2*i-2,2*i-3) = -1; 
        A(2*i-2,2*i) = 1;
    end
    A(2*n_pts-3,1) = 1;
    A(2*n_pts-3,2) = -1;
    b(2*n_pts-3,:) = [0, 0];   %pos(1,:) - pos(2,:);

    A(2*n_pts-2,2*n_pts-3) = 1;
    A(2*n_pts-2,2*n_pts-2) = -1;
    b(2*n_pts-2,:) = [0, 0] ; %pos(n_pts-1,:) - pos(n_pts,:);
    
    x = A\b;

    %% 构造参数
    for i = 1:n_pts-1,
        for j = 1:1000,
            curve((i-1)*1000+j,:) = (1-j/1000.)^3*pos(i,:) + 3*(1-j/1000.)^2*(j/1000.)*x(2*i-1,:) + 3*(1-j/1000.)*(j/1000.)^2*x(2*i,:) + (j/1000.)^3*pos(i+1,:);
        end
    end

    %% 画出参数图
    pt = zeros(3*n_pts-2,2);
    for i = 1:n_pts-1
        pt(3*i-2,:) = pos(i,:);
        pt(3*i-1,:) = x(2*i-1,:);
        pt(3*i,:) = x(2*i,:);
    end
    pt(3*n_pts-2,:) = pos(n_pts,:);
    bg = plot(pt(:,1),pt(:,2),'r');
    bg_pts =  plot(pt(:,1),pt(:,2),'ko');    
end
