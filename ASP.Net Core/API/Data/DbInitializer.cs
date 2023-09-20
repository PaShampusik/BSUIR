using Domain.Entities;
using Microsoft.EntityFrameworkCore;

namespace API.Data;

public class DbInitializer
{
	public static async Task SeedData(WebApplication app)
	{
		var _categories = new List<Category>
		{
			new Category { Name="Рефракционные", NormalizedName="Refraction"},
			new Category { Name="Отражательные", NormalizedName="Reflection"},
		};

		var _telescopes = new List<Telescope>
			{
			new Telescope { Name="Celestron PowerSeeker 70EQ",
			Description="Рефракционный телескоп",
			FocusLength =900 , Img="Images/Celestron PowerSeeker 70EQ.jpg",
			Price = 1100,
			Category= _categories.Find(c=>c.NormalizedName.Equals("Refraction"))},

			new Telescope { Name="Meade Instruments Infinity 80mm",
			Description="Рефракционный телескоп",
			FocusLength =400, Img ="Images/Meade Instruments Infinity 80mm AZ.jpg",
			Price = 800,
			Category=
			_categories.Find(c=>c.NormalizedName.Equals("Refraction"))},

			new Telescope { Name="Sky-Watcher ProED 80mm",
			Description="Рефракционный телескоп",
			Price = 1000,
			FocusLength = 600 , Img="Images/Sky-Watcher ProED 80mm Doublet APO Refractor.jpg",
			Category= _categories.Find(c=>c.NormalizedName.Equals("Refraction"))},

			new Telescope {  Name="Orion EON 115mm ED",
			Description="Рефракционный телескоп",
			FocusLength = 805, Img ="Images/Orion EON 115mm ED Triplet Apochromatic Refractor.jpg",
			Price = 1500,
			Category=
			_categories.Find(c=>c.NormalizedName.Equals("Refraction"))},

			new Telescope
			{
				Name = "Meade Instruments Infinity 80mm AZ",
				Description = "Отражательный телескоп",
				FocusLength = 1200,
				Img = "Images/Meade Instruments Infinity 80mm AZ.jpg",
				Price = 2000,
				Category =
			_categories.Find(c => c.NormalizedName.Equals("Reflection")) },

			new Telescope {  Name="Orion SkyQuest XT8",
				Description="Отражательный телескоп",
				FocusLength = 2032, Img ="Images/Orion SkyQuest XT8 Classic Dobsonian.jpg",
				Price = 1300,
				Category =
				_categories.Find(c=>c.NormalizedName.Equals("Reflection"))},
			new Telescope
			{
				Name = "Celestron AstroMaster 130EQ",
				Description = "Отражательный телескоп",
				FocusLength = 650,
				Img = "Images/Celestron AstroMaster 130EQ.jpg",
				Price = 2300,
				Category =
			_categories.Find(c => c.NormalizedName.Equals("Reflection")) },
			new Telescope
			{
				Name = "Meade Instruments LX90-ACF",
				Description = "Отражательный телескоп",
				FocusLength = 2000,
				Img = "Images/Meade Instruments LX90-ACF.jpg",
				Price = 2500,
				Category =
			_categories.Find(c => c.NormalizedName.Equals("Reflection")) }
			};

		using var scope = app.Services.CreateScope();

		var context = scope.ServiceProvider.GetRequiredService<AppDbContext>();

		if (context.Database.GetPendingMigrations().Any())
		{
			await context.Database.MigrateAsync();
		}

		if (!context.Categories.Any())
		{
			await context.Categories.AddRangeAsync(_categories!);
			await context.SaveChangesAsync();
		}

		var imageBaseUrl = app.Configuration.GetValue<string>("ImageUrl");
		if (!context.Telescopes.Any())
		{

			foreach (var telescope in _telescopes)
			{
				telescope.Img = $"{imageBaseUrl}/{telescope.Img}";
			}
			await context.Telescopes.AddRangeAsync(_telescopes);
			await context.SaveChangesAsync();
		}
	}
}