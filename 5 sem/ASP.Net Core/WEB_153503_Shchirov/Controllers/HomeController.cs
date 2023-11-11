using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using WEB_153503_Shchirov.Models;

namespace WEB_153503_Shchirov.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            

            ViewData["Title"] = "Лабораторная работа №2";

            var demoList = new List<ListDemo>
        {
            new ListDemo { Id = 1, Name = "Item 1" },
            new ListDemo { Id = 2, Name = "Item 2" },
            new ListDemo { Id = 3, Name = "Item 3" }
        };

            ViewData["DemoList"] = demoList;

            return View();
        }
    }
}
