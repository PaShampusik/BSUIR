using System.Net.Http;
using System.Net.Http.Headers;
using System.Text;
using System.Text.Json;
using Domain.Entities;
using Domain.Models;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Http;

namespace WEB_153503_Shchirov.Services.TelescopeService;

public class ApiTelescopeService : ITelescopeService
{
    private readonly HttpClient _httpClient;
    private readonly ILogger<ApiTelescopeService> _logger;
    private readonly HttpContext _httpContext;
    private readonly JsonSerializerOptions _jsonSerializerOptions;
    private readonly int _pageSize;

    public ApiTelescopeService(HttpClient httpClient, IConfiguration configuration, ILogger<ApiTelescopeService> logger,
        IHttpContextAccessor httpContextAccessor)
    {
        _httpClient = httpClient;
        _logger = logger;
        _httpContext = httpContextAccessor.HttpContext!;
        _jsonSerializerOptions = new JsonSerializerOptions()
        {
            PropertyNamingPolicy = JsonNamingPolicy.CamelCase
        };
        _pageSize = configuration.GetValue<int>("ItemsPerPage");
    }

    public async Task<ResponseData<ListModel<Telescope>>> GetTelescopesListAsync(string? categoryNormalizedName, int pageNo = 1)
    {
        var urlString = new StringBuilder($"{_httpClient.BaseAddress!.AbsoluteUri}Telescopes/");
        var token = await _httpContext.GetTokenAsync("access_token");
        _httpClient.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("bearer", token);
        if (categoryNormalizedName != null)
        {
            urlString.Append($"{categoryNormalizedName}/");
        };
        if (pageNo > 1)
        {
            urlString.Append($"{pageNo}");
        };
        if (!_pageSize.Equals("3"))
        {
            urlString.Append(QueryString.Create("pageSize", _pageSize.ToString()));
        }

        var response = await _httpClient.GetAsync(new Uri(urlString.ToString()));
        if (response.IsSuccessStatusCode)
        {
            try
            {
                return await response.Content.ReadFromJsonAsync<ResponseData<ListModel<Telescope>>>(_jsonSerializerOptions);
            }
            catch (JsonException ex)
            {
                _logger.LogError($"-----> Ошибка: {ex.Message}");
                return new ResponseData<ListModel<Telescope>>
                {
                    Success = false,
                    ErrorMessage = $"Ошибка: {ex.Message}"
                };
            }
        }
        _logger.LogError($"-----> Данные не получены от сервера. Error:{response.StatusCode}");
        return new ResponseData<ListModel<Telescope>>()
        {
            Success = false,
            ErrorMessage = $"Данные не получены от сервера. Error:{response.StatusCode}"
        };
    }

    public async Task<ResponseData<Telescope>> GetTelescopesByIdAsync(int id)
    {

        var urlString = new StringBuilder($"{_httpClient.BaseAddress!.AbsoluteUri}Telescopes/{id}");
        var token = await _httpContext.GetTokenAsync("access_token");
        _httpClient.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("bearer", token);
        var response = await _httpClient.GetAsync(new Uri(urlString.ToString()));

        if (response.IsSuccessStatusCode)
        {
            try
            {
                return await response.Content.ReadFromJsonAsync<ResponseData<Telescope>>(_jsonSerializerOptions);
            }
            catch (JsonException ex)
            {
                _logger.LogError($"-----> Ошибка: {ex.Message}");
                return new ResponseData<Telescope>
                {
                    Success = false,
                    ErrorMessage = $"Ошибка: {ex.Message}"
                };
            }
        }
        _logger.LogError($"-----> Данные не получены от сервера. Error:{response.StatusCode}");
        return new ResponseData<Telescope>()
        {
            Success = false,
            ErrorMessage = $"Данные не получены от сервера. Error:{response.StatusCode}"
        };
    }

    public async Task UpdateTelescopesAsync(int id, Telescope product, IFormFile? formFile)
    {
        var urlString = new StringBuilder($"{_httpClient.BaseAddress!.AbsoluteUri}Telescopes/{id}");
        var token = await _httpContext.GetTokenAsync("access_token");
        _httpClient.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("bearer", token);

        var response = await _httpClient.PutAsync(new Uri(urlString.ToString()),
            new StringContent(JsonSerializer.Serialize(product), Encoding.UTF8, "application/json"));

        if (response.IsSuccessStatusCode)
        {
            if (formFile is not null)
            {
                int telescopeId = (await response.Content.ReadFromJsonAsync<ResponseData<Telescope>>(_jsonSerializerOptions)).Data.Id;
                await SaveImageAsync(telescopeId, formFile);
            }
        }
        else
        {
            _logger.LogError($"-----> Данные не получены от сервера. Error:{response.StatusCode}");
        }
    }

    public async Task DeleteTelescopesAsync(int id)
    {
        var uriString = new StringBuilder($"{_httpClient.BaseAddress!.AbsoluteUri}Telescopes/{id}");
        var token = await _httpContext.GetTokenAsync("access_token");
        _httpClient.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("bearer", token);
        var response = await _httpClient.DeleteAsync(new Uri(uriString.ToString()));

        if (!response.IsSuccessStatusCode)
        {
            _logger.LogError($"-----> Данные не получены от сервера. Error:{response.StatusCode}");
        }
    }

    public async Task<ResponseData<Telescope>> CreateTelescopesAsync(Telescope product, IFormFile? formFile)
    {
        var uri = new Uri(_httpClient.BaseAddress!.AbsoluteUri + "Telescopes");
        var token = await _httpContext.GetTokenAsync("access_token");
        _httpClient.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("bearer", token);
        var response = await _httpClient.PostAsJsonAsync(uri, product, _jsonSerializerOptions);

        if (response.IsSuccessStatusCode)
        {
            var data = await response.Content.ReadFromJsonAsync<ResponseData<Telescope>>(_jsonSerializerOptions);
            if (formFile is not null)
            {
                await SaveImageAsync(data.Data.Id, formFile);
            }
            return data;
        }
        _logger.LogError($"-----> Объект не добавлен. Error:{response.StatusCode}");
        return new ResponseData<Telescope>
        {
            Success = false,
            ErrorMessage = $"Объект не добавлен. Error:{response.StatusCode}"
        };
    }

    private async Task SaveImageAsync(int id, IFormFile image)
    {
        var request = new HttpRequestMessage
        {
            Method = HttpMethod.Post,
            RequestUri = new Uri($"{_httpClient.BaseAddress?.AbsoluteUri}Telescopes/{id}")
        };
        var content = new MultipartFormDataContent();
        var streamContent = new StreamContent(image.OpenReadStream());
        content.Add(streamContent, "formFile", image.FileName);
        request.Content = content;
        var token = await _httpContext.GetTokenAsync("access_token");
        _httpClient.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("bearer", token);
        await _httpClient.SendAsync(request);
    }
}