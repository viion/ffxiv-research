using System;

namespace SqpackIndex2
{
    class Program
    {
        static void Main(string[] args)
        {
            var sqpackTest = new Sqpack();
            sqpackTest.OpenFile(5, 0);

            Console.WriteLine("Press enter to exit..");
            Console.ReadLine();
        }
    }
}
