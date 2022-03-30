using Task_3;
bool t = true;

while (t)
{
    Console.WriteLine("1 - Get the day of week of 'your' date");
    Console.WriteLine("2 - Get duration between 'now' and 'your' dates");
    Console.WriteLine("3 - Exit the program");
    Console.Write("\nEnter your choice: ");
    int choice = Convert.ToInt32(Console.ReadLine());
    switch (choice)
    {
        case 1:
            {
                var date = new DateService();
                Console.WriteLine("\nEnter your date (dd.mm.yy): ");
                string userdate = Console.ReadLine();
                string day_of_week = date.GetDayOfWeek(userdate);
                Console.WriteLine($"\nDay of week is {day_of_week}\n");
                break;
            }
        case 2:
            {
                Console.WriteLine("\nEnter your date (dd.mm.yy): ");
                var date = new DateService();
                var userdate = Console.ReadLine();
                string[] parametrs = userdate.Split(new char[] { '.' }, StringSplitOptions.RemoveEmptyEntries);
                int duration = date.GetDaysSpan(Convert.ToInt32(parametrs[0]), Convert.ToInt32(parametrs[1]), Convert.ToInt32(parametrs[2]));
                Console.WriteLine($"\nDuration between your date and now date is {duration}\n");
                break;
            }
        case 3:
            {
                t = false;
                break;
            }
        default:
            {
                t = false;
                break;
            }
    }
}