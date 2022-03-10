using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Task_2_Tests
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void enter10_10()
        {
            int a = -10, b = -10, c = -23;



            Task d = new Task();
            string f = "Point is laying on the Border.";

            Assert.AreEqual(d.Func(a, b, c), f);
        }

        [TestMethod]
        public void enter12_10()
        {
            int a = -12, b = -10, c = -23;



            Task d = new Task();
            string f = "Yes.";

            Assert.AreEqual(d.Func(a, b, c), f);
        }

        [TestMethod]
        public void enter12_20()
        {
            int a = -12, b = -20, c = -23;



            Task d = new Task();
            string f = "No.";

            Assert.AreEqual(d.Func(a, b, c), f);
        }
    }
}