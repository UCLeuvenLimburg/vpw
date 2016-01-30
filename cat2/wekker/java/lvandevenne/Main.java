//package domain;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;

public class Main {

    private static HashSet<String> rijgjes = null;
    private static ArrayList<String> copy = null;

        
    public static void main(String[] args){
        R.open();
                
        int aantal = R.integer();
        int[] start = null;
        int[] end = null;
        int push;

        for(int i = 1; i <= aantal; i++){
        	start = R.intArray();
        	end = R.intArray();
        	push = count(start, end);
        	
        	System.out.println(i + " " + push);
        }
                
        R.close();
    }
  
    private static int count(int[] start, int[] end) {
    	int from = getMinutesFromMidnight(start);
    	int to = getMinutesFromMidnight(end);
    	int calc = Math.abs(from - to );
    	
    	int hPush = (int)(calc / 60);
    	int mPush = calc%60;
    	
    	if(mPush > 30){
    		hPush++;
    		mPush = 60 - mPush;
    	}

    	if(hPush > 12){
    		hPush = 24 - hPush;
    	}
    	    	
    	return hPush + mPush;
    }
    
    private static int getMinutesFromMidnight(int[] arr) {
    	return 60*arr[0] + arr[1];
	}
    
    /*
    private static int count(int[] start, int[] end) {
    	int pushes = 0;
    	int sHour = start[0];
    	int sMin = start[1];
    	int eHour = end[0];
    	int eMin = end[1];
    	    	
    	int mPushes = Math.abs(sMin - eMin);
    	if((60 - mPushes < 30)
    			&& (eHour - sHour < 12)
    			){
    		System.out.println(eHour - sHour);
    		pushes += 60 - mPushes;
    		sHour++;
    	}else{
	    	if(mPushes > 30){
	    		pushes += mPushes - 30;
	    	}else{
	    		pushes += mPushes;
	    	}
	    }
    	System.out.println("startuur: " + sHour);
    	
    	System.out.println("einduur: " + eHour);

    	System.out.println("totalpush: " + pushes);

    	
    	int hPushes = Math.abs(sHour - eHour);
    	if(hPushes > 12){
    		pushes += hPushes - 12;
    	}else{
    		pushes += hPushes;
    	}
    	
    	System.out.println(Math.abs(sHour - eHour));    	
    	System.out.println(Math.abs(sMin - eMin));
 	
    	return pushes;
	}*/

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
