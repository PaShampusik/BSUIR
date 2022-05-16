using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Lab_7
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()
        {
            Rational[] list = new Rational[5000];
            for (int i = 1; i < 5000; i++)
            {
                list[i] = new Rational(1, i);
            }
            for (int i = 1; i < 5000; i++)
            {
                Assert.AreEqual(list[i].Denominator, i);
            }
        }
    }
}