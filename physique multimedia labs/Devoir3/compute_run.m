function k1 = compute_run(qi, deltaT)
    qi = qi.';	
	ri = qi(1,:);
	vi = qi(2,:);
	m = 1010;	

	R = position([ri(1); ri(2)], [vi(1); vi(2)], [0;0], deltaT);
	deltaR = [R(1)-ri(1),R(2)-ri(2)];

	k1 = [[deltaR, 0].' [0 0 0].' [0; 0; 0]];
