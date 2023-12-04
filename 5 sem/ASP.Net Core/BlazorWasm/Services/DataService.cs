using System.Text.Json;
using System.Text;
using Domain.Entities;
using Domain.Models;
using System.Net.Http.Json;
using Microsoft.AspNetCore.Components.WebAssembly.Authentication;
using System.Net.Http.Headers;

namespace BlazorWasm.Services;

public class DataService : IDataService
{
	private readonly HttpClient _httpClient;
	private readonly IAccessTokenProvider _accessTokenProvider;
	private readonly int _pageSize = 3;
	private readonly JsonSerializerOptions _jsonSerializerOptions;

	public DataService(HttpClient httpClient, IConfiguration configuration, IAccessTokenProvider accessTokenProvider)
	{
		_httpClient = httpClient;
		_pageSize = configuration.GetSection("PageSize").Get<int>(); 
		_accessTokenProvider = accessTokenProvider;
		_jsonSerializerOptions = new JsonSerializerOptions()
		{
			PropertyNamingPolicy = JsonNamingPolicy.CamelCase
		};
	}

	public List<Category>? Categories { get; set; }
	public List<Telescope>? TelescopeList { get; set; }
	public bool Success { get; set; } = true;
	public string? ErrorMessage { get; set; }
	public int TotalPages { get; set; }
	public int CurrentPage { get; set; }

	public async Task GetTelescopesListAsync(string? categoryNormalizedName, int pageNo = 1)
	{
		var tokenRequest = await _accessTokenProvider.RequestAccessToken();
		if (tokenRequest.TryGetToken(out var token))
		{
			_httpClient.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", token.Value);
			var urlString = new StringBuilder($"{_httpClient.BaseAddress!.AbsoluteUri}api/Telescopes/");
			if (categoryNormalizedName != null)
			{
				urlString.Append($"category={categoryNormalizedName}");
			}
			else
			{
				urlString.Append($"category=Все");
			}
			if (pageNo > 1)
			{
				urlString.Append($"pageNo={pageNo}");
			}
			else
			{
				urlString.Append($"pageNo=1");
			}
			if (!_pageSize.Equals("3"))
			{
				urlString.Append($"pageSize={_pageSize.ToString()}");
			}
			else
			{
				urlString.Append($"pageSize=3");
			}

			var response = await _httpClient.GetAsync(new Uri(urlString.ToString()));
			if (response.IsSuccessStatusCode)
			{
				try
				{
					var responseData = await response.Content.ReadFromJsonAsync<ResponseData<ListModel<Telescope>>>(_jsonSerializerOptions);
					TelescopeList = responseData?.Data?.Items;
					TotalPages = responseData?.Data?.TotalPages ?? 0;
					CurrentPage = responseData?.Data?.CurrentPage ?? 0;
				}
				catch (JsonException ex)
				{
					Success = false;
					ErrorMessage = $"Ошибка: {ex.Message}";
				}
			}
			else
			{
				Success = false;
				ErrorMessage = $"Данные не получены от сервера. Error:{response.StatusCode}";
			}
		}
	}

	public async Task<Telescope?> GetTelescopeByIdAsync(int id)
	{
		var tokenRequest = await _accessTokenProvider.RequestAccessToken();
		if (tokenRequest.TryGetToken(out var token))
		{
			_httpClient.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", token.Value);
			var urlString = new StringBuilder($"{_httpClient.BaseAddress!.AbsoluteUri}api/Telescopes/{id}");
			var response = await _httpClient.GetAsync(new Uri(urlString.ToString()));

			if (response.IsSuccessStatusCode)
			{
				try
				{
					return (await response.Content.ReadFromJsonAsync<ResponseData<Telescope>>(_jsonSerializerOptions))?.Data;
				}
				catch (JsonException ex)
				{
					Success = false;
					ErrorMessage = $"Ошибка: {ex.Message}";
					return null;
				}
			}
			Success = false;
			ErrorMessage = $"Данные не получены от сервера. Error:{response.StatusCode}";
		}
		return null;
	}

	public async Task GetCategoryListAsync()
	{
		var tokenRequest = await _accessTokenProvider.RequestAccessToken();
		if (tokenRequest.TryGetToken(out var token))
		{
			_httpClient.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("Bearer", token.Value);
			var urlString = new StringBuilder($"{_httpClient.BaseAddress?.AbsoluteUri}api/Categories/");
			var response = await _httpClient.GetAsync(new Uri(urlString.ToString()));
			if (response.IsSuccessStatusCode)
			{
				try
				{
					var responseData = await response.Content.ReadFromJsonAsync<ResponseData<List<Category>>>(_jsonSerializerOptions);
					Categories = responseData?.Data;
				}
				catch (JsonException ex)
				{
					Success = false;
					ErrorMessage = $"Ошибка: {ex.Message}";
				}
			}
			else
			{
				Success = false;
				ErrorMessage = $"Данные не получены от сервера. Error:{response.StatusCode}";
			}
		}
	}
}