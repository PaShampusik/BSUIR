using System.ComponentModel;
using System.Runtime.CompilerServices;
using Microsoft.VisualBasic;
using System.Diagnostics;
using System.Globalization;
using System;
using System.Threading;

namespace Lab_1;

public partial class IntegralCalculation : ContentPage, INotifyPropertyChanged
{
	public event PropertyChangedEventHandler? PropertyChanged;

    public CancellationTokenSource _CancellationTokenSource = default(CancellationTokenSource);

    public bool canceled = false;

    public IntegralCalculation()
    {
        InitializeComponent();
        BindingContext = this;
    }

    protected override void OnPropertyChanged([CallerMemberName] string propertyName = "")
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }

	string state = "Click Start to Calculate!";
	public string State
	{
        get => state;
        set
        {
            if (value == state) return;
            state = value;
            OnPropertyChanged();
        }
    }
    async Task CalculationAsync(IProgress<double> progress, CancellationToken token)
	{
        try
        {
            double result = 0;
            double delta = 0.00000001;
            double percent = 0;

            for (double i = 0.0; i <= 1.0; i += delta)
            {
                result += Math.Sin(i) * delta;
                if (percent != Math.Round(i, 2))
                {
                    token.ThrowIfCancellationRequested();
                    progress.Report(percent);
                    percent = Math.Round(i, 2);
                }
            }
            progress.Report(percent + 0.005);
            State = $"Result: {Math.Round(result, 6)}";
        }
        catch(OperationCanceledException)
        {
            State = "Canceled";
        }
        finally
        {

            _CancellationTokenSource.Dispose();
            _CancellationTokenSource = null;
        }
    }

	async void OnStartClicked(object sender, EventArgs args)
	{
        Cancel.IsEnabled = true;
        Start.IsEnabled = false;
        canceled = false;

        _CancellationTokenSource = new CancellationTokenSource();

        Progress<double> progress = new Progress<double>(m =>
        {
            if (canceled)
            {
                _CancellationTokenSource.Cancel();
            }
            Percent.Text = $"{(int)(m * 100)}%";
            ProgressBar.Progress = m;
        });

        State = "Calculating...";

        await Task.Run(() => CalculationAsync(progress, _CancellationTokenSource.Token));
        Start.IsEnabled = true;
	}


    void OnCancelClicked(object sender, EventArgs args)
    {
        Start.IsEnabled = true;
        Cancel.IsEnabled = false;
        canceled = true;
    }

    [Obsolete]
    void OnButtonReleased(object sender, EventArgs args)
    {
        Button but = new();
        but = (Button)sender;
        but.BackgroundColor = Color.FromHex("#512bd4");
    }
}