Task_1 a = new Task_1();

a.Input();

public class Task_1{
    public void Input()
    {
        int a = 0;

        Console.Write("Enter the first number(*** format): ");
        a = Convert.ToInt32(Console.ReadLine());

        while ((a / 100 == 0) || (a / 100 > 9))
        {
            Console.Write("You have entered wrong input, try again: ");
            a = Convert.ToInt32(Console.ReadLine());
        }

        Func(a);
    }
    public string Func(int a) {
        int c, b;
        b = a % 100 / 10;
        c = a % 100 % 10;

        if (b > c)
        {
            Console.Write("Second number is bigger than third.");
            return "Second number is bigger than third.";
        }
        else if (c > b)
        {
            Console.Write("Third number is bigger than second.");
            return "Third number is bigger than second.";
        }
        else
        {
            Console.Write("Third and second numbers are equal.");
            return "Third and second numbers are equal.";

        }
    }
}