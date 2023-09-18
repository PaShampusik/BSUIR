using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Domain.Entities
{
    public class Telescope
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
        public Category? Category{ get; set; }
        public int FocusLength {  get; set; }       
        public string? img {  get; set; }
        public string mime { get; set; } 
    }
}
