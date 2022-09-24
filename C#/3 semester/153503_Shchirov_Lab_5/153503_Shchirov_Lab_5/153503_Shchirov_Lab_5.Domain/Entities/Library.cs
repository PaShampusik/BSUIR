using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace _153503_Shchirov_Lab_5.Domain.Entities
{
    [Serializable, XmlRoot("Library")]
    public class Library : Book_Depository
    {
        private Book_Depository depository = new Book_Depository();
        [XmlElement("Name")]
        public string Name { get; set; } = "Library";
        [XmlElement("Count")]
        public int Count { get; set; } = 0;

        public Library(string name, int count)
        {
            depository.Name = name;
            depository.Count = count;
            Name = name;
            Count = count;
        }
        public Library()
        {
            
        }
        public void AddDepository(string name, int count)
        {
            depository.Name = name;
            depository.Count = count;
        }
        
        public IEnumerable<Book_Depository> GetDepository()
        {
            yield return depository;
        }
        public override string ToString()
        {
            return $"{depository.Name} {depository.Count}";           
        }

        public IEnumerable<Library> GetLibrary()
        {
            yield return this;
        }
    }
}
