using Microsoft.VisualStudio.TestTools.UnitTesting;
using Lab_4;

namespace TestProject1
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()
        {
            int[] arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            long[] expected = { 1 * 223, 2 * 223, 3 * 223, 4 * 223, 5 * 223, 6 * 223, 7 * 223, 8 * 223, 9 * 223, 10 * 223 };
            railway_station station = railway_station.getInstance("Москва", 1000, 777, 30);
            for (int i = 0; i < 10; i++)
            {
                station.EditPrice = arr[i];
                Assert.AreEqual(station.calculate(), expected[i]);
            }
        }
    }
}
