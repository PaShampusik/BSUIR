using Lab_1.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Lab_1.Services
{
    public interface IDbService
    {
        List<Author> GetAllAuthors();
        List<Book> GetAuthorBooks(int id);
        void Init();
    }
}
