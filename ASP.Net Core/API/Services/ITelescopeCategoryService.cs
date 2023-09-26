using Domain.Entities;
using Domain.Models;

namespace API.Services
{
    public interface ITelescopeCategoryService
    {

        /// <summary>
        /// Получение списка всех категорий
        /// </summary>
        /// <returns></returns>
        public Task<ResponseData<List<Category>>> GetTelescopesCategoryListAsync();
    }
}
