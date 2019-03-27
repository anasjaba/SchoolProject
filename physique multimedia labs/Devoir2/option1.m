function k1 = option1(q0, deltat)
	m_b = 2.74 / 1000;
	rayon = 1.99 / 100;
	ri = q0(1,:);
	vi = q0(2,:);
	wi = q0(3,:);

	F = force_g(m_b);
	a = acceleration(F, m_b);
	v = velocity(vi, deltat, a);
	r = position(ri, v, a, deltat);
	wi = [0 0 0];
	k1 = [r-ri; v-vi; wi];
