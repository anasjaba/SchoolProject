function [isCollision, pointsCollisions] = check_collision(system, carNumber)
  source = system(1:4,:);
  incoming = system(5:8,:);

  minY = source(3, 2);
  maxY = source(2, 2);

  minX = source(1, 1);
  maxX = source(2, 1);

  isCollision = 0;
  pointsCollisions = [[0 0]; [0 0]; [0 0]];
  for c = incoming.'
    x = c(1);
    y = c(2);

    if x >= minX && x <= maxX && y >= minY && y <= maxY
      distLeft = x - minX;
      distRight = maxY - x;
      distTop = maxY - y;
      distBottom = y - minY;

      isCollision = carNumber;
      hit = [x y];
      [ws,whichSide] = min([distLeft, distRight, distTop, distBottom]);
      if whichSide == 1
        pointOfCollision1 = [minX minY];
        pointOfCollision2 = [minX maxY];
      elseif whichSide == 3
        pointOfCollision1 = [minX maxY];
        pointOfCollision2 = [maxX maxY];
      elseif whichSide == 2
        pointOfCollision1 = [maxX maxY];
        pointOfCollision2 = [maxX minY];
      elseif whichSide == 4
        pointOfCollision1 = [maxX minY];
        pointOfCollision2 = [minX minY];
      end
      pointsCollisions = [hit; pointOfCollision1; pointOfCollision2];
      break;
    end
  end
