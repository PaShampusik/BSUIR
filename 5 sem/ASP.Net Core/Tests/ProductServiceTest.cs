using System.Data.Common;
using API.Data;
using API.Services;
using Domain.Entities;
using Domain.Models;
using Microsoft.Data.Sqlite;
using Microsoft.EntityFrameworkCore;
using NuGet.Common;

namespace Tests;
public class ProductServiceTest : IDisposable
{
    public void Dispose() => _connection.Dispose();

    private readonly DbConnection _connection;
    private readonly DbContextOptions<AppDbContext> _contextOptions;

    public ProductServiceTest()
    {
        _connection = new SqliteConnection("Filename=:memory:");
        _connection.Open();

        _contextOptions = new DbContextOptionsBuilder<AppDbContext>()
            .UseSqlite(_connection)
            .Options;

        using var context = new AppDbContext(_contextOptions);
        context.Database.EnsureCreated();
        context.Categories.AddRange(
            new Category() { Id = 1, Name = "Отражающие", NormalizedName = "reflection" },
            new Category() { Id = 2, Name = "Зеркальные", NormalizedName = "mirror" });
        context.Telescopes.AddRange(
            new Telescope() { Id = 1, Price = 10.2M, Description = "Дорага", FocusLength = 300, Name = "Jesus1", CategoryId = 2 },
            new Telescope() { Id = 2, Price = 10.2M, Description = "Дорага", FocusLength = 400, Name = "Jesus2", CategoryId = 2 },
            new Telescope() { Id = 3, Price = 10.2M, Description = "Дорага", FocusLength = 500, Name = "Jesus3", CategoryId = 2 },
            new Telescope() { Id = 4, Price = 10.2M, Description = "Дорага", FocusLength = 600, Name = "Jesus4", CategoryId = 2 },
            new Telescope() { Id = 5, Price = 10.2M, Description = "Дорага", FocusLength = 700, Name = "Eva1", CategoryId = 1 },
            new Telescope() { Id = 6, Price = 10.2M, Description = "Дорага", FocusLength = 800, Name = "Eva2", CategoryId = 1 },
            new Telescope() { Id = 7, Price = 10.2M, Description = "Дорага", FocusLength = 900, Name = "Eva3", CategoryId = 1 });
        context.SaveChanges();
    }

    private AppDbContext CreateContext() => new AppDbContext(_contextOptions);

    [Fact]
    public void GetTelescopesListAsync_ReturnsFirstPageWithThreeItems_WhenDefaultParametersPassed()
    {
        // Arrange
        using var context = CreateContext();
        TelescopeService service = new(context, null!, null!);

        // Act
        var result = service.GetTelescopesListAsync(null).Result;

        // Assert
        Assert.IsType<ResponseData<ListModel<Telescope>>>(result);
        Assert.True(result.Success);
        Assert.Equal(1, result.Data!.CurrentPage);
        Assert.Equal(5, result.Data.Items.Count);
        Assert.Equal(2, result.Data.TotalPages);
        Assert.Equal(context.Telescopes.First(), result.Data.Items[0]);
    }

    [Fact]
    public void GetTelescopeListAsync_ReturnsSecondPageWithSecondThreeItems_WhenPageParameterEquals2()
    {
        // Arrange
        using var context = CreateContext();
        TelescopeService service = new(context, null!, null!);

        // Act
        var result = service.GetTelescopesListAsync(null, 2).Result;

        // Assert
        Assert.IsType<ResponseData<ListModel<Telescope>>>(result);
        Assert.True(result.Success);
        Assert.Equal(2, result.Data!.CurrentPage);
        Assert.Equal(2, result.Data.Items.Count);
        Assert.Equal(2, result.Data.TotalPages);
        Assert.Equal(context.Telescopes.Skip(5).First(), result.Data.Items.First());
    }

    [Fact]
    public void GetTelescopeListAsync_ReturnsValidTelescopesByCategory_WhenCategoryParameterPassed()
    {
        // Arrange
        using var context = CreateContext();
        TelescopeService service = new(context, null!, null!);

        // Act
        var result = service.GetTelescopesListAsync("reflection").Result;

        // Assert
        Assert.IsType<ResponseData<ListModel<Telescope>>>(result);
        Assert.True(result.Success);
        Assert.Equal(1, result.Data!.CurrentPage);
        Assert.Equal(3, result.Data.Items.Count);
        Assert.Equal(1, result.Data.TotalPages);
        Assert.DoesNotContain(result.Data.Items, x => x.CategoryId != 1);
    }

    [Fact]
    public void GetTelescopeListAsync_ReturnsSuccessFalse_WhenPageNumberParameterIsGreaterThanTotalPages()
    {
        // Arrange
        using var context = CreateContext();
        TelescopeService service = new(context, null!, null!);

        // Act
        var result = service.GetTelescopesListAsync(null, 1000).Result;

        // Assert
        Assert.IsType<ResponseData<ListModel<Telescope>>>(result);
        Assert.False(result.Success);
    }

    [Fact]
    public void GetTelescopeListAsync_DoesNotAllowToSetPageSizeGreaterThanMaxPageSize_WhenGreaterPageSizePassed()
    {
        // Arrange
        using var context = CreateContext();
        TelescopeService service = new(context, null!, null!);

        // Act
        var result = service.GetTelescopesListAsync(null!, 1, service.MaxPageSize + 1).Result;

        // Assert
        Assert.True(result.Success);
        Assert.True(result.Data!.Items.Count <= service.MaxPageSize);
    }
}