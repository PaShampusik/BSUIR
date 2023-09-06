using Microsoft.AspNetCore.Mvc;

namespace WEB_153503_Shchirov.ViewComponents;

public class Cart : ViewComponent
{
	public Task<IViewComponentResult> InvokeAsync()
	{
		return Task.FromResult<IViewComponentResult>(View());
	}
}