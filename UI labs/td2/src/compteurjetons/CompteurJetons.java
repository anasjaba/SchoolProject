package compteurjetons;

/*
 * CompteurJetons.java
 *
 * Created on 1 octobre 2007, 13:48
 * Mise à jour par Dany Khalife le 20 février 2014
 *
 */

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Random;
import java.util.Scanner;
import java.util.Observer;
import java.util.Observable;

import java.security.InvalidParameterException;

import javax.swing.JFileChooser;
import javax.swing.JFrame;

/**
 * Compte les jetons d'un fichier.
 * 
 * @author michel
 * @author Dany
 */
public class CompteurJetons extends Observable {
	// longueur moyenne (approximative) des jetons initialisée à 4
	private float longueurMoyenne = 4;
	// longueur du fichier en octets
	private long nbOctets = -1;
	// nombre de jetons trouvés
	private int nbJetons = 0;
	// vrai lorsque terminé
	private boolean termine = false;

	private Random rand = new Random();

	/**
	 * Constructeur par parametre Necessite l'utilisation d'un observer pour
	 * recevoir les evennements de notification suite a la lecture d'un nouvel
	 * jeton
	 */
	public CompteurJetons(Observer o) {
		if (o == null)
			throw new InvalidParameterException();
			
		addObserver(o);
	}

	/**
	 * Methode d'acces au nombre de jetons lus
	 */
	public int getJetons() {
		return nbJetons;
	}

	/**
	 * Methode d'acces au progres de la lecture Cette methode retourne un
	 * pourcentage approximatif du progrès et ne garanti pas d'atteindre 100% à
	 * la fin de la tâche. Le calcul dépend de la longueur moyenne des jetons
	 * lus.
	 */
	public int getProgres() {
		if (termine)
			return 100;

		return Math.max(Math.min((int) ((100.0 * (double) longueurMoyenne * (double) nbJetons / (double) nbOctets)), 100), 0);
	}

	/**
	 * Methode d'acces au statut de la lecture
	 */
	public boolean estTermine() {
		return termine;
	}

	/**
	 * Methode qui permet d'effectuer un compte sur un fichier
	 */
	public long compter(File fichier) throws FileNotFoundException {
		Scanner s = new Scanner(new BufferedReader(new FileReader(fichier)));
		nbOctets = fichier.length();

		termine = false;
		nbJetons = 0;
		longueurMoyenne = 4;
		System.out.println("Fichier: " + nbOctets);

		String dernierJeton;
		try {
			while (s.hasNext()) {
				dernierJeton = s.next();
				System.out.println("jeton : " + dernierJeton);
				nbJetons++;
				longueurMoyenne = longueurMoyenne + ((float) dernierJeton.length() - longueurMoyenne) / (float) nbJetons;

				setChanged();
				notifyObservers();

				Thread.sleep(rand.nextInt(500));
			}
			
			termine = true;
			setChanged();
			notifyObservers();
			System.out.println("terminé");
		}catch(InterruptedException e){
		} finally {
			s.close();
		}
		
		return nbJetons;
	}
}