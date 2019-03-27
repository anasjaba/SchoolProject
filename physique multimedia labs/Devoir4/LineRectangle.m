function [R d] = LineRectangle(w0, intersectxy, r0, hCylindre, mCylindre, rCylindre, isOut)
	if w0(1) ~= 0
		t = (intersectxy(1) - r0(1)) / w0(1);
	elseif w0(2) ~= 0
		t = (intersectxy(2) - r0(2)) / w0(2);
	else
		error('there is no slope, only Zuul');
	end

	normal = [r0(1)-intersectxy(1) r0(2)-intersectxy(2) 0];
	x = intersectxy(1);
	y = intersectxy(2);
	maxz = mCylindre(3) + hCylindre / 2;
	minz = mCylindre(3) - hCylindre / 2;
	[d R] = LinePlane(r0, w0, normal, [x y 0], x, x, y, y, minz, maxz);

	if ~d
		if (w0(3) > 0 && isOut) || (w0(3) < 0 && ~isOut)
			z = mCylindre(3) - hCylindre / 2;
		else
			z = mCylindre(3) + hCylindre / 2;
		end

		t = (z - r0(3)) / w0(3);
		r = r0 + t * w0;

		if norm(R(1:2) - mCylindre(1:2)) < rCylindre
			R = r;
			d = 1;
		else
			R = NaN;
			d = 0;
		end
	end
