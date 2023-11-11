using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_3
{
    public class DateService
    {
       
        ///////////////////////
        public DateTime now_date = DateTime.Now;
        //////////////////////
      
        public string GetDayOfWeek(string date)
        {
            string year = date;
            year = year.Remove(0, 6);
            int year_ = Convert.ToInt32(year);
            string month = date;
            month = month.Remove(0, 3);
            month = month.Remove(2, 5);
            int month_ = Convert.ToInt32(month);
            string day = date;
            day = day.Remove(2, 8);
            int day_ = Convert.ToInt32(day);
            DateOnly date_ = new DateOnly(year_, month_, day_);
            string day_of_week = (date_.DayOfWeek).ToString();
            return day_of_week;
        }

        public int GetDaysSpan(int day, int month, int year)
        {
            var date = new DateTime(year, month, day);
            var duration = now_date.Subtract(date);
            if (duration.Days <= 0)
            {
                return Math.Abs(duration.Days) + 1;
            }
            return duration.Days;
        }

        public string[] days = new string[7]
        {
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday",
            "Sunday"
        };
    }
}