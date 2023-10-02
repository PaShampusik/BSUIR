using Domain.Entities;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Mvc.Rendering;
using WEB_153503_Shchirov.Services.TelescopeCategoryService;
using WEB_153503_Shchirov.Services.TelescopeService;

namespace WEB_153503_Shchirov.Areas.Admin.Pages
{
    public class EditModel : PageModel
    {
        private readonly ITelescopeService _telescopeService;
        private readonly ITelescopeCategoryService _telescopeCategoryService;

        public EditModel(ITelescopeService telescopeService, ITelescopeCategoryService telescopeCategoryService)
        {
            _telescopeService = telescopeService;
            _telescopeCategoryService = telescopeCategoryService;
        }

        [BindProperty]
        public Telescope Telescope { get; set; } = default!;

        [BindProperty]
        public IFormFile? Image { get; set; }

        public async Task<IActionResult> OnGetAsync(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var response = await _telescopeService.GetTelescopesByIdAsync(id.Value);

            if (!response.Success)
            {
                return NotFound();
            }

            var responseCtg = await _telescopeCategoryService.GetCategoryListAsync();
            if (!response.Success)
            {
                return NotFound();
            }
            ViewData["CategoryId"] = new SelectList(responseCtg.Data, "Id", "Name");

            Telescope = response.Data!;

            return Page();
        }

        public async Task<IActionResult> OnPostAsync()
        {
            if (!ModelState.IsValid)
            {
                return Page();
            }


            try
            {
                await _telescopeService.UpdateTelescopesAsync(Telescope.Id, Telescope, Image);
            }
            catch (Exception)
            {
                if (!await ClothesExists(Telescope.Id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return RedirectToPage("./Index");
        }

        private async Task<bool> ClothesExists(int id)
        {
            var response = await _telescopeService.GetTelescopesByIdAsync(id);
            return response.Success;
        }
    }
}