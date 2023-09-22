using API.Data;
using Microsoft.EntityFrameworkCore;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddRazorPages();
builder.Services.Add add
RegisterDbContext(builder);

var app = builder.Build();

app.UseStaticFiles();

app.UseHttpsRedirection();

app.UseAuthentication();
app.UseAuthorization();

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