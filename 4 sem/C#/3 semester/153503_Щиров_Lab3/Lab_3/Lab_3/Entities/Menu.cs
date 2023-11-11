using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_3.Entities
{
    internal class Menu : Shop
    {
        private Shop shop;


        public Menu()
        {
            var shop = new Shop();
        }
        public void menu()
        {

            Console.WriteLine("1. Add product");
            Console.WriteLine("2. Add client");
            Console.WriteLine("3. Buy product");
            Console.WriteLine("4. Show all products");
            Console.WriteLine("5. Show all clients");
            Console.WriteLine("6. Get full sum of sold products");
            Console.WriteLine("7. Show all products bought by client");
            Console.WriteLine("8. Get the most impactful client");
            Console.WriteLine("9. Count of clients with bought products for sum more than");
            Console.WriteLine("10. Show all products bought by client");
            Console.WriteLine("11. Exit");

            Console.Write("Enter your choice: ");
            int choice = Convert.ToInt32(Console.ReadLine());
            if (choice == 1)
            {
                add_product();
                border();
                menu();
            }
            else if (choice == 2)
            {
                add_client();
                border();
                menu();
            }
            else if (choice == 3)
            {
                buy_product();
                border();
                menu();
            }
            else if (choice == 4)
            {
                show_all_products();
                border();
                menu();
            }
            else if (choice == 5)
            {
                show_all_clients();
                border();
                menu();
            }
            else if (choice == 6)
            {

                get_full_sum_of_sold_products();
                border();
                menu();
            }
            else if (choice == 7)
            {
                get_full_sum_of_sold_products_for_a_client();
                border();
                menu();
            }
            else if (choice == 8)
            {
                get_name_of_most_impactful_buyer();
                border();
                menu();
            }
            else if (choice == 9)
            {
                get_number_of_buyers_with_sum_of_bought_products_more();
                border();
                menu();
            }
            else if (choice == 10)
            {
                get_sum_payed_for_each_product_in_shop_by_name();
                border();
                menu();
            }
            else if (choice == 11)
            {
                Environment.Exit(0);
            }
            else
            {
                Console.WriteLine("Wrong choice");
                border();
                menu();
            }
        }

        public void border()
        {
            Console.WriteLine("---------------------------------------------------------------");
            System.Threading.Thread.Sleep(300);
        }
    }
}
