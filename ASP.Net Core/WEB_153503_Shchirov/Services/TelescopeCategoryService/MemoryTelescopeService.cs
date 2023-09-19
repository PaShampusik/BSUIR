using Domain.Entities;
using Domain.Models;

namespace WEB_153503_Shchirov.Services.TelescopeCategoryService
{
    public class MemoryTelescopeCategoryService : ITelescopeCategoryService
    {
        public Task<ResponseData<List<Category>>>
        GetCategoryListAsync()
        {
            var categories = new List<Category>
                {
                new Category {Id=1, Name="Рефракционные", NormalizedName = "Refraction" },
                new Category {Id=2, Name="Отражающие", NormalizedName = "Reflection" }
                };
            var result = new ResponseData<List<Category>>();
            result.Data = categories;
            return Task.FromResult(result);
        }
    }
}
