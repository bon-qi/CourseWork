%% 需要设置的超参数
t = 0:0.001:2*pi;
ft = zeros(size(t,2),2);
a = 2;
b = 1;

%% 实现参数化
for i = 1:size(t,2),
    ft(i,:) = c(t(i), a, b) + 1/k(t(i), a, b) * e2(t(i), a, b);
end

%% 画图
plot(ft(:,1),ft(:,2));
axis equal;


%% 需要的函数
function ret = c(t, a, b)
    ret = [a*sin(t), b*cos(t)];
end

function ret = e1(t, a, b)
    ret = [-a*sin(t), b*cos(t)] / ( sqrt(a^2*cos(t)^2+b^2*sin(t)^2) );
end

function ret = e2(t, a, b)
    ret = [-b*cos(t), -a*sin(t)] / ( sqrt(a^2*cos(t)^2+b^2*sin(t)^2) );
end

function ret = k(t, a, b)
    ret = a*b / (a^2 * sin(t) ^2 + b^2 * cos(t)^2)^1.5;
end
