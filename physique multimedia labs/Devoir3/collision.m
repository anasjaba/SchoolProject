function [isCollision, hits] = collision(angA, angB, rotatedA, rotatedB)
  ... Angle en radiant selon les axes des x positif
  systemA = rotate(-angA, [rotatedA ; rotatedB]);
  [isCollision, hits] = check_collision(systemA, 2);

  if isCollision
    hits = rotate(angA, hits);
  else
    systemB = rotate(-angB, [rotatedB ; rotatedA]);
    [isCollision, hits] = check_collision(systemB, 1);
    if isCollision
      hits = rotate(angB, hits);
    end
  end
    
