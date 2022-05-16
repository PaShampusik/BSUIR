namespace Lab_7{
    class Program
    {
        static void Main(string[] args)
        {
            
            Rational r1 = new Rational(3, 7);
            Rational r2 = new Rational(2, 9);
            Console.WriteLine("r1 = 3 / 7");
            Console.WriteLine("r2 = 2 / 9");
            Console.WriteLine("r1 + r2 = " + (r1 + r2).ToString());
            Console.WriteLine("r1 - r2 = " + (r1 - r2).ToString());
            Console.WriteLine("r1 * r2 = " + (r1 * r2).ToString());
            Console.WriteLine("r1 / r2 = " + (r1 / r2).ToString());
            Console.WriteLine("r1++ = " + (r1++).ToString());
            Console.WriteLine("++r1 = " + (++r1).ToString());
            Console.WriteLine("r1-- = " + (r1--).ToString());
            Console.WriteLine("--r1 = " + (--r1).ToString());
            Console.WriteLine("r1 > r2 = ???  " +  "====  " + (r1 > r2));
            Console.WriteLine("r1 < r2 = ???  " + "====  " + (r1 < r2));
            Console.WriteLine("r1 == r2 = ???  " + "====  " + (r1 == r2));
            Console.WriteLine("r1 != r2 = ???  " + "====  " + (r1 != r2));
            Console.WriteLine("r1 >= r2 = ???  " + "====  " + (r1 >= r2));
            Console.WriteLine("r1 <= r2 = ???  " + "====  " + (r1 <= r2));

        }
    }
}