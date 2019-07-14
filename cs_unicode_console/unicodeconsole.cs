using System;

namespace HelloConsoleApp {
    class Program {
        static void Main(string[] args) {
            System.Console.OutputEncoding = new System.Text.UTF8Encoding();
            System.Console.WriteLine("こんにちは！");
            System.Console.ReadKey();
        }
    }
}
