using Microsoft.VisualBasic;
using System.ComponentModel;
using System.Diagnostics;
using System.Globalization;
using System.Runtime.CompilerServices;

namespace Lab_1;




public partial class MainPage : ContentPage, INotifyPropertyChanged
{
    public event PropertyChangedEventHandler? PropertyChanged;

    protected override void OnPropertyChanged([CallerMemberName] string propertyName = "")
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }

    [Obsolete]
    void OnButtonPressed(object sender, EventArgs args)
    {
        Button but = new();
        but = (Button)sender;
        if (but.Text == "=")
        {
            but.BackgroundColor = Color.FromHex("#2d3941");

        }
        else 
        {
            but.BackgroundColor = Color.FromHex("#c8c8c8"); 
        }

    }

    [Obsolete]
    void OnButtonReleased(object sender, EventArgs args)
    {
        Button but = new();
        but = (Button)sender;
        if (but.Text == "=")
        {
            but.BackgroundColor = Color.FromHex("#4c5f6b");

        }
        else
        {
            but.BackgroundColor = Color.FromHex("#fbf8f7");
        }
    }

    string calc = "";
    public string Calc
    {
        get => calc;
        set
        {
            if (value == calc) return;
            calc = value;
            OnPropertyChanged();
        }
    }
    string res = "0";
    public string Res
    {
        get => res;
        set
        {
            if (value == res) return;
            res = value;
            OnPropertyChanged();
        }
    }

    private string firstNum = "";
    private string secondNum = "";
    private string sign = "";
    private string lastSign = "";
    private string lastNum = "";
    private string memory = "";

    bool memoryNotEmpty = false;

    public bool MemoryNotEmpty
    {
        get => memoryNotEmpty;
        set
        {
            if (value == memoryNotEmpty) return;
            memoryNotEmpty = value;
            OnPropertyChanged();
        }
    }

    public MainPage()
    {
        InitializeComponent();
        BindingContext = this;
    }

    void OnButtonClicked(object sender, EventArgs args)
    {
        if (Res == Calc)
        {
            Res = "";
            Calc = "";
        }
        Button but = new();
        but = (Button)sender;
        if (sign == "")
        {
            if (firstNum != null && firstNum.Length > 13)
            {
                return;
            }
            else if (but.Text == "0" && firstNum == "0")
            {
                return;
            }
            if (but.Text == "," && !firstNum.Contains(",") && !firstNum.Contains("."))
            {
                if (firstNum == "" || firstNum == "0")
                {
                    firstNum = "0,";
                }
                else
                {
                    firstNum += ",";
                }
            }
            else if (but.Text != ",")
            {
                if (firstNum == "0")
                {
                    firstNum = "";
                }
                firstNum += but.Text;
            }

            Res = firstNum;
            Calc = "";

        }
        else
        {
            if (secondNum.Length > 13)
            {
                return;
            }
            else if (but.Text == "0" && secondNum == "0")
            {
                return;
            }
            if (but.Text == "," && !secondNum.Contains(",") && !secondNum.Contains("."))
            {
                if (secondNum == "" || secondNum == "0")
                {
                    secondNum = "0,";
                }
                else
                {
                    secondNum += ",";
                }
            }
            else if (but.Text != ",")
            {
                if (secondNum == "0")
                {
                    secondNum = "";
                }
                secondNum += but.Text;
            }
            Res = secondNum;
            Calc = firstNum + sign;
        }
    }

    void OnOperationClicked(object sender, EventArgs args)
    {
        if (Calc.Length > 0 && Calc[^1].ToString() == "=")
        {
            secondNum = "";
            sign = "";
        }
        Button but = new();
        but = (Button)sender;
        if (sign == "" && secondNum == "")
        {
            sign += but.Text;
            if (firstNum == "")
            {
                firstNum = "0";
            }
            Calc = firstNum + sign;
            return;
        }
        else if (sign != "" && secondNum == "")
        {
            if (sign != but.Text)
            {
                sign = but.Text;
                Calc = firstNum + sign;
                return;
            }
            else
            {
                return;
            }
        }
        else
        {
            firstNum = Calculate();
            sign = but.Text;
            secondNum = "";
            Res = firstNum;
            Calc = firstNum + sign;
        }
    }

    string Calculate()
    {
        if (secondNum != "" && sign != "")
        {
            lastNum = secondNum;
            lastSign = sign;
        }
        try
        {
            TryParse(firstNum, out double first);
            TryParse(secondNum, out double second);
            double result = 0;
            switch (sign)
            {
                case "+":
                    result = Math.Round(first + second, 3);
                    break;
                case "-":
                    result = Math.Round(first - second, 3);
                    break;
                case "×":
                    result = Math.Round(first * second, 3);
                    break;
                case "÷":
                    if (second == 0)
                    {
                        Error("Деление на 0!");
                        Calc = "";
                        Res = "0";
                        firstNum = "";
                        secondNum = "";
                        sign = "";

                        return null;
                    }
                    result = Math.Round(first / second, 3);
                    break;
            }
            return result.ToString();
        }
        catch (OverflowException)
        {
            Error("Переполнение типа double!");
            Calc = "";
            Res = "0";
            firstNum = "";
            secondNum = "";
            sign = "";

            return null;
        }
    }
    static readonly CultureInfo ru = CultureInfo.GetCultureInfo("ru-RU");
    bool TryParse(string input, out double result)
    {
        var @decimal = NumberStyles.AllowDecimalPoint | NumberStyles.AllowLeadingSign | NumberStyles.AllowLeadingWhite | NumberStyles.AllowTrailingWhite;
        return double.TryParse(input, @decimal, CultureInfo.InvariantCulture, out result) ||
            double.TryParse(input, @decimal, ru, out result);
    }


    void OnMCclicked(object sender, EventArgs args)
    {
        DisableButtons();
        memory = "";
    }

    void OnMRclicked(object sender, EventArgs args)
    {
        if (sign != "" && secondNum == "")
        {
            secondNum = memory;
            Res = secondNum;
            Calc = firstNum + sign;
        }
        else if(sign == "" && secondNum == "")
        {
            firstNum = memory;
            Res = firstNum;
            Calc = "";
        }else if(sign != "" && secondNum != "")
        {
            secondNum = memory;
            Res = secondNum;
        }
        else
        {
            firstNum = memory;
            Res = firstNum;
        }
    }

    void OnMPlusClicked(object sender, EventArgs args)
    {
        if (Calc.Length > 1 && Calc[^1].ToString() == "=")
        {
            TryParse(memory, out double buf);
            TryParse(firstNum, out double buf_2);
            memory = Math.Round((buf + buf_2), 3).ToString();
            secondNum = "";
            sign = "";
            Calc = "";
        }
        else if (secondNum == "" && firstNum == "")
        {
            return;
        }else if(secondNum == "" && firstNum != "")
        {             
            TryParse(memory, out double buf);
            TryParse(firstNum, out double buf_2);
            memory = Math.Round((buf + buf_2), 3).ToString();
        }
        else
        {
            TryParse(memory, out double buf);
            TryParse(secondNum, out double buf_2);
            memory = Math.Round((buf + buf_2), 3).ToString();
        }
    }

    void OnMMinusClicked(object sender, EventArgs args)
    {
        if (Calc.Length > 1 && Calc[^1].ToString() == "=")
        {
            TryParse(memory, out double buf);
            TryParse(firstNum, out double buf_2);
            memory = Math.Round((buf - buf_2), 3).ToString();
            secondNum = "";
            sign = "";
            Calc = "";
        }
        else if (secondNum == "" && firstNum == "")
        {
            return;
        }
        else if (secondNum == "" && firstNum != "")
        {
            TryParse(memory, out double buf);
            TryParse(firstNum, out double buf_2);
            memory = Math.Round((buf - buf_2), 3).ToString();
        }
        else
        {
            TryParse(memory, out double buf);
            TryParse(secondNum, out double buf_2);
            memory = Math.Round((buf - buf_2), 3).ToString();
        }
    }

    void EnableButtons()
    {
        MemoryValue.IsEnabled = true;
        MRbutton.IsEnabled = true;
        MCbutton.IsEnabled = true;
    }

    void DisableButtons()
    {
        MemoryValue.IsEnabled = false;
        MRbutton.IsEnabled = false;
        MCbutton.IsEnabled = false;
    }
    void OnMSclicked(object sender, EventArgs args)
    {
        if (Calc.Length > 1 && Calc[^1].ToString() == "=")
        {
            memory = firstNum;
            secondNum = "";
            sign = "";
            Calc = "";
        }       
        else if (sign == "" || secondNum == "")
        {
            if (firstNum == "0")
            {
                return;
            }
            memory = firstNum;

        }
        else
        {
            if (secondNum == "0")
            {
                return;
            }
            memory = secondNum;
        }
        EnableButtons();
        memoryNotEmpty = true;
    }

    async void OnMMenuClicked(object sender, EventArgs args)
    {
        await DisplayAlert("Число в памяти: ", memory , " ОK");
    }

    async public void Error(string str)
    {
        await DisplayAlert("Ошибка ", str, " ОK");
    }

    void OnPercentClicked(object sender, EventArgs args)
    {
        if (sign == "" && secondNum == "" && firstNum != "")
        {
            Res = "0";
            firstNum= "0";
        }
        else if(secondNum == "" && firstNum != "" && sign != "")
        {
            TryParse(firstNum, out double buf);
            secondNum = Math.Round((buf * buf / 100), 3).ToString();
            Res = secondNum;
            Calc = firstNum + sign + secondNum;
        }
        else if(secondNum != "" && firstNum != "" && sign != "" && Calc.Length > 1 && Calc[^1].ToString() == "=")
        {
            TryParse(firstNum, out double buf);
            firstNum = Math.Round((buf * buf / 100), 3).ToString();
            Res = firstNum;
            Calc = firstNum;
        }
        else if (secondNum != "" && firstNum != "" && sign != "")
        {
            TryParse(firstNum, out double buf);
            TryParse(secondNum, out double buf_2);

            secondNum = Math.Round((buf * buf_2 / 100), 3).ToString();
            Res = secondNum; Calc = firstNum + sign + secondNum;
        }
    }

    void OnCEclicked(object sender, EventArgs args)
    {
        firstNum = "";
        secondNum = "";
        sign = "";
        Calc = "";
        Res = "0";
    }

    void OnCclicked(object sender, EventArgs args)
    {
        firstNum = "";
        secondNum = "";
        sign = "";
        Calc = "";
        Res = "0";
    }

    void OnDelClicked(object sender, EventArgs args)
    {
        if (sign == "")
        {
            if (firstNum != null && firstNum.Length <= 1)
            {
                firstNum = "0";
                Res = "0";
                return;
            }
            else
            {
                firstNum = firstNum[..^1];
                Res = firstNum;
                return;
            }
        }
        else if (sign != "")
        {
            if (Calc.Length > 1 && Calc[^1].ToString() == "=")
            {
                Calc = "";
                secondNum = "";
                return;
            }
            if (secondNum.Length <= 1)
            {
                secondNum = "0";
                Res = "0";
                return;
            }
            else
            {
                secondNum = secondNum[..^1];
                Res = secondNum;
                return;
            }
        }

        return;
    }

    void OnCircleSquareClicked(object sender, EventArgs args)
    {
        if (sign == "" && secondNum == "" && firstNum != "")
        {
            TryParse(firstNum, out double buf);
            firstNum = Math.Round((3.1415 * buf * buf), 3).ToString();
            Res = firstNum;
        }
        else if (secondNum == "" && firstNum != "" && sign != "")
        {
            TryParse(firstNum, out double buf);
            secondNum = Math.Round((buf * buf * 3.1415), 3).ToString();
            Res = secondNum;
            Calc = firstNum + sign + secondNum;
        }
        else if (secondNum != "" && firstNum != "" && sign != "" && Calc.Length > 1 && Calc[^1].ToString() == "=")
        {
            TryParse(firstNum, out double buf);
            firstNum = Math.Round((buf * buf * 3.14), 3).ToString();
            Res = firstNum;
            Calc = firstNum;
        }
        else if (secondNum != "" && firstNum != "" && sign != "")
        {
            TryParse(secondNum, out double buf);

            secondNum = Math.Round((buf * buf * 3.1415), 3).ToString();
            Res = secondNum; Calc = firstNum + sign + secondNum;
        }
    }

    void OnSquareClicked(object sender, EventArgs args)
    {
        if (sign == "" && secondNum == "" && firstNum != "")
        {
            TryParse(firstNum, out double buf);
            Calc = firstNum + "*" + firstNum;
            firstNum = Math.Round((buf * buf), 3).ToString();
            Res = firstNum;
        }
        else if (secondNum == "" && firstNum != "" && sign != "")
        {
            Calc = firstNum + sign + firstNum + "*" + firstNum;
            TryParse(firstNum, out double buf);
            secondNum = Math.Round((buf * buf), 3).ToString();
            Res = secondNum;
        }
        else if (secondNum != "" && firstNum != "" && sign != "" && Calc.Length > 1 && Calc[^1].ToString() == "=")
        {
            Calc = firstNum + "*" + firstNum;
            TryParse(firstNum, out double buf);
            firstNum = Math.Round((buf * buf), 3).ToString();
            Res = firstNum;
            secondNum = "";
            sign = "";
        }
        else if (secondNum != "" && firstNum != "" && sign != "")
        {
            Calc = firstNum + sign + secondNum + "*" + secondNum;
            TryParse(secondNum, out double buf_2);
            secondNum = Math.Round((buf_2 * buf_2), 3).ToString();
            Res = secondNum;
        }
    }

    void OnSqrtClicked(object sender, EventArgs args)
    {
        if (sign == "" && secondNum == "" && firstNum != "")
        {
            TryParse(firstNum, out double buf);
            Calc = "√" + firstNum;
            firstNum = Math.Round(Math.Sqrt(buf), 3).ToString();
            Res = firstNum;
        }
        else if (secondNum == "" && firstNum != "" && sign != "")
        {
            Calc = firstNum + sign + "√" + firstNum ;
            TryParse(firstNum, out double buf);
            secondNum = Math.Round(Math.Sqrt(buf), 3).ToString();
            Res = secondNum;
        }
        else if (secondNum != "" && firstNum != "" && sign != "" && Calc.Length > 1 && Calc[^1].ToString() == "=")
        {
            Calc = "√" + firstNum;
            TryParse(firstNum, out double buf);
            firstNum = Math.Round(Math.Sqrt(buf), 3).ToString();
            Res = firstNum;
            secondNum = "";
            sign = "";
        }
        else if (secondNum != "" && firstNum != "" && sign != "")
        {
            Calc = firstNum + sign + "√" + secondNum;
            TryParse(secondNum, out double buf_2);
            secondNum = Math.Round(Math.Sqrt(buf_2), 3).ToString();
            Res = secondNum;
        }
    }

    void OnChangeSignClicked(object sender, EventArgs args)
    {
        if (sign == "" && secondNum == "" && firstNum != "")
        {
            if (firstNum[0].ToString() == "-")
            {
                firstNum = firstNum[1..];
            }
            else
            {
                firstNum = "-" + firstNum;
            }
            Res = firstNum;
        }
        else if (secondNum == "" && firstNum != "" && sign != "")
        {
            Calc = firstNum + sign + "neg(" + firstNum + ")";
            if (firstNum[0].ToString() == "-")
            {
                secondNum = firstNum[1..];
            }
            else
            {
                secondNum = "-" + firstNum;
            }
            Res = secondNum;
        }
        else if (secondNum != "" && firstNum != "" && sign != "" && Calc.Length > 1 && Calc[^1].ToString() == "=")
        {
            Calc = "neg(" + firstNum + ")";
            if (firstNum[0].ToString() == "-")
            {
                firstNum = firstNum[1..];
            }
            else
            {
                firstNum = "-" + firstNum;
            }
            Res = firstNum;
            secondNum = "";
            sign = "";
        }
        else if (secondNum != "" && firstNum != "" && sign != "")
        {
            Calc = firstNum + sign;
            if (secondNum[0].ToString() == "-")
            {
                secondNum = secondNum[1..];
            }
            else
            {
                secondNum = "-" + secondNum;
            }
            Res = secondNum;
        }
    }

    void OnEqualClicked(object sender, EventArgs args)
    {
        if (secondNum == "" && sign != "")
        {
            secondNum = firstNum;
            Res = Calculate();
            Calc = firstNum + sign + secondNum + "=";
            firstNum = Res;
        }
        else if (Calc.Length > 0 && Calc[^1].ToString() == "=")
        {
            Res = Calculate();
            Calc = firstNum + sign + secondNum + "=";
            firstNum = Res;
        }
        else if (firstNum != "" && secondNum != "")
        {
            Res = Calculate();
            Calc = firstNum + sign + secondNum + "=";
            firstNum = Res;
        }

    }
}