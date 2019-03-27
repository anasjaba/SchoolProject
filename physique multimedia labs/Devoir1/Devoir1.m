function [pcmNL INL alphaNL]=Devoir1(AngRot, vangulaire, forces, posNL)
    
    % NAVETTE %
    r_nav = 3.5;
    
    h_nav_cyl = 27.93;
    h_nav_cone = 9.31;
    
    vol_nav_cyl = vol_cylindre(r_nav, h_nav_cyl);
    vol_nav_cone = vol_cone(r_nav, h_nav_cone);
    
    m_nav = 109;
    m_nav_cyl = m_nav / (vol_nav_cyl + vol_nav_cone) * vol_nav_cyl;
    m_nav_cone = m_nav / (vol_nav_cyl + vol_nav_cone) * vol_nav_cone;
    
    cm_nav_cyl = cm_cylindre(h_nav_cyl) + posNL;
    cm_nav_cone = cm_cone(h_nav_cone) + [0 0 h_nav_cyl] + posNL;
    cm_navette =...
        cm_compute([m_nav_cyl m_nav_cone], [cm_nav_cyl; cm_nav_cone]);
    
    ic_nav_cyl = inertia_cylindre(m_nav_cyl, r_nav, h_nav_cyl);
    ic_nav_cone = inertia_cone(m_nav_cone, r_nav, h_nav_cone);
    
    
    % RESERVOIRE %
    r_res = 4.2;
    
    h_res = 46.9;
    h_res_cone = 7.8;
    h_res_top = 1/3 * h_res - h_res_cone;
    h_res_bot = 2/3 * h_res;
    
    v_res_top = vol_cylindre(r_res, h_res_top);
    v_res_bot = vol_cylindre(r_res, h_res_bot);
    v_res_cone = vol_cone(r_res, h_res_cone);
    
    m_top_cone = 631;
    m_res_top = m_top_cone / (v_res_top + v_res_cone) * v_res_top;
    m_res_cone = m_top_cone / (v_res_top + v_res_cone) * v_res_cone;
    m_res_bot = 108;
    m_res = m_top_cone + m_res_bot;
    
    res_top_offset = [0 r_nav + r_res h_res_bot];
    res_bot_offset = [0 r_nav + r_res 0];
    res_cone_offset = [0 r_nav + r_res h_res - h_res_cone];
    
    cm_res_top = cm_cylindre(h_res_top) + res_top_offset + posNL;
    cm_res_bot = cm_cylindre(h_res_bot) + res_bot_offset + posNL;
    cm_res_cone = cm_cone(h_res_cone) + res_cone_offset + posNL;
    cm_reservoire = cm_compute(...
        [m_res_top m_res_bot m_res_cone],...
        [cm_res_top; cm_res_bot; cm_res_cone]...
    );
    
    ic_res_top = inertia_cylindre(m_res_top, r_res, h_res_top);
    ic_res_bot = inertia_cylindre(m_res_bot, r_res, h_res_bot);
    ic_res_cone = inertia_cone(m_res_cone, r_res, h_res_cone);
    
    
    % PROPULSEURS %
    r_prop = 1.855;
    
    h_prop_cyl = 39.9;
    h_prop_cone = 5.6;
    
    vol_prop_cyl = vol_cylindre(r_prop, h_prop_cyl);
    vol_prop_cone = vol_cone(r_prop, h_prop_cone);
    
    m_prop = 469;
    m_prop_cyl = m_prop / (vol_prop_cyl + vol_prop_cone) * vol_prop_cyl;
    m_prop_cone = m_prop / (vol_prop_cyl + vol_prop_cone) * vol_prop_cone;
    
    prop_left_cyl_offset = [-r_res - r_prop, r_nav+r_res 0];
    prop_right_cyl_offset = [r_res + r_prop, r_nav+r_res 0];
    
    prop_left_cone_offset = [-r_res - r_prop, r_nav+r_res h_prop_cyl];
    prop_right_cone_offset = [r_res + r_prop, r_nav+r_res h_prop_cyl];
    
    cm_prop_cyl = cm_cylindre(h_prop_cyl);
    cm_prop_cone = cm_cone(h_prop_cone);
    
    cm_prop_left_cyl = cm_prop_cyl + prop_left_cyl_offset + posNL;
    cm_prop_right_cyl = cm_prop_cyl + prop_right_cyl_offset + posNL;
    cm_prop_left_cone = cm_prop_cone + prop_left_cone_offset + posNL;
    cm_prop_right_cone = cm_prop_cone + prop_right_cone_offset + posNL;
    cm_prop_left = cm_compute(...
        [m_prop_cyl m_prop_cone],...
        [cm_prop_left_cyl; cm_prop_left_cone]...
    );
    cm_prop_right = cm_compute(...
        [m_prop_cyl m_prop_cone],...
        [cm_prop_right_cyl; cm_prop_right_cone]...
    );

    ic_prop_left_cyl = inertia_cylindre(m_prop_cyl, r_prop, h_prop_cyl);
    ic_prop_right_cyl = ic_prop_left_cyl;
    ic_prop_left_cone = inertia_cone(m_prop_cone, r_prop, h_prop_cone);
    ic_prop_right_cone = ic_prop_left_cone;
    
    
    % TOTAL %
    centre_de_masse = cm_compute(...
        [m_nav m_res m_prop m_prop],...
        [cm_navette; cm_reservoire; cm_prop_left; cm_prop_right]...
    );

    pcmNL = centre_de_masse;
    
    id_nav_cyl = translate_inertia(ic_nav_cyl, pcmNL, cm_nav_cyl, m_nav_cyl);
    id_nav_cone = translate_inertia(ic_nav_cone, pcmNL, cm_nav_cone, m_nav_cone);
    id_res_top = translate_inertia(ic_res_top, pcmNL, cm_res_top, m_res_top);
    id_res_bot = translate_inertia(ic_res_bot, pcmNL, cm_res_bot, m_res_bot);
    id_res_cone = translate_inertia(ic_res_cone, pcmNL, cm_res_cone, m_res_cone);
    id_prop_left_cyl = translate_inertia(ic_prop_left_cyl, pcmNL, cm_prop_left_cyl, m_prop_cyl);
    id_prop_left_cone = translate_inertia(ic_prop_left_cone, pcmNL, cm_prop_left_cone, m_prop_cone);
    id_prop_right_cyl = translate_inertia(ic_prop_right_cyl, pcmNL, cm_prop_right_cyl, m_prop_cyl);
    id_prop_right_cone = translate_inertia(ic_prop_right_cone, pcmNL, cm_prop_right_cone, m_prop_cone);

    INL = id_nav_cyl + id_nav_cone + id_res_top + id_res_bot + id_res_cone + id_prop_left_cyl + id_prop_left_cone + id_prop_right_cyl + id_prop_right_cone;

    posForces = posNL+[[0 0 0]; prop_left_cyl_offset; prop_right_cyl_offset];
    forces = horzcat(zeros(3,2), forces.');
    alphaNL = aAngulaire(forces, centre_de_masse, INL, vangulaire, AngRot, posForces);
