using Domain.Entities;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WEB_153503_Shchirov.Services.TelescopeService;

namespace WEB_153503_Shchirov.Areas.Admin.Pages
{
    public class IndexModel : PageModel
    {
        private readonly ITelescopeService _telescopeService;

        public IndexModel(ITelescopeService telescopeService)
        {
            _telescopeService = telescopeService;
        }

        public IList<Telescope> Telescopes { get; set; } = default!;

        public int CurrentPage { get; set; }
        public int TotalPages { get; set; }

        public async Task OnGetAsync(int pageNo = 1)
        {
            var response = await _telescopeService.GetTelescopesListAsync(null, pageNo);

            if (response.Success)
            {
                Telescopes = response.Data?.Items!;
                CurrentPage = response.Data.CurrentPage;
                TotalPages = response.Data.TotalPages;
            }
        }
    }
}