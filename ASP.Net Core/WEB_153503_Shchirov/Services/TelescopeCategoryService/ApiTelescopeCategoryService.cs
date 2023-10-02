using System.Text;
using System.Text.Json;
using Domain.Entities;
using Domain.Models;
using WEB_153503_Shchirov.Services.TelescopeCategoryService;

namespace WEB_153503_Shchirov.Services.TelescopeCategoryService;

public class ApiTelescopeCategoryService : ITelescopeCategoryService
{
    private readonly HttpClient _httpClient;
    private readonly ILogger<ApiTelescopeCategoryService> _logger;
    private readonly JsonSerializerOptions _jsonSerializerOptions;

    public ApiTelescopeCategoryService(HttpClient httpClient, ILogger<ApiTelescopeCategoryService> logger)
    {
        _httpClient = httpClient;
        _logger = logger;
        _jsonSerializerOptions = new JsonSerializerOptions()
        {
            PropertyNamingPolicy = JsonNamingPolicy.CamelCase
        };
    }

    public async Task<ResponseData<List<Category>>> GetCategoryListAsync()
    {
        var urlString = new StringBuilder($"{_httpClient.BaseAddress?.AbsoluteUri}Categories/");
        var response = await _httpClient.GetAsync(new Uri(urlString.ToString()));
        if (response.IsSuccessStatusCode)
        {
            try
            {
                return await response.Content.ReadFromJsonAsync<ResponseData<List<Category>>>(_jsonSerializerOptions);
            }
            catch (JsonException ex)
            {
                _logger.LogError($"-----> Ошибка: {ex.Message}");
                return new ResponseData<List<Category>>
                {
                    Success = false,
                    ErrorMessage = $"Ошибка: {ex.Message}"
                };

            }
        }
        _logger.LogError($"-----> Данные не получены от сервера. Error:{response.StatusCode}");
        return new ResponseData<List<Category>>()
        {
            Success = false,
            ErrorMessage = $"Данные не получены от сервера. Error:{response.StatusCode}"
        };
    }
}