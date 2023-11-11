using Domain.Entities;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;

namespace API.Data
{
	public class AppDbContext : DbContext
	{
		public DbSet<Telescope> Telescopes { get; set; }
		public DbSet<Category> Categories { get; set; }

		public AppDbContext(DbContextOptions<AppDbContext> options) 
			: base(options)
		{
			Database.MigrateAsync();
		}
	}
}
