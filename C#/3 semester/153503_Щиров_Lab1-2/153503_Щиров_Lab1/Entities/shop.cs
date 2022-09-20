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
        public static Journal notifications = new Journal();

        event AccountHandler Notify;
        public shop()
        {
            
            Notify += DisplayGreenMessage;
        }
        delegate void AccountHandler(string message);
        void DisplayGreenMessage(string message) => Console.WriteLine(message);
        /*{
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine(message);
            Console.ResetColor();
        }*/

        public void border()
        {
            System.Threading.Thread.Sleep(500);
            Console.WriteLine("------------------------------------------------------------------------------------------");
        }
        public void menu()
        {
            Console.WriteLine("Намжмите 1, чтобы получить даннные о заказах по фамилии");
            Console.WriteLine("Намжмите 2, чтобы получить даннные о сумме заказов покупателя по фамилии");
            Console.WriteLine("Намжмите 3, чтобы зарегистрировать новый заказ");
            Console.WriteLine("Намжмите 4, чтобы вывести все заказы на экран");
            Console.WriteLine("Намжмите 5, чтобы удалить заказ по имени товара");
            Console.WriteLine("Намжмите 6, чтобы просмотреть журнал уведомлений");
            Console.WriteLine("Намжмите 7, чтобы завершить программу");


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
                list_all_orders();
            }
            else if (a == 5)
            {
                delete_by_name_and_price();
            }
            else if (a == 6)
            {
                show_journal();
            }
            else if (a == 7)
            {
                Environment.Exit(0);
            }
            else
            {
                Console.WriteLine("Неверный ввод, порпробуйте еще раз");
                menu();
            }
        }

        public void show_journal()
        {
            notifications.Show();
            border();
            menu();
        }
        
        public void delete_by_name_and_price()
        {
            Console.WriteLine("Введите имя Заказчика: ");
            string? name = Console.ReadLine();
            Console.WriteLine("Введите имя товара: ");
            string? order_name = Console.ReadLine();
            Console.WriteLine("Введите сумму заказа: ");
            string? price = Console.ReadLine();



            System.Threading.Thread.Sleep(500);
            if (orders.is_exist(name) && orders.is_exist(order_name) && orders.is_exist(price))
            {
                orders.Remove(name);
                orders.Remove(order_name);
                orders.Remove(price);
                Notify("Заказ успешно удален!");
                notifications.Add("Заказ успешно удален!");
            }
            else
            {
                Console.WriteLine("Такого заказа не существует!");
            }
            border();
            menu();
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
            border();
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
            border();

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
            Notify(name + ", ваш заказ на сумму " + price + " успешно обработан!");
            notifications.Add(name + ", ваш заказ на сумму " + price + " успешно обработан!");
            //Console.WriteLine(name + ", ваш заказ на сумму " + price + " успешно обработан!");
            border();
            menu();
        }
        
        public void list_all_orders()
        {
            Console.WriteLine("Список всех заказов:");
            
            Console.WriteLine("------------------------------------------------------------------------------------------");
            int count = 0;
            foreach (var item in orders)
            {

                Console.WriteLine(item);
                count++;
                if (count % 3 == 0)
                {
                    Console.WriteLine("------------------------------------------------------------------------------------------");
                }
            }
            border();
            menu();
        }
    }
}
