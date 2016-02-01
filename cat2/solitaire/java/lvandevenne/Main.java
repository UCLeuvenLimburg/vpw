//package domain;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;
import java.util.Set;

public class Main {
	
	private static Set<Integer[]> result;
	
    public static void main(String[] args){
        R.open();
                
        int aantal = R.integer();
        int index = 0;
        int[] input = null;
           
        for(int i = 1; i <= aantal; i++){
        	result = new HashSet<>();
        	input = R.intArray();
        	input = solve(input);
        	print(input);
        }
                
        R.close();
    }
  
    private static ArrayList<int[]> successors( int[] cfg ){
    	ArrayList<int[]> succes = new ArrayList<>();
    	int left = -1;
    	int right = -1;
    	for(int i = 1; i < cfg.length; i++){
    		left = findLeft(cfg, i);
    		right = findRight(cfg, i);
    		if(left != -1){
    			int[] cfgLCopy = Arrays.copyOf(cfg, cfg.length);
    			cfgLCopy = jump(left, cfgLCopy, false);
    			succes.add(cfgLCopy);
    		}
    		if(right != -1){
    			int[] cfgRCopy = Arrays.copyOf(cfg, cfg.length);
    			cfgRCopy = jump(right, cfgRCopy, true);
    			succes.add(cfgRCopy);
    		}
    	}
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

	private static int[] jump(int x, int[] sol, boolean b) {
		if(b){
			sol[x] = 0;
			sol[x+1] = 0;
			sol[x+2] = 1;
			return sol;
		}else{
			sol[x] = 1;
			sol[x+1] = 0;
			sol[x+2] = 0;
			return sol;
		}
	}


	private static int findRight(int[] sol, int k) {
		for(int i = k; i < sol.length-2; i++){
			if(sol[i] == 1
				&& sol[i+1] == 1
				&& sol[i+2] == 0)
				
				return i;
		}
		return 0;
	}
	
	private static int findLeft(int[] sol, int k) {
		for(int i = k; i < sol.length-2; i++){
			if(sol[i] == 0
				&& sol[i+1] == 1
				&& sol[i+2] == 1)
				
				return i;
		}
		return 0;
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
