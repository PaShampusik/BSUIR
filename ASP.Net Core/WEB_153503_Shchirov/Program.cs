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

builder.Services.AddAuthentication(opt =>
{
    
    opt.DefaultScheme = "cookie";
    opt.DefaultChallengeScheme = "oidc";
})
.AddCookie("cookie", options =>
{
    options.Cookie.SameSite = SameSiteMode.None;  // I ADDED THIS LINE!!!
})
.AddOpenIdConnect("oidc", options =>
{
    options.Authority =
    builder.Configuration["InteractiveServiceSettings:AuthorityUrl"];
    options.ClientId =
    builder.Configuration["InteractiveServiceSettings:ClientId"];
    options.ClientSecret =
    builder.Configuration["InteractiveServiceSettings:ClientSecret"];
    options.GetClaimsFromUserInfoEndpoint = true;
    options.ResponseType = "code";
    options.ResponseMode = "query";
    options.SaveTokens = true;
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

app.UseCookiePolicy(new CookiePolicyOptions
{
    MinimumSameSitePolicy = SameSiteMode.None,
    Secure = CookieSecurePolicy.Always
});

app.UseAuthentication();
app.UseAuthorization();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");
app.MapRazorPages();
app.MapRazorPages().RequireAuthorization();
app.Run();
