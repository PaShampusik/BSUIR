using Lab_1.Services;
using Lab_1;
using Lab_1.Entities;
using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace Lab_1;

public partial class Currency_Converter : ContentPage
{
    public event PropertyChangedEventHandler? PropertyChanged;
    protected override void OnPropertyChanged([CallerMemberName] string propertyName = "")
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }

    IRateService _rateService;

    IEnumerable<Rate> _rates;

    DateTime selectedDate;
    public DateTime SelectedDate
    {
        get => selectedDate;
        set
        {
            if (value == selectedDate) return;
            selectedDate = value;
            OnPropertyChanged();
        }
    }
    // 298 = id(100 * rub), 143 = id(1 * GBP), 130 = id(CHF * 1), 304 = id(10 * CNY), 292 = id(1 * EUR), 145 = id(1 * USD)
    public Currency_Converter(IRateService rateService)
    {
        InitializeComponent();
        _rateService = rateService;
        selectedDate = DateTime.Today;
        _rates = _rateService.GetRates(selectedDate);
    }
}