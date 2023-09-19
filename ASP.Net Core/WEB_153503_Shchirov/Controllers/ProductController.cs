using Domain.Entities;
using Microsoft.AspNetCore.Mvc;
using WEB_153503_Shchirov.Services.TelescopeService;
using WEB_153503_Shchirov.Services.TelescopeCategoryService;



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


        public async Task<IActionResult> Index(string? category, string? currentCategory, int pageNo = 1)
        {
            ViewData["currentcategory"] = currentCategory;
            var productResponse = await _telescopeService.GetTelescopeListAsync(category, pageNo);
            if (!productResponse.Success)
            {
                return NotFound(productResponse.ErrorMessage);
            }
            var allCategories = await _telescopeCategoryService.GetCategoryListAsync();
            return View((productResponse.Data!.Items, allCategories.Data,
                productResponse.Data.CurrentPage, productResponse.Data.TotalPages));
        }
    }
}
