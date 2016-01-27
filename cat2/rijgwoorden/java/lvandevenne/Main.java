package domain;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;

public class Main {

	private static HashSet<String> rijgjes = null;

	
	public static void main(String[] args){
		R.open();
		
		int aantal = R.integer();
		ArrayList<String> words = null;
		
		for(int i = 1; i <= aantal; i++){
			rijgjes = new HashSet<>();
			words = new ArrayList<String>( Arrays.asList(R.lineArray()) );
			if(Integer.parseInt(words.get(0)) < 3){
				System.out.print(i + " geen oplossing\n");
			}else{
				words.remove(0);
				permute(words, 0);
				print(i);
			}
		}
		
		R.close();
	}
	
	private static void print(int index){
		if(rijgjes.isEmpty()){
			System.out.print(index + " geen oplossing\n");
		}else{
			System.out.print(index);
			for(String s : rijgjes){
				System.out.print(" " + s);
			}
			System.out.print("\n");

		}
	}
	
	private static void permute(ArrayList<String> words, int k){
        for(int i = k; i < words.size(); i++){
            Collections.swap(words, i, k);
            String rijg = find(words);
            if(rijg != null){
            	addRijg(rijg);
            }else{
            	permute(words, k+1);
            	Collections.swap(words, k, i);
            }
        }
        if (k == words.size() -1){
            return;
        }
    }

	private static void addRijg(String rijg) {
		if(rijgjes.isEmpty()){
    		rijgjes.add(rijg);
        }else if(rijg.length() > rijgjes.iterator().next().length() ){
        			rijgjes.clear();
	            	rijgjes.add(rijg);
        		
        	}
	}

	private static String find(ArrayList<String> words) {
		int wordCount = 1;
		String rijg = words.get(0);
		for(int i = 1; i < words.size(); i++){
			if( words.get(i-1).charAt( words.get(i-1).length()-1 ) == words.get(i).charAt(0) ){
				rijg += words.get(i);
				wordCount++;
			}else if(wordCount >= 3){
					return rijg;
			}else{
				return null;
			}
		}
		return null;
	}
	
	public static class  R{
		
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