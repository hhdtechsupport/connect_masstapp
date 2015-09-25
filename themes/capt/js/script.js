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

var iPh6H = 667;
var iPh6W = 375;
  // new variable to account for the division between phone and tablet styles
  var phone_tablet_divide = 767;
  var imagePath = '../../../sites/captconnect.edc.org/themes/capt/images/';
  var why_reg_heights = ['191','130','34'];

    // event panel variables
  var desc = ['div.group-description h4','div.field-name-field-body'];
  var aud = ['div.group-audience h4','div.field-name-field-audience'];
  var pres = ['div.group-presenter h4','div.field-name-presenters'];
  var mater =['div#block-views-materials-block h2','div.view-material'];
  var eventPanels = [desc,aud,pres,mater];
  // dashboard variables
  var dashblock = 'div#block-views-dashboard-block-';
  //var ev = ['h1#page-title','div#content > .view-dashboard'] ** THIS IS IF UPCOMING EVENTS ARE USED
  var reg = [dashblock+'1 h2',dashblock+'1 > .view-dashboard']
  var arch = [dashblock+'2 h2',dashblock+'2 > .view-dashboard']
  var dashPanels = [/*ev,*/reg,arch]; // HERE TOO
  var panels_activated = false;
  var currentWinWidth;

  (function ($, Drupal, window, document, undefined) {

// To understand behaviors, see https://drupal.org/node/756722#behaviors
Drupal.behaviors.my_custom_behavior = {
  attach: function(context, settings) {
  /**
   *  Menu Logic
   */
   function init () {
    currentWinWidth = window.innerWidth;
    $('span.toggle-help').click();
    $('a.menu-toggle').hide();
    if ($('body').hasClass('node-type-event')) {
      checkDates();
      if (!panels_activated) activatePanels(eventPanels);
    }
    else if ($('body').hasClass('section-events')) {

      if (isPhone()) {
        hide_panels(dashPanels);
        if (!panels_activated) activatePanels(dashPanels);
      }

    }
  }


  // currently not used - replaced with phone_tablet_divide

  $(document).ready(function () {
   init();
 });


  function addShowHide(arr) {
   var myButton = arr[0];
   var myBody = arr[1];
   $(myButton).click(function () {
    togglePanel(myButton,myBody);





  });
   /**
   *  Responsive Show - Hides
   */
  // function for toggling a panel on click of header
  function togglePanel(header, body, panel, compact, expanded)
  {

    var retval = 'default';
    var mql = window.matchMedia("screen and (max-width:"+phone_tablet_divide+"px)");
    if (mql.matches)
    {

      switch($(body).css('display')) {
        case 'none':
        $(header).css('backgroundImage','url('+imagePath+'icons/hide.png)');
        $(body).slideDown("fast", function () { $(body).show()});
        retval= 'open';
        break;

        default:
        $(header).css('backgroundImage','url('+imagePath+'icons/show.png)');
        $(body).slideUp("fast",function () {$(body).hide()});
        retval='closed';

        break;
      }
    }
    return retval;
  }
}

  function activatePanels (arr) {

    for (var i = 0; i < 3; ++i) {
      addShowHide(arr[i]);

    }
    panels_activated = true;
  }


  $(window).resize(function(){
        // TO DO: if this is an event page


        if ($('body').hasClass('node-type-event') ) {
          checkDates();
          adjust_panels(eventPanels);
        }
        else if ($('body').hasClass('section-events')) {
          adjust_panels(dashPanels);
        }
        currentWinWidth = window.innerWidth;

      });

function adjust_panels (arr) {
    for (var i = 0; i < 3; ++i) panel_respond(arr[i], arr);
}

function hide_panels (arr) {
  for (var i = 0; i < 3; ++i)  {

    if ($(arr[i][0]).attr('id') != 'page-title')
    $(arr[i][1]).hide();

     showHideIcons(arr[i][0], arr[i][1])
  }
}

/* date box logic for events page */
var datePanel = $('div.field-name-event-date-s-');


/* handler for date movement */

function isPhone () {
  var min = phone_tablet_divide;

    // var mql = window.matchMedia("screen and (max-width:"+min+"px)");
    return window.innerWidth < min;
  }

  function checkDates() {

   /* make into a function perhaps*/
   var phoneDates = ($('.group-left').find(datePanel).css('backgroundColor'));
   var ph = isPhone();
   /* check size and if dates are not already where they should be*/
   if (!ph && phoneDates != undefined)
     $('.group-right').prepend(datePanel);
   else if (ph && phoneDates ==undefined)
   {
     $(datePanel).insertBefore($('.group-description'));
     hide_panels(eventPanels);
   }
   // alert (ph + ',' + phoneDates);

 }
  // correct styles when browser is resized
  // this function is flexible so keep it
  function panel_respond(arr, panels)

  {
    var header = arr[0];
    var body = arr[1];
    var min = phone_tablet_divide+1;
    var mql = window.matchMedia("screen and (min-width:"+min+"px)");
    if (mql.matches)
    {
          // laptop
         // show body
         if ($(body).css('display') == 'none') $(body).show();

         if ($(header).attr('id') == 'page-title')
           $(header).css('backgroundImage','url('+imagePath+'icons/dashboard.png)');
        else
           $(header).css('backgroundImage','none');


         if (arguments.length == 5)
           $(panel).css('height',laptop_height)
       }
       else
       {
          // mobile
            if ($(header).attr('id') != 'page-title' && currentWinWidth > phone_tablet_divide)
              $(body).hide();

               showHideIcons(header, body)
          // if resizing to mobile for the first time
           if (!panels_activated)
             activatePanels(panels);

        }
      }

  /*
   *  End responsive show-hide functionality
   */

  function showHideIcons (header, body) {

      if ($(body).css('display') == 'none')
         $(header).css('backgroundImage','url('+imagePath+'icons/show.png)');
      else
         $(header).css('backgroundImage','url('+imagePath+'icons/hide.png)');

   }

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
    $templateSelect = $notificationFieldset.find('.field-name-field-use-a-default-template select');

    $templateSelect.chosen();

    $('.field-type-text input, .field-type-text-long')
    if($templateSelect.next().find('a.chosen-single').text() == "- None -") {
      $notificationFieldset.find('.field-name-field-use-a-default-template').next().show();
      $notificationFieldset.find('.field-name-field-use-a-default-template').next().next().show();
    }
    else {
      $notificationFieldset.find('.field-name-field-use-a-default-template').next().hide();
      $notificationFieldset.find('.field-name-field-use-a-default-template').next().next().hide();
    }

    $templateSelect.change(function(){
      if($templateSelect.next().find('a.chosen-single').text() == "- None -") {
        $notificationFieldset.find('.field-name-field-use-a-default-template').next().show();
        $notificationFieldset.find('.field-name-field-use-a-default-template').next().next().show();
      }
      else {
        $notificationFieldset.find('.field-name-field-use-a-default-template').next().hide();
        $notificationFieldset.find('.field-name-field-use-a-default-template').next().next().hide();
      }
    });
  });

  /*
   * END OF: HIDING NOTIFICATION FIELDS & LIMIT DEFAULT TEMPLATES
   */




  // /*
  //  * START: "MY PROFILE" EDIT/VIEW FUNCTIONALITY
  //  */
  //
  // // Grabbing form data, printing those data, and showing/hiding individual form fieldsets
  //
  // // Create pseudo Save, Cancel, and Edit buttons
  // var saveButton = '<div class="button save-button">Save</div>';
  // var cancelButton = '<div class="button cancel-button">Cancel</div>';
  // var editButton = '<div class="button edit-button">Edit</div>';
  // // And hide the "real" Save button
  // $('#user-profile-form input[value="Save"]').css('display','none');
  // // We are going to allow editing of each fieldset's form fields separately, so iterate over each fieldset grouping
  // $('#user-profile-form > div > fieldset').each(function(){
  //   var formData = '';
  //   var $section = $(this);
  //   // Create the variable that will collect the form data in a structured html string
  //   var $dataView = $('<div class="data-view">');
  //   var $formFields = $section.children('.fieldset-wrapper');
  //   // Add the cancel and save buttons to the form edit version of each section
  //   $formFields.css('display','none').prepend(cancelButton).prepend(saveButton);
  //   $formFields.append(saveButton).append(cancelButton);
  //   // Add the edit buttons to the data view version of the each section
  //   $dataView.prepend(editButton);
  //   // Move the temporarily empty data view div into the section below the legend
  //   $section.children('legend').after($dataView);
  //   // Start grabbing the labels and values of each form element
  //   $section.find('.form-item').each(function(){
  //     // Grab labels and values from text fields
  //     if ($(this).hasClass('form-type-textfield')){
  //       var label = $(this).find('label').clone().children().remove().end().text().trim();
  //       var input = $(this).find('input').val();
  //       // Only add colon if the label doesn't end with a question mark
  //       if (label.substr(label.length-1) != '?') {
  //         label = label + ':';
  //       }
  //       // Remove the empty "please specify" fields
  //       if (!((label == 'Please specify:') && (input == ''))) {
  //         formData = formData + '<div class="item"><span class="label">' + label + ' </span><span class="value">' + input + '</span></div>';
  //       }
  //     }
  //     // Create a generic password line
  //     if ($(this).hasClass('password-parent')) {
  //       formData = formData + '<div class="item"><span class="label">Password: </span><span class="value">********</span></div>';
  //       $(this).find('input').val();
  //     }
  //     // Grab labels and values from the select fields
  //     if ($(this).hasClass('form-type-select')) {
  //       var label = $(this).find('label').clone().children().remove().end().text().trim();
  //       var input = $(this).find('option:selected').text().trim();
  //       // Only add colon if the label doesn't end with a question mark
  //       if (label.substr(label.length-1) != '?') {
  //         label = label + ':';
  //       }
  //       formData = formData + '<div class="item"><span class="label">' + label + ' </span><span class="value">' + input + '</span></div>';
  //     }
  //     // Grab labels and selected values from the radio buttons
  //     if ($(this).hasClass('form-type-radios')) {
  //       var label = $(this).find('input:checked').parent().parent().prev().clone().children().remove().end().text().trim();
  //       var input = $(this).find('input:checked').next().text().trim();
  //       // Only add colon if the label doesn't end with a question mark
  //       if (label.substr(label.length-1) != '?') {
  //         label = label + ':';
  //       }
  //       // Special case (see below as well) for when CAPT Staff or Consultant is "N/A"
  //       if (input != '') {
  //         formData = formData + '<div class="item"><span class="label">' + label + ' </span><span class="value">' + input + '</span></div>';
  //       }
  //     }
  //     // Grab labels and selected values from the checkboxes
  //     if ($(this).hasClass('form-type-checkboxes')) {
  //       var label = $(this).find('input:checked').parent().parent().prev().clone().children().remove().end().text().trim().split(' (choose all that apply)').join('');
  //       var input = '';
  //       // Only add colon if the label doesn't end with a question mark
  //       if (label.substr(label.length-1) != '?') {
  //         label = label + ':';
  //       }
  //       // If multiple selections, add commas between them
  //       $(this).find('input:checked').each(function(){
  //         input = input + ', ' + $(this).next().text().trim();
  //       });
  //       formData = formData + '<div class="item"><span class="label">' + label + ' </span><span class="value">' + input.substr(2) + '</span></div>';
  //     }
  //   });
  //   // Move the form data into the awaiting data view div
  //   $(formData).appendTo($dataView);
  //   // Remove parts of the form data that we don't want to show
  //   $dataView.find('.item').each(function(){
  //     // Make sure to remove the colon/question mark and space
  //     var labelText = $(this).children('.label').text().slice(0, -2);
  //     // Check whether the label matches any of the "bad" fields we don't want to display
  //     if (labelText == 'Status' ||
  //       labelText == 'Roles' ||
  //       labelText == 'Default state' ||
  //       labelText == 'Show the disable/enable rich text editor toggle' ||
  //       labelText == 'Editor width' ||
  //       labelText == 'Language' ||
  //       labelText == 'Auto-detect language') {
  //       // And remove them from the dataView if they do
  //     $(this).remove();
  //   }
  // });
  //   // Action to take when edit button is clicked
  //   $section.find('.button.edit-button').on('click',function(){
  //     $section.siblings('fieldset').each(function(){
  //       if ($(this).children('.fieldset-wrapper').is(':visible')) {
  //         $(this).children('.fieldset-wrapper').toggle();
  //         $(this).find('.data-view').toggle();
  //       }
  //     });
  //     $formFields.toggle();
  //     $section.find('.data-view').toggle();
  //     $('html, body').scrollTop($section.offset().top - 50);
  //   });
  //   // Action to take when save button is clicked
  //   $section.find('.button.save-button').on('click', function(){
  //     $('#user-profile-form input[value="Save"]').trigger('click');
  //   });
  //   // Action to take when cancel button is clicked
  //   $section.find('.button.cancel-button').on('click', function(){
  //     location.reload();
  //   });
  // });

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
      $field.next().css('display','block');
      $field.find('input').removeClass('other-required');
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

  // If any required fields are not completed, then expand the corresponding fieldsets
  $('.section-user input.error').each(function(){
    var $section = $(this).closest('fieldset');
    $section.children('.fieldset-wrapper').css('display', 'block');
    $section.children('.data-view').css('display','none');
    if ($(this).hasClass('form-radio') || $(this).hasClass('form-checkbox')) {
      cl($(this).closest('.form-wrapper'));
      $(this).closest('.form-wrapper').children('div').children('div').css('border', '2px solid red');
    }
  });



  /*
   * END OF: "MY PROFILE" EDIT/VIEW FUNCTIONALITY
   */


 /*
  * SWITCH BANNER IF CATEGORY FOR EVENT EXISTS
  */

  var category = $('#block-block-13').clone().children().remove().end().text().trim();
  if (category != "Your access point for all CAPT virtual events") {
    $('#name-and-slogan').addClass('category');
    $('.region-highlighted').addClass('category');
  }



  /*
   * MAKE DASHBOARD BLOCKS SAME HEIGHT IF ONLY TWO (I.E. NO "UPCOMING EVENTS" PAGE)
   */

   if ($('body').hasClass('section-events') && !$('body').hasClass('page-events')) {
     $block1 = $('#block-views-dashboard-block-1');
     $block2 = $('#block-views-dashboard-block-2');
     max = Math.max($block1.height(),$block2.height());
     $block1.height(max - 50);
     $block2.height(max - 50);
   }




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




  $('.access-information').each(function(){
    $(this).find('p').wrapAll('<div class="access-information-content"></div>');
    $(this).prepend('<div class="show-access-information">Show Access Information</div>');
  });

  $('.show-access-information').each(function(){
    $(this).next().toggle();
    $(this).on('click', function(){
      $(this).next().toggle();
    });
  });

  var $registrationsTitle = $('.page-node-registrations h1#page-title');
  var titleString = $registrationsTitle.text();
  var parsedTitle = titleString.substring(titleString.indexOf('"') + 1, titleString.lastIndexOf('"'));
  $registrationsTitle.html('<em>View Event Registrations</em>' + parsedTitle);

  var $workflowTitle = $('.page-node-workflow h1#page-title');
  var parsedTitle = $workflowTitle.text();
  $workflowTitle.html('<em>Workflow History</em>' + parsedTitle);

  var $develTitle = $('.page-node-devel h1#page-title');
  var parsedTitle = $develTitle.text();
  $develTitle.html('<em>Devel</em>' + parsedTitle);





  $('.section-events .block-views .view-filters').css('display','none');


  $('.view-empty').each(function(){
    if($('#edit-keys-wrapper input[type="text"]').val() != "") {
      $(this).text("No events match your search terms.");
    }
  });






  // BANNER IMAGE SWAP START //

  $headerPhotos = $('.header-photos');

  // Real random number generator
  function rand(min, max) {
	   return Math.floor(Math.random() * (max - min + 1)) + min;
  }

  // Creating an array of consequtive numbers of any length
  function makeArray(min, max) {
    var list = [];
    for (var i = min; i <= max; i++) {
        list.push(i);
    }
    return list;
  }

  var photo_count = 0;

  $('.photos').each(function(){
    photo_count = photo_count + 1;
  });

  // Initially, the grid uses the first 16 photos (or 6 of on logged in or event pages), with numbered filenames
  var photos = makeArray(1,photo_count);

  var counter = 0;

  // The function that calls itself at the end to keep the loop going, and which has a delay
  function timeout_init(photos, photo_count) {
    setTimeout(function(){

      // Which photo cell in the grid should be swapped
      var rand_position = rand(1,photo_count);

      // Which photo (by numbered filename) should be swapped into that spot
      var new_photo = rand(1,32);

      // Make sure that the photo to replace the existing one isn't already in the grid
      do {
        var new_photo = rand(1,32);
      } while (photos.indexOf(new_photo) != -1);

      // Add that number to the array
      photos.push(new_photo);

      // Wrap the photo cell with jQuery
      var $photo_cell = $('.photos:nth-child(' + rand_position + ')');

      // The photo cell includes both a visible and an invisible photo --
      // one on top of the other. Here we identify which is which and wrap in jQuery
      var $photo_current = $photo_cell.find('.photo-inner').filter(function(){
        return $(this).css('opacity') == '1';
      });
      var $photo_replace = $photo_cell.find('.photo-inner').filter(function(){
        return $(this).css('opacity') == '0';
      });

      // Not sure why we need to do this, but sometimes we get a "null" for the
      // background image and better just to skip and re-run the timeout_init function
      if ($photo_current.css('background-image') != null) {

        // Get the background image path of the visible image
        path = $photo_current.css('background-image').replace('url(','').replace(')','');

        // Get the numbered filename (without extension) from the visible image
        file_number = path.replace(/^.*[\\\/]/, '').replace(/\.[^\.]+$/, '');

        // Make sure to remove that number from the list of visible photos so that
        // it can be shown on the next function cycle if need be
        photos.splice(photos.indexOf(parseInt(file_number)),1);

        // Set the url of the photo to be used as a replacement
        $photo_replace.css('background-image', 'url("/sites/captconnect.edc.org/themes/capt/images/banner-photos/' + new_photo + '.png")');

        // Fade in the replacement photo
        $photo_replace.animate({
          opacity: 1
        }, 2000);

        // Fade out the existing photo
        $photo_current.animate({
          opacity: 0
        }, 2000);
      }

      counter = counter + 1;

      if (counter < 30) {
        // Run the function again, passing in the array of current numbered filenames
        timeout_init(photos, photo_count);
      }

    }, rand(1,5) * 1000);
  }


  // On page load (for a few specific pages), set the opacity of each initial photo
  // in each cell and run the timeout_init function
  if ($('body').hasClass('front')              ||
      $('body').hasClass('page-user-password') ||
      $('body').hasClass('page-user-register') ||
      $('body').hasClass('page-anon-login')    ||
      $('body').hasClass('page-anon-register') ||
      $('body').hasClass('page-403')           ||
      $('body').hasClass('page-404')) {
    $('.header-photos .photos .photo-inner:nth-child(1)').each(function(){ $(this).css('opacity','1'); });
    $('.header-photos .photos .photo-inner:nth-child(2)').each(function(){ $(this).css('opacity','0'); });
    timeout_init(photos, photo_count);
  }


  if ($('body').hasClass('logged-in') ||
      $('body').hasClass('.page-events')) {
        $('.header-photos-2 .photos .photo-inner:nth-child(1)').each(function(){ $(this).css('opacity','1'); });
        $('.header-photos-2 .photos .photo-inner:nth-child(2)').each(function(){ $(this).css('opacity','0'); });
        timeout_init(photos, photo_count);
      }



  // BANNER IMAGE SWAP END //





  // FRONT PAGE SHOW/HIDE QUESTIONS

  $('.section-head').each(function(){
    $(this).on('click',function(){
      $(this).next('.section-detail').slideToggle();
    });
  });



}
};


})(jQuery, Drupal, this, this.document);
