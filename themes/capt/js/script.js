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
    /**
     *  Responsive Show - Hides
     */
    var iPh6H = 375;
    var iPh6W = 667;
    var imagePath = '../../../sites/captconnect.edc.org/themes/capt/images/';
    var why_reg_heights = ['207','140','34'] 
    // laptop, mobile-expanded, mobile-compact

    // function for toggling a panel on click of header
    function togglePanel(header, body, panel, compact, expanded)
    {
      var mql = window.matchMedia("screen and (max-width:"+iPh6W+"px");
       if (mql.matches)
       {
          switch($(body).css('display')) {
          case 'none':
          $(body).show();
          $(header).css('backgroundImage','url('+imagePath+'icons/hide.png)');
          if (arguments.length == 5) $(panel).css('height',expanded);

          break;

          default: 
          $(body).hide();
          $(header).css('backgroundImage','url('+imagePath+'icons/show.png)');
          if (arguments.length == 5) $(panel).css('height',compact);

          break;
        }
      }
    }
    /**
     * Click Listeners
     */
    $('#page-title').click(function () {
         togglePanel('#page-title','#user-login');
    });
    $('#block-block-8 h2.block-title').click(function () {
          togglePanel('#block-block-8 h2.block-title', '#block-block-8 div.panel-body')
    });
      $('#block-block-9 h2.block-title').click(function () {
          togglePanel('#block-block-9 h2.block-title', 
                      '#block-block-9 div.panel-body',
                      '#block-block-9',
                       why_reg_heights[2],
                       why_reg_heights[1])
        
    });
    // reset if resizing browser 
      $(window).resize(function(){
          panel_respond('#page-title','#user-login');

          panel_respond('#block-block-8 h2.block-title',
                        '#block-block-8 div.panel-body');

          panel_respond('#block-block-9 h2.block-title',
                        '#block-block-9 div.panel-body',
                        '#block-block-9',
                        '207px',
                        why_reg_heights[1]);

      });

    // reset panel 
    function panel_respond(header, body, panel, laptop_height, mobile_height)
    {

          var min = iPh6W+1;
          var mql = window.matchMedia("screen and (min-width:"+min+"px");
          if (mql.matches)
          {  
            // laptop
            if ($(body).css('display') == 'none') $(body).show();
              $(header).css('backgroundImage','none');
  
              if (arguments.length == 5)
                 $(panel).css('height',laptop_height)
          }
          else
          {
            // mobile
            if ($(body).css('backgroundImage') == 'none') {
              $(header).css('backgroundImage','url('+imagePath+'icons/hide.png)');
           
                if (arguments.length == 5)
                $(panel).css('height',mobile_height)

            }

          }
    }

    

  
    // Print to console log
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
    
    
    
    
    // Reduce height of the surrounding divs for scaled notification previews
    $('.form-field-type-markup .views-field-field-email-body > div > div > table').each(function(){
      var height = $(this).height();
      cl(height); // Becomes 0 because of the collapsed fieldsets... need to fix
      $(this).parent().css('height', height*.75);
    });
    
    
    
    // Add user registration using exposed entityform in the event-specific registrations view
    $entityform = $('.view-registrations #add-user-registration-entityform-edit-form');
    $entityformInstance = $entityform.find('#edit-field-entityform-instance');
    $entityformUser = $entityform.find('#edit-field-entityform-user');
    
    $entityformUser.hide();
    
    $entityformInstance.find('select').on('change', function(){
      
      var instanceNID;
      var userUID;
      
      $entityformUser.find('option[value="_none"]').prop('selected',true);

      if ($(this).find('option:selected').val() != '_none') {
        instanceNID = $(this).val();
        $entityformUser.show();
      }
      else {
        $entityformUser.hide();
      }
        
      
    });
    
    
    
    
    // Limit default template options and hide notification fields if "Do not send this type of notification" selected
    
    var subject = '';
    var body = '';
    
    $('#event-notifications-node-form .form-field-type-entityreference').each(function(){
      
      // Store the contents of the fieldset in a variable
      var $notificationForm = $(this).children('div').children('fieldset');
      
      // Get the "do not send this type of notification" checkbox
      var $preventCheckbox = $notificationForm.find('.field-name-field-prevent-notification');
      
      // Hide fieldset contents if "do not send this type of notification" is checked when form is loaded
      if ($preventCheckbox.find('input').prop('checked')) {
        $notificationForm.children('.fieldset-wrapper').children('.form-wrapper').children('div').each(function(){
          $(this).css('display','none');
        });
        $preventCheckbox.css('display','block');
      }
      
      // Show or hide fieldset contents if "do not send this type of notification" checkbox is changed
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
      
      // Limit the available default templates to those that fit the type of notification, based on taxonomy
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
    
    $('#user-profile-form .group-account, #user-profile-form .group-contact-information, #user-profile-form .group-demographic-information').each(function(){
      
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
