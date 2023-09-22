using Domain.Entities;
using Domain.Models;

namespace API.Services.TelescopeCategoryService
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
