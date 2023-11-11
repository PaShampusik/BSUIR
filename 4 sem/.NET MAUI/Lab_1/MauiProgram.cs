using Lab_1.Services;
using Microsoft.Extensions.DependencyInjection;

namespace Lab_1;

public static class MauiProgram
{

    public static MauiApp CreateMauiApp()
	{
		var builder = MauiApp.CreateBuilder();
		builder
			.UseMauiApp<App>()
			.ConfigureFonts(fonts =>
			{
				fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
				fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
			});

        builder.Services.AddTransient<IDbService, SQLiteService>();
		builder.Services.AddSingleton<DatabasePage>();
        builder.Services.AddSingleton<Currency_Converter>();
		builder.Services.AddHttpClient<IRateService, RateService>(opt => opt.BaseAddress = new Uri("https://www.nbrb.by/api/exrates/rates"));
        return builder.Build();
    }
}
