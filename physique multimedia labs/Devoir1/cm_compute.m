function cm=cm_combine(masses, cms)
    mass = sum(masses);
    cm = 1 / mass * sum(masses * cms, 1);
    