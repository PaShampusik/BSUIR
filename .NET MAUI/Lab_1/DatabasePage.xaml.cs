namespace Lab_1;
using Lab_1.Services;
using Lab_1.Entities;
using SQLite;
using System.ComponentModel;
using System.Runtime.CompilerServices;

public partial class DatabasePage : ContentPage, INotifyPropertyChanged
{
    public event PropertyChangedEventHandler? PropertyChanged;
    protected override void OnPropertyChanged([CallerMemberName] string propertyName = "")
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }

    SQLiteService service;

    List<Author> authors;
    List<Book> books;
    public List<Author> Authors
    {
        get => authors;
        set
        {
            if (value == authors) return;
            authors = value;
            OnPropertyChanged();
        }
    }
    public List<Book> Books
    {
        get => books;
        set
        {
            if (value == books) return;
            books = value;
            OnPropertyChanged();
        }
    }
     
    public DatabasePage()
    {
        InitializeComponent();
        BindingContext = this;
        service = new SQLiteService();
        Authors = service.GetAllAuthors();
    }

    void ShowBooks(object sender, EventArgs e)
    {
        Picker but = new();
        but = (Picker)sender;
        if (but.SelectedIndex != -1)
        {
            Books = service.GetAuthorBooks(but.SelectedIndex);
        }
    }
}