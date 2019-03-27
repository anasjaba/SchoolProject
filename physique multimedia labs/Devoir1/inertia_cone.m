function inertia = inertia_cone(m, r, h)
    ix = (12 * r^2 + 3 * h^2) / 80;
    iy = ix;
    iz = (3 * r^2) / 10;
    inertia = m * [ix iy iz];
