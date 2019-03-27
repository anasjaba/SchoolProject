package compteurjetons;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Observer;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.SwingWorker;

/**
 *
 * @author Samuel Rondeau
 */
public class Computer extends SwingWorker<Long, Void> {

    private CompteurJetons compteur;
    private File fichier;
    private boolean termine = false;

    public Computer(Observer obs) {
        compteur = new CompteurJetons(obs);
    }

    public String selectFichier(FenetreCompteur parent) {
        fichier = null;

        // sélection de fichier
        final JFileChooser fc = new JFileChooser();
        int returnVal = fc.showOpenDialog(parent);

        // validité
        if (returnVal == JFileChooser.APPROVE_OPTION) {
            fichier = fc.getSelectedFile();
        }

        // nom du fichier
        String filepath = "";
        try {
            filepath = fichier.getName();
        } catch (NullPointerException e) {
        }

        return filepath;
    }

    // le comptage
    @Override
    public Long doInBackground() {
        long nbJetons = 0;
        try {
            nbJetons = compteur.compter(fichier);
        } catch (FileNotFoundException e) {
        }
        return nbJetons;
    }

    // action lorsque terminé
    @Override
    protected void done() {
        termine = true;
    }

    // annulation
    public void arreter() {
        cancel(true);
    }

    // exécution
    public void executer() {
        termine = false;
        execute();
    }

    // retourne l'état terminé ou non
    public boolean termine() {
        return termine;
    }

    // affiche un message de succès
    public void msgSucces() {
        JOptionPane.showMessageDialog(null,
                "Le comptage est terminé",
                "Comptage terminé",
                JOptionPane.INFORMATION_MESSAGE);
    }
}
