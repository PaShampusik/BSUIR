using Domain.Entities;
using Microsoft.EntityFrameworkCore;

namespace API.Data
{
	public class AppDbContext : DbContext
	{
		public DbSet<Telescope> Telescopes { get; set; }
		public DbSet<Category> Category { get; set; }

		public AppDbContext(DbContextOptions<AppDbContext> options) 
			: base(options)
		{
			Database.EnsureCreated();
		}
	}
}
