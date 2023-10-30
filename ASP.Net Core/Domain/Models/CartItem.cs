using Domain.Entities;

namespace Domain.Models;
public class CartItem
{
    public Telescope Telescope { get; set; }
    public int Quantity { get; set; }
}