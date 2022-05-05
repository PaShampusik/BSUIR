namespace Lab_5
{
    public class Railwaystation
    {

        public List<Tarif> tarifs = new List<Tarif>();
        public List<Client> clients = new List<Client>();
        public List<Tuple<Tarif, Client>> bought = new List<Tuple<Tarif, Client>>();

        public Railwaystation()
        {
            tarifs.Add(new Tarif("Москва", 10));
            tarifs.Add(new Tarif("Санкт-Петербург", 11));
            tarifs.Add(new Tarif("Екатеринбург", 12));
            tarifs.Add(new Tarif("Новосибирск", 13));
            tarifs.Add(new Tarif("Красноярск", 14));
            tarifs.Add(new Tarif("Казань", 15));
            tarifs.Add(new Tarif("Самара", 16));
            tarifs.Add(new Tarif("Омск", 17));
            tarifs.Add(new Tarif("Челябинск", 18));
            tarifs.Add(new Tarif("Ростов-на-Дону", 19));
            tarifs.Add(new Tarif("Уфа", 20));
            tarifs.Add(new Tarif("Воронеж", 21));
            tarifs.Add(new Tarif("Краснодар", 22));
            tarifs.Add(new Tarif("Саратов", 23));
            tarifs.Add(new Tarif("Тольятти", 24));
            tarifs.Add(new Tarif("Тюмень", 25));

            clients.Add(new Client("Semen", "123765876789"));
            clients.Add(new Client("Petr", "123456789"));
            clients.Add(new Client("Vasya", "1765789"));
            clients.Add(new Client("Dima", "12789"));
            clients.Add(new Client("Kolya", "123456789"));
            clients.Add(new Client("Masha", "3218659"));
            clients.Add(new Client("Vanya", "123456789"));
            clients.Add(new Client("Sasha", "1236789"));
            clients.Add(new Client("Vlad", "123455789"));
            clients.Add(new Client("Vladimir", "156789"));
            clients.Add(new Client("Vladislav", "34231789"));

        }

        public void ShowTarifs()
        {
            foreach (var item in tarifs)
            {
                Console.WriteLine(item.WhereToGo + " " + item.Price);
            }
        }

        public void ShowClients()
        {
            foreach (var item in clients)
            {
                Console.WriteLine(item.Name + " " + item.Number);
            }
        }

        public void ShowBought()
        {
            foreach (var item in bought)
            {
                Console.WriteLine(item.Item2.Name + " " + item.Item2.Number + " " + item.Item1.WhereToGo + " " + item.Item1.Price);
            }
        }

        public void BuyTarif(Client client, Tarif tarif)
        {
            bought.Add(new Tuple<Tarif, Client>(tarif, client));
        }

        public void ShowBoughtTarifs1(Client client)
        {
            foreach (var item in bought)
            {
                if (item.Item2 == client)
                {
                    Console.WriteLine(item.Item1.ToString());
                }
            }
        }

        public void ShowBoughtTarifs2(Tarif tarif)
        {
            foreach (var item in bought)
            {
                if (item.Item1 == tarif)
                {
                    Console.WriteLine(item.Item2.ToString());
                }
            }
        }

        public int CalculateSumOfBoughtTicketsForClient(string name, string number)
        {
            int sum = 0;
            foreach (var item in bought)
            {
                if (item.Item2.Name == name && item.Item2.Number == number)
                {
                    sum += item.Item1.Price;
                }
            }
            Console.WriteLine("Сумма покупок клиента " + name + " с номером " + number + " равна " + sum);
            return sum;
        }

        public void menu()
        {
            Console.WriteLine("1 - Show all the tarifs");
            Console.WriteLine("2 - Show all the clients of the railwaystation");
            Console.WriteLine("3 - Show all the bought tarifs");
            Console.WriteLine("4 - Buy tarif for a client");
            Console.WriteLine("5 - Show all the bought tarifs by a client.");
            Console.WriteLine("6 - Show all the bought tarifs by a tarif");
            Console.WriteLine("7 - Calculate the cost of the bought tarifs for a client");

            Console.WriteLine("0 - Exit");

            int a = Convert.ToInt32(Console.ReadLine());

            if (a == 0)
            {
                return;
            }
            else if (a == 1)
            {
                this.ShowTarifs();
                Console.WriteLine("Press any button to continue");
                Console.ReadKey();
                this.menu();
            }
            else if (a == 2)
            {
                this.ShowClients();
                Console.WriteLine("Press any button to continue");
                Console.ReadKey();
                this.menu();
            }
            else if (a == 3)
            {
                this.ShowBought();
                Console.WriteLine("Press any button to continue");
                Console.ReadKey();
                this.menu();
            }
            else if (a == 4)
            {
                Console.WriteLine("Enter name of a client");
                string name = Console.ReadLine();
                Console.WriteLine("Enter number of a client");
                string number = Console.ReadLine();
                Console.WriteLine("Enter name of a tarif");
                string nameTarif = Console.ReadLine();
                Console.WriteLine("Enter pricce of a tarif");
                int price = Convert.ToInt32(Console.ReadLine());
                Tarif tarif = new Tarif(nameTarif, price);
                Client client = new Client(name, number);
                this.BuyTarif(client, tarif);
                Console.WriteLine("Press any button to continue");
                Console.ReadKey();
                this.menu();
            }
            else if (a == 5)
            {
                Console.WriteLine("Enter name of a client");
                string name = Console.ReadLine();
                Console.WriteLine("Enter number of a client");
                string number = Console.ReadLine();
                this.ShowBoughtTarifs1(new Client(name, number));
                Console.WriteLine("Press any button to continue");
                Console.ReadKey();
                this.menu();
            }
            else if (a == 6)
            {
                Console.WriteLine("Enter name of a tarif");
                string nameTarif = Console.ReadLine();
                Console.WriteLine("Enter pricce of a tarif");
                int price = Convert.ToInt32(Console.ReadLine());
                Tarif tarif = new Tarif(nameTarif, price);
                this.ShowBoughtTarifs2(tarif);
                Console.WriteLine("Press any button to continue");
                Console.ReadKey();
                this.menu();
            }
            else if (a == 7)
            {
                Console.WriteLine("Enter name of a client");
                string name = Console.ReadLine();
                Console.WriteLine("Enter number of a client");
                string number = Console.ReadLine();

                this.CalculateSumOfBoughtTicketsForClient(name, number);
                Console.WriteLine("Press any button to continue");
                Console.ReadKey();
                this.menu();
            }
            else
            {
                Console.WriteLine("Error");
                Console.WriteLine("Press any button to continue");
                Console.ReadKey();
                this.menu();
            }
        }
    }
}
