using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab_1.Entities;

namespace Lab_1.Services
{
    public interface IRateService
    {
        IEnumerable<Rate> GetRates(DateTime date);       
    }

}
