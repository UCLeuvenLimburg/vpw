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

    public int size()
    {
        return contents.length;
    }

    private boolean[] copyContents()
    {
        return Arrays.copyOf( contents, contents.length );
    }

    public int countStones()
    {
        // TODO
    }

    public boolean canJumpLeft(int i)
    {
        // TODO
    }

    public Configuration jumpLeft(int i)
    {
        // TODO
    }

    public boolean canJumpRight(int i)
    {
        // TODO
    }

    public Configuration jumpRight(int i)
    {
        // TODO
    }

    public Set<Configuration> successors(int i)
    {
        // TODO
    }

    public Set<Configuration> successors()
    {
        // TODO
    }

    public static Set<Configuration> successors(Set<Configuration> configurations)
    {
        // TODO
    }

    public Set<Configuration> reachableSolutions()
    {
        // TODO
    }

    public int indexOfLeftMostStone()
    {
        // TODO
    }

    public int indexOfLeftMostStoneInSolution()
    {
        // TODO
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
