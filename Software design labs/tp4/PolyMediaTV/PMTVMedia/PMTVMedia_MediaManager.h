
#ifndef PMTV_MEDIA_MEDIA_MANAGER_H
#define PMTV_MEDIA_MEDIA_MANAGER_H

class PMTVMedia_Media;

class PMTVMedia_MediaManager
{
private:
    PMTVMedia_Media* m_currentMediaPlaying; // M�dia qui joue

public:
    // Constructeur & Destructeur
    PMTVMedia_MediaManager()  {};
    ~PMTVMedia_MediaManager() {};

    // Retourne une r�f�rence vers le m�dia jouant pr�sentement
    PMTVMedia_Media* getCurrentMediaPlaying() { return m_currentMediaPlaying; }

    //------------------------------
    // Contr�le m�dia
    //------------------------------ 
    void playMedia(PMTVMedia_Media* media) { m_currentMediaPlaying = media; } // Joue le media demand�
    void stopMedia() { m_currentMediaPlaying = 0; } // Arr�te le media

};

#endif
