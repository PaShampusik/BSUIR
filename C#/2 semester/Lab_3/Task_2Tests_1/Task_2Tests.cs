using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using static Task_2;
namespace Tests
{
    [TestClass()]
    public class Task_2Tests
    {
        [TestMethod()]
        public void FuncTest()
        {
            double[] arr1 = { -2, 0, 2 };
            double[] arr2 = {1.59, -0.69, 8.17};
            double e = 0.02;
            for (int i = 0; i < 3; i++)
            {
                Assert.IsTrue(Math.Abs(Task_2.Func(arr1[i]) - arr2[i]) < e);
            }
            
        }
    }
}