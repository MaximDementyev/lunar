clear all
eps = 1e-6;
a = 0;
b = 5;
x1_0 = -5;
x2_0 = 10;
x3_0 = 0;


alpha = 0;
m = 1;
g = 10;
mu = 1;




t(1) = a;
h = 0.1;
x1_solve(1) = x1_0;
x2_solve(1) = x2_0;
x3_solve(1) = x3_0;
err(1) = 0;
i = 1;
tic
while (t < b)
    if t + h > b
        'END'
    end
    x3_solve(i+1) = func_x3(t(i), x1_solve(i), x2_solve(i), x3_solve(i));
    
    K = koef4(t, x1_solve(i), x2_solve(i), x3_solve(i), h);
    z1 = x1_solve(i) + (K.kx1.k1 + 2 * K.kx1.k2 + 2 * K.kx1.k3 + K.kx1.k4) / 6;
    z2 = x2_solve(i) + (K.kx2.k1 + 2 * K.kx2.k2 + 2 * K.kx2.k3 + K.kx2.k4) / 6;
    
    
    Km = koef4(t, x1_solve(i), x2_solve(i), x3_solve(i), h/2);
    y1 = x1_solve(i) + (Km.kx1.k1 + 2 * Km.kx1.k2 + 2 * Km.kx1.k3 + Km.kx1.k4) / 6;
    y2 = x2_solve(i) + (Km.kx2.k1 + 2 * Km.kx2.k2 + 2 * Km.kx2.k3 + Km.kx2.k4) / 6;
    Km = koef4(t+h/2, x1_solve(i), x2_solve(i), x3_solve(i), h/2);
    y1 = y1 + (Km.kx1.k1 + 2 * Km.kx1.k2 + 2 * Km.kx1.k3 + Km.kx1.k4) / 6;
    y2 = y2 + (Km.kx2.k1 + 2 * Km.kx2.k2 + 2 * Km.kx2.k3 + Km.kx2.k4) / 6;
    
    tmp_err = abs(z1-y1);
    tmp_err2 = abs(z2-y2);
    if (tmp_err > tmp_err2)
        err(i+1) = tmp_err;
    else
        err(i+1) = tmp_err2;
    end
    
    if (err(i+1) < eps)
		if (err(i+1) < 0.001 * eps)
            if (h < 0.2)
     			h = h * 2;
            else
               i = i+1;
               x1_solve(i) = (16 * y1 - z1)/15;
               x2_solve(i) = (16 * y2 - z2)/15;
               t(i) = t(i-1) + h;
           end
        else
            i = i+1;
			x1_solve(i) = (16 * y1 - z1)/15;
			x2_solve(i) = (16 * y2 - z2)/15;
			t(i) = t(i-1) + h;
        end
    else
        h = h / 2;
    end
end

toc


figure(3)
hold on
    plot (t,x1_solve,'k');
    plot (t,x2_solve,'b');
    plot (t,x3_solve,'g');
    grid on
    legend('x1','x2','x3');
hold off

% figure(2)
%     plot (t,err,'r');
%     grid on
% hold off