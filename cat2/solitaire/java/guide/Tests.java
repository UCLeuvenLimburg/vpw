import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

import org.junit.Test;

public class Tests
{
    @Test
    public void countStones()
    {
        assertCountStones( "", 0 );
        assertCountStones( ".", 0 );
        assertCountStones( "..", 0 );
        assertCountStones( "...", 0 );
        assertCountStones( "x", 1 );
        assertCountStones( "xx", 2 );
        assertCountStones( "xxx", 3 );
        assertCountStones( "x..", 1 );
        assertCountStones( ".x..", 1 );
        assertCountStones( "...x", 1 );
    }

    @Test
    public void indexOfLeftMostStone()
    {
        assertIndexOfLeftMostStone( "x", 0 );
        assertIndexOfLeftMostStone( "x.", 0 );
        assertIndexOfLeftMostStone( "x..", 0 );
        assertIndexOfLeftMostStone( "xx", 0 );
        assertIndexOfLeftMostStone( "x.....x", 0 );
        assertIndexOfLeftMostStone( ".x", 1 );
        assertIndexOfLeftMostStone( "..x", 2 );
        assertIndexOfLeftMostStone( "..xxxxx", 2 );
    }

    @Test
    public void canJumpLeft()
    {
        assertCanJumpLeft( "" );
        assertCanJumpLeft( "." );
        assertCanJumpLeft( "x" );
        assertCanJumpLeft( ".." );
        assertCanJumpLeft( "xx" );
        assertCanJumpLeft( ".x" );
        assertCanJumpLeft( "x." );
        assertCanJumpLeft( ".xx", 2 );
        assertCanJumpLeft( "..x" );
        assertCanJumpLeft( ".xxx", 2 );
        assertCanJumpLeft( ".xx.xx", 2, 5 );
    }

    @Test
    public void canJumpRight()
    {
        assertCanJumpRight( "" );
        assertCanJumpRight( "." );
        assertCanJumpRight( "x" );
        assertCanJumpRight( ".." );
        assertCanJumpRight( "xx" );
        assertCanJumpRight( ".x" );
        assertCanJumpRight( "x." );
        assertCanJumpRight( ".xx" );
        assertCanJumpRight( "xx.", 0 );
        assertCanJumpRight( "..x" );
        assertCanJumpRight( ".xxx" );
        assertCanJumpRight( ".xx.xx", 1 );
        assertCanJumpRight( ".xx.xx.", 1, 4 );
    }

    @Test
    public void jumpLeft()
    {
        assertJumpLeft( ".xx", 2, "x.." );
        assertJumpLeft( ".xx.", 2, "x..." );
        assertJumpLeft( "..xx", 3, ".x.." );
        assertJumpLeft( "x.xx", 3, "xx.." );
        assertJumpLeft( "xx.xx", 4, "xxx.." );
    }

    @Test
    public void jumpRight()
    {
        assertJumpRight( "xx.", 0, "..x" );
        assertJumpRight( "xxx.", 1, "x..x" );
        assertJumpRight( "xxx..", 1, "x..x." );
        assertJumpRight( "xxx.x", 1, "x..xx" );
        assertJumpRight( ".xx.x", 1, "...xx" );
    }

    @Test
    public void successorsAt()
    {
        assertSuccessors( ".", 0 );
        assertSuccessors( "x", 0 );
        assertSuccessors( "..", 0 );
        assertSuccessors( "xx", 0 );
        assertSuccessors( "xxx", 0 );
        assertSuccessors( "xx.", 0, "..x" );
        assertSuccessors( "xx.xx", 0, "..xxx" );
        assertSuccessors( ".xxx.", 2, "x..x.", ".x..x" );
        assertSuccessors( ".xxx..", 2, "x..x..", ".x..x." );
        assertSuccessors( "x.xxx..", 3, "xx..x..", "x.x..x." );
    }

    @Test
    public void successors()
    {
        assertSuccessors( "" );
        assertSuccessors( "." );
        assertSuccessors( "x" );
        assertSuccessors( "x." );
        assertSuccessors( "xx" );
        assertSuccessors( "xx.", "..x" );
        assertSuccessors( "xx.xx", "..xxx", "xxx.." );
        assertSuccessors( ".xxx.", "x..x.", ".x..x" );
        assertSuccessors( ".xxx..", "x..x..", ".x..x." );
        assertSuccessors( "x.xxx..", "xx..x..", "x.x..x." );
        assertSuccessors( ".xx.", "x...", "...x" );
        assertSuccessors( ".xx.xx", "x...xx", "...xxx", ".xxx.." );
    }

    @Test
    public void successorsOfSet()
    {
        assertSuccessors( cfgs( "" ), cfgs() );
        assertSuccessors( cfgs( "." ), cfgs() );
        assertSuccessors( cfgs( "x" ), cfgs() );
        assertSuccessors( cfgs( "", ".", "x" ), cfgs() );
        assertSuccessors( cfgs( "xx." ), cfgs( "..x" ) );
        assertSuccessors( cfgs( "xx.", "x" ), cfgs( "..x" ) );
        assertSuccessors( cfgs( "xx.", "." ), cfgs( "..x" ) );
        assertSuccessors( cfgs( "xx.", "xx." ), cfgs( "..x" ) );
        assertSuccessors( cfgs( "xx.", ".xx" ), cfgs( "..x", "x.." ) );
        assertSuccessors( cfgs( "xx.xx", ".xx" ), cfgs( "..xxx", "xxx..", "x.." ) );
    }

    @Test
    public void reachableSolutions()
    {
        assertReachable( "" );
        assertReachable( "." );
        assertReachable( "." );
        assertReachable( "xx" );
        assertReachable( "x.", "x." );
        assertReachable( ".x", ".x" );
        assertReachable( ".x.", ".x." );
        assertReachable( "..x", "..x" );
        assertReachable( ".xx", "x.." );
        assertReachable( ".xx.", "x...", "...x" );
    }

    @Test
    public void indexOfLeftMostStoneInSolution()
    {
        assertIndexOfLeftMostStoneInSolution( "x.", 0 );
        assertIndexOfLeftMostStoneInSolution( ".x", 1 );
        assertIndexOfLeftMostStoneInSolution( "x..", 0 );
        assertIndexOfLeftMostStoneInSolution( ".xx..", 0 );
        assertIndexOfLeftMostStoneInSolution( "..xx..", 1 );
        
        assertIndexOfLeftMostStoneInSolution( ".x.x.x.xx.", 0 );
        assertIndexOfLeftMostStoneInSolution( ".xx.x.x.x.", 6 );
        assertIndexOfLeftMostStoneInSolution( "xx.x.xxx.x", 5 );
        assertIndexOfLeftMostStoneInSolution( "x.xxxxx.xx", 3 );
    }

    private void assertIndexOfLeftMostStoneInSolution(String c, int expected)
    {
        Configuration cfg = cfg( c );

        assertEquals( expected, cfg.indexOfLeftMostStoneInSolution() );
    }

    private void assertIndexOfLeftMostStone(String c, int expected)
    {
        Configuration cfg = cfg( c );

        assertEquals( expected, cfg.indexOfLeftMostStone() );
    }

    private void assertReachable(String originalString, String... expectedStrings)
    {
        Configuration original = cfg( originalString );
        Set<Configuration> expected = cfgs( expectedStrings );
        Set<Configuration> actual = original.reachableSolutions();

        for ( Configuration e : expected )
        {
            assertTrue( String.format( "%s should be solution of %s", e, original ), actual.contains( e ) );
        }

        for ( Configuration a : actual )
        {
            assertTrue( String.format( "%s shouldn't be solution of %s", a, original ), expected.contains( a ) );
        }
    }

    private void assertSuccessors(Set<Configuration> original, Set<Configuration> expected)
    {
        Set<Configuration> actual = Configuration.successors( original );

        for ( Configuration e : actual )
        {
            assertTrue( String.format( "%s should be successor of %s", e, original ), expected.contains( e ) );
        }

        for ( Configuration a : expected )
        {
            assertTrue( String.format( "%s shouldn't be successor of %s", a, original ), actual.contains( a ) );
        }
    }

    private void assertCountStones(String s, int expected)
    {
        Configuration c = cfg( s );

        assertEquals( String.format( "%s should count %d stones", c, expected ), expected, c.countStones() );
    }

    private void assertSuccessors(String initString, String... successorStrings)
    {
        Configuration init = cfg( initString );
        Set<Configuration> expected = cfgs( successorStrings );
        Set<Configuration> actual = init.successors();

        for ( Configuration e : expected )
        {
            assertTrue( String.format( "%s should be successor of %s", e, init ), actual.contains( e ) );
        }

        for ( Configuration a : actual )
        {
            assertTrue( String.format( "%s shouldn't be successor of %s", a, init ), expected.contains( a ) );
        }
    }

    private void assertSuccessors(String initString, int index, String... successorStrings)
    {
        Configuration init = cfg( initString );
        Set<Configuration> expected = cfgs( successorStrings );
        Set<Configuration> actual = init.successors( index );

        for ( Configuration e : expected )
        {
            assertTrue( String.format( "%s should be successor of %s @ %d", e, init, index ), actual.contains( e ) );
        }

        for ( Configuration a : actual )
        {
            assertTrue( String.format( "%s shouldn't be successor of %s @ %d", a, init, index ), expected.contains( a ) );
        }
    }

    private Set<Configuration> cfgs(String... ss)
    {
        Set<Configuration> set = new HashSet<>();

        for ( String s : ss )
        {
            set.add( cfg( s ) );
        }

        return set;
    }

    private void assertJumpLeft(String initString, int index, String expectedString)
    {
        Configuration init = cfg( initString );
        Configuration expected = cfg( expectedString );

        assertEquals( expected, init.jumpLeft( index ) );
    }

    private void assertJumpRight(String initString, int index, String expectedString)
    {
        Configuration init = cfg( initString );
        Configuration expected = cfg( expectedString );

        assertEquals( expected, init.jumpRight( index ) );
    }

    private void assertCanJumpLeft(String s, Integer... indices)
    {
        HashSet<Integer> set = new HashSet<Integer>( Arrays.<Integer> asList( indices ) );

        for ( int i = 0; i != s.length(); ++i )
        {
            assertCanJumpLeft( set.contains( i ), s, i );
        }
    }

    private void assertCanJumpRight(String s, Integer... indices)
    {
        HashSet<Integer> set = new HashSet<Integer>( Arrays.<Integer> asList( indices ) );

        for ( int i = 0; i != s.length(); ++i )
        {
            assertCanJumpRight( set.contains( i ), s, i );
        }
    }

    private void assertCanJumpLeft(boolean expected, String s, int index)
    {
        if ( expected )
        {
            assertTrue( String.format( "%s @ %d should be left-jumpable", s, index ), cfg( s ).canJumpLeft( index ) );
        }
        else
        {
            assertFalse( String.format( "%s @ %d shouldn't be left-jumpable", s, index ), cfg( s ).canJumpLeft( index ) );
        }
    }

    private void assertCanJumpRight(boolean expected, String s, int index)
    {
        if ( expected )
        {
            assertTrue( String.format( "%s @ %d should be right-jumpable", s, index ), cfg( s ).canJumpRight( index ) );
        }
        else
        {
            assertFalse( String.format( "%s @ %d shouldn't be right-jumpable", s, index ), cfg( s ).canJumpRight( index ) );
        }
    }

    private static Configuration cfg(boolean[] bs)
    {
        return new Configuration( bs );
    }

    private static Configuration cfg(String s)
    {
        boolean[] bs = new boolean[s.length()];

        for ( int i = 0; i != s.length(); ++i )
        {
            bs[i] = s.charAt( i ) == 'x';
        }

        return cfg( bs );
    }
}
