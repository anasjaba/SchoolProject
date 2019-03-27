function posRotated = rotate(angA, posToRotate)
  rotA = [cos(angA) -sin(angA) ;...
          sin(angA) cos(angA)];
  posRotated = (rotA * posToRotate.').';
