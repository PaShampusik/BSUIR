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
        [TestMethod]
        public void TestMethod2()
        {
            Rational rational = new Rational(1, 10000);
            Rational rational2 = new Rational(1, 1);
            Rational[] list = new Rational[5000];
            Rational rrational3 = new Rational(1, 2);

            Assert.IsTrue(rational != rational2);
        }
        [TestMethod]
        public void TestMethod3()
        {
         
            Rational rational2 = new Rational(1, 1);
           
            Rational rational3 = new Rational(1, 2);

            Assert.IsTrue(rational2 > rational3);
            
        }
        [TestMethod]
        public void TestMethod4()
        {
            Rational rational = new Rational(1, 10000);
            Rational rational2 = new Rational(1, 1);

            Assert.IsTrue(rational < rational2);
        }
    }
}