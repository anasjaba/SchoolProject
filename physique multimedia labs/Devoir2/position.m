function pos = position(posi, v, a, deltat)
	pos = posi + v * deltat - 1/2 * a * deltat ^ 2;
