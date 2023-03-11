t = 0:0.001:1;
figure('Units', 'pixel', 'Position', [100,100,1000,700], 'toolbar', 'none');

hp = drawpolyline;
hp.set('InteractionsAllowed');
title("beizer curve, please pts")
hold on;
pos = hp.Position;
curve = mk_curve(pos);
global h;
h = plot(curve(:,1),curve(:,2),'b');
axis([0 1 0 1]);
addlistener(hp, 'ROIMoved', @draw);

function ret = draw(varargin)
    hp = evalin('base', 'hp');
    global h;
    delete(h);
    pos = hp(1).Position();
    curve = mk_curve(pos);
    h = plot(curve(:,1),curve(:,2),'b');
    axis([0 1 0 1]);
end

function curve=mk_curve(pos)
    curve = zeros(1000,2);
    n_pts = size(pos,1);
    process = zeros(size(pos,1),size(pos,1),2);
    process(:,1,:) = pos;
    for i = 1:1000,
        for k = 1:n_pts-1,
            for j = 1:n_pts - k,
                process(j,k+1,:) = (1-i/1000.)*process(j,k,:) + (i/1000.)*process(j+1,k,:);
            end
        end
        curve(i,:) = process(1,n_pts,:);
    end
end
