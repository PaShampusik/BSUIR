using API.Data;
using Domain.Entities;
using Domain.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace API.Services;

public class TelescopeService : ITelescopeService
{
	private readonly AppDbContext _dbContext;
	private readonly IConfiguration _configuration;
	private readonly IWebHostEnvironment _webHostEnvironment;
	private readonly IHttpContextAccessor _httpContextAccessor;
    public int MaxPageSize { get; private set; } = 5;

    public TelescopeService(AppDbContext dbContext, IWebHostEnvironment webHostEnvironment, IHttpContextAccessor httpContextAccessor)
	{
		_dbContext = dbContext;
		_webHostEnvironment = webHostEnvironment;
		_httpContextAccessor = httpContextAccessor;
	}

	public async Task<ResponseData<ListModel<Telescope>>> GetTelescopesListAsync(string? categoryNormalizedName, int pageNo = 1, int pageSize = 5)
	{
		if (pageSize > MaxPageSize)
		{
			pageSize = MaxPageSize;
		}

		var query = _dbContext.Telescopes.AsQueryable();
		var dataList = new ListModel<Telescope>();
		if (categoryNormalizedName != "Все" || categoryNormalizedName != null)
		{
			query = query.Where(d => categoryNormalizedName == null
			|| d.Category.NormalizedName.Equals(categoryNormalizedName));
		}
		var count = query.Count();
		if (count == 0)
		{
			return new ResponseData<ListModel<Telescope>>
			{
				Data = dataList
			};
		}
		int totalPages = (int)Math.Ceiling(count / (double)pageSize);
		if (pageNo > totalPages)
		{
			return new ResponseData<ListModel<Telescope>>
			{
				Data = null,
				Success = false,
				ErrorMessage = "Нет такой страницы"

			};
		}

		dataList.Items = await query
		.Skip((pageNo - 1) * pageSize)
		.Take(pageSize)
		.ToListAsync();

		dataList.CurrentPage = pageNo;
		dataList.TotalPages = totalPages;
		var response = new ResponseData<ListModel<Telescope>>
		{
			Data = dataList
		};
		return response;
	}

	public async Task<ResponseData<Telescope>> GetTelescopesByIdAsync(int id)
	{
		var clothes = await _dbContext.Telescopes.FindAsync(id);
		if (clothes is null)
		{
			return new ResponseData<Telescope>()
			{
				Data = null,
				Success = false,
				ErrorMessage = "Нет телескопа с таким id"
			};
		}

		return new ResponseData<Telescope>()
		{
			Data = clothes
		};
	}

	public async Task UpdateTelescopesAsync(int id, Telescope product)
	{
		var telescopes = await _dbContext.Telescopes.FindAsync(id);
		if (telescopes is null)
		{
			throw new ArgumentException("Нет телескопа с таким id");
		}

		telescopes.Name = product.Name;
		telescopes.Description = product.Description;
		telescopes.Price = product.Price;
		telescopes.CategoryId = product.CategoryId;
		telescopes.Category = product.Category;
		_dbContext.Entry(telescopes).State = EntityState.Modified;
		await _dbContext.SaveChangesAsync();
	}

	public async Task DeleteTelescopesAsync(int id)
	{
		var telescopes = await _dbContext.Telescopes.FindAsync(id);
		if (telescopes is null)
		{
			throw new ArgumentException("Нет телескопа с таким id");
		}

		_dbContext.Telescopes.Remove(telescopes);
		await _dbContext.SaveChangesAsync();
	}

	public async Task<ResponseData<Telescope>> CreateTelescopesAsync(Telescope product)
	{
		_dbContext.Telescopes.Add(product);
		try
		{
			await _dbContext.SaveChangesAsync();
		}
		catch (DbUpdateConcurrencyException ex)
		{
			return new ResponseData<Telescope>()
			{
				Data = null,
				Success = false,
				ErrorMessage = ex.Message
			};
		}
		return new ResponseData<Telescope>()
		{
			Data = product
		};
	}

	public async Task<ResponseData<string>> SaveImageAsync(int id, IFormFile formFile)
	{
		var responseData = new ResponseData<string>();
		var telescopes = await _dbContext.Telescopes.FindAsync(id);
		if (telescopes == null)
		{
			responseData.Success = false;
			responseData.ErrorMessage = "No item found";
			return responseData;
		}
		var host = "https://" + _httpContextAccessor.HttpContext?.Request.Host;
		var imageFolder = Path.Combine(_webHostEnvironment.WebRootPath, "images");

		if (formFile != null)
		{
			if (!string.IsNullOrEmpty(telescopes.Img))
			{
				var prevImage = Path.GetFileName(telescopes.Img);
				var prevImagePath = Path.Combine(imageFolder, prevImage);
				if (File.Exists(prevImagePath))
				{
					File.Delete(prevImagePath);
				}
			}
			var ext = Path.GetExtension(formFile.FileName);
			var fName = Path.ChangeExtension(Path.GetRandomFileName(), ext);
			var filePath = Path.Combine(imageFolder, fName);
			using (var stream = new FileStream(filePath, FileMode.Create))
			{
				await formFile.CopyToAsync(stream);
			}

			telescopes.Img = $"{host}/images/{fName}";
			telescopes.Mime = formFile.ContentType;
			_dbContext.Entry(telescopes).State = EntityState.Modified;
			await _dbContext.SaveChangesAsync();
		}
		responseData.Data = telescopes.Img;
		return responseData;
	}
}