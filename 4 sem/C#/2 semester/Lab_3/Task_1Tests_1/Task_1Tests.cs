using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static Task_1;

namespace Tests
{
    [TestClass()]
    public class Task_1Tests
    {
        [TestMethod()]
        public void FuncTest()
        {
            int [] arr1 = { 12, 11, 11, -11, 0 };
            int [] arr2 = { 3, 5, -5, 5, 0 };
            int [] arr3 = { -72, -66, -56, -6, 0 };
            for (int i = 0; i < 5; i++)
            {
                Assert.AreEqual(Task_1.Func(arr1[i], arr2[i]), arr3[i]);
            }
        }

        [TestMethod()]
        public void maxTest()
        {
            int[] arr1 = { 12, 11, 11, -11, 0 };
            int[] arr2 = { 12, 5, -5, 5, 0 };
            int[] arr3 = { 12, 11, 11, 5, 0 };
            for (int i = 0; i < 5; i++)
            {
                Assert.AreEqual(Task_1.max(arr1[i], arr2[i]), arr3[i]);
            }
        }
    }
}