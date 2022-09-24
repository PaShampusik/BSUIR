using _153503_Shchirov_Lab_5.Domain.Entities;

class Progam
{
    static void Main(string[] args)
    {
        List<Library> lib = new List<Library>();
        lib.Add(new Library("Science", 100));
        lib.Add(new Library("Math", 200));
        lib.Add(new Library("Physics", 300));
        lib.Add(new Library("Chemistry", 400));
        lib.Add(new Library("Biology", 500));
        lib.Add(new Library("History", 600));
        lib.Add(new Library("Geography", 700));
        




        Serializer.Serializer serializer = new Serializer.Serializer();
        serializer.SerializeByJSON(lib, "test.json");

        serializer.SerializeByLINQ(lib, "test_with_linq.xml");

        //serializer.SerializeByXML(lib, "test.xml");

        Console.WriteLine("------------------------------------------------------------------------");

        Console.WriteLine("READED FILES:");

        Console.WriteLine("JSON:");
        foreach (var item in serializer.DeSerializeJSON("test.json"))
        {
            Console.WriteLine(item.Name + " " + item.Count);
        }
        Console.WriteLine("------------------------------------------------------------------------");
        Console.WriteLine("XML:");
        foreach (var item in serializer.DeSerializeByXML("test.xml"))
        {
            Console.WriteLine(item.Name + " " + item.Count);
        }
        Console.WriteLine("------------------------------------------------------------------------");

        
        Console.WriteLine("XML with LINQ:");
        foreach (var item in serializer.DeSerializeByXML("test_with_linq.xml"))
        {
            Console.WriteLine(item.Name + " " + item.Count);
        }
        Console.WriteLine("------------------------------------------------------------------------");

    }
}