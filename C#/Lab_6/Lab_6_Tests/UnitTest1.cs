using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Lab_6
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()
        {
            Buffet buf = new Buffet();

            for (int i = 0; i < 100; i++)
            {
                buf.AddBulkaForTests(i.ToString());
                buf.SetBulkaPrice(i.ToString(), i);
                double price = buf.GetBulkaPrice(i.ToString());
                Assert.AreEqual(price, i);
            }
        }
    }
}