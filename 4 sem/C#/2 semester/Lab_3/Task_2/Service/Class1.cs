
public class Task_2
{
    public static void Input()
    {
        Console.Write("Enter the first number: ");
        double a = Convert.ToInt32(Console.ReadLine());

        Func(a);
    }
    public static double Func(double a)
    {
        if (a < -1)
        {
            a = -a / 3;
        }
        else
        {
            a = Math.Abs(a);
        }

        double c = Math.Log(a + 0.5) + (Math.Exp(a) - Math.Exp(-a));
        Console.WriteLine(c);

        return c;
    }
}