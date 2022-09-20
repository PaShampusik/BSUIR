using System;
using System.Collections.Generic;
using System.ComponentModel.Design;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_3.Entities
{
    internal class Shop
    {
        Dictionary<string, Product> list_of_products = new Dictionary<string, Product>();
        List<Client> list_of_clients = new List<Client>();
        
        public Shop()
        {
            list_of_clients.Add(new Client("Sasha"));
            list_of_clients.Add(new Client("Pasha"));
            list_of_clients.Add(new Client("Sasha"));
            list_of_clients.Add(new Client("Vadzim"));
            list_of_clients.Add(new Client("Sergey"));
            list_of_clients.Add(new Client("Kirill"));
            list_of_clients.Add(new Client("Oleg"));
            list_of_clients.Add(new Client("Timofei"));
            //////////////////////////////////////////////
            list_of_products.Add("Bread", new Product("Bread", 1));
            list_of_products.Add("TV", new Product("TV", 200));
            list_of_products.Add("Pencil", new Product("Pencil", 5));
            list_of_products.Add("Potato", new Product("Potato", 3));
            list_of_products.Add("Sofa", new Product("Sofa", 100));
            list_of_products.Add("Milk", new Product("Milk", 4));
            list_of_products.Add("Cheese", new Product("Cheese", 9));
            list_of_products.Add("Cola", new Product("Cola", 4));
            list_of_products.Add("Cucumber", new Product("Cucumber", 3));
            list_of_products.Add("Eggs", new Product("Eggs", 2));
        }
        public void border()
        {
            Console.WriteLine("---------------------------------------------------------------");
            System.Threading.Thread.Sleep(300);
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
            Console.WriteLine("9. Show all products bought by client");
            Console.WriteLine("10. Show all products bought by client");
            Console.WriteLine("11. Exit");

            Console.Write("Enter your choice: ");
            int choice = Convert.ToInt32(Console.ReadLine());
            if (choice == 1)
            {
                add_product();
            }
            else if (choice == 2)
            {
                add_client();
            }
            else if (choice == 3)
            {
                buy_product();
            }
            else if (choice == 4)
            {
                show_all_products();
            }
            else if (choice == 5)
            {
                show_all_clients();
            }
            else if (choice == 6)
            {

                get_full_sum_of_sold_products();
            }
            else if (choice == 7)
            {
                get_full_sum_of_sold_products_for_a_client();
            }
            else if (choice == 8)
            {
                get_name_of_most_impactful_buyer();
            }
            else if (choice == 9)
            {
                get_number_of_buyers_with_sum_of_bought_products_more();
            }
            else if (choice == 10)
            {
                get_sum_payed_for_each_product_in_shop_by_name();
            }
            else if (choice == 11)
            {
                Environment.Exit(0);
            }
            else
            {
                Console.WriteLine("Wrong choice");
            }
        }
        public void show_all_products()
        {
            var ordered_products = list_of_products.OrderBy(x => x.Value.Price);
            foreach (var product in ordered_products)
            {
                Console.WriteLine($"Name: {product.Value.Name}, Price: {product.Value.Price}");
            }
            border();
            menu();
        }

        public void show_all_clients()
        {
            foreach (var client in list_of_clients)
            {
                Console.WriteLine($"Name: {client.Name}");
            }
            border();
            menu();
        }

        public void buy_product()
        {            
                Console.Write("Enter client name: ");
                string client_name = Console.ReadLine();
                Console.Write("Enter product name: ");
                string product_name = Console.ReadLine();
                if (list_of_products.ContainsKey(product_name))
                {
                    if (list_of_clients.Any(x => x.Name == client_name))
                    {
                        var client = list_of_clients.First(x => x.Name == client_name);
                        var product = list_of_products.First(x => x.Key == product_name);
                        client.get_bought_products().Add(product.Value);
                        Console.WriteLine($"Product {product_name} was bought by {client_name}");
                    }
                    else
                    {
                        Console.WriteLine("Client not found");
                    }
                }
                else
                {
                    Console.WriteLine("Product not found");
                }
                border();
                menu();           
        }

        public void add_client()
        {
            Console.WriteLine("Enter client name: ");
            string client_name = Console.ReadLine();
            if (list_of_clients.Any(x => x.Name == client_name))
            {
                Console.WriteLine("Client already exists");
            }
            else
            {
                list_of_clients.Add(new Client(client_name) );
                Console.WriteLine($"Client {client_name} was added");
            }
            menu();
        }

        public void add_product()
        {
            Console.Write("Enter product name: ");
            string product_name = Console.ReadLine();
            Console.Write("Enter product price: ");
            int product_price = Convert.ToInt32(Console.ReadLine());
            if (list_of_products.ContainsKey(product_name))
            {
                Console.WriteLine("Product already exists");
            }
            else
            {
                list_of_products.Add(product_name, new Product(product_name, product_price));
                Console.WriteLine($"Product {product_name} was added");
            }
            menu();
        }

        public void get_full_sum_of_sold_products()
        {
            int? sum = 0;
            foreach (var person in list_of_clients)
            {
                foreach (var product in person.get_bought_products())
                {
                    sum += product.Price;
                }
            }
            Console.WriteLine($"Full sum of sold products: {sum}");
            border();
            menu();
        }



        public void get_full_sum_of_sold_products_for_a_client()
        {
            Console.WriteLine("Enter name of a client: ");
            string? name = Convert.ToString(Console.ReadLine());
            
                int? sum = 0;
                foreach (var person in list_of_clients)
                {
                    if (person.Name == name)
                    {
                        foreach (var product in person.get_bought_products())
                        {
                            sum += product.Price;
                        }
                    }
                }
                Console.WriteLine($"Full sum of sold products for {name}: {sum}");
                border();
            menu();
        }

        public void get_name_of_most_impactful_buyer()
        {
            int? max = 0;
            string? max_name = "";
            int? sum = 0;
            foreach (var person in list_of_clients)
            {
                foreach (var product in person.get_bought_products())
                {
                    sum += product.Price;
                }
                if (sum > max)
                {
                    max = sum;
                    max_name = person.Name;
                }
                else
                {
                    sum = 0;
                }
            }
            Console.WriteLine("The most impactful buyer is " + max_name);
            border();
            menu();
        }

        public void get_number_of_buyers_with_sum_of_bought_products_more()
        {
            Console.WriteLine("Enter minimal sum: ");
            int? sum = Convert.ToInt32(Console.ReadLine());
            int? sum_of_bought_products = 0;
            int? number_of_buyers = 0;
            foreach (var person in list_of_clients)
            {
                foreach (var product in person.get_bought_products())
                {
                    sum_of_bought_products += product.Price;
                }
                if (sum_of_bought_products > sum)
                {
                    number_of_buyers++;
                }
                sum_of_bought_products = 0;
            }
            Console.WriteLine($"Number of buyers with sum of bought products more than {sum}: {number_of_buyers}");
            border();
            menu();
        }
        
        public void get_sum_payed_for_each_product_in_shop_by_name()            
        {
            Console.WriteLine("Enter name of a client: ");
            string? name = Convert.ToString(Console.ReadLine());
            
                int? sum = 0;
                foreach (var person in list_of_clients)
                {
                    if (person.Name == name)
                    {
                        foreach (var product in list_of_products)
                        {
                            foreach (var item in person.get_bought_products())
                            {
                                if(item.Name == product.Value.Name)
                                {
                                    
                                    sum += product.Value.Price;
                                    
                                }
                            }
                            Console.WriteLine("Sum payed for " + product.Value.Name + " by " + name + " is " + sum);
                        }
                    }
                }                
                border();
            menu();
        }

        




    }
    
    
}
