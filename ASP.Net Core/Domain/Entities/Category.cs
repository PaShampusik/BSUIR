using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Domain.Entities
{
    public class Category
    {
        public int Id { get; set; }
        public string Name { get; set; } = string.Empty;
        public string NormalizedName { get; set; } = string.Empty;

		public List<Telescope> Telescopes { get; set; } = new();
	}
}
