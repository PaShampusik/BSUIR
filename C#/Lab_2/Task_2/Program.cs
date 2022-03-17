Task task = new Task();

task.menu();


public class Task{
    public void Input()
    {
        int a = 1, b = 1, c = -23;

        Console.Write("Enter X coordinate: ");
        a = Convert.ToInt32(Console.ReadLine());

        Console.Write("Enter Y coordinate: ");
        b = Convert.ToInt32(Console.ReadLine());

        Func(a, b, c);
    }

    public string Func(int a, int b, int c)
    {
        if (a > c && b > a && a < 0 && b < 0)
        {
            Console.Write("Yes.\n");
            return "Yes.";
        }
        else if ((a == c && b >= c && b <= 0) || (a >= c && a <= 0 && b == 0) || (a >= c && a <= 0 && b == a))
        {
            Console.Write("Point is laying on the Border.\n");
            return "Point is laying on the Border.";
        }
        else
        {
            Console.Write("No.\n");
            return "No.";
        }

    }
    public void menu()
    {
        int a = -1;
        Console.Write("Enter 1 if you want to enter point, otherwise click 0: ");
        a = Convert.ToInt32(Console.ReadLine());
        if(a == 1)
        {
            Input();
        }
        else if(a == 0)
        {
            Environment.Exit(0);
        }
        else
        {
            Console.Write("Wrong input, try again.");
        }
        menu();
    }
}





