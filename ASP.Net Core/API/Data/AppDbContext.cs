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
		}

		protected override void OnModelCreating(ModelBuilder modelBuilder)
		{
			modelBuilder.Entity<Telescope>().HasKey(tl => tl.Id);
			modelBuilder.Entity<Telescope>().Property(tl => tl.Id).ValueGeneratedOnAdd();
		    modelBuilder.Entity<Telescope>().HasOne(tl => tl.Category).WithMany(cat => cat.Telescopes).HasForeignKey(tl => tl.CategoryId);
			
			modelBuilder.Entity<Category>().HasKey(tc => tc.Id);
			modelBuilder.Entity<Category>().Property(tc => tc.Id).ValueGeneratedOnAdd();
		}
	}
}
