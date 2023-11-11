using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab_1.Entities;
using SQLite;

namespace Lab_1.Services
{
    public class SQLiteService : IDbService
    {
        string databasePath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments), "DatabasePage.db");

        public SQLiteService()
        {
            var db = new SQLiteConnection(databasePath);
            db.DropTable<Author>();
            db.DropTable<Book>();
            Init();
        } 

        public List<Author> GetAllAuthors()
        {
            var db = new SQLiteConnection(databasePath);
            return db.Table<Author>().ToList();
        }

        public int GetAuthorId(string name)
        {
            var db = new SQLiteConnection(databasePath);
            return db.Table<Author>().Where(x => x.Name == name).FirstOrDefault().Id;
        }

        public List<Book> GetAuthorBooks(int id)
        {
            var db = new SQLiteConnection(databasePath);
            return db.Table<Book>().Where(x => x.AuthorId == id).ToList();
        }

        public void Init()
        {
            var db = new SQLiteConnection(databasePath);

            db.CreateTable<Author>();

            AddAuthor(db, "Ночная Абоба", "2007", 3);
            AddAuthor(db, "Александр Бах", "2006", 7);
            AddAuthor(db, "Олег Шиз", "2003", 4);

            db.CreateTable<Book>();

            AddBook(db, "451 Мандарин", 7, 1);
            AddBook(db, "2003. Конец", 6, 1);
            AddBook(db, "2003. Начало", 5, 1);
            AddBook(db, "Суровый 2008", 4, 1);
            AddBook(db, "1985", 3, 1);

            AddBook(db, "Красный Компот", 7, 2);
            AddBook(db, "Птица без Крыльев", 6, 2);
            AddBook(db, "Вжух", 5, 2);
            AddBook(db, "Иван Петрович", 4, 2);
            AddBook(db, "Тяжело", 3, 2);

            AddBook(db, "Как поесть", 7, 3);
            AddBook(db, "Пора Домой", 6, 3);
            AddBook(db, "Стул", 5, 3);
            AddBook(db, "Габон", 4, 3);
            AddBook(db, "Гибон", 3, 3);
        }

        public static void AddBook(SQLiteConnection db, string name, int age, int authorId)
        {
            var book = new Book()
            {
                Name = name,
                Age = age,
                AuthorId = authorId
            };
            db.Insert(book);
        }

        public static void AddAuthor(SQLiteConnection db, string name, string birth, int experience)
        {
            var author = new Author()
            {
                Name = name,
                BirthDate = birth,
                Experience = experience
            };
            db.Insert(author);
        }
    }
}
