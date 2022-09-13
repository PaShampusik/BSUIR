using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _153503_Щиров_Lab1.Collections;

namespace _153503_Щиров_Lab1.Entities
{
    internal class shop 
    {
        public static MyCustomCollection<string> orders = new MyCustomCollection<string>();
        
        
        
        public void menu()
        {
            Console.WriteLine("Намжмите 1, чтобы получить даннные о заказах по фамилии");
            Console.WriteLine("Намжмите 2, чтобы получить даннные о сумме заказов покупателя по фамилии");
            Console.WriteLine("Намжмите 3, чтобы зарегистрировать новый заказ");
            Console.WriteLine("Намжмите 4, чтобы завершить программу");


            int a = Convert.ToInt32(Console.ReadLine());

            if (a == 1)
            {
                info_by_name();
            }
            else if(a == 2)
            {
                sum_by_name();
                
            }else if(a == 3)
            {
                new_order();
            }else if(a == 4)
            {
                Environment.Exit(0);
            }
            else
            {
                Console.WriteLine("Неверный ввод, порпробуйте еще раз");
                menu();
            }
        }

        public void info_by_name()
        {
            Console.WriteLine("Введите фамилию покупателя: ");
            string? name = Console.ReadLine();
            int Cursor = 0;
            int sum = 0;

            for (int i = 0; i < orders.Count; i++)
            {
                if (orders[i].Contains(name))
                {

                    Console.WriteLine("Наименование товара: " + orders[i + 1] + "        Цена: " + orders[i + 2]);
                    

                }
            }
            Console.WriteLine("------------------------------------------------------------------------------------------");
            menu();
        }
        
        public void sum_by_name()
        {
            Console.WriteLine("Введите фамилию покупателя: ");
            string? name = Console.ReadLine();
            int sum = 0;
            for (int i = 0; i < orders.Count; i++)
            {
                if (orders[i].Contains(name))
                {

                    sum += Convert.ToInt32(orders[i + 2]);


                }
            }
            Console.WriteLine("Покупатель совершил заказов на сумму: " + sum);
            System.Threading.Thread.Sleep(500);
            Console.WriteLine("------------------------------------------------------------------------------------------");

            menu();
        }

        public void new_order()
        {
            Console.WriteLine("Введите фамилию покупателя: ");
            string? name = Console.ReadLine();
            Console.WriteLine("Введите наименование товара: ");
            string? item = Console.ReadLine();
            Random rnd = new Random();
            int price = rnd.Next(10, 1000);
            System.Threading.Thread.Sleep(500);

            orders.Add(name);
            orders.Add(item);
            orders.Add(price.ToString());
            Console.WriteLine(name + ", ваш заказ на сумму " + price + " успешно обработан!");
            Console.WriteLine("------------------------------------------------------------------------------------------");

            System.Threading.Thread.Sleep(500);
            menu();
        }
    }
}
