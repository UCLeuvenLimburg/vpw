
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class Main
{
    private static ArrayList<String> results;

    private static String[] wordParts;

    public static void main(String[] args)
    {
        try ( Scanner scanner = new Scanner( System.in ))
        {
            int n = scanner.nextInt();

            for ( int caseIndex = 1; caseIndex <= n; ++caseIndex )
            {
                int k = scanner.nextInt();

                String[] wordParts = new String[k];
                for ( int i = 0; i != k; ++i )
                {
                    wordParts[i] = scanner.next();
                }

                solve( caseIndex, wordParts );
            }
        }
    }

    private static void solve(int caseIndex, String... parts)
    {
        results = new ArrayList<>();
        wordParts = parts;

        for ( char c : "abcdefghijklmnopqrstuvwxyz".toCharArray() )
        {
            solve( c, "", 0 );
        }

        if ( results.isEmpty() )
        {
            System.out.println( String.format( "%d geen oplossing", caseIndex ) );
        }
        else
        {
            Collections.sort( results );

            System.out.println( String.format( "%d %s", caseIndex, String.join( " ", results ) ) );
        }
    }

    private static void solve(char startChar, String accumulator, int n)
    {
        if ( n > 1 )
        {
            registerPotentialSolution( accumulator );
        }

        for ( int i = 0; i != wordParts.length; ++i )
        {
            String wordPart = wordParts[i];

            if ( wordPart != null && firstLetter( wordPart ) == startChar )
            {
                // Remove word part from list
                wordParts[i] = null;

                // Continue search
                solve( lastLetter( wordPart ), accumulator + wordPart, n + 1 );

                // Restore array to its former glory
                wordParts[i] = wordPart;
            }
        }
    }

    private static void registerPotentialSolution(String string)
    {
        if ( results.isEmpty() )
        {
            results.add( string );
        }
        else
        {
            String existingSolution = results.get( 0 );

            if ( existingSolution.length() < string.length() )
            {
                // New solution is longer than previous ones
                // Toss out old solutions and keep only new longer solution
                results.clear();
                results.add( string );
            }
            else if ( existingSolution.length() == string.length() )
            {
                // New solution is as long as previous ones
                // Keep new solution along with all others
                results.add( string );
            }
        }
    }

    private static char firstLetter(String str)
    {
        return str.charAt(0);
    }

    private static char lastLetter(String str)
    {
        return str.charAt(str.length() - 1);
    }
}
