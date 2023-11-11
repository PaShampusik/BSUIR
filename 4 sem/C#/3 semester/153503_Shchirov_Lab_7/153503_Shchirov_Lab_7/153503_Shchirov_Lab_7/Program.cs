using ClassLibrary;

class Program
{
    public static void Main(string[] args)
    {
        List<string> results = new List<string>();
        Integral_Calculation integral_Calculation = new Integral_Calculation(ThreadPriority.Highest, 1);
        Integral_Calculation integral_Calculation2 = new Integral_Calculation(ThreadPriority.Lowest, 2);
        Thread.Sleep(200);
        Integral_Calculation integral_Calculation_3 = new Integral_Calculation(ThreadPriority.Normal, 3);
        Integral_Calculation integral_Calculation_4 = new Integral_Calculation(ThreadPriority.Normal, 4);
        Integral_Calculation integral_Calculation_5 = new Integral_Calculation(ThreadPriority.Normal, 5);

        while (integral_Calculation_5.thread.IsAlive || integral_Calculation_4.thread.IsAlive || integral_Calculation_3.thread.IsAlive || integral_Calculation2.thread.IsAlive || integral_Calculation.thread.IsAlive)
        {
            Thread.Sleep(50);
            (int a, int b) = Console.GetCursorPosition();
            Console.SetCursorPosition(0, 25);
            integral_Calculation.display_progress();
            integral_Calculation2.display_progress();
            integral_Calculation_3.display_progress();
            integral_Calculation_4.display_progress();
            integral_Calculation_5.display_progress();          
            Console.SetCursorPosition(a, b);
        }
    }
}