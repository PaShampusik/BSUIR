using SQLite;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_1.Entities
{
    [Table("Books")]
    public class Book
    {
        [PrimaryKey, AutoIncrement, Indexed]
        [Column("Id")]
        public int BookId { get; set; }
        public string Name { get; set; }
        public int Age { get; set; }
        [Indexed]
        public int AuthorId { get; set; }
    }
}
