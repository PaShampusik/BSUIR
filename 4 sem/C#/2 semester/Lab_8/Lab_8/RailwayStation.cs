using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_8
{
    public class RailwayStation
    {
        private static List<Tarif> list = new List<Tarif>();

        public void AddTarifWithDiscFortests(int price, int disc, string wheretogo)
        {
            list.Add(new Tarif(new DiscPrice(price, disc).GetPrice(), wheretogo));
            
        }

        public void AddTarifWithDisc()
        {
            Console.WriteLine("Введите цену билета");
            int price = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Введите скидку");
            int disc = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Введите место назначения");
            string wheretogo = Console.ReadLine();
            list.Add(new Tarif(new DiscPrice(price, disc).GetPrice(), wheretogo));
            menu();

        }
        
        public int getTarif(string name)
        {
            foreach (Tarif t in list)
            {
                if (t.Wherewego == name)
                {
                    return t.Price;
                }
            }
            return 2;
        }
        public void AddTarifWithNoDiscForTests(int price, string wheretogo)
        {
            list.Add(new Tarif(price, wheretogo));
        }

        public void AddTarifWithNoDisc()
        {
            Console.WriteLine("Введите цену билета");
            int price = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("Введите место назначения");
            string wheretogo = Console.ReadLine();
            list.Add(new Tarif(price, wheretogo));
            menu();
        }

        /*public void AddDiscToTarif(string name, int disc)
        {
            foreach(var tar in list)
            {
                if(tar.Wherewego == name)
                {
                    tar = new Tarif(new DiscPrice(price, disc).GetPrice(), name);
                }
            }
        }*/

        public static Tuple<int, string> FindMinPrice(RailwayStation oof)
        {
            int min = 10000000;
            string name = " ";
           foreach(var tar in list)
            {
                if (tar.Price < min)
                {
                    min = tar.Price;
                    name = tar.Wherewego;
                }
            }
           foreach(var tar in list){
                if (tar.Price == min && tar.Wherewego == name)
                {
                    Console.WriteLine("Минимальная цена поездки в городе {0} составляет {1} рублей", tar.Wherewego, tar.Price);
                    oof.menu();
                    return new Tuple<int, string>(min, name);
                }
            }
            return new Tuple<int, string>(0, " ");
            
        }

        public void PrintAllTarifes()
        {
            Console.WriteLine("Все тарифы:");
            foreach (var tar in list)
            {
                Console.WriteLine(tar.Price + " " + tar.Wherewego);
            }
            menu();
        }

        public void menu()
        {
            Console.WriteLine("1. Add Tarif with discount");
            Console.WriteLine("2. Add Tarif without discount");
            Console.WriteLine("3. Find min price");
            Console.WriteLine("4. Show all tarifs");
            Console.WriteLine("5. Exit");

            int a = Convert.ToInt32(Console.ReadLine());

            if (a == 1)
            {
                AddTarifWithDisc();
                menu();
            }
            else if (a == 2)
            {
                AddTarifWithNoDisc();
                menu();
            }
            else if (a == 3)
            {
                FindMinPrice(this);
                menu();
            }
            else if (a == 4)
            {
                PrintAllTarifes();
                menu();
            }
            else if (a == 5)
            {
                Console.WriteLine("Выход");
            }
            else
            {
                Console.WriteLine("Неверный ввод");
                menu();
            }

        }
    }
}
