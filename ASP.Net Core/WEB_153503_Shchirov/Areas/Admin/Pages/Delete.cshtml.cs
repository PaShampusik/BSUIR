﻿using Domain.Entities;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WEB_153503_Shchirov.Services.TelescopeService;

namespace WEB_153503_Shchirov.Areas.Admin.Pages
{
    public class DeleteModel : PageModel
    {
        private readonly ITelescopeService _telescopeService;

        public DeleteModel(ITelescopeService telescopeService)
        {
            _telescopeService = telescopeService;
        }

        [BindProperty]
        public Telescope Telescope { get; set; } = default!;

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

            Telescope = response.Data!;

            return Page();
        }


        public async Task<IActionResult> OnPostAsync(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            try
            {
                await _telescopeService.DeleteTelescopesAsync(id.Value);
            }
            catch (Exception e)
            {
                return NotFound(e.Message);
            }

            return RedirectToPage("./Index");
        }
    }
}