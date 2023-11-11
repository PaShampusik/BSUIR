using System;
using System.Collections.Generic;
using System.ComponentModel.Design;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace Lab_3.Entities
{
    internal class Shop
    {
        Dictionary<string, Product> list_of_products = new Dictionary<string, Product>();
        List<Client> list_of_clients = new List<Client>();

        delegate void AccountHandler(string message);
        event AccountHandler Notify;

        public void Displaymessage(string message)
        {           
                Console.WriteLine(message);           
        }

        public Shop()
        {
            Notify += Displaymessage;
            list_of_clients.Add(new Client("Sasha"));
            list_of_clients.Add(new Client("Pasha"));
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

        public void show_all_products()
        {
            var ordered_products = from product in list_of_products
                                   orderby product.Value.Price
                                   select product.Value;
            foreach (var product in ordered_products)
            {
                Console.WriteLine("Name of item: " + product.Name + "    Product price: " + product.Price);
            }

        }

        public void show_all_clients()
        {
            foreach (var client in list_of_clients)
            {
                Console.WriteLine($"Name: {client.Name}");
            }
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
                    Notify?.Invoke($"Client {client.Name} bought product {product.Value.Name}");                   
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
        }

        public void add_client()
        {
            Console.WriteLine("Enter client name: ");
            string client_name = Console.ReadLine();
            if (list_of_clients.Any(x => x.Name == client_name))
            {
                Notify?.Invoke($"Client {client_name} already exists");
            }
            else
            {
                list_of_clients.Add(new Client(client_name));
                Notify?.Invoke($"Client {client_name} is added");
            }
        }

        public void add_product()
        {
            Console.Write("Enter product name: ");
            string? product_name = Console.ReadLine();
            Console.Write("Enter product price: ");
            int product_price = Convert.ToInt32(Console.ReadLine());
            if (list_of_products.ContainsKey(product_name))
            {
                Notify?.Invoke("Such product already exists");
            }
            else
            {
                list_of_products.Add(product_name, new Product(product_name, product_price));
                Notify?.Invoke($"Product {product_name} was added");
                
            }
        }

        public void get_full_sum_of_sold_products()
        {
            var sum = (from client in list_of_clients
                       from product in client.get_bought_products()
                       select product.Price).Sum();

            Notify?.Invoke($"Full sum of sold products: {sum}");
        }



        public void get_full_sum_of_sold_products_for_a_client()
        {
            Console.WriteLine("Enter name of a client: ");
            var name = Convert.ToString(Console.ReadLine());
            if (list_of_clients.Any(x => x.Name == name)) { 
                var sum = (from client in list_of_clients
                           from product in client.get_bought_products()
                           where client.Name == name
                           select product.Price).Sum();
                Notify?.Invoke($"Full sum of sold products for {name}: {sum}");
            }
            else{               
                Notify?.Invoke("Client not found");
            }
        }

        public void get_name_of_most_impactful_buyer()
        {
            var client = (from c in list_of_clients
                          orderby c.get_bought_products().Sum(x => x.Price) descending
                          select c).First();
            Notify?.Invoke("Name of most impactful buyer: " + client.Name);
        }

        public void get_number_of_buyers_with_sum_of_bought_products_more()
        {
            Console.WriteLine("Enter minimal sum: ");
            var sum = Convert.ToInt32(Console.ReadLine());
            
            var clients = list_of_clients.Aggregate(0, (number_of_clients, client) => number_of_clients + (client.Get_total_cost() > sum ? 1 : 0));
            Notify?.Invoke($"Number of buyers with sum of bought products more than {sum}: {clients}");            
        }

        public void get_sum_payed_for_each_product_in_shop_by_name()
        {
            Console.WriteLine("Enter name of a client: ");
            string? name = Convert.ToString(Console.ReadLine());

            var list_of_products = (from client in list_of_clients
                                    where client.Name == name
                                    select client.bought_products)
                                    .Single()
                                    .GroupBy(product => product.Name)
                                    .Select(group => (group.Key, group.Sum(product => product.Price)))
                                    .ToList();
            foreach (var product in list_of_products){
                Notify?.Invoke("Name of product: " + product.Key + "    Sum payed: " + product.Item2);
            }
        }
    }
}
