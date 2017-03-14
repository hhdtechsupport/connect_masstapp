/**
 * @file
 * A JavaScript file for the custom module.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */

// JavaScript should be made compatible with libraries other than jQuery by
// wrapping it with an "anonymous closure". See:
// - https://drupal.org/node/1446420
// - http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth
(function ($, Drupal, window, document, undefined) {
// To understand behaviors, see https://drupal.org/node/756722#behaviors
Drupal.behaviors.my_custom_module_behavior = {
  attach: function(context, settings) {
    
    if($('.page-user-register').length > 0 || $('.page-admin-people-create').length > 0) {
      // CREATE NEW ACCOUNT Multipage

      // Toggles which heading to highlight when Prev or Next buttons clicked (see below))
      function paneToggle($paneLink) {
        $paneLink.parent().parent().find('.pane-item').each(function(){
          $(this).removeClass('active');
        });
        $paneLink.addClass('active');
      }
      // When page loads, trigger the first heading to highlight
      paneToggle($('.pane-1'));

      // Checks to make sure form fields are completed on the current pane
      function checkFields($pane) {

        $('.messages').remove();

        var errorsList = '';
        var errorsCount = 0;
        var requiredStatus = 0;

        $pane.find('.form-wrapper > .form-item > label, .form-wrapper > div > .form-item > label').each(function(){
          // Get label text
          var label = $(this).contents().filter(function() { return this.nodeType == 3; }).text().trim();
          // First check: required?
          if ($(this).find('span').text().trim() == '*' && $(this).closest('.form-wrapper').css('display') == 'block') {
            // Second check: "Other" field?
            if (label == 'Please specify') {
              $controllingField = $(this).parent().parent().parent().prev();
              if ($controllingField.hasClass('field-name-field-role') || $controllingField.hasClass('field-name-field-organizational-affiliation')) {
                if ($controllingField.hasClass('field-name-field-role')) {
                  labelPlus = ' (role through which you participate in CAPT services)';
                }
                if ($controllingField.hasClass('field-name-field-organizational-affiliation')) {
                  labelPlus = ' (primary focus of organization/agency)';
                }
                if ($controllingField.find('select').val() == 117 || $controllingField.find('select').val() == 20) {
                  // Check if there's a value in there
                  if ($(this).next('input').val() == '') {
                    errorsCount = errorsCount + 1;
                    errorsList += '<li class="messages__item">' + label + labelPlus + '</li>';
                  }
                }
              }
              else if ($controllingField.hasClass('field-name-field-tribal-affiliation')) {
                labelPlus = ' (tribal affiliation)';
                $controllingField.find('input[type="checkbox"]:checked').each(function(){
                  if ($(this).val() == 'Other') {
                    errorsCount = errorsCount + 1;
                    errorsList += '<li class="messages__item">' + label + labelPlus + '</li>';
                  }
                });
              }
            }
            else {
              // Third check: type of field?
              if ($(this).parent('div').hasClass('form-type-textfield') || $(this).parent('div').hasClass('form-type-password')) {
                // Fourth check: error?
                if (!$(this).next('input').val()) {
                  errorsCount = errorsCount + 1;
                  errorsList += '<li class="messages__item">' + label + '</li>';
                }
              }
              else if ($(this).parent('div').hasClass('form-type-select')) {
                if ($(this).next('select').val() == '_none') {
                  errorsCount = errorsCount + 1;
                  errorsList += '<li class="messages__item">' + label + '</li>';
                }
              }
              else if ($(this).parent('div').hasClass('form-type-radios')) {
                if (!$(this).next().find('input[type="radio"]:checked').val()) {
                  errorsCount = errorsCount + 1;
                  errorsList += '<li class="messages__item">' + label + '</li>';
                }
              }
              else if ($(this).parent('div').hasClass('form-type-checkboxes')) {
                if (!$(this).next().find('input[type="checkbox"]:checked').val()) {
                  errorsCount = errorsCount + 1;
                  errorsList += '<li class="messages__item">' + label + '</li>';
                }
              }
            }
          }
        });
        if (errorsCount > 0) {
          $('<div class="messages--error messages error"><h2 class="element-invisible">Error message</h2>The following fields are required: <ul class="messages__list"></ul></div>').insertAfter('#main-content');
          $('.messages__list').append(errorsList);
          $pane.next().find('.multipage-link-previous').click();
        }
      }

      // Action when Prev or Next buttons are clicked
      $('.multipage-pane').each(function(){
        var $pane = $(this);
        var paneNumber = $('.multipage-pane').index($pane) + 1;
        $(this).find('.multipage-controls-list input[type="button"]').each(function(){
          $(this).on('click',function(){
            if ($(this).hasClass('multipage-link-previous')) {
              paneToggle($('.pane-' + (paneNumber - 1).toString()));
            }
            else if ($(this).hasClass('multipage-link-next')) {
              paneToggle($('.pane-' + (paneNumber + 1).toString()));
              checkFields($pane);
            }
            scrollToLocation('main');
          });
        });
      });
      // ScrollToLocation function
      function scrollToLocation(id){
        /*if ($("#"+).offset() != undefined ) {
          $('html, body').animate({ scrollTop: $("#"+id).offset().top },'slow');
        }*/
        $('body').animate({ scrollTop: this.top },'slow');
      }
    }
  }
};

})(jQuery, Drupal, this, this.document);