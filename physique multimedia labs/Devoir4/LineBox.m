function [collision face r] = LineBox(r0, w0)
	minX = 0.03;
	maxX = 0.04;
	minY = 0.03;
	maxY = 0.05;
	minZ = 0.12;
	maxZ = 0.17;

	[collision1, r1, t1] = LinePlane(r0, w0, [1 0 0], [minX 0 0], minX, maxX, minY, maxY, minZ, maxZ);
	[collision2, r2, t2] = LinePlane(r0, w0, [1 0 0], [maxX 0 0], minX, maxX, minY, maxY, minZ, maxZ);
	[collision3, r3, t3] = LinePlane(r0, w0, [0 1 0], [0 minY 0], minX, maxX, minY, maxY, minZ, maxZ);
	[collision4, r4, t4] = LinePlane(r0, w0, [0 1 0], [0 maxY 0], minX, maxX, minY, maxY, minZ, maxZ);
	[collision5, r5, t5] = LinePlane(r0, w0, [0 0 1], [0 0 minZ], minX, maxX, minY, maxY, minZ, maxZ);
	[collision6, r6, t6] = LinePlane(r0, w0, [0 0 1], [0 0 maxZ], minX, maxX, minY, maxY, minZ, maxZ);

	minT = inf;
	face = 0;
	r = [0 0 0];
	collision = false;
	if collision1 && norm(r1 - r0) < minT
		minT = norm(r1 - r0);
		collision = true;
		face = 1;
		r = r1;
	end
	if collision2 && norm(r2 - r0) < minT
		minT = norm(r2 - r0);
		collision = true;
		face = 2;
		r = r2;
	end
	if collision3 && norm(r3 - r0) < minT
		minT = norm(r3 - r0);
		collision = true;
		face = 3;
		r = r3;
	end
	if collision4 && norm(r4 - r0) < minT
		minT = norm(r4 - r0) ;
		collision = true;
		face = 4;
		r = r4;
	end
	if collision5 && norm(r5 - r0) < minT
		minT = norm(r5 - r0);
		collision = true;
		face = 5;
		r = r5;
	end
	if collision6 && norm(r6 - r0) < minT
		minT = norm(r6 - r0);
		collision = true;
		face = 6;
		r = r6;
	end
