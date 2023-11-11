using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_4
{
    public class railway_station
    {
        private string name;
        private int number_of_passangers;
        private int number_sold_tickets;
        ticket ticket_ = new ticket();
        private const int number_of_tickets = 1000;


        private static railway_station instance;

        private railway_station(string name, int number_of_passangers, int number_of_sold_tickets, int cost)
        {
            this.name = name;
            this.number_of_passangers = number_of_passangers;
            this.number_sold_tickets = number_of_sold_tickets;
            this.ticket_.Cost = cost;
        }

        public static railway_station getInstance(string name, int number_of_passangers, int number_of_sold_tickets, int cost)
        {
            if (instance == null)
                instance = new railway_station(name, number_of_passangers, number_of_sold_tickets, cost);
            return instance;
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public int Number_of_passangers
        {
            get { return number_of_passangers; }
            set { number_of_passangers = value; }
        }

        public int Number_sold_tickets
        {
            get { return number_sold_tickets; }
            set { number_sold_tickets = value; }
        }

        public int EditPrice
        {
            get
            {
                return ticket_.Cost;
            }
            set
            {
                ticket_.cost = value;
            }
        }

        public long calculate()
        {
            return ticket_.Cost * (number_of_tickets - number_sold_tickets);
        }
    }

    public class ticket
    {
        public int cost;

        public int Cost
        {
            get { return cost; }
            set { cost = value; }
        }
    }
}
