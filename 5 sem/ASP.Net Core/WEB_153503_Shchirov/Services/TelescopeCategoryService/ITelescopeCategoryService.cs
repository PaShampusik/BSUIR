using Domain.Entities;
using Domain.Models;

namespace WEB_153503_Shchirov.Services.TelescopeCategoryService
{
    public interface ITelescopeCategoryService
    {
        /// <summary>
        /// Получение списка всех категорий
        /// </summary>
        /// <returns></returns>
        public Task<ResponseData<List<Category>>> GetCategoryListAsync();
    }
}
