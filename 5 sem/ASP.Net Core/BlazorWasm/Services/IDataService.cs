using Domain.Entities;

namespace BlazorWasm.Services;

public interface IDataService
{
	List<Category>? Categories { get; set; }
	List<Telescope>? TelescopeList { get; set; }
	bool Success { get; set; }
	string? ErrorMessage { get; set; }
	int TotalPages { get; set; }
	int CurrentPage { get; set; }

	public Task GetTelescopesListAsync(string? categoryNormalizedName, int pageNo = 1);

	public Task<Telescope?> GetTelescopeByIdAsync(int id);

	public Task GetCategoryListAsync();
}