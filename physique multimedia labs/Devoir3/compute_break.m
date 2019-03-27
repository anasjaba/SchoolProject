function k1 = compute_break(qi, deltaT)
	qi = qi.';	
	ri = qi(1,:);
	vi = qi(2,:);

	if qi(3,1)==1
		m = 1540;
	elseif qi(3,1)==2
		m = 1010;
	else
		error('Unwanted option exception')
    end

	F = force_friction(m, vi);
	A = acceleration(F, m);
	V = velocity([vi(1); vi(2)], deltaT, A);
	R = position([ri(1); ri(2)], [vi(1); vi(2)], A, deltaT);

	deltaR = [R(1)-ri(1), R(2)-ri(2)];
	deltaV = [V(1),V(2)] - [vi(1), vi(2)];
	k1 = [[deltaR(1); deltaR(2); 0] [deltaV(1); deltaV(2); 0] [0; 0; 0]];

