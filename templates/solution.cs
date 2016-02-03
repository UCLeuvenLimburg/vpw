using System.IO;

namespace ConsoleApplication
{
    class Program
    {

        private static TextReader stdin = System.Console.In;
        private static TextWriter stdout = System.Console.Out;

        static void Main(string[] args)
        {
            int n = int.Parse(stdin.ReadLine());
            for (int i = 0; i < n; i++) {
                string[] l = stdin.ReadLine().Split(' ');
                int k = int.Parse(l[0]);
                stdout.WriteLine(l[1].Substring(k - 1, 1));
            }
        }

    }
}