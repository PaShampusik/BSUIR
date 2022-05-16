using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_6
{
    public class Buffet 
    {
        List<Bulka> Bulki= new List<Bulka>();
        List<Sup> Soups = new List<Sup>();


        public void AddBulka()
        {
            Console.WriteLine("Введите название булки: ");
            string? name = Console.ReadLine();
            Console.WriteLine("Введите цену булки: ");
            double price = Convert.ToDouble(Console.ReadLine());
            Console.WriteLine("Введите массу булки: ");
            double mass = Convert.ToDouble(Console.ReadLine());
            Console.WriteLine("Свежая ли булка? Если да, то введите 0, иначе, другой вариант: ");
            string fresh = Console.ReadLine();
            bool f = true;
            if (fresh == "0")
            {
                f = true;
            }
            else
            {
                f = false;
            }
            Bulka bulka = new Bulka(name, price, mass, f);
            Bulki.Add(bulka);

            Console.WriteLine("Нажмите любую клавишу, чтобы прдолжить: ");
            Console.ReadLine();
            menu();
        }

        public void AddSup()
        {
            Console.WriteLine("Введите название супа: ");
            string? name = Console.ReadLine();
            Console.WriteLine("Введите цену супа: ");
            double price = Convert.ToDouble(Console.ReadLine());
            Console.WriteLine("Введите массу супа: ");
            double mass = Convert.ToDouble(Console.ReadLine());
            Console.WriteLine("Горячий ли суп? Если да, то введите 0, иначе, другой вариант:");
            string? hot = Console.ReadLine();
            
            bool h = true;
            if (hot == "0")
            {
                h = true;
            }
            else
            {
                h = false;
            }
            Sup sup = new Sup(name, price, mass, h);
            Soups.Add(sup);

            Console.WriteLine("Нажмите любую клавишу, чтобы прдолжить: ");
            Console.ReadLine();
            menu();
        }
        
        public int GetCountBulki()
        {
            return Bulki.Count;
        }
        public int GetCountSoups()
        {
            return Soups.Count;
        }

        public void PrintAll()
        {
            
            Console.WriteLine("Все булки: ");
            Console.WriteLine("Название    Цена    Масса    Свежая    Масса/Цена");
            foreach (var bulka in Bulki)
            {
                Console.WriteLine(bulka.Name + "        " + bulka.Price + "       " + bulka.Weight + "       " + bulka.Fresh + "        " + ((float)bulka.WeightToPrice()));
            }
            Console.WriteLine("Все супы: ");
            Console.WriteLine("Название       Цена       Масса       Свежая       Масса/Цена");

            foreach (var sup in Soups)
            {
                Console.WriteLine(sup.Name + "      " + sup.Price + "       " + sup.Weight + "       " + sup.Hot + "       " + ((float)sup.WeightToPrice()));
            }
            
            Console.WriteLine("Нажмите любую клавишу, чтобы прдолжить: ");
            Console.ReadLine();
            menu();
        }

        public void DeleteBulka()
        {
            Console.WriteLine("Введите название булки, которую хотите удалить: ");
            string? name = Console.ReadLine();
            if (name == null)
            {
                return;
            }
            else
            {
                Bulka? bulka = Bulki.Find(x => x.Name == name);
                if (bulka != null)
                {
                    Bulki.Remove(bulka);
                }
                else
                {
                    Console.WriteLine("Такой булки нет");
                }
            }
            Console.WriteLine("Нажмите любую клавишу, чтобы прдолжить: ");
            Console.ReadLine();
            menu();
        }
        public void DeleteSup()
        {
            Console.WriteLine("Введите название супа: ");
            string? name = Console.ReadLine();
            if (name == null)
            {
                return;
            }
            else
            {
                Sup? sup = Soups.Find(x => x.Name == name);
                if (sup != null)
                {
                    Soups.Remove(sup);
                }
                else
                {
                    Console.WriteLine("Такого супа нет");
                }
            }
            Console.WriteLine("Нажмите любую клавишу, чтобы прдолжить: ");
            Console.ReadLine();
            menu();            
        }

        public void menu()
        {
            Console.WriteLine("Выберите действие: ");
            Console.WriteLine("1.Покаазать все булки и супы");
            Console.WriteLine("2. Добавить булку");
            Console.WriteLine("3. Добавить суп");
            Console.WriteLine("4. Удалить булку по названию");
            Console.WriteLine("5. Удалить суп по названию");           
            Console.WriteLine("6. Выход");
            int ind = Convert.ToInt32(Console.ReadLine());

            if (ind == 1)
            {
                PrintAll();
            }
            if (ind == 2)
            {
                AddBulka();
            }
            if (ind == 3)
            {
                AddSup();
            }
            if (ind == 4)
            {
                DeleteBulka();
            }
            if (ind == 5)
            {
                DeleteSup();
            }
            if(ind == 6)
            {
                return;
            }
            Console.WriteLine("Вы не попали по клавишам, попробуйте еще раз: ");
            menu();
        }
        public void SetBulkaPrice(string name, double price)
        {
            Bulka? bulka = Bulki.Find(x => x.Name == name);
            bulka.Price = price;
        }

        public double GetBulkaPrice(string name)
        {
            Bulka? bulka = Bulki.Find(x => x.Name == name);
            return bulka.Price;
        }

        public void SetSupPrice(string name, double price)
        {
            Sup? sup = Soups.Find(x => x.Name == name);
            sup.Price = price;
        }

        public double GetSupPrice(string name)
        {
            Sup? sup = Soups.Find(x => x.Name == name);
            return sup.Price;
        }

        public void AddBulkaForTests(string name)
        {
            Bulki.Add(new Bulka(name));
        }
    }
}
