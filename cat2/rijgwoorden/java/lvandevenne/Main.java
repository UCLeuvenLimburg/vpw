//package domain;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;

public class Main {

    private static HashSet<String> rijgjes = null;
    private static ArrayList<String> copy = null;

        
    public static void main(String[] args){
        R.open();
                
        int aantal = R.integer();
        ArrayList<String> words = null;
                
        for(int i = 1; i <= aantal; i++){
        	rijgjes = new HashSet<>();
        	words = new ArrayList<>(Arrays.asList(R.lineArray()));
        	
        	if(Integer.parseInt( words.get(0) ) >= 2){
        		words.remove(0);
	        	permute(words, 0);
        	}
        	
        	copy = new ArrayList<>(rijgjes);
	        Collections.sort(copy);
        	
	        print(i);
        	
        }
                
        R.close();
    }
        
    private static void print(int index){
        if(copy.isEmpty()){
            System.out.print(index + " geen oplossing\n");
        }else{
            System.out.print(index);
            for(String s : copy){
                System.out.print(" " + s);
            }
            System.out.print("\n");

        }
    }
        
    private static void permute(ArrayList<String> words, int k){
    	if(k >= 2){
	    	String rijg = "";
	    	for(int count = 0; count < k; count++){
	    		rijg += words.get(count);
	    	}
	    	addRijg(rijg);
    	}
   	
        for(int i = k; i < words.size(); i++){
	        if( k == 0 
	           	|| ( lastLetter(words.get(k-1)) == firstLetter(words.get(i)) ) ){
	         
	        	Collections.swap(words, i, k);
	           	permute(words, k+1);
	            Collections.swap(words, k, i);
	        }
        }

    }

    private static void addRijg(String rijg) {
        if(rijgjes.isEmpty()){
            rijgjes.add(rijg);
        }else if(rijg.length() > rijgjes.iterator().next().length() ){
            rijgjes.clear();
            rijgjes.add(rijg);
        }if(rijg.length() == rijgjes.iterator().next().length() ){
        	rijgjes.add(rijg);
        }
    }

    private static String find(ArrayList<String> words) {
        int wordCount = 1;
        String rijg = words.get(0);
        for(int i = 1; i < words.size(); i++){
            if( lastLetter( words.get(i-1) ) == firstLetter( words.get(i) ) ){
                rijg += words.get(i);
                wordCount++;
            }else if(wordCount >= 2){
                return rijg;
            }else{
                return null;
            }
        }
        return null;
    }

    private static char firstLetter(String string)
    {
        return string.charAt(0);
    }

    private static char lastLetter(String string)
    {
        return string.charAt( string.length() - 1 );
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
            char[] s = line().toCharArray();
            int[] rij = new int[s.length];
                        
            for(int i = 0; i < rij.length; i++){
                rij[i] = (int)s[i];
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
