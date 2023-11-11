using Domain.Entities;
using Domain.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using System.Diagnostics.Metrics;
using WEB_153503_Shchirov.Services.TelescopeCategoryService;

namespace WEB_153503_Shchirov.Services.TelescopeService
{
    public class MemoryTelescopeService : ITelescopeService
    {
        List<Telescope>? _telescopes;
        List<Category>? _categories;
        private readonly IConfiguration _configuration;

		public MemoryTelescopeService(ITelescopeCategoryService clothesCategoryService,
	   [FromServices] IConfiguration configuration)
		{
			_categories = clothesCategoryService.GetCategoryListAsync()?.Result?.Data;
			SetupData();
			_configuration = configuration;
		}

		private void SetupData()
        {
            _telescopes = new List<Telescope>
            {
            new Telescope {Id = 1, Name="Celestron PowerSeeker 70EQ",
            Description="Рефракционный телескоп",
            FocusLength =900 , Img="Images/Celestron PowerSeeker 70EQ.jpg",
            Price = 1100,
            Category= _categories.Find(c=>c.NormalizedName.Equals("Refraction"))},

            new Telescope { Id = 2, Name="Meade Instruments Infinity 80mm",
            Description="Рефракционный телескоп",
            FocusLength =400, Img ="Images/Meade Instruments Infinity 80mm AZ.jpg",
            Price = 800,
            Category=
            _categories.Find(c=>c.NormalizedName.Equals("Refraction"))},

            new Telescope {Id = 3, Name="Sky-Watcher ProED 80mm",
            Description="Рефракционный телескоп",
            Price = 1000,
            FocusLength = 600 , Img="Images/Sky-Watcher ProED 80mm Doublet APO Refractor.jpg",
            Category= _categories.Find(c=>c.NormalizedName.Equals("Refraction"))},

            new Telescope { Id = 4, Name="Orion EON 115mm ED",
            Description="Рефракционный телескоп",
            FocusLength = 805, Img ="Images/Orion EON 115mm ED Triplet Apochromatic Refractor.jpg",
            Price = 1500,
            Category=
            _categories.Find(c=>c.NormalizedName.Equals("Refraction"))},

            new Telescope
            {
                Id = 5,
                Name = "Meade Instruments Infinity 80mm AZ",
                Description = "Отражательный телескоп",
                FocusLength = 1200,
                Img = "Images/Meade Instruments Infinity 80mm AZ.jpg",
                Price = 2000,
                Category =
            _categories.Find(c => c.NormalizedName.Equals("Reflection")) },

            new Telescope { Id = 6, Name="Orion SkyQuest XT8",
                Description="Отражательный телескоп",
                FocusLength = 2032, Img ="Images/Orion SkyQuest XT8 Classic Dobsonian.jpg",
                Price = 1300,
                Category =
                _categories.Find(c=>c.NormalizedName.Equals("Reflection"))},
            new Telescope
            {
                Id = 7,
                Name = "Celestron AstroMaster 130EQ",
                Description = "Отражательный телескоп",
                FocusLength = 650,
                Img = "Images/Celestron AstroMaster 130EQ.jpg",
                Price = 2300,
                Category =
            _categories.Find(c => c.NormalizedName.Equals("Reflection")) },
            new Telescope
            {
                Id = 8,
                Name = "Meade Instruments LX90-ACF",
                Description = "Отражательный телескоп",
                FocusLength = 2000,
                Img = "Images/Meade Instruments LX90-ACF.jpg",
                Price = 2500,
                Category =
            _categories.Find(c => c.NormalizedName.Equals("Reflection")) }
            };           
        }

        public Task<ResponseData<ListModel<Telescope>>> GetTelescopesListAsync(string? categoryNormalizedName, int pageNo = 1)
        {
			var itemsPerPage = _configuration.GetValue<int>("ItemsPerPage");
			var itemsTemp = _telescopes.
                Where(c => categoryNormalizedName == null || c.Category?.NormalizedName == categoryNormalizedName);
            int totalPages = (int)Math.Ceiling((double)itemsTemp.Count() / itemsPerPage);
            var items = itemsTemp
                .Skip((pageNo - 1) * itemsPerPage)
                .Take(itemsPerPage)
                .ToList();
            return Task.FromResult(new ResponseData<ListModel<Telescope>>()
            {
                //Success = !(items.Count() == 0),
                Success = true,
                Data = new ListModel<Telescope>()
                {
                    Items = items,
                    CurrentPage = pageNo,
                    TotalPages = totalPages
                },
                ErrorMessage = !(items.Count() == 0) ? "" : "Ошибка :("
            });
        }
        public Task<ResponseData<Telescope>> CreateTelescopesAsync(Telescope product, IFormFile? formFile)
        {
            throw new NotImplementedException();
        }
        public Task DeleteTelescopesAsync(int id)
        {
            throw new NotImplementedException();
        }
        public Task<ResponseData<Telescope>> GetTelescopesByIdAsync(int id)
        {
            throw new NotImplementedException();
        }
        public Task UpdateTelescopesAsync(int id, Telescope product, IFormFile? formFile)
        {
            throw new NotImplementedException();
        }
    }
}
