// Please see documentation at https://docs.microsoft.com/aspnet/core/client-side/bundling-and-minification
// for details on configuring this project to bundle and minify static web assets.

// Write your JavaScript code.


$(document).ready(function () {
    $(document).on('click', '.page-link', function (e) {
        e.preventDefault();

        var url = $(this).data('ajax-url');
        var method = $(this).data('ajax-method');

        $.ajax({
            url: url,
            type: method,
            success: function (result) {
                /*$('#telescopes-container').html(result.telescopes);
                $('#pager-container').html(result.pager);*/
                $('#catalog').html(result);
            },
            error: function () {
                // Error handling for AJAX request
            }
        });
    });
});