using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using API.Data;
using Domain.Entities;
using Domain.Models;
using API.Services;
using Microsoft.AspNetCore.Authorization;

namespace API.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class TelescopesController : ControllerBase
    {
        private readonly ITelescopeService _service;

        public TelescopesController(ITelescopeService service)
        {
            _service = service;
        }

        [HttpGet("{category?}/{pageNo:int?}/{pagesize:int?}")]
        public async Task<ActionResult<ResponseData<List<Telescope>>>> GetTelescopes(string? category,
            int pageNo = 1, int pageSize = 3)
        {
            return Ok(await _service.GetTelescopesListAsync(category, pageNo, pageSize));
        }

        // GET: api/Telescopes/5
        [HttpGet("{id:int}")]
        public async Task<ActionResult<ResponseData<Telescope>>> GetTelescopes(int id)
        {
            return Ok(await _service.GetTelescopesByIdAsync(id));
        }

        // PUT: api/Telescopes/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("{id:int}")]
        [Authorize]
        public async Task<ActionResult<ResponseData<Telescope>>> PutTelescopes(int id, Telescope telescopes)
        {
            try
            {
                await _service.UpdateTelescopesAsync(id, telescopes);
            }
            catch (Exception e)
            {
                return NotFound(new ResponseData<Telescope>()
                {
                    Data = null,
                    Success = false,
                    ErrorMessage = e.Message
                });
            }

            return Ok(new ResponseData<Telescope>()
            {
                Data = telescopes,
            });
        }

        // POST: api/Clothes
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        public async Task<ActionResult<ResponseData<Telescope>>> PostTelescopes(Telescope telescopes)
        {
            if (telescopes is null)
            {
                return BadRequest(new ResponseData<Telescope>()
                {
                    Data = null,
                    Success = false,
                    ErrorMessage = "Telescopes is null"
                });
            }
            var response = await _service.CreateTelescopesAsync(telescopes);

            if (!response.Success)
            {
                return BadRequest(response.ErrorMessage);
            }

            return CreatedAtAction("GetTelescopes", new { id = telescopes.Id }, new ResponseData<Telescope>()
            {
                Data = telescopes
            });
        }

        // DELETE: api/Clothes/5
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteTelescopes(int id)
        {
            try
            {
                await _service.DeleteTelescopesAsync(id);
            }
            catch (Exception e)
            {
                return NotFound(new ResponseData<Telescope>()
                {
                    Data = null,
                    Success = false,
                    ErrorMessage = e.Message
                });
            }

            return NoContent();
        }

        // POST: api/Dishes/5
        [HttpPost("{id}")]
        [Authorize]
        public async Task<ActionResult<ResponseData<string>>> PostImage(int id, IFormFile formFile)
        {
            var response = await _service.SaveImageAsync(id, formFile);
            if (response.Success)
            {
                return Ok(response);
            }
            return NotFound(response);
        }
        private bool TelescopeExists(int id)
        {
            return _service.GetTelescopesByIdAsync(id).Result.Success;
        }
    }
}
