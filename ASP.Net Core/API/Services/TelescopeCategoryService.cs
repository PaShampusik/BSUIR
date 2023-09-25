using API.Data;
using Domain.Entities;
using Domain.Models;
using Microsoft.EntityFrameworkCore;

namespace API.Services;

public class TelescopeCategoryService : ITelescopeCategoryService
{
    private readonly AppDbContext _dbContext;

    public TelescopeCategoryService(AppDbContext dbContext)
    {
        _dbContext = dbContext;
    }

    public async Task<ResponseData<List<Category>>> GetTelescopeCategoryListAsync()
    {
        var categories = _dbContext.Categories.ToListAsync();
        return new ResponseData<List<Category>>()
        {
            Data = await categories
        };
    }
}