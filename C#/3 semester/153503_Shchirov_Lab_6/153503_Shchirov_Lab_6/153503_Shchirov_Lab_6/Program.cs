using _153503_Shchirov_Lab_6.Entities;
using System.Reflection;
using _153503_Shchirov_Lab_6.Interfaces;

class Program {
    static void Main(string[] args)
    {
        List<Employee> employees = new List<Employee>();

        employees.Add(new Employee("Ivan", true, 25));
        employees.Add(new Employee("Maria", false, 30));
        employees.Add(new Employee("Pavel", true, 19));
        employees.Add(new Employee("Sasha", true, 24));
        employees.Add(new Employee("Anastasia", false, 23));


        Assembly asm = Assembly.LoadFrom("CLassLibrary.dll");       
        Type type = asm.GetType("CLassLibrary.Entities.FileService");
        if (type is not null)
        {
            MethodInfo? save = type.GetMethod("SaveData");
            save = save.MakeGenericMethod(typeof(Employee));
            MethodInfo? read = type.GetMethod("ReadFile")
                .MakeGenericMethod(typeof(Employee));
            if (save is not null && read is not null)
            {
                save.Invoke(Activator.CreateInstance(type), new object[] { employees, "employees.json" });
                var result = read.Invoke(Activator.CreateInstance(type), new object[] { "employees.json" });
                Console.WriteLine("----------------------------------\n READED DATA:");
                foreach (var item in (IEnumerable<Employee>)result)
                {
                    Console.WriteLine(item.Name + "    " + item.Male + "     " + item.Age);
                }
            }
        }
    }
}
