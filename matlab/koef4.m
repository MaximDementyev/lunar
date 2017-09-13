function K = koef4( t, x1_solve, x2_solve, x3_solve, h)

    K.kx1.k1 = func_x1(t,     x1_solve,     x2_solve,     x3_solve)*h;
	K.kx2.k1 = func_x2(t,     x1_solve,     x2_solve,     x3_solve)*h;
    K.kx3.k1 = func_x3(t,     x1_solve,     x2_solve,     x3_solve)*h;
    
    
	K.kx1.k2 = func_x1(t + h / 2,     x1_solve + K.kx1.k1 / 2,     x2_solve + K.kx1.k1 / 2,     x3_solve + K.kx1.k1 / 2)*h;
	K.kx2.k2 = func_x2(t + h / 2,     x2_solve + K.kx2.k1 / 2,     x2_solve + K.kx2.k1 / 2,     x3_solve + K.kx2.k1 / 2)*h;
    K.kx3.k2 = func_x3(t + h / 2,     x2_solve + K.kx3.k1 / 2,     x2_solve + K.kx3.k1 / 2,     x3_solve + K.kx3.k1 / 2)*h;
   
    
	K.kx1.k3 = func_x1(t + h / 2,     x1_solve + K.kx1.k2 / 2,     x2_solve + K.kx1.k2 / 2,     x3_solve + K.kx1.k2 / 2)*h;
	K.kx2.k3 = func_x2(t + h / 2,     x1_solve + K.kx2.k2 / 2,     x2_solve + K.kx2.k2 / 2,     x3_solve + K.kx2.k2 / 2)*h;
    K.kx3.k3 = func_x3(t + h / 2,     x1_solve + K.kx3.k2 / 2,     x2_solve + K.kx3.k2 / 2,     x3_solve + K.kx3.k2 / 2)*h;
	
    
	K.kx1.k4 = func_x1(t + h,     x1_solve + K.kx1.k3,     x2_solve + K.kx1.k3,     x3_solve + K.kx1.k3)*h;
    K.kx2.k4 = func_x2(t + h,     x1_solve + K.kx2.k3,     x2_solve + K.kx2.k3,     x3_solve + K.kx2.k3)*h;
    K.kx3.k4 = func_x3(t + h,     x1_solve + K.kx3.k3,     x2_solve + K.kx3.k3,     x3_solve + K.kx3.k3)*h;

end

