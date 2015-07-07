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
   *  Menu Logic
   */
  function init () {
    $('span.toggle-help').click();
    $('a.menu-toggle').hide();
  }
  init();
  /**
   *  Responsive Show - Hides
   */

  // currently not used - replaced with phone_tablet_divide
  var iPh6H = 667;
  var iPh6W = 375;
  // new variable to account for the division between phone and tablet styles
  var phone_tablet_divide = 736;
  var imagePath = '../../../sites/captconnect.edc.org/themes/capt/images/';
  var why_reg_heights = ['207','140','34']
  // laptop, mobile-expanded, mobile-compact

  // function for toggling a panel on click of header
  function togglePanel(header, body, panel, compact, expanded)
  {
    var mql = window.matchMedia("screen and (max-width:"+phone_tablet_divide+"px)");
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
    $('#block-block-8 h2.custom_block_title').click(function () {
        togglePanel('#block-block-8 h2.custom_block_title', '#block-block-8 p');

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
        var min = phone_tablet_divide+1;
        var mql = window.matchMedia("screen and (min-width:"+min+"px)");
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



  // Print to console log for bug testing
  function cl(thing){
    if(typeof(console) !== 'undefined' && console != null){
      console.log(thing);
    }
  }



  // Submenu hover fix
  $('#main-menu li.menu-parent:not(.active-trail) ul.sub-menu.tier-two li').each(function(){
    $(this).hover(function(){
      $(this).parent().prev().css('background','#efefef');
    }, function(){
      $(this).parent().prev().css('background','');
    });
  });



  /*
   * START: HIDING NOTIFICATION FIELDS & LIMIT DEFAULT TEMPLATES
   */

  // Limit default template options and hide notification fields if "Do not send this type of notification" selected
  var subject = '';
  var body = '';

  $('#event-notifications-node-form > div > .panel').each(function(){
    // Store the contents of the fieldset in a variable
    var $notificationFieldset = $(this);
    // Get the "do not send this type of notification" checkbox
    var $preventCheckbox = $notificationFieldset.find('.field-name-field-prevent-notification');
    // Hide fieldset contents if "do not send this type of notification" is checked when form is loaded
    if ($preventCheckbox.find('input').prop('checked')) {
      $notificationFieldset.find('.group-form').css('display','none').next().css('display','none');
    }

    // Show or hide fieldset contents if "do not send this type of notification" checkbox is changed
    $preventCheckbox.find('input').change(function(){
      $notificationFieldset.find('.group-form').slideToggle().next().toggle();
    });

    // Limit the available default templates to those that match the category of notification, based on taxonomy
    $notificationFieldset.find('.field-name-field-use-a-default-template select option').each(function(){
      // Get this option's value
      var optionValue = $(this).text().trim();
      // Split the option so that we get the category of the template (we can have many different templates of a particular category)
      var optionCategory = optionValue.split('|');
      // Grab this fieldset's label so we can compare
      var notificationLabel = $notificationFieldset.find('legend').text().trim();
      // Compare the category of the template with the fieldset's label and only keep if they match
      if ((optionCategory[0] != notificationLabel) && (optionCategory[0] != '- None -')) {
        $(this).remove();
      }
      else {
        $(this).text(optionCategory[0]);
      }
    });
    $notificationFieldset.find('.field-name-field-use-a-default-template select').chosen();

  });

  /*
   * END OF: HIDING NOTIFICATION FIELDS & LIMIT DEFAULT TEMPLATES
   */




  /*
   * START: "MY PROFILE" EDIT/VIEW FUNCTIONALITY
   */

  // Grabbing form data, printing those data, and showing/hiding individual form fieldsets

  // Create pseudo Save, Cancel, and Edit buttons
  var saveButton = '<div class="button save-button">Save</div>';
  var cancelButton = '<div class="button cancel-button">Cancel</div>';
  var editButton = '<div class="button edit-button">Edit</div>';
  // And hide the "real" Save button
  $('#user-profile-form input[value="Save"]').css('display','none');
  // We are going to allow editing of each fieldset's form fields separately, so iterate over each fieldset grouping
  $('#user-profile-form > div > fieldset').each(function(){
    var formData = '';
    var $section = $(this);
    // Create the variable that will collect the form data in a structured html string
    var $dataView = $('<div class="data-view">');
    var $formFields = $section.children('.fieldset-wrapper');
    // Add the cancel and save buttons to the form edit version of each section
    $formFields.css('display','none').prepend(cancelButton).prepend(saveButton);
    $formFields.append(saveButton).append(cancelButton);
    // Add the edit buttons to the data view version of the each section
    $dataView.prepend(editButton);
    // Move the temporarily empty data view div into the section below the legend
    $section.children('legend').after($dataView);
    // Start grabbing the labels and values of each form element
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
        $(this).find('input').val();
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
        // Special case (see below as well) for when CAPT Staff or Consultant is "N/A"
        if (input != '') {
          formData = formData + '<div class="item"><span class="label">' + label + ' </span><span class="value">' + input + '</span></div>';
        }
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
      // Make sure to remove the colon/question mark and space
      var labelText = $(this).children('.label').text().slice(0, -2);
      // Check whether the label matches any of the "bad" fields we don't want to display
      if (labelText == 'Status' ||
          labelText == 'Roles' ||
          labelText == 'Default state' ||
          labelText == 'Show the disable/enable rich text editor toggle' ||
          labelText == 'Editor width' ||
          labelText == 'Language' ||
          labelText == 'Auto-detect language') {
        // And remove them from the dataView if they do
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
      $('html, body').scrollTop($section.offset().top - 50);
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

  // Controlling the special selections, like "Other" and "I prefer not to answer"

  // When a "Please specify" textfield is detected
  $('.field-type-text').each(function(){
    var $field = $(this);
    var fieldLabel = $field.find('label').clone().children().remove().end().text().trim();
    if (fieldLabel == 'Please specify') {
      var $fieldPrev = $field.prev();
      // Action to take when form element is a selecbox
      if ($fieldPrev.is('.field-widget-options-select')) {
        var $fieldPrevSelectbox = $fieldPrev.find('select');
        // On page load
        otherSelectbox ($field, $fieldPrev);
        // On selectbox change
        $fieldPrevSelectbox.change(function(){
          otherSelectbox ($field, $fieldPrev);
        });
      }
      // Action to take when form element is checkboxes or radios
      else if ($fieldPrev.is('.field-widget-options-buttons')) {
        $fieldPrev.find('input').each(function(){
          var $selection = $(this);
          // On page load
          otherCheckbox ($selection, $field, $fieldPrev);
          // On checkbox or radio button change
          $selection.change(function(){
            otherCheckbox ($selection, $field, $fieldPrev);
          });
        });
      }
    }
  });

  function otherSelectbox ($field, $fieldPrev) {
    var selection = $fieldPrev.find('option:selected').text();
    // Empty and hide the "other" field if any option except for "Other" is selected
    if (selection != 'Other') {
      $field.find('input').val('');
      $field.css('display','none');
      // Special case: when "CAPT Staff or Consultant" is selected for the "Role" question
      if ($field.is('#edit-field-other-role') && selection != 'CAPT Staff or Consultant') {
        $field.next().css('display','none');
        $field.next().find('label:contains("N/A ")').prev().attr('checked',true);
      }
      else {
        $field.next().css('display','block');
        $field.find('input').removeClass('other-required');
      }
    }
    // Otherwise, show the "other" field
    else {
      $field.css('display','block');
      $field.find('input').addClass('other-required');
    }
  }

  function otherCheckbox ($selection, $field, $fieldPrev) {
    var selection = $selection.next().text().trim();
    // Because this will be run for each checkbox, make sure we're looking at the "other" checkbox
    if (selection == 'Other') {
      // Empty and hide the "other" field if the "other" checkbox is unchecked
      if ($selection.is(':not(:checked)')) {
        $field.find('input').val('');
        $field.css('display','none');
        $field.find('input').removeClass('other-required');
    }
      // Otherwise, show the "other" field
      else {
        $field.css('display','block');
        $field.find('input').addClass('other-required');
      }
    }
  }

  // What to do when a particular selection implies exclusivity and all other options should be unchecked
  $('.field-widget-options-buttons').each(function(){
    var $field = $(this);
    $field.find('.form-type-checkbox').each(function(){
      var $checkbox = $(this);
      $checkbox.change(function(){
        var $input = $(this).find('input');
        noAnswer ($input, $field);
      });
    });
  });

  function noAnswer ($input, $field) {
    var inputLabel = $input.next().text().trim();
    // Define the particular selections that require all others to be unchecked
    var preferText = 'I prefer not to answer';
    var noAffiliationText = 'No, I am not affiliated with Federally-funded prevention initiatives for any of these Tribes';
    // Check whether the checkbox's label matches one of the selections defined above...
    if (inputLabel == preferText || inputLabel == noAffiliationText) {
      // ...if it does and is checked, then uncheck all other options...
      if ($input.is(':checked')) {
        $field.find('input').each(function(){
          $(this).attr('checked',false);
          // ...(making sure to empty and hide the "other" field because the "other" checkbox was unchecked)...
          otherCheckbox ($(this), $field.next(), $field);
        });
        // ...and re-checking the current checkbox
        $input.attr('checked',true);
      }
    }
    // Otherwise, uncheck the "particular selections" from above (as they can only be exclusively checked off)
    else {
      if ($input.is(':checked')) {
        $field.find('label:contains("' + preferText + '")').prev().attr('checked',false);
        $field.find('label:contains("' + noAffiliationText + '")').prev().attr('checked',false);
      }
    }
  }

// WORKING ON THIS - REQUIRING OTHER TEXT FIELDS
  $('#user-profile-form').submit(function(event){
    //event.preventDefault();
    $(this).find('input.other-required').each(function(){
      cl($(this));
      if ($(this).val() == '') {
        cl($(this));
      //  return false;
      }
    });
  });


  // If any required fields are not completed, then expand the corresponding fieldsets
  $('.page-user-edit div.messages.error li').each(function(){
    var split = $(this).text().split(' field is required.').join('');
    split += ' *';
    $('.form-wrapper > .form-item > label, .form-wrapper > div > .form-item > label').each(function(){
      if ($(this).text().trim() == split) {
        var $section = $(this).closest('fieldset');
        $section.children('.fieldset-wrapper').css('display', 'block');
        $section.children('.data-view').css('display','none');
      }
    });
  });



  /*
   * END OF: "MY PROFILE" EDIT/VIEW FUNCTIONALITY
   */




 /*
  * START: VARIOUS FORM FIELD CONTROLS
  */


  if ($('#edit-field-category select option:selected').val() != '_none'){
    $('#edit-field-banner-text').find('input').val('');
    $('#edit-field-banner-text').css('display','none');
  }

  $('#edit-field-category').change(function(){
   if ($(this).find('select option:selected').val() != '_none'){
     $('#edit-field-banner-text').find('input').val('');
     $('#edit-field-banner-text').css('display','none');
   }
   else {
     $('#edit-field-banner-text').css('display','block');
   }
  });









  }
};


})(jQuery, Drupal, this, this.document);
