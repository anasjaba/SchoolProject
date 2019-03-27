function [w1 isRefracted] = Refraction(r, w0, mCylindre, hCylindre, nin, nout, isOut)
	if ~isOut
		n1 = nin;
		n2 = nout;
		factor = -1;
	else
		n1 = nout;
		n2 = nin;
		factor = 1;
	end
	epsilon = 1e-10;
	low_z = mCylindre(3) - 0.5 * hCylindre;
	high_z  = mCylindre(3) + 0.5 * hCylindre;
	z = r(3);

	if z == low_z
		normal = [0 0 -1] * factor;
		z_offset = pi;
	elseif z == high_z
		normal = [0 0 1] * factor;
		z_offset = 0;
	else
		normal = [r(1)-mCylindre(1) r(2)-mCylindre(2) 0] * factor;
		z_offset = pi / 2;
	end

	w0_xy = w0(1:2);
	normal_xy = normal(1:2);
	phi_out = 0;
	p_in = 1;
	if norm(w0_xy) ~= 0 && norm(normal_xy) ~= 0
		phi_in = acos(dot(w0_xy, normal_xy) / (norm(w0_xy) * norm(normal_xy) + epsilon));
		p_in = n1 * sin(phi_in) / n2;
		phi_out = asin(p_in);
	end

	w0_xz = [norm(w0(1:2)) w0(3)];
	normal_xz = [norm(normal(1:2)) normal(3)];
	theta_in = acos(dot(w0_xz, normal_xz) / (norm(w0_xz) * norm(normal_xz) + epsilon));
	t_in = n1 * sin(theta_in) / n2;
	if p_in < 1 && p_in > -1 && t_in < 1 && t_in > -1
		theta_out = asin(t_in);

		angleNormal_xy = atan2(normal(2), normal(1));
		theta = z_offset - theta_out;
		phi = pi - phi_out + angleNormal_xy;
		w1 = [sin(theta)*cos(phi) sin(theta)*sin(phi) cos(theta)];
		isRefracted = 1;
	else
		unitNorm = normal / norm(normal);
		w1 = w0 - 2 * dot(w0, unitNorm) * unitNorm;
		isRefracted = 0;
	end
