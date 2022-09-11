using Microsoft.VisualStudio.TestTools.UnitTesting;
using Lab_5;
using System;
using System.Collections.Generic;

namespace Lab_5
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()
        {
            Railwaystation station = new Railwaystation();
            foreach (var item in station.clients)
            {
                Assert.AreEqual(station.CalculateSumOfBoughtTicketsForClient(item.Name, item.Number), 0);
            }

        }
    }
}