function [isCollision vecteur_resultant t] = LinePlane(r0, v, n, point, minX, maxX, minY, maxY, minZ, maxZ)
	t = 0;
	epsilon = 1e-10;
	top = dot(n, point) - dot(n, r0);
	bottom = dot(v, n);

	if bottom == 0
		isCollision = false;
		vecteur_resultant = [0 0 0];
	else
		t = top / bottom;
		vecteur_resultant = r0 + t * v;
		x = vecteur_resultant(1);
		y = vecteur_resultant(2);
		z = vecteur_resultant(3);

		if t > 0
			isCollision = true;
		else
			isCollision = false;
		end
		if x < minX - epsilon || x > maxX + epsilon
			isCollision = false;
		end
		if y < minY - epsilon || y > maxY + epsilon
			isCollision = false;
		end
		if z < minZ - epsilon || z > maxZ + epsilon
			isCollision = false;
		end
	end
