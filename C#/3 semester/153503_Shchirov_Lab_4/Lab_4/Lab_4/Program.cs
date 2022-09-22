using Lab_4.Entities;
using Lab_4.Interfaces;
using Lab_4.Services;
using System;
using System.Runtime.ConstrainedExecution;

class Program
{
    public static void Main(string[] args)
    {
        FileService<SuperHeroes> fileService = new FileService<SuperHeroes>();
        try
        {
            System.IO.FileInfo fi0 = new System.IO.FileInfo("SuperHeroes.txt");
            if (fi0.Exists)
            {
                System.IO.File.Delete("SuperHeroes.txt");
            }
        }
        catch
        {
            Console.WriteLine("Error");
        }


        List<SuperHeroes> heroes = new List<SuperHeroes>();
        heroes.Add(new SuperHeroes("IronMan", 35, true));
        heroes.Add(new SuperHeroes("Hulk", 48, true));
        heroes.Add(new SuperHeroes("Tor", 765, false));
        heroes.Add(new SuperHeroes("Tanos", 20000, false));
        heroes.Add(new SuperHeroes("BlackPanther", 42, true));
        try
        {
            File.Create("Heroes.txt").Close();


            fileService.SaveData(heroes.AsEnumerable(), "Heroes.txt");

        }
        catch
        {
            Console.WriteLine("Error2");
        }

        try
        {
            string sourceFile = "Heroes.txt";
            // Create a FileInfo  
            System.IO.FileInfo fi = new System.IO.FileInfo(sourceFile);
            // Check if file is there  
            if (fi.Exists)
            {
                // Move file with a new name. Hence renamed.  
                System.IO.File.Move("Heroes.txt", "SuperHeroes.txt");
                Console.WriteLine("File Renamed.");
                System.IO.File.Delete("Heroes.txt");
            }
        }
        catch
        {

            Console.WriteLine("Error3");


        }

        //List<SuperHeroes> new_heroes = new List<SuperHeroes>();

        var new_heroes = fileService.ReadFile("SuperHeroes.txt");
        var comparer = new MyCustomComparer<SuperHeroes>();
        var buf = new_heroes.OrderBy(x => x, comparer);


        Console.WriteLine("----------------------------------------------------\nNew Collection: ");
        foreach (var item in buf)
        {
            Console.WriteLine(item + "\n");
        }
        Console.WriteLine("----------------------------------------------------\nOld Collection: ");
        foreach (var item in heroes)
        {
            Console.WriteLine(item + "\n");
        }
        Console.WriteLine("----------------------------------------------------");

    }
}