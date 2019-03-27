function inertia=inertia_cylindre(m, r, h)
    ix = (3 * r^2 + h^2) / 12;
    iy = ix;
    iz = (r ^ 2) / 2;
    inertia = m * [ix iy iz];
