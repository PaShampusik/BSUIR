using Domain.Entities;
using Microsoft.AspNetCore.Mvc;
using WEB_153503_Shchirov.Services.TelescopeService;
using WEB_153503_Shchirov.Services.TelescopeCategoryService;
using Microsoft.AspNetCore.Mvc.RazorPages;
using static System.Runtime.InteropServices.JavaScript.JSType;
using WEB_153503_Shchirov.Extensions;

namespace WEB_153503_Shchirov.Controllers
{
    public class ProductController : Controller
    {
        private readonly ITelescopeService _telescopeService;
        private readonly ITelescopeCategoryService _telescopeCategoryService;

        public ProductController(ITelescopeService clothesService, ITelescopeCategoryService clothesCategoryService)
        {
            _telescopeService = clothesService;
            _telescopeCategoryService = clothesCategoryService;
        }

		[Route("Telescopes")]
		[Route("Telescopes/{category?}")]
		public async Task<IActionResult> Index(string? category, string? currentCategory, int pageNo = 1)
        {
            ViewData["currentcategory"] = currentCategory;
            ViewData["page"] = pageNo;
            var productResponse = await _telescopeService.GetTelescopesListAsync(category, pageNo);
            if (!productResponse.Success)
            {
                return NotFound(productResponse.ErrorMessage);
            }

            var allCategories = await _telescopeCategoryService.GetCategoryListAsync();

            if (Request.IsAjaxRequest())
            {
                // Render the partial view for synchronous Ajax request
                return PartialView("_ProductCardsAndPagerPartial", new
                {
                    CurrentCategory = currentCategory,
                    Category = category,
                    ReturnUrl = "", // Provide the appropriate value for returnUrl
                    CurrentPage = productResponse.Data!.CurrentPage,
                    TotalPages = productResponse.Data!.TotalPages,
                    Telescopes = productResponse.Data!.Items,
                    InAdminArea = false
                });
            }

            return View((productResponse.Data!.Items, allCategories.Data,
                productResponse.Data.CurrentPage, productResponse.Data.TotalPages));
        }
    }
}

