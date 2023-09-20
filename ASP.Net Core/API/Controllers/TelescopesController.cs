using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using API.Data;
using Domain.Entities;

namespace API.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class TelescopesController : ControllerBase
    {
        private readonly AppDbContext _context;

        public TelescopesController(AppDbContext context)
        {
            _context = context;
        }

        // GET: api/Telescopes
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Telescope>>> GetTelescopes()
        {
          if (_context.Telescopes == null)
          {
              return NotFound();
          }
            return await _context.Telescopes.ToListAsync();
        }

        // GET: api/Telescopes/5
        [HttpGet("{id}")]
        public async Task<ActionResult<Telescope>> GetTelescope(int id)
        {
          if (_context.Telescopes == null)
          {
              return NotFound();
          }
            var telescope = await _context.Telescopes.FindAsync(id);

            if (telescope == null)
            {
                return NotFound();
            }

            return telescope;
        }

        // PUT: api/Telescopes/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("{id}")]
        public async Task<IActionResult> PutTelescope(int id, Telescope telescope)
        {
            if (id != telescope.Id)
            {
                return BadRequest();
            }

            _context.Entry(telescope).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!TelescopeExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return NoContent();
        }

        // POST: api/Telescopes
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        public async Task<ActionResult<Telescope>> PostTelescope(Telescope telescope)
        {
          if (_context.Telescopes == null)
          {
              return Problem("Entity set 'AppDbContext.Telescopes'  is null.");
          }
            _context.Telescopes.Add(telescope);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetTelescope", new { id = telescope.Id }, telescope);
        }

        // DELETE: api/Telescopes/5
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteTelescope(int id)
        {
            if (_context.Telescopes == null)
            {
                return NotFound();
            }
            var telescope = await _context.Telescopes.FindAsync(id);
            if (telescope == null)
            {
                return NotFound();
            }

            _context.Telescopes.Remove(telescope);
            await _context.SaveChangesAsync();

            return NoContent();
        }

        private bool TelescopeExists(int id)
        {
            return (_context.Telescopes?.Any(e => e.Id == id)).GetValueOrDefault();
        }
    }
}
