using API.Data;
using Microsoft.EntityFrameworkCore;
using API.Services;
using Microsoft.AspNetCore.Authentication.JwtBearer;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddRazorPages();
builder.Services.AddScoped<ITelescopeCategoryService, TelescopeCategoryService>();
builder.Services.AddScoped<ITelescopeService, TelescopeService>();
builder.Services.AddControllers();
builder.Services.AddHttpContextAccessor();

RegisterDbContext(builder);

builder.Services
.AddAuthentication(JwtBearerDefaults.AuthenticationScheme)
.AddJwtBearer(opt =>
{
    opt.Authority = builder
    .Configuration
    .GetSection("isUri").Value;
    opt.TokenValidationParameters.ValidateAudience = false;
    opt.TokenValidationParameters.ValidTypes =
    new[] { "at+jwt" };
});
builder.Services.AddCors(options =>
{
	options.AddPolicy("BlazorWasmPolicy", builder =>
	{
		builder.WithOrigins("https://localhost:7258")
			   .AllowAnyMethod()
			   .AllowAnyHeader();
	});
});

var app = builder.Build();

app.UseStaticFiles();

app.UseHttpsRedirection();

app.UseCookiePolicy(new CookiePolicyOptions
{
    Secure = CookieSecurePolicy.Always
});

app.UseAuthentication();
app.UseAuthorization();
app.UseCors("BlazorWasmPolicy");
app.MapControllers();

using (var scope = app.Services.CreateScope())
{
	var services = scope.ServiceProvider;
	var dbContext = services.GetRequiredService<AppDbContext>();

	// Выполнение миграции
	dbContext.Database.Migrate();

	await DbInitializer.SeedData(app);
}


app.Run();

static void RegisterDbContext(WebApplicationBuilder builder)
{
	var connectionString = builder.Configuration
		   .GetConnectionString("Default");
	string dataDirectory = AppDomain.CurrentDomain.BaseDirectory + Path.DirectorySeparatorChar;
	connectionString = string.Format(connectionString!, dataDirectory);
	builder.Services.AddDbContext<AppDbContext>(options => options.UseSqlite(connectionString).EnableSensitiveDataLogging());
}