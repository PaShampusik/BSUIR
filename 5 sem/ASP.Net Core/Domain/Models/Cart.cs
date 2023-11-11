using Domain.Entities;

namespace Domain.Models;
public class Cart
{
    public Dictionary<int, CartItem> CartItems { get; set; } = new();

    public virtual void Add(Telescope telescope)
    {
        if (!CartItems.ContainsKey(telescope.Id))
        {
            CartItems.Add(telescope.Id, new CartItem() { Telescope = telescope, Quantity = 1 });
        }
        else
        {
            ++CartItems[telescope.Id].Quantity;
        }
    }

    public virtual void Remove(int id)
    {
        if (--CartItems[id].Quantity <= 0)
        {
            CartItems.Remove(id);
        }
    }

    public virtual void Clear()
    {
        CartItems.Clear();
    }

    public int Quantity => CartItems.Sum(item => item.Value.Quantity);

    public decimal TotalPrice => CartItems.Sum(item => item.Value.Telescope.Price * item.Value.Quantity);

}