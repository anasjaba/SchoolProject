function [coup, tf, rbf, vbf] = Devoir2(option, rbi, vbi, wbi)
	deltaT = 0.001;

	tf = 0;
	rbf = rbi;
	vbf = vbi;
	coup = coup_verification(rbi, rbf);

	if option == 1
		g = 'option1';
	elseif option == 2
		g = 'option2';
	elseif option == 3
		g = 'option3';
	else
		error('Unwanted option exception')
	end

	q = [rbf; vbf; wbi];

	rbfx = [];
	rbfy = [];
	rbfz = [];

	tic
	while coup < 0
		q = SEDRK4t0(q, tf, deltaT, g);
		rbf = q(1,:);
		rbfx = [rbfx; rbf(1)];
		rbfy = [rbfy; rbf(2)];
		rbfz = [rbfz; rbf(3)];
		vbf = q(2,:);
		plot3(rbfx, rbfy, rbfz);
		drawnow;
		tf = tf + deltaT;
		coup = coup_verification(rbi, rbf);
	end
	toc
