function f_a = force_air(v, rayon)
	C = 0.5;
	p = 1.2;
	A = pi * rayon ^ 2;
	f_a = -1/2 * p * C * A * abs(v) .* v;
