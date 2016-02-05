import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class Configuration
{
    private final boolean[] contents;

    public Configuration( boolean... contents )
    {
        this.contents = contents;
    }

    public boolean canJumpLeft(int i)
    {
        return i >= 2 && !contents[i - 2] && contents[i - 1] && contents[i];
    }

    public Configuration jumpLeft(int i)
    {
        if ( !canJumpLeft( i ) )
        {
            throw new IllegalArgumentException();
        }
        else
        {
            boolean[] copy = copyContents();

            copy[i] = false;
            copy[i - 1] = false;
            copy[i - 2] = true;

            return new Configuration( copy );
        }
    }

    public boolean canJumpRight(int i)
    {
        return i + 2 < contents.length && !contents[i + 2] && contents[i + 1] && contents[i];
    }

    public Configuration jumpRight(int i)
    {
        if ( !canJumpRight( i ) )
        {
            throw new IllegalArgumentException();
        }
        else
        {
            boolean[] copy = copyContents();

            copy[i] = false;
            copy[i + 1] = false;
            copy[i + 2] = true;

            return new Configuration( copy );
        }
    }

    private boolean[] copyContents()
    {
        return Arrays.copyOf( contents, contents.length );
    }

    public Set<Configuration> successors(int i)
    {
        Set<Configuration> result = new HashSet<>();

        if ( canJumpLeft( i ) )
        {
            result.add( jumpLeft( i ) );
        }

        if ( canJumpRight( i ) )
        {
            result.add( jumpRight( i ) );
        }

        return result;
    }

    public Set<Configuration> successors()
    {
        Set<Configuration> result = new HashSet<>();

        for ( int i = 0; i != contents.length; ++i )
        {
            result.addAll( successors( i ) );
        }

        return result;
    }

    public int countStones()
    {
        int result = 0;

        for ( int i = 0; i != this.contents.length; ++i )
        {
            if ( contents[i] )
            {
                ++result;
            }
        }

        return result;
    }

    public static Set<Configuration> successors(Set<Configuration> configurations)
    {
        Set<Configuration> result = new HashSet<>();

        for ( Configuration c : configurations )
        {
            result.addAll( c.successors() );
        }

        return result;
    }

    public Set<Configuration> reachableSolutions()
    {
        Set<Configuration> configurations = new HashSet<Configuration>();

        int i = countStones() - 1;

        if ( i >= 0 )
        {
            configurations.add( this );

            while ( i > 0 )
            {
                configurations = successors( configurations );

                --i;
            }
        }

        return configurations;
    }

    public int indexOfLeftMostStone()
    {
        int i = 0;

        while ( !contents[i] )
        {
            ++i;
        }

        return i;
    }

    public int size()
    {
        return contents.length;
    }
    
    public int indexOfLeftMostStoneInSolution()
    {
        int min = contents.length;
        
        for ( Configuration cfg : reachableSolutions() )
        {
            min = Math.min( min, cfg.indexOfLeftMostStone() );
        }
        
        return min;
    }

    @Override
    public boolean equals(Object object)
    {
        if ( !(object instanceof Configuration) )
        {
            return false;
        }
        else
        {
            Configuration other = (Configuration) object;

            return Arrays.equals( this.contents, other.contents );
        }
    }

    @Override
    public int hashCode()
    {
        return Arrays.hashCode( contents );
    }

    @Override
    public String toString()
    {
        StringBuilder sb = new StringBuilder();

        sb.append( '[' );

        for ( boolean b : contents )
        {
            sb.append( b ? 'x' : '.' );
        }

        sb.append( ']' );

        return sb.toString();
    }
}
