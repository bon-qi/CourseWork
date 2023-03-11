t = 0:0.001:2*pi;
ft = zeros(size(t,2),2);
r = 1;
R = 3;
O = 0;

for i = 1:size(t,2),
    ft(i,:) =  [ (R + r) * cos( t(i)) - r * cos(t(i) + R/r * t(i) + O ),  - (R + r) * sin(t(i)) + r * sin(t(i) + R/r * t(i) + O )];
end

plot(ft(:,1),ft(:,2));
axis equal;
