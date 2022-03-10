using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Task_1_Tests
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void enter999()
        {
            int a = 999;
            

            Task_1 d = new Task_1();
            string f = "Third and second numbers are equal.";

            Assert.AreEqual(d.Func(a), f);

        }
        [TestMethod]
        public void enter123()
        {
            int a = 123;


            Task_1 d = new Task_1();
            string f = "Third number is bigger than second.";

            Assert.AreEqual(d.Func(a), f);

        }

        [TestMethod]
        public void enter321()
        {
            int a = 321;


            Task_1 d = new Task_1();
            string f = "Second number is bigger than third.";

            Assert.AreEqual(d.Func(a), f);

        }
    }
}
 