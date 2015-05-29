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
    if ($('body').hasClass('role-anonymous-user'))
    {
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
    }
    // reset if resizing browser 
      $(window).resize(function(){
          var bclass = '.role-anonymous-user ';
          panel_respond(bclass + '#page-title','#user-login');

          panel_respond(bclass + '#block-block-8 h2.block-title',
                        bclass + '#block-block-8 div.panel-body');

          panel_respond(bclass + '#block-block-9 h2.block-title',
                        bclass + '#block-block-9 div.panel-body',
                        bclass + '#block-block-9',
                        '207px',
                        why_reg_heights[1]);

      });

    // correct styles when browser is resized
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
    /* 
     *  End responsive show-hide functinality
     */
    

  
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
    
    var saveButton = '<div class="button save-button">Save</div>';
    var cancelButton = '<div class="button cancel-button">Cancel</div>';
    var editButton = '<div class="button edit-button">Edit</div>';
    
    $('#user-profile-form input[value="Save"]').css('display','none');
    
    $('#user-profile-form > div > fieldset').each(function(){
      
      var formData = '';
      var $section = $(this);
      var $dataView = $('<div class="data-view">');
      var $formFields = $section.children('.fieldset-wrapper');
      
      // Add the cancel and save buttons to the form edit version of each section
      $formFields.css('display','none').prepend(cancelButton).prepend(saveButton);
      $formFields.append(saveButton).append(cancelButton);
      
      // Add the edit buttons to the data view version of the each section
      $dataView.prepend(editButton);
      
      // Move the temporarily empty data view div into the section below the legend
      $section.children('legend').after($dataView);

      $section.find('.form-item').each(function(){
        
        // Grab labels and values from text fields
        if ($(this).hasClass('form-type-textfield')){
          var label = $(this).find('label').clone().children().remove().end().text().trim();
          var input = $(this).find('input').val();
          // Only add colon if the label doesn't end with a question mark
          if (label.substr(label.length-1) != '?') {
            label = label + ':';
          }
          // Remove the empty "please specify" fields
          if (!((label == 'Please specify:') && (input == ''))) {
            formData = formData + '<div class="item"><span class="label">' + label + ' </span><span class="value">' + input + '</span></div>';
          }
        }
        
        // Create a generic password line
        if ($(this).hasClass('password-parent')) {
          formData = formData + '<div class="item"><span class="label">Password: </span><span class="value">********</span></div>';
        }
        
        // Grab labels and values from the select fields
        if ($(this).hasClass('form-type-select')) {
          var label = $(this).find('label').clone().children().remove().end().text().trim();
          var input = $(this).find('option:selected').text().trim();
          // Only add colon if the label doesn't end with a question mark
          if (label.substr(label.length-1) != '?') {
            label = label + ':';
          }
          formData = formData + '<div class="item"><span class="label">' + label + ' </span><span class="value">' + input + '</span></div>';
        }
        
        // Grab labels and selected values from the radio buttons
        if ($(this).hasClass('form-type-radios')) {
          var label = $(this).find('input:checked').parent().parent().prev().clone().children().remove().end().text().trim();
          var input = $(this).find('input:checked').next().text().trim();
          // Only add colon if the label doesn't end with a question mark          
          if (label.substr(label.length-1) != '?') {
            label = label + ':';
          }
          formData = formData + '<div class="item"><span class="label">' + label + ' </span><span class="value">' + input + '</span></div>';
        }
        
        // Grab labels and selected values from the checkboxes
        if ($(this).hasClass('form-type-checkboxes')) {
          var label = $(this).find('input:checked').parent().parent().prev().clone().children().remove().end().text().trim().split(' (choose all that apply)').join('');
          var input = '';
          // Only add colon if the label doesn't end with a question mark          
          if (label.substr(label.length-1) != '?') {
            label = label + ':';
          }
          // If multiple selections, add commas between them
          $(this).find('input:checked').each(function(){
            input = input + ', ' + $(this).next().text().trim();
          });
          
          formData = formData + '<div class="item"><span class="label">' + label + ' </span><span class="value">' + input.substr(2) + '</span></div>';
        }        
        
      });
      
      
      // Move the form data into the awaiting data view div
      $(formData).appendTo($dataView);
      
      // Remove parts of the form data that we don't want to show
      $dataView.find('.item').each(function(){
        
        var labelText = $(this).children('.label').text().slice(0, -2);
         
        if (labelText == 'Status' ||
            labelText == 'Roles' ||
            labelText == 'Default state' ||
            labelText == 'Show the disable/enable rich text editor toggle' ||
            labelText == 'Editor width' ||
            labelText == 'Language' ||
            labelText == 'Auto-detect language') {
          
          $(this).remove();
        }
        
        
      });
      
      // Action to take when edit button is clicked
      $section.find('.button.edit-button').on('click',function(){
        $section.siblings('fieldset').each(function(){
          if ($(this).children('.fieldset-wrapper').is(':visible')) {
            $(this).children('.fieldset-wrapper').toggle();
            $(this).find('.data-view').toggle();
          }
        });
        $formFields.toggle();
        $section.find('.data-view').toggle();
      });
      
      // Action to take when save button is clicked    
      $section.find('.button.save-button').on('click', function(){
        $('#user-profile-form input[value="Save"]').trigger('click');
      });
      
      // Action to take when cancel button is clicked
      $section.find('.button.cancel-button').on('click', function(){
        location.reload();
      });
      
      
    });
    
    
    
    

 /* MATT IS WORKING ON THIS STUFF   
    
    
    // If switching from "other" to something else in a form field, then clear text entry field
    
    // First deal with the select boxes...
    $('.field-widget-options-select').each(function(){      
      $that = $(this);
      var $nextField = $(this).next();
      
      $(this).find('select').change(function(){
        
        toggleSelectOther($(this),$nextField);
        
      });
      
      
    });
    
    // Now deal with the checkboxes...
    $('.field-widget-options-buttons').each(function(){

      var $nextField = $(this).next();

      // Clear out the "please specify" text in case "other" had been selected previously
      $(this).find('input').change(function(){      
        toggleCheckboxOther($(this),$nextField);
      });
      
    });
    
    
    // If "I prefer not to answer" or "No, I am not affiliated" selected then uncheck everything else in checkboxes
    $('.field-widget-options-buttons').each(function(){
      
      var $that = $(this);
      var $nextField = $that.next();
      
      $(this).find('input').change(function(){
        
        // Uncheck all other options if first or last checkbox selected
        if ((($(this).next().text().trim() == 'I prefer not to answer') ||
            ($(this).next().text().trim() == 'No, I am not affiliated with Federally-funded prevention initiatives for any of these Tribes'))
            && ($(this).is(':checked'))) {
          
          $(this).parent().siblings().find('input').attr('checked',false);
          
       
          
        }
        
        // Uncheck the first and last checkboxes if any of the other checkboxes are selected
        if (($(this).next().text().trim() != 'I prefer not to answer') &&
            ($(this).next().text().trim() != 'No, I am not affiliated with Federally-funded prevention initiatives for any of these Tribes') &&
            ($(this).is(':checked'))) {
          $that.find('.form-type-checkbox:first-child input').attr('checked',false);
          $that.find('.form-type-checkbox:last-child input').attr('checked',false);
        }
        


        
      });
      
    });
    
    
    
    function toggleSelectOther($selection,$nextField) {
      if ($nextField.find('label').clone().children().remove().end().text().trim() == 'Please specify') {
        if ($selection.find('option:selected').text() != 'Other') {
          var $nextFieldValue = $nextField.find('input');
          $nextFieldValue.val('');
        }
        $nextField.toggle();
      }
      
      // Check the "N/A" option in case "CAPT Staff or Consultant" had been selected previously
      else if ($nextField.next().find('label').clone().children().remove().end().text().trim() == 'Select your CAPT team') {
        if ($selection.find('option:selected').text() != 'CAPT Staff or Consultant') {
          $nextField = $nextField.next().find('input[value="_none"]').attr('checked','checked');
        }
        $nextField.toggle();
      }
    }
    
    function toggleCheckboxOther ($selection,$nextField) {
      if (($selection.next().text().trim() == 'Other') && ($selection.is(':not(:checked)'))) {          
        if ($nextField.find('label').clone().children().remove().end().text().trim() == 'Please specify') {
          var $nextFieldValue = $nextField.find('input');
          $nextFieldValue.val('');
        }
      }
      $nextField.toggle();
    }
        
    
   */ 
    
    
    
    
    

  }
};


})(jQuery, Drupal, this, this.document);
