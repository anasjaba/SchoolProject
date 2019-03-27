
#ifndef PMTV_MEDIA_MEDIA_MANAGER_H
#define PMTV_MEDIA_MEDIA_MANAGER_H

class PMTVMedia_Media;

class PMTVMedia_MediaManager
{
private:
    PMTVMedia_Media* m_currentMediaPlaying; // Média qui joue

public:
    // Constructeur & Destructeur
    PMTVMedia_MediaManager()  {};
    ~PMTVMedia_MediaManager() {};

    // Retourne une référence vers le média jouant présentement
    PMTVMedia_Media* getCurrentMediaPlaying() { return m_currentMediaPlaying; }

    //------------------------------
    // Contrôle média
    //------------------------------ 
    void playMedia(PMTVMedia_Media* media) { m_currentMediaPlaying = media; } // Joue le media demandé
    void stopMedia() { m_currentMediaPlaying = 0; } // Arrête le media

};

#endif
