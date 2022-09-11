using Microsoft.VisualStudio.TestTools.UnitTesting;
using Task_3;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_3.Tests
{
    [TestClass()]
    public class DateServiceTests
    {
        [TestMethod]
        public void TestGetDayOfWeek()
        {
            string[] dates = { "15.03.2022", "11.03.2022", "10.03.2022" };
            string[] expected = { "Tuesday", "Friday", "Thursday" };

            DateService date = new DateService();
            for (int i = 0; i < 3; i++)
            {
                Assert.AreEqual(date.GetDayOfWeek(dates[i]), expected[i]);
            }
        }

        [TestMethod]
        public void TestGetDaysSpan()
        {
            string[] dates = { "8.03.2022", "10.03.2022", "01.04.2022"};
            int[] expected = { 23, 21, 2};

            DateTime date1 = new DateTime(2022, 03, 31);
            DateService daySpan = new DateService();
            daySpan.now_date = date1;
            for (int i = 0; i < 3; i++)
            {
                string[] parametrs = dates[i].Split(new char[] { '.' }, StringSplitOptions.RemoveEmptyEntries);
                Assert.AreEqual(daySpan.GetDaysSpan(Convert.ToInt32(parametrs[0]), Convert.ToInt32(parametrs[1]), Convert.ToInt32(parametrs[2])), expected[i]);
            }
        }
    }
}