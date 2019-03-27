function [rotated] = rotated_position(rf, lon)
  mX = rf(1);
  mY = rf(2);
  ang = rf(3);
  lonX = lon(1);
  lonY = lon(2);
  posNotRotated = [-lonX lonY ;...
                      lonX lonY ;...
                      lonX -lonY ;...
                   -lonX -lonY ];
  rotated = rotate(ang, posNotRotated) + [mX  mY];
  