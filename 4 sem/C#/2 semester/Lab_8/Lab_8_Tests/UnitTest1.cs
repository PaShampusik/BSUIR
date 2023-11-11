using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Lab_8
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()
        {
            RailwayStation oof = new RailwayStation();
            for (int i = 0; i < 5000; i++)
            {
                oof.AddTarifWithNoDiscForTests(i, i.ToString());
            }
            for (int i = 0; i < 5000; i++)
            {
                Assert.AreEqual(oof.getTarif(i.ToString()), i);
            }
            
        }
    }
}