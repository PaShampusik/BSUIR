using Microsoft.AspNetCore.Authentication.Negotiate;
using WEB_153503_Shchirov.Models;
using WEB_153503_Shchirov.Services.TelescopeCategoryService;
using WEB_153503_Shchirov.Services.TelescopeService;

var builder = WebApplication.CreateBuilder(args);


// Add services to the container.
builder.Services.AddControllersWithViews();
builder.Services.AddRazorPages();

UriData uriData = builder.Configuration.GetSection("UriData").Get<UriData>()!;
builder.Services.AddHttpClient<ITelescopeService, ApiTelescopeService>(client =>
{
    client.BaseAddress = new Uri(uriData.ApiUri);
});

builder.Services.AddHttpClient<ITelescopeCategoryService, ApiTelescopeCategoryService>(client =>
{
    client.BaseAddress = new Uri(uriData.ApiUri);
});
builder.Services.AddAuthentication(NegotiateDefaults.AuthenticationScheme)
   .AddNegotiate();

builder.Services.AddHttpContextAccessor();

builder.Services.AddAuthorization(options =>
{
    // By default, all incoming requests will be authorized according to the default policy.
    options.FallbackPolicy = options.DefaultPolicy;
});

var app = builder.Build();

// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}

app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();

app.UseAuthorization();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");

app.Run();
