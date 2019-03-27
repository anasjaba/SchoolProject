function x = position(xi, v, a, deltat)
	x = xi + v * deltat - 0.5 * a * deltat ^ 2;
