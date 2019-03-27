function [vaf, vbf] = postCollision(raf, vaf, rbf, vbf, mImpact, auto)

	epsi = 0.8;
	masseA = 1540;
	masseB = 1010;

	pImpact = mImpact(1,:);
	vecteurArrete = mImpact(3,:) - mImpact(2,:);
	vecteurN = [-vecteurArrete(2) vecteurArrete(1)]/norm(vecteurArrete);

	vap = [vaf(1) vaf(2) 0] + cross([0 0 vaf(3)], [pImpact-[raf(1) raf(2)] 0]);
	vbp = [vbf(1) vbf(2) 0] + cross([0 0 vbf(3)], [pImpact-[rbf(1) rbf(2)] 0]);

	vrMinus = dot([vecteurN 0], (vap - vbp));

	j = -(1+epsi) * vrMinus / (1/masseA + 1/masseB);

	inertieA = inertia_rectangle(masseA, 4.78, 1.8, 1.82);
	inertieB = inertia_rectangle(masseB, 4.23, 1.8, 1.6);
	inertieA = [0 0 0; 0 0 0; 0 0 inertieA(1)];
	inertieB = [0 0 0; 0 0 0; 0 0 inertieB(1)];

	rap = [pImpact-[raf(1) raf(2)] 0];
	rbp = [pImpact-[rbf(1) rbf(2)] 0];

	omegaAF = vaf(3) + j * pinv(inertieA) * cross(rap, [vecteurN 0]).';
	omegaBF = vbf(3) + j * pinv(inertieB) * cross(rbp, [vecteurN 0]).';

	if auto == 1
		factor = 1;
	else
		factor = -1;
	end
	vaf = [vaf(1) vaf(2)] + factor * vecteurN * j / masseA;
	vbf = [vbf(1) vbf(2)] - factor * vecteurN * j / masseB;

	vaf = [vaf omegaAF(3)];
	vbf = [vbf omegaBF(3)];
