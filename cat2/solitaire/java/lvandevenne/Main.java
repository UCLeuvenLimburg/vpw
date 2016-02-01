//package domain;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;
import java.util.Set;

public class Main {
                
    public static void main(String[] args){
        R.open();
                
        int aantal = R.integer();
        int index = 0;
        int[] input = null;
        ArrayList<ArrayList<int[]>> start = new ArrayList<>();
        ArrayList<ArrayList<int[]>> general = new ArrayList<>();
   
        
        for(int i = 1; i <= aantal; i++){
            start = new ArrayList<>();
            input = R.intArray();
                
            start.add(successors(input));
                
            for(ArrayList<int[]> arl : start){
                general.addAll(successors(arl));
            }
            print(general);
        }
       
        R.close();
    }

    private static ArrayList<int[]> successors( ArrayList<int[]> cfg ){
        ArrayList<int[]> list = new ArrayList<>();
        for(int[] arr : cfg){
            list.addAll( successors(arr) );
        }
        return list;
    }
    
    private static void print(int[] input) {
        for(int i = 1; i < input.length; i++){
            System.out.print(input[i] + " ");
        }
    }


    private static int[] solve(int[] sol) {
        int x = 0;
        x = findLeft(sol, 0);
        sol = jump(x, sol, false);
                
        return sol;
    }

    private static Set<int[]> successors(int[] configuration)
    {
        Set<int[]> result = new HashSet<>();

        for ( int i = 0; i != configuration.length; ++i )
        {
            result.addAll( leftJump(configuration, i) );
            result.addAll( rightJump(configuration, i) );
        }

        return result;
    }

    private static Set<int[]> leftJump(int[] configuration, int index)
    {
        Set<int[]> result = new HashSet<>();
        
        if ( index >= 2 && configuration[index - 2] == 0 && configuration[index - 1] == 1 && configuration[index] == 1 )
        {
            int[] successor = copy(configuration);
            
            successor[index  ] = 0;
            successor[index-1] = 0;
            successor[index-2] = 1;

            result.add(successor);
        }

        return result;
    }

    private static Set<int[]> rightJump(int[] configuration, int index)
    {
        Set<int[]> result = new HashSet<>();
        
        if ( index + 2 < configuration.length && configuration[index + 2] == 0 && configuration[index + 1] == 1 && configuration[index] == 1 )
        {
            int[] successor = copy(configuration);
            
            successor[index  ] = 0;
            successor[index+1] = 0;
            successor[index+2] = 1;

            result.add(successor);
        }

        return result;
    }

    private static int[] copy(int[] xs)
    {
        return Arrays.copyOf(xs, xs.length);
    }

    public static class R {
                
        private static Scanner scan;
                
        public static int integer(){
            return Integer.parseInt( line() );
        }
                
        public static String line(){
            return scan.nextLine();
        }
                
        public static String[] lineArray(){
            return line().split(" ");
        }
                
        public static String[] lineArrayNoDelimeter(){
            char[] s = line().toCharArray();
            String[] rij = new String[s.length];
            for( int i = 0; i < s.length; i++){
                rij[i] = "" + s[i];
            }
            return rij;
        }
                
        public static char[] charArrayNoDelimeter(){
            return line().toCharArray();
        }
                
        public static List<String> lineList(){
            return (List<String>) Arrays.asList( lineArray() );
        }
                
        public static int[] intArray(){
            String[] input = lineArray();
            int[] rij = new int[input.length];
                        
            for(int i = 0; i < rij.length; i++){
                rij[i] = Integer.parseInt(input[i]);
            }
                        
            return rij;
        }
                
        public static ArrayList<Integer> intArrayList(){
            char[] input = charArrayNoDelimeter();
            System.out.println(input);
            ArrayList<Integer> list = new ArrayList<>();
                        
            for(int i = 0; i < input.length; i++){
                list.add( input[i] - '0' );
                System.out.println((int) input[i]);
            }
                        
            return list;
        }
                
        public static void open(){
            scan = new Scanner(System.in);
        }
                
        public static void close(){
            scan.close();
        }
    }
}