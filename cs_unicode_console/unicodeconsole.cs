using System;

namespace UnicodeHelloConsoleApp {
    public class Program {
        public static void Main(string[] args) {
            Console.InputEncoding = Console.OutputEncoding = new System.Text.UTF8Encoding();
            Console.WriteLine("こんにちは！");
            Console.ReadKey();
        }
    }
}
