// Please see documentation at https://docs.microsoft.com/aspnet/core/client-side/bundling-and-minification
// for details on configuring this project to bundle and minify static web assets.

// Write your JavaScript code.


$(document).ready(function () {
    $(document).on('click', '.page-link', function (e) {
        e.preventDefault();

        var url = $(this).data('ajax-url');

        $('#catalog').load(url);
    });
});