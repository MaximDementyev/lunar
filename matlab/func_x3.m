function res = func_x3( t, x1, x2, x3)
    alpha = 0;
    m = 1;
    g = 10;
    mu = 1;
    F = 0;
%     if t > 2
%         F = 11;
%     end
    if ( abs(x2) < 1e-3)
        Q = F - m*g*sin(alpha*pi/180);
        if (abs(Q) <= abs(mu*m*g*cos(alpha*pi/180)))
            res = 0;
        else
            res = (Q - mu*m*g*cos(alpha*pi/180)*sign(Q))/m;
        end
    else
        res = (F - mu*m*g*cos(alpha*pi/180)*sign(x2)-m*g*sin(alpha*pi/180))/m;
    end
end

