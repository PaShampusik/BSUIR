using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _153503_Shchirov_Lab_5.Domain.Entities;

namespace _153503_Shchirov_Lab_5.Domain.Interfaces
{
    public interface ISerializer
    {
        IEnumerable<Library> DeSerializeByLINQ(string fileName);
        IEnumerable<Library> DeSerializeByXML(string fileName);
        IEnumerable<Library> DeSerializeJSON(string fileName);

        void SerializeByLINQ(IEnumerable<Library> lib, string filenNane);
        void SerializeByXML(IEnumerable<Library> lib, string filenNane);
        void SerializeByJSON(IEnumerable<Library> lib, string filenNane);
    }
}
