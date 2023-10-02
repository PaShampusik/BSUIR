using Domain.Entities;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Mvc.Rendering;
using WEB_153503_Shchirov.Services.TelescopeCategoryService;
using WEB_153503_Shchirov.Services.TelescopeService;

namespace WEB_153503_Shchirov.Areas.Admin.Pages
{
	public class CreateModel : PageModel
	{
		private readonly ITelescopeService _telescopeService;
		private readonly ITelescopeCategoryService _telescopeCategoryService;

		public CreateModel(ITelescopeService telescopeService, ITelescopeCategoryService telescopeCategoryService)
		{
			_telescopeService = telescopeService;
			_telescopeCategoryService = telescopeCategoryService;
		}

		public async Task<IActionResult> OnGet()
		{
			var response = await _telescopeCategoryService.GetCategoryListAsync();
			if (!response.Success)
			{
				return NotFound();
			}
			ViewData["CategoryId"] = new SelectList(response.Data, "Id", "Name");
			return Page();
		}

		[BindProperty]
		public Telescope Telescope { get; set; } = default!;

		[BindProperty]
		public IFormFile? Image { get; set; }

		// To protect from overposting attacks, see https://aka.ms/RazorPagesCRUD
		public async Task<IActionResult> OnPostAsync()
		{
			if (!ModelState.IsValid)
			{
				return Page();
			}

			var response = await _telescopeService.CreateTelescopesAsync(Telescope, Image);

			if (!response.Success)
			{
				return Page();
			}

			return RedirectToPage("./Index");
		}
	}
}