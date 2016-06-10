//adds classes for step boxes on Prevention Planning Overview page
jQuery(function ($) {
    $(document).ready(function () {
        $('div.box').filter(function (index) {
            $(this).removeClass('box').addClass('box-' + index);
        })
    });
});