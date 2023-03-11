%% 失败的尝试，用最小二乘解
h = drawpolyline;
p = h.Position;
axis([0 1 0 1]);
f = mk_approx(p, 1000);
f(:,1:10)
plot(f(1,:),f(2,:));
% axis([0 1 0 1]);

function f = mk_approx(p, npts)
 % assert p = n x 2 mat
 x = p(:,1) ;
 y = p(:,2) ;
 n = size(x,1) ;
 mat = zeros(n,n+1) ;
 for i = 1:n+1
     for j = 1:n
        mat(j,i) = f_basis(x(j), p, i-1);
     end
 end
 b = mat \ y;
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

 
function ret=f_approx(x, b, p)
% %  b(1)
%  size(b) 
%  size(p)
 ret = f_basis(x,p,0);
 n = size(p,1); 
 for i = 1:n
     ret = ret + b(i) * f_basis(x,p,i);
 end
end

function ret = f_basis(x,p,i)
    d = 4;
    if i == 0
        ret = 1;
    else
        ret = 1/((x - p(i,2))^2 + d);
    end
end
