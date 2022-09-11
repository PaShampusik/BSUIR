Task_1.Input();

public class Task_1
{
    public static void Input()
    {
        Console.Write("Enter the first number: ");
        int a = Convert.ToInt32(Console.ReadLine());

        Console.Write("Enter the second number: ");
        int b = Convert.ToInt32(Console.ReadLine());

        Func(a, b);
    }

    public static int max(int a, int b)
    {
        if (a > b)
        {
            return a;
        }
        else
        {
            return b;
        }
    }

    public static int Func(int a, int b)
    {
        int c = max(a, 2 * b + a) - max(7 * a + 2 * b, b);
        Console.WriteLine(c);
        return c;
    }


}