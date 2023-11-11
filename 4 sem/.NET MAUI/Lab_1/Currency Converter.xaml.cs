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

    private List<string> currencyList = new List<string>
{
    "USD", "EUR", "RUB", "CHF", "CNY", "GBP", "BYN"
};

    private List<string> currencyIds = new List<string>
{
    "431", "451", "456", "426", "462", "429"
};

    IRateService _rateService { get; init; }

    public static IEnumerable<Rate> _rates;

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
    public Currency_Converter(IRateService service)
    {
        InitializeComponent();
        _rateService = service;
        selectedDate = DateTime.Today;
        _rates = _rateService.GetRates(selectedDate);
        fromPicker.ItemsSource = currencyList;
        toPicker.ItemsSource = currencyList;
        amountEntry.Text = "0";
        fromPicker.SelectedIndex = 6;
        toPicker.SelectedIndex = 0;
    }

    private void OnConvertClicked(object sender, EventArgs e)
    {
        string fromCurrency = fromPicker.SelectedItem?.ToString();
        string toCurrency = toPicker.SelectedItem?.ToString();
        if (!decimal.TryParse(amountEntry.Text, out decimal amount))
        {
            DisplayAlert("Ошибка", "Неправильно введена сумма!", "ОK");
            amountEntry.Text = string.Empty;
        }

        // Получаем курсы валют
        decimal fromRate, toRate;
        if (fromCurrency == "BYN")
        {
            fromRate = 1;
        }
        else
        {
            fromRate = _rates.FirstOrDefault(r => r.Cur_ID == Convert.ToInt32(currencyIds[currencyList.IndexOf(fromCurrency)]))?.Cur_OfficialRate ?? 0;
        }
        if (toCurrency == "BYN")
        {
            toRate = 1;
        }
        else
        {
            toRate = _rates.FirstOrDefault(r => r.Cur_ID == Convert.ToInt32(currencyIds[currencyList.IndexOf(toCurrency)])).Cur_OfficialRate ?? 0;
        }

        // Конвертируем сумму

        decimal result;
        if (fromRate != 0 && toRate != 0)
        {
            result = amount * fromRate / toRate;
            if (fromCurrency == "RUB" && toCurrency != "RUB")
            {
                result /= 100;
            }
            else if (fromCurrency != "RUB" && toCurrency == "RUB")
            {
                result *= 100;
            }
            else if (fromCurrency != "CNY" && toCurrency == "CNY")
            {
                result *= 10;
            }else if(fromCurrency == "CNY" && toCurrency != "CNY")
            {
                result /= 10;
            }
        }
        else
        {
            result = amount;
        }
        resultEntry.Text = result.ToString("0.00");
    }

    public void NewDateSelected(object sender, EventArgs e)
    {

        DateTime now = DateTime.Now;
        DatePicker date = (DatePicker)sender;

        if (now < date.Date)
        {
            date.Date = selectedDate;
            DisplayAlert("Ошибка", "Неправильно указана дата!", "ОK");
        }
        else
        {
            selectedDate = date.Date;
            _rates = _rateService.GetRates(selectedDate);
        }

    }
}