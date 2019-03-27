function [collision face r] = FindCollision(r0, v0, count, mCylindre, hCylindre, rCylindre, nin, nout)
	epsilon = 1e-10;

	if count == 0
		v = Refraction(r0, v0, mCylindre, hCylindre, nin, nout, 1);
	else
		v = Refraction(r0, v0, mCylindre, hCylindre, nin, nout, 0);
	end

	[collision face r] = LineBox(r0, v);

	if ~collision
		[collision, r] = LineCylinder(r0, v, hCylindre, mCylindre, rCylindre);
		diff = r - r0;
		isDifferent = (norm(diff) > epsilon);
		if collision && (count <= 100) && isDifferent
			[collision face r] = FindCollision(r, r - r0, count + 1, mCylindre, hCylindre, rCylindre, nin, nout);
		else
			collision = false;
		end
	end
