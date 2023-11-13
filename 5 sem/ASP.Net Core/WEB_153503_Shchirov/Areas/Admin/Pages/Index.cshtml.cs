using Domain.Entities;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WEB_153503_Shchirov.Extensions;
using WEB_153503_Shchirov.Services.TelescopeService;

namespace WEB_153503_Shchirov.Areas.Admin.Pages
{
	//[Authorize(Roles = "admin")] пока что роли не работают
	public class IndexModel : PageModel
	{
		private readonly ITelescopeService _telescopeService;

		public IndexModel(ITelescopeService clothesService)
		{
			_telescopeService = clothesService;
		}

		public IList<Telescope> Telescopes { get; set; } = default!;

		public int CurrentPage { get; set; }
		public int TotalPages { get; set; }

		public async Task<IActionResult> OnGetAsync(int pageNo = 1)
		{
			var response = await _telescopeService.GetTelescopesListAsync(null, pageNo);

			if (response.Success)
			{
				Telescopes = response.Data?.Items!;
				CurrentPage = response.Data.CurrentPage;
				TotalPages = response.Data.TotalPages;
			}

			if (Request.IsAjaxRequest())
			{
				return Partial("_ProductCardsAndPagerPartial", new
				{
					CurrentPage,
					TotalPages,
					Telescopes,
					InAdminArea = true,
				});
			}

			return Page();
		}
	}
}