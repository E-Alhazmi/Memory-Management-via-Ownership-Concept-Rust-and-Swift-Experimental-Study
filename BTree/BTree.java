import java.util.Random;
/**
 * COPYRIGHT (c) 2018 Elaf Alhazmi . All Rights Reserved.
 * Java BTree class
 */
class BTree {

    public static void main(String[] args) {

        BT bt = new BT();
        int Num_of_Nodes = 50000000;
        int[] array_of_Rand_Num = new int[Num_of_Nodes];        
        System.out.println("Loop : Generating Permutation Numbers from 0 - " + Num_of_Nodes);
        System.out.println("Elapsed Time (NT) ");
        System.out.println ("-------------------");
        double start_NT_loop1 = System.nanoTime( );

        for (int i = 0; i < Num_of_Nodes; i++) {
            array_of_Rand_Num[i] = i;
        }
        double end_NT_loop1 = System.nanoTime( );
        double diff_NT_loop1 = end_NT_loop1 - start_NT_loop1;
        System.out.println ((diff_NT_loop1)/1000000.0D );
        System.out.println("\n\nShuffle : Shuffle Permutation number");
        System.out.println("Elapsed Time (NT) ");
        System.out.println ("----------------------");
        double start_NT_shuffle1 = System.nanoTime( );
        shuffle(array_of_Rand_Num, Num_of_Nodes);
        double end_NT_shuffle1 = System.nanoTime( );
        double diff_NT_shuffle1 = end_NT_shuffle1 - start_NT_shuffle1;
        System.out.println ((diff_NT_shuffle1)/1000000.0D );
        System.out.println("\n\nInsert");
        System.out.println("Elapsed Time (NT)");
        System.out.println ("--------------------------");
        double start_NT_insert1 = System.nanoTime( );

        for (int i = 0; i < Num_of_Nodes; i++) {
            bt.insert(array_of_Rand_Num[i]);
        }
        double end_NT_insert1 = System.nanoTime( );
        double diff_NT_insert1 = end_NT_insert1 - start_NT_insert1;

        
        System.out.println("\n\nBinary Search Tree");
        System.out.println("Elapsed Time (NT) ");
        System.out.println ("--------------------------------");
        double start_NT_binary1 = System.nanoTime( );
        Random r2 = new Random();
        boolean c;
        int c_found =0 ;
        int c_not_found = 0;
        for (int j = 0; j < Num_of_Nodes; j++) {
            c = bt.search(r2.nextInt(Num_of_Nodes), bt.root);
            if (c == true)
            { c_found++;}
            else
            { c_not_found++ ;}

        }
        double end_NT_binary1 = System.nanoTime( );
        double diff_NT_binary1 = end_NT_binary1 - start_NT_binary1;
        System.out.println ((diff_NT_binary1)/1000000.0D);
        System.out.println("\n\nBinary Tree - Replacement");
        System.out.println("Elapsed Time (NT) ");
        System.out.println ("--------------------------------");
        double start_NT_replace1 = System.nanoTime( );
        Random r3 = new Random();

        for (int j = 0; j < Num_of_Nodes; j++) {
            bt.replase(r3.nextInt(Num_of_Nodes), bt.root);
            
        }
        double end_NT_replace1 = System.nanoTime( );
        double diff_NT_replace1 = end_NT_replace1 - start_NT_replace1;
        System.out.println ((diff_NT_replace1)/1000000.0D); 
        System.out.println ("Nodes created = "+ bt.Nodes_created);

    }

    public static void shuffle(int[] a, int count_num) {
        int r;
        int temp;
        for (int i = count_num - 1; i > 0; --i) {
            Random r1 = new Random();
            r = r1.nextInt(count_num);
            temp = a[i];
            a[i] = a[r];
            a[r] = temp;
        }
    }
}
