function [collision r] = LineCylinder(r0, w0, hCylindre, mCylindre, rCylindre)
	[x, y, d] = LineCircle(w0, r0, mCylindre, rCylindre, 0);
	collision = 0;
	r = r0;

	if d
		intersectxy = [x y];
		[r collision] = LineRectangle(w0, intersectxy, r0, hCylindre, mCylindre, rCylindre, 1);
	end
