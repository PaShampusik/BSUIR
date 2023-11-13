using Domain.Entities;
using Domain.Models;
using Microsoft.AspNetCore.Mvc;
using Moq;
using WEB_153503_Shchirov.Controllers;
using WEB_153503_Shchirov.Services.TelescopeService;
using WEB_153503_Shchirov.Services.TelescopeCategoryService;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Primitives;

namespace Tests;

class TelescopeCategoryComparer : IEqualityComparer<Category>
{
    public bool Equals(Category? x, Category? y)
    {
        if (ReferenceEquals(x, y))
            return true;

        if (ReferenceEquals(x, null) || ReferenceEquals(y, null))
            return false;

        return x.Id == y.Id && x.Name == y.Name && x.NormalizedName == y.NormalizedName;
    }

    public int GetHashCode(Category obj)
    {
        int hash = 17;
        hash = hash * 23 + obj.Id.GetHashCode();
        hash = hash * 23 + obj.Name.GetHashCode();
        hash = hash * 23 + obj.NormalizedName.GetHashCode();
        return hash;
    }
}

public class ProductControllerTest
{
    private List<Category> GetSampleCategories()
    {
        return new List<Category>() {
                new Category() { Id = 1, Name="Отражательные", NormalizedName="reflection"},
                new Category() { Id = 2, Name="Зеркальные", NormalizedName="mirror"}
            };
    }

    private List<Telescope> GetSampleTelescopes()
    {
        return new List<Telescope>()
                {
                    new Telescope() { Id = 1, Price=10.2M, Name="Jesus", FocusLength = 300, CategoryId=2},
                    new Telescope() { Id = 2, Price=10.2M, Name="Jesus2", FocusLength = 400, CategoryId=1},
                };
    }

    [Fact]
    public void Index_ReturnsViewWithListOfClothesModel_WhenNotAjaxQuery()
    {
        //Arrange
        Mock<ITelescopeCategoryService> categories_moq = new();
        categories_moq.Setup(m => m.GetCategoryListAsync()).ReturnsAsync(new ResponseData<List<Category>>()
        {
            Data = GetSampleCategories()
        });

        Mock<ITelescopeService> clothes_moq = new();
        clothes_moq.Setup(m => m.GetTelescopesListAsync(null, 1)).ReturnsAsync(new ResponseData<ListModel<Telescope>>()
        {
            Success = true,
            ErrorMessage = null,
            Data = new ListModel<Telescope>()
            {
                Items = GetSampleTelescopes()
            }
        });

        var header = new Dictionary<string, StringValues>();
        var controllerContext = new ControllerContext();
        var moqHttpContext = new Mock<HttpContext>();
        moqHttpContext.Setup(c => c.Request.Headers).Returns(new HeaderDictionary(header));
        controllerContext.HttpContext = moqHttpContext.Object;

        //Act
        var controller = new ProductController(clothes_moq.Object, categories_moq.Object) { ControllerContext = controllerContext };
        var result = controller.Index(null).Result;
        //Assert
        Assert.NotNull(result);
        var viewResult = Assert.IsType<ViewResult>(result);
        Assert.IsType<List<Telescope>>(viewResult.Model);
    }

    [Fact]
    public void Index_ReturnsPartialView_WhenAjaxQuery()
    {
        //Arrange
        Mock<ITelescopeCategoryService> categories_moq = new();
        categories_moq.Setup(m => m.GetCategoryListAsync()).ReturnsAsync(new ResponseData<List<Category>>()
        {
            Data = new List<Category>() {
                new Category() { Id = 1, Name="Отражательные", NormalizedName="reflection"},
                new Category() { Id = 2, Name="Зеркальные", NormalizedName="mirror"}
            }
        });

        Mock<ITelescopeService> telescopes_moq = new();
        telescopes_moq.Setup(m => m.GetTelescopesListAsync(null, 1)).ReturnsAsync(new ResponseData<ListModel<Telescope>>()
        {
            Success = true,
            ErrorMessage = null,
            Data = new ListModel<Telescope>()
            {
                Items = new List<Telescope>()
                {
                    new Telescope() { Id = 1, Price=10.2M, Name="Jesus", FocusLength = 300, CategoryId=2},
                    new Telescope() { Id = 2, Price=10.2M, Name="Jesus2", FocusLength = 400, CategoryId=1},
                }
            }
        });

        var header = new Dictionary<string, StringValues>()
        {
            ["X-Requested-With"] = "XMLHttpRequest"
        };
        var controllerContext = new ControllerContext();
        var moqHttpContext = new Mock<HttpContext>();
        moqHttpContext.Setup(c => c.Request.Headers).Returns(new HeaderDictionary(header));
        controllerContext.HttpContext = moqHttpContext.Object;

        //Act
        var controller = new ProductController(telescopes_moq.Object, categories_moq.Object) { ControllerContext = controllerContext };
        var result = controller.Index(null).Result;
        //Assert
        Assert.NotNull(result);
        var viewResult = Assert.IsType<PartialViewResult>(result);
    }

    [Fact]
    public void Index_ReturnsError404_WhenUnsuccessfullyReceivedCategories()
    {
        //Arrange
        Mock<ITelescopeCategoryService> categories_moq = new();
        categories_moq.Setup(m => m.GetCategoryListAsync()).ReturnsAsync(new ResponseData<List<Category>>()
        {
            Success = false
        });

        Mock<ITelescopeService> clothes_moq = new();
        clothes_moq.Setup(m => m.GetTelescopesListAsync(null, 1)).ReturnsAsync(new ResponseData<ListModel<Telescope>>()
        {
            Success = true
        });

        var header = new Dictionary<string, StringValues>();
        var controllerContext = new ControllerContext();
        var moqHttpContext = new Mock<HttpContext>();
        moqHttpContext.Setup(c => c.Request.Headers).Returns(new HeaderDictionary(header));
        controllerContext.HttpContext = moqHttpContext.Object;

        //Act
        var controller = new ProductController(clothes_moq.Object, categories_moq.Object) { ControllerContext = controllerContext };
        var result = controller.Index(null).Result;
        //Assert
        Assert.NotNull(result);
        var viewResult = Assert.IsType<NotFoundObjectResult>(result);
        Assert.Equal(StatusCodes.Status404NotFound, viewResult.StatusCode);
    }

    [Fact]
    public void Index_ReturnsError404_WhenUnsuccessfullyReceivedClothes()
    {
        //Arrange
        Mock<ITelescopeCategoryService> categories_moq = new();
        categories_moq.Setup(m => m.GetCategoryListAsync()).ReturnsAsync(new ResponseData<List<Category>>()
        {
            Success = true
        });

        Mock<ITelescopeService> telescopes_moq = new();
        telescopes_moq.Setup(m => m.GetTelescopesListAsync(null, 1)).ReturnsAsync(new ResponseData<ListModel<Telescope>>()
        {
            Success = false
        });

        var header = new Dictionary<string, StringValues>();
        var controllerContext = new ControllerContext();
        var moqHttpContext = new Mock<HttpContext>();
        moqHttpContext.Setup(c => c.Request.Headers).Returns(new HeaderDictionary(header));
        controllerContext.HttpContext = moqHttpContext.Object;

        //Act
        var controller = new ProductController(telescopes_moq.Object, categories_moq.Object) { ControllerContext = controllerContext };
        var result = controller.Index(null).Result;
        //Assert
        Assert.NotNull(result);
        var viewResult = Assert.IsType<NotFoundObjectResult>(result);
        Assert.Equal(StatusCodes.Status404NotFound, viewResult.StatusCode);
    }

    [Fact]
    public void Index_ViewDataContainsCategories_WhenSuccessfullyReceivedData()
    {
        //Arrange
        Mock<ITelescopeCategoryService> categories_moq = new();
        categories_moq.Setup(m => m.GetCategoryListAsync()).ReturnsAsync(new ResponseData<List<Category>>()
        {
            Data = GetSampleCategories()
        });

        Mock<ITelescopeService> telescope_moq = new();
        telescope_moq.Setup(m => m.GetTelescopesListAsync(null, 1)).ReturnsAsync(new ResponseData<ListModel<Telescope>>()
        {
            Success = true,
            ErrorMessage = null,
            Data = new ListModel<Telescope>()
            {
                Items = GetSampleTelescopes()
            }
        });

        var header = new Dictionary<string, StringValues>();
        var controllerContext = new ControllerContext();
        var moqHttpContext = new Mock<HttpContext>();
        moqHttpContext.Setup(c => c.Request.Headers).Returns(new HeaderDictionary(header));
        controllerContext.HttpContext = moqHttpContext.Object;


        //Act
        var controller = new ProductController(telescope_moq.Object, categories_moq.Object) { ControllerContext = controllerContext };
        var result = controller.Index(null).Result;
        //Assert
        Assert.NotNull(result);
        var viewResult = Assert.IsType<ViewResult>(result);
        Assert.True(viewResult.ViewData.ContainsKey("allCategories"));

        Assert.Equal(GetSampleCategories(), viewResult.ViewData["allCategories"] as IEnumerable<Category>, new TelescopeCategoryComparer());
    }

    [Fact]
    public void Index_ViewDataContainsValidCurrentCategoryValue_WhenCategoryParameterIsNotNull()
    {
        //Arrange
        Mock<ITelescopeCategoryService> categories_moq = new();
        categories_moq.Setup(m => m.GetCategoryListAsync()).ReturnsAsync(new ResponseData<List<Category>>()
        {
            Data = GetSampleCategories()
        });

        Mock<ITelescopeService> telescopes_moq = new();
        telescopes_moq.Setup(m => m.GetTelescopesListAsync("reflection", 1)).ReturnsAsync(new ResponseData<ListModel<Telescope>>()
        {
            Data = new ListModel<Telescope>()
            {
                Items = GetSampleTelescopes()
            }
        });

        var header = new Dictionary<string, StringValues>();
        var controllerContext = new ControllerContext();
        var moqHttpContext = new Mock<HttpContext>();
        moqHttpContext.Setup(c => c.Request.Headers).Returns(new HeaderDictionary(header));
        controllerContext.HttpContext = moqHttpContext.Object;

        //Act
        var controller = new ProductController(telescopes_moq.Object, categories_moq.Object) { ControllerContext = controllerContext };
        var result = controller.Index("reflection", 1).Result;
        //Assert
        Assert.NotNull(result);
        var viewResult = Assert.IsType<ViewResult>(result);
        Assert.True(viewResult.ViewData.ContainsKey("currentCategory"));
        var buf = viewResult.ViewData["currentCategory"] as string;
        Assert.Equal("Отражательные", buf);
    }

    [Fact]
    public void Index_ViewDataContainsValidCurrentCategoryValue_WhenCategoryParameterIsNull()
    {
        //Arrange
        Mock<ITelescopeCategoryService> categories_moq = new();
        categories_moq.Setup(m => m.GetCategoryListAsync()).ReturnsAsync(new ResponseData<List<Category>>()
        {
            Data = GetSampleCategories()
        });

        Mock<ITelescopeService> telescope_moq = new();
        telescope_moq.Setup(m => m.GetTelescopesListAsync(null, 1)).ReturnsAsync(new ResponseData<ListModel<Telescope>>()
        {
            Data = new ListModel<Telescope>()
            {
                Items = GetSampleTelescopes()
            }
        });

        var header = new Dictionary<string, StringValues>();
        var controllerContext = new ControllerContext();
        var moqHttpContext = new Mock<HttpContext>();
        moqHttpContext.Setup(c => c.Request.Headers).Returns(new HeaderDictionary(header));
        controllerContext.HttpContext = moqHttpContext.Object;

        //Act
        var controller = new ProductController(telescope_moq.Object, categories_moq.Object) { ControllerContext = controllerContext };
        var result = controller.Index(null).Result;
        //Assert
        Assert.NotNull(result);
        var viewResult = Assert.IsType<ViewResult>(result);
        Assert.True(viewResult.ViewData.ContainsKey("currentCategory"));
        var buf = viewResult.ViewData["currentCategory"] as string;
        Assert.Equal("Все", buf);
    }
}