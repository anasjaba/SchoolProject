import java.util.Random;

public class Main  
{
   /**
     * Fonction principale
     */
   public static void main(String[] args) 
   {
      // creer un monceau avec 22 elements et un tableau equivalent
      int numItems = 22;
      BinaryHeap<Integer> heap = new BinaryHeap<Integer>( );
      Integer [ ] items = new Integer[ numItems ];

      int i;
      int j;

      // en inserant les elements un a un
      for( i = 11, j = 0; j != numItems; i = ( i + 37 ), j++ )
      {
         heap.insert( i );
         items[ j ] = i;
         
         i %=  numItems; 
      }

      // en construisant le monceau depuis le depart
      System.out.println("Monceau contruit élément par élément:");
      System.out.println( heap.printFancyTree() );

      heap = new BinaryHeap<Integer>( items );
      System.out.println("Monceau contruit d'un trait:");
      System.out.println( heap.printFancyTree() );

      heap.buildMaxHeap( );
      System.out.println("Monceau max contruit d'un trait:");
      System.out.println( heap.printFancyTree() );

      System.out.println();
      System.out.println("Affichage récursif:");
      System.out.println( heap.printFancyTree() );

      System.out.println("Affichage non récursif:");
      System.out.println( heap.nonRecursivePrintFancyTree() );

      System.out.println();
      System.out.println("Tableau d'origine:");
      System.out.println( printArray( items ) );

      BinaryHeap.heapSort( items );
      System.out.println("Tableau ordonne:");
      System.out.println( printArray( items ) );

      BinaryHeap.heapSortReverse( items );
      System.out.println("Tableau inversement ordonne:");
      System.out.println( printArray( items ) );


      /*
       * Ajouter appels pour repondre a la question
       **/
      Integer[] aleatoire = new Integer[1000];
      // Genere les nombres aleatoires
      Random random = new Random();
      random.setSeed(System.nanoTime());
      for(i = 0; i < 1000; i++){
         aleatoire[i] = random.nextInt();
      }

      Integer[] ordonne = aleatoire;
      Integer[] inverse = aleatoire;
      BinaryHeap.heapSort( ordonne );
      BinaryHeap.heapSortReverse( inverse );

      // Cache
      performInsert(aleatoire, 100, 1000, 100);
      performTab(aleatoire, 100, 1000, 100);

      System.out.println("");

      System.out.println("Insertion ordonnee");
      System.out.println(performInsert(ordonne, 100, 1000, 100));
      System.out.println("Tableau ordonne");
      System.out.println(performTab(ordonne, 100, 1000, 100));

      System.out.println("Insertion inversee");
      System.out.println(performInsert(inverse, 100, 1000, 100));
      System.out.println("Tableau inverse");
      System.out.println(performTab(inverse, 100, 1000, 100));

      System.out.println("Insertion non-ordonnee");
      System.out.println(performInsert(aleatoire, 100, 1000, 100));
      System.out.println("Tableau non-ordonne");
      System.out.println(performTab(aleatoire, 100, 1000, 100));

   }

   private static String performInsert(Integer[] a, int start, int stop, int offset){
      String outputString = "";

      long debut = 0;
      long fin = 0;
      int numItems = 0;
      BinaryHeap<Integer> heap;
      for(numItems = 100; numItems <= 1000; numItems+=100){
         heap = new BinaryHeap<Integer>( );
         // Debut de la zone de controle
         debut = System.nanoTime();
         for(int i = 0; i < numItems; i++){
            heap.insert(a[i]);
         }
         fin = System.nanoTime() - debut;
         // Fin de la zone de controle
         outputString += numItems + "\t" + fin + "\n";
      }

      return outputString;
   }

   private static String performTab(Integer[] a, int start, int stop, int offset){
      String outputString = "";

      long debut = 0;
      long fin = 0;
      int numItems = 0;
      BinaryHeap<Integer> heap;
      Integer[] tab;
      for(numItems = 100; numItems <= 1000; numItems+=100){
         tab = new Integer[numItems];
         for(int i = 0; i < numItems; i++){
            tab[i] = a[i];
         }
         // Debut de la zone de controle
         debut = System.nanoTime();
         heap = new BinaryHeap<Integer>( tab );
         fin = System.nanoTime() - debut;
         // Fin de la zone de controle
         outputString += numItems + "\t" + fin + "\n";
      }

      return outputString;
   }

   private static <AnyType> 
   String printArray(AnyType[] a)
   {
      String outputString = "";

      for(AnyType item : a)
      {
         outputString += item;
         outputString += ", ";
      }

      return outputString;
   }
}
