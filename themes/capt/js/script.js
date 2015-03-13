/**
 * @file
 * A JavaScript file for the theme.
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
Drupal.behaviors.my_custom_behavior = {
  attach: function(context, settings) {

    function cl(thing){
      if(typeof(console) !== 'undefined' && console != null){
        console.log(thing);
      }
    }
    
    // Remove later on... this is just for theme dev
    if(!(($('body').hasClass('role-administrator')) || ($('body').hasClass('role-event-creator')))) {
      $('ul.primary').remove();
      $('.field-name-add-a-date').remove();
      $('.field-name-add-a-presenter').remove();
    }
    
    
    
    // (1) Hide notification fields if "Do not send this type of notification" selected; (2) limit default template options
    
    var subject = '';
    var body = '';
    
    $('.group-notifications .form-field-type-entityreference').each(function(){
      
      var $notificationForm = $(this).children('div').children('fieldset');
      
      var $preventCheckbox = $notificationForm.find('.field-name-field-prevent-notification');
      
      if ($preventCheckbox.find('input').prop('checked')) {
        $notificationForm.children('.fieldset-wrapper').children('.form-wrapper').children('div').each(function(){
          $(this).css('display','none');
        });
        $preventCheckbox.css('display','block');
      }
      
      $preventCheckbox.find('input').change(function(){
        if (this.checked) {
          $notificationForm.children('.fieldset-wrapper').children('.form-wrapper').children('div').each(function(){
            $(this).css('display','none');
          });
          $preventCheckbox.css('display','block');
        }
        else {
          $notificationForm.children('.fieldset-wrapper').children('.form-wrapper').children('div').each(function(){
            $(this).css('display','block');
          });
        }
        
      });
      
      $notificationForm.find('.field-name-field-use-a-default-template select option').each(function(){
        var optionValue = $(this).text().trim();
        var optionCategory = optionValue.split('|');
        var notificationLabel = $notificationForm.children('legend').text().trim();
        
        if ((optionCategory[0] != notificationLabel) && (optionCategory[0] != '- None -')) {
          $(this).remove();
        }
        else {
          $(this).text(optionCategory[0]);
        }
        
      });
      
      
      
    });
    
    

  
    
    
    // Click to edit sections of the profile
    
    var saveButton = $('#user-profile-form input[value="Save"]').parent().html();
    $('#user-profile-form input[value="Save"]').addClass('real').css('display','none');
    
    $('#user-profile-form .group-account, #user-profile-form .group-profile').each(function(){
      
      var formData = '';
      var $section = $(this);
      var $dataView = $('<div class="data-view">');
      var $formFields = $section.children('.fieldset-wrapper');
      var $editButton = $('<div class="edit-button" style="font-weight:bold; float: right;">EDIT</div>');
            
      $section.find('.form-item').each(function(){
        
        if ($(this).hasClass('form-type-textfield')) {
          var $label = $(this).find('label');
          var $input = $(this).find('input');
          formData = formData + '<div class="item"><span class="label">' + $label.text() + ': </span><span class="value">' + $input.val() + '</span></div>';
        }

        
      });
      
      $(formData).appendTo($dataView);      
      $section.children('legend').after($dataView).after($editButton);
      $formFields.css('display','none').append(saveButton);
      
      $formFields.children('input[value="Save"]').on('click', function(){
        $('.real').trigger('click');
      });
      
      $section.find('.edit-button').on('click',function(){
        
        $formFields.toggle();
        $section.find('.data-view').toggle();
        
      });

      
      
    });
    
    
    
    

  }
};


})(jQuery, Drupal, this, this.document);
