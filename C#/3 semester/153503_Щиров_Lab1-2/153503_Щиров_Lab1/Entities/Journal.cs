using _153503_Щиров_Lab1.Collections;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153503_Щиров_Lab1.Entities
{
    internal  class Journal
    {
        MyCustomCollection<string> notifications;
        public Journal()
        {
            notifications = new MyCustomCollection<string>();
        }

        public void Add(string message)
        {
            notifications.Add(message);
        }

        public void Show()
        {
            foreach (var item in notifications)
            {
                Console.WriteLine(item);
            }
        }
    }
}
