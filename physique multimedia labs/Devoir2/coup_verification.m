function coup = coup_verification(rbi, rbf)
	rayon = 0.0199;

	if (rbf(1)>=0-rayon && rbf(1)<1.37-rayon) && (rbf(2)>=0-rayon && rbf(2)<=1.525+rayon) && (rbf(3)<=0.76+rayon)
		if rbi(1) < 1.37
			coup = 1;
		else
			coup = 0;
		end
	elseif (rbf(1)>1.37+rayon && rbf(1)<=2.74-rayon) && (rbf(2)>=0-rayon && rbf(2)<=1.525+rayon) && (rbf(3)<=0.76+rayon)
		if rbi(1) < 1.37
			coup = 0;
		else
			coup = 1;
		end
	elseif (rbf(1)>=1.37-rayon && rbf(1)<=1.37+rayon) && (rbf(2)>=rayon-0.1525 && rbf(2)<=1.6775+rayon) && (rbf(3)>=0.76+rayon && rbf(3)<=0.9125+rayon)
		coup = 2;
	elseif rbf(3)<=rayon
		coup = 3;
	else
		coup = -1;
	end
