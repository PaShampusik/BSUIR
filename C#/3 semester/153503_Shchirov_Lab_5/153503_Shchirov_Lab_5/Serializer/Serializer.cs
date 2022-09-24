
using _153503_Shchirov_Lab_5.Domain.Entities;
using System;
using System.Text.Json;
using System.Xml;
using System.Xml.Linq;
using System.Xml.Serialization;

namespace Serializer
{
    public class Serializer : _153503_Shchirov_Lab_5.Domain.Interfaces.ISerializer
    {
        public IEnumerable<Library> DeSerializeByLINQ(string fileName)
        {

            XDocument xdoc = XDocument.Load(fileName);
            var items = from xe in xdoc.Element("Libraries").Descendants("Library")
                        select new Library
                        {
                            Name = xe.Element("Name").Value,
                            Count = int.Parse(xe.Element("Count").Value)
                        };
            return items;
        }

        public IEnumerable<Library> DeSerializeByXML(string fileName)
        {
            XmlRootAttribute xRootnew = new XmlRootAttribute();
            xRootnew.ElementName = "Libraries";
            xRootnew.IsNullable = true;
            

            XmlSerializer xmlSerializer = new XmlSerializer(typeof(List<Library>), xRootnew);
            var resolver = new XmlUrlResolver();
            var settings = new XmlReaderSettings();
            settings.XmlResolver = resolver;
            using (XmlReader reader = XmlReader.Create(fileName, settings))
            {
                List<Library> libraries = xmlSerializer.Deserialize(reader) as List<Library>;
                return libraries;
            }
        }

        public IEnumerable<Library> DeSerializeJSON(string fileName)
        {
            string json = File.ReadAllText(fileName);
            return JsonSerializer.Deserialize<IEnumerable<Library>>(json);
        }

        public void SerializeByJSON(IEnumerable<Library> lib, string fileName)
        {
            string json = JsonSerializer.Serialize(lib);
            Console.WriteLine(json);
            if (File.Exists(fileName))
            {
                File.Delete(fileName);
            }
            else
            {
                File.Create(fileName);
            }
            File.WriteAllText(fileName, json);
        }

        public void SerializeByLINQ(IEnumerable<Library> lib, string fileName)
        {
            var xml_output = from library in lib
                             select new XElement("Library",
                             new XElement("Name", library.Name),
                             new XElement("Count", library.Count));
            var xml = new XElement("Libraries", xml_output);
        }
        

        public void SerializeByXML(IEnumerable<Library> lib, string fileName)
        {
            XmlSerializer xmlSerializer = new XmlSerializer(typeof(List<Library>), new XmlRootAttribute("Libraries")) ;
            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;
            settings.OmitXmlDeclaration = false;
            using (XmlWriter writer = XmlWriter.Create(fileName, settings))
            {
                xmlSerializer.Serialize(writer, lib);
            }
        }
    }
}