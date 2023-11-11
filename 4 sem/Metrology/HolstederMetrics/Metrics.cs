using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Text.RegularExpressions;

namespace HolstederMetrics
{
    public class Metrics
    {
        public static Dictionary<string, int> GetUniqueOperators(string filePath)
        {
            var uniqueOperators = new Dictionary<string, int>();
            var operatorsRegex = new Regex("[+\\-*\\%&|^=!<>\\?]+");

            using (var reader = new StreamReader(filePath))
            {
                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var matches = operatorsRegex.Matches(line);

                    foreach (Match match in matches)
                    {
                        var operatorName = match.Value;

                        if (uniqueOperators.ContainsKey(operatorName))
                        {
                            uniqueOperators[operatorName]++;
                        }
                        else
                        {
                            uniqueOperators[operatorName] = 1;
                        }
                    }
                }
            }
            return uniqueOperators;
        }

        public static Dictionary<string, int> GetOperandsDictionary(string filePath)
        {
            // Словарь для хранения операндов и их количества в программе
            Dictionary<string, int> operands = new Dictionary<string, int>();

            // Регулярное выражение для поиска операндов
            var operandsRegex = new Regex(@"\b[\w\d]+\b");

            // Открываем файл и читаем его содержимое
            string fileContent = File.ReadAllText(filePath);

            // Ищем все операнды в файле и добавляем их в словарь
            foreach (Match match in operandsRegex.Matches(fileContent))
            {
                string operand = match.Value;
                if (!operands.ContainsKey(operand))
                {
                    operands.Add(operand, 1);
                }
                else
                {
                    operands[operand]++;
                }
            }

            return operands;
        }
    }
}
