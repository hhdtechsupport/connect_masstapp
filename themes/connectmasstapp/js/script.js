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



      // Temporarily changing the flag confirm title to "Please Complete Your Registration" in case of form errors && change confirm button
      /*  $('.page-flag-confirm-flag-registration h1#page-title').text('Please Complete Your Registration');
      $('.page-flag-confirm-flag-registration .form-actions').prepend('<a class="button">Confirm Registration</a>');
      $('.page-flag-confirm-flag-registration input[type="submit"]').css('display','none');
      $('.page-flag-confirm-flag-registration a.button').css('color','#fff')
                                                          .css('display','inline-block')
                                                          .css('margin-right','20px')
                                                          .css('cursor','pointer')
                                                          .on('click',function(){
                                                            $('.page-flag-confirm-flag-registration input[type="submit"]').click();
                                                          });
      */

      //
      // $newRegisterButton = $('.page-flag-confirm-flag-registration input[type="submit"]').clone();
      // $newRegisterButton.val('.').prependTo('.page-flag-confirm-flag-registration .form-actions');

      // Get browser's timezone - NOT DOING ANYTHING WITH THIS RIGHT NOW
      // cl(jstz.determine().name());


      // TEMPORARY HIDING OF MAILING LIST AND OTHER STUFF
      /*  $('.page-node-notifications:not(.role-administrator) .vertical-tab-button').each(function(){
        if ($(this).find('strong').text() == 'Event Announcement') {
          $(this).next().children('a').click();
          $(this).remove();
          $('#edit-group_event_announcement').remove();
        };
      });

      $('.page-node-notifications:not(.role-administrator) #block-views-send-message-block-1').remove();
      $('.page-node-notifications:not(.role-administrator) #edit-field-notification-type select').val('126').trigger('chosen:updated');
      $('.page-node-notifications:not(.role-administrator) #edit-field-notification-type select option[value="182"]').remove();
      $('.page-node-notifications:not(.role-administrator) #edit-field-notification-type select').trigger('chosen:updated');
      */


      // POTENTIALLY TEMPORARY (ADDING OPT-GROUPS)
      $('.page-user-register #edit-field-state-or-jurisdiction, .page-anon-register #edit-field-state-or-jurisdiction').each(function(){
        $select = $(this).find('select');
        $select.children('option').slice(1, 50).wrapAll('<optgroup label="States">');
        $select.children('option[value!="_none"]').wrapAll('<optgroup label="Jurisdictions">');
        $select.trigger('chosen:updated');
      });
      $('.page-user-edit #edit-field-state-or-jurisdiction').each(function(){
        $select = $(this).find('select');
        $select.children('option').slice(1, 50).wrapAll('<optgroup label="States">');
        $select.children('option').wrapAll('<optgroup label="Jurisdictions">');
        $select.children('optgroup[label="Jurisdictions"]').children('option:first-child').prependTo($select.children('optgroup[label="States"]'));
        $select.children('optgroup[label="States"]').insertBefore($select.children('optgroup[label="Jurisdictions"]'));
        $select.trigger('chosen:updated');
      });



      // new variable to account for the division between phone and tablet styles
      var phone_tablet_divide = 767;

      // Initial setting
      var oldDevice = 0;

      // Check if phone
      if (window.innerWidth < phone_tablet_divide) {
        oldDevice = 1;
      }

      /*
      function deviceSwitch() {

        // Are we dealing with a phone?
        if (window.innerWidth < phone_tablet_divide) {

          // Add appropriate classes
          $('.field-group-html-element').each(function(){
            $(this).addClass('accordion');
            $(this).children('h4').addClass('header');
            $(this).children('.field').addClass('body');
          });
          $('.field-type-ds:not(.field-name-portal-page-groupings):not(.field-name-resources), .section-events .block-views').each(function(){
            $(this).addClass('accordion');
            $(this).find('h2.block-title, > div.field-label').addClass('header');
            $(this).find('h2.block-title ~ div:not(.contextual-links-wrapper), > div.field-label ~ div.field-items').addClass('body');
          });

          $('.field-name-portal-navigation-1').prependTo('.group-left');
          $('.field-name-portal-navigation-3').prependTo('.group-left');
          $('.field-name-event-date-s-').prependTo('.group-left');
          $('.field-name-join-this-event').prependTo('.group-left');
          $('.field-name-join-this-event-2').prependTo('.group-left');
          $('.field-name-already-registered-please-login').prependTo('.group-left');

        }

        else {

          // Remove the show/hide functionality and reveal the body content
          $('.accordion:not(.views-row)').each(function(){
            $(this).removeClass('accordion').removeClass('closed');
            $(this).find('.header').removeClass('header').removeClass('closed');
            $(this).find('.body').removeClass('body').removeClass('closed').show();
          });

          $('.field-name-portal-navigation-1').prependTo('.group-right');
          $('.field-name-portal-navigation-3').prependTo('.group-right');
          $('.field-name-event-date-s-').prependTo('.group-right');
          $('.field-name-join-this-event').prependTo('.group-right');
          $('.field-name-join-this-event-2').prependTo('.group-right');
          $('.field-name-already-registered-please-login').prependTo('.group-right');

        }

      }*/


      // Show-Hide
      function showHide($accordion, index) {

        // Added this check so that the show/hide is only added once (getting jittery animations)
        if (!$accordion.hasClass('accordion-processed')) {
          // Set panels closed initially unless first
          if (index != 0 || $accordion.hasClass('field-name-portal-navigation-1') || $accordion.hasClass('field-name-portal-navigation-3')) {
            $accordion.addClass('closed');
            $accordion.find('.header').addClass('closed');
            $accordion.find('.body').addClass('closed').css('display','none');
          }

          // Add show/hide functionality
          $accordion.find('.header').on('click', function(){

            // Set the header, body, and accordion grouping
            $header = $(this);
            $body = $(this).closest('.accordion').find('.body');
            $accordion = $(this).closest('.accordion');

            // Change state
            if ($accordion.hasClass('closed')) {
              $body.stop(true,true).slideDown('fast');
              $accordion.removeClass('closed');
              $header.removeClass('closed');
              $body.removeClass('closed');
            }
            else {
              $body.stop(true,true).slideUp('fast');
              $accordion.addClass('closed');
              $header.addClass('closed');
              $body.addClass('closed');
            }
          });

          $accordion.addClass('accordion-processed');
        }

      }



      /*
       * MAKE DASHBOARD BLOCKS SAME HEIGHT IF ONLY TWO (not yet working if resizing from phone to tablet)
       */

      // function equalHeightDivs($div1, $div2) {
      //   max = Math.max($div1.height(), $div2.height());
      //   $div1.height(max - 50);
      //   $div2.height(max - 50);
      // }

      // if (window.innerWidth >= phone_tablet_divide && $('body').hasClass('page-node-1046')) {
      //   equalHeightDivs($('#block-views-dashboard-block-1'), $('#block-views-dashboard-block-2'));
      // }




      var newDevice = 0;

      $(window).resize(function(){

        // Check if changing from one device to another
        if (window.innerWidth < phone_tablet_divide) {
          newDevice = 1;

          // if ($('body').hasClass('page-node-1046')) {
          //   $('#block-views-dashboard-block-1').height('auto');
          //   $('#block-views-dashboard-block-2').height('auto');
          // }

        }
        else {
          newDevice = 0;

          // if ($('body').hasClass('page-node-1046')) {
          //   equalHeightDivs($('#block-views-dashboard-block-1'), $('#block-views-dashboard-block-2'));
          // }

        }

        // If changing devices, then run the show-hide function
        if (newDevice != oldDevice) {
        //  deviceSwitch();
          // Only add show/hide functionality if it's a phone
          if (newDevice == 1) {
            // Turn into panels and add on-click functionality
            $('.accordion').each(function(index){
              showHide($(this), index);
            });
          }
        }

        // Set the old device to the current device
        oldDevice = newDevice;

      });

      // Run show-hide on initial page load
   //   deviceSwitch();
      $('.accordion').each(function(index){
        showHide($(this), index);
      });



      // Duplicating some of the above, but this is more straightforward
      $('.views-accordion').each(function() {

        $accordion = $(this);
        $label = $(this).children('.portal-grouping-label');
        $content = $(this).children('.portal-grouping-content');

        $accordion.addClass('closed');
        $label.addClass('closed');
        $content.addClass('closed').css('display','none');

        // Add show/hide functionality
        $label.on('click', function(){

          $label = $(this);
          $accordion = $label.closest('.views-accordion');
          $content = $accordion.children('.portal-grouping-content');

          // Change state
          if ($accordion.hasClass('closed')) {

            // First roll-up all of the other accordion rows
            $accordion.siblings().each(function(){
              $otheraccordion = $(this);
              $otherlabel = $(this).children('.portal-grouping-label');
              $othercontent = $(this).children('.portal-grouping-content');
              $otheraccordion.addClass('closed');
              $otherlabel.addClass('closed');
              $othercontent.addClass('closed').css('display','none');
              $othercontent.stop(true,true).slideUp('fast');
            });

            $accordion.children('').stop(true,true).slideDown('fast');
            $accordion.removeClass('closed');
            $label.removeClass('closed');
            $content.removeClass('closed');

          }
          else {
            $content.stop(true,true).slideUp('fast');
            $accordion.addClass('closed');
            $label.addClass('closed');
            $content.addClass('closed');
          }
        });
      });


      // Print to console log for bug testing
      function cl(thing){
        if(typeof(console) !== 'undefined' && console != null){
          console.log(thing);
        }
      }

      // ScrollToLocation function
      function scrollToLocation(id){
        $('html, body').animate({ scrollTop: $("#"+id).offset().top },'slow');
      }

      // Submenu hover fix
      $('#main-menu li.menu-parent:not(.active-trail) ul.sub-menu.tier-two li').each(function(){
        $(this).hover(function(){
          $(this).parent().prev().css('background','#efefef');
        }, function(){
          $(this).parent().prev().css('background','');
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
        var selection = $fieldPrev.find('option:selected').text().trim();
        // Empty and hide the "other" field if any option except for "Other" is selected
        if (selection != 'Other') {
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

      /*
      * SWITCH BANNER IF CATEGORY FOR EVENT EXISTS
      */

      /*  var category = $('#block-block-13').clone().children().remove().end().text().trim();
        if (category != "Your access point for all CAPT virtual events") {
          $('#name-and-slogan').addClass('category');
          $('.region-highlighted').addClass('category');
        }
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

      var $membershipTitle1 = $('.page-group-node-admin-people-edit-membership h1#page-title');
      var parsedTitle = $membershipTitle1.text().split('Edit membership in group ');
      $membershipTitle1.html('<em>Modify user membership for</em>' + parsedTitle[1]);

      var $membershipTitle1 = $('.page-group-node-admin-people-delete-membership h1#page-title');
      var parsedTitle = $membershipTitle1.text().split('Remove membership in group ');
      $membershipTitle1.html('<em>Remove user membership from</em>' + parsedTitle[1]);


      // commented out until we add back in the exposed search terms filters in dashbaord
      //
      // $('.section-events .block-views .view-filters').css('display','none');
      //
      //
      // $('.view-empty').each(function(){
      //   if($('#edit-keys-wrapper input[type="text"]').val() != "") {
      //     $(this).text("No events match your search terms.");
      //   }
      // });
      //




        /*
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
            rand_position = rand(1,photo_count);

            // Which photo (by numbered filename) should be swapped into that spot
            var new_photo = rand(1,55);

            // Make sure that the photo to replace the existing one isn't already in the grid
            do {
              var new_photo = rand(1,55);
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
              $photo_replace.css('background-image', 'url("/sites/captconnect.edc.org/themes/capt/images/banner-photos/' + new_photo + '.jpg")');

              // Fade in the replacement photo
              $photo_replace.animate({
                opacity: 1
              }, 2000);

              // Fade out the existing photo
              $photo_current.animate({
                opacity: 0
              }, 2000);
            }
            else {
              // Remove the recently added photo from the list if there was an error
              photos.splice(photos.indexOf(new_photo),1);
            }

            counter = counter + 1;

            if (counter < 30) {
              // Run the function again, passing in the array of current numbered filenames
              timeout_init(photos, photo_count);
            }

          }, rand(2,5) * 1000);
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


        if ($('body').hasClass('logged-in')   ||
            $('body').hasClass('page-events') ||
            $('body').hasClass('node-type-page') ||
            $('body').hasClass('node-type-event')) {
          $('.header-photos-2 .photos .photo-inner:nth-child(1)').each(function(){ $(this).css('opacity','1'); });
          $('.header-photos-2 .photos .photo-inner:nth-child(2)').each(function(){ $(this).css('opacity','0'); });
          timeout_init(photos, photo_count);
        }



        // BANNER IMAGE SWAP END //

      */


      /*

        // FRONT PAGE SHOW/HIDE QUESTIONS

        $('.section-head').each(function(){
          $(this).on('click',function(){
            $(this).next('.section-detail').slideToggle();
          });
        });


      */

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


      // Change button text from "Create New Account" to "Done"
      $('input[value="Create new account"]').val('Done');

      // Change the "Administration" title on create user page
      $('.page-admin-people-create h1#page-title').text('Create User');

      // Capitalize the mail log title
      $('.page-admin-reports-mail-logger h1#page-title').text('Outgoing Mail Log');

      // Change title of anon_login and anon_register
      $('.page-anon-login h1#page-title').text('Log in to complete your registration');

      // Change the "Please review your submission" page elements
      $('div.messages:contains("Please review your submission")').removeClass('status').addClass('warning').text('Please review your pending email below. If you are satisfied with the recipients selected and content entered, then click "Send Message" to confirm.');
      $('.entityform .content .submitted').remove();

      // Change "Name" to "Email" for the subscriber taxonomy term form
      $('.page-admin-structure-taxonomy-subscribers label[for="edit-name"]').each(function(){
        var span = $(this).find('span');
        $(this).html('Email ').append(span);
      });

      if ($('#block-block-26 > h3').text() == 'Edit Subscriber') {
        $('label[for="edit-name"]').each(function(){
          var span = $(this).find('span');
          $(this).html('Email ').append(span);
        });
      }

      // Change edit term pages' titles to Admin
      $('.page-taxonomy-term-edit h1#page-title').text('Admin');

      // If Event Materials block is empty, then remove the entire block from DOM
      $('#block-views-materials-block > .view-materials').each(function(){
        if ($(this).text().trim() == '') {
          $(this).closest('.field-name-materials').remove();
        }
      });

      // If Event Materials .view-content is empty, then remove that part from DOM
      $('#block-views-materials-block > .view-materials .view-content').each(function(){
        if ($(this).text().trim() == '') {
          $(this).remove();
        }
      });

      // If Event Materials .view-content is empty, then remove that part from DOM
      $('#block-views-materials-block > .view-materials .view-footer').each(function(){
        if ($(this).text().trim() == '') {
          $(this).remove();
        }
      });

      // If the "a welcome message" is shown in addition to the activation message, remove
      var numMessage = $('ul.messages__list li').length;
      if (numMessage > 1) {
        $('ul.messages__list li:contains("A welcome message")').remove();
      }

      // If the message is the one indicating the user should check their email for activation link, then make bigger
      var $message = $('li.messages__item');
      if ($('li.messages__item:contains("Thank you for creating a new account at CAPT Connect!")')) {
        $message.css('font-size','1.4em').css('display','block').css('margin-left','-20px');
      }




        /*
         * START: HIDING NOTIFICATION FIELDS & LIMIT DEFAULT TEMPLATES
         */
      /*
        // Limit default template options and hide notification fields if "Do not send this type of notification" selected
        var subject = '';
        var body = '';

        $('#event-notifications-node-form .vertical-tabs-panes .field-widget-inline-entity-form-single').each(function(){
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
            $notificationFieldset.find('.group-form').toggle().next().toggle();
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


        // If pending notification being sent, then skip down that tab and update message
        if ($('.messages.warning:contains("Please review your pending email below")').length) {
          $warningMessage = $('.messages.warning');
          pendingFormTitle = $('#edit-change').closest('.entity-entityform-type').find('h2').text().trim();
          $('.vertical-tab-button').each(function(){
            if ($(this).find('> a > strong').text() == pendingFormTitle) {
              $(this).find('> a').click();
            }
          });
        }
        else {
          $('input[value="Send message"]').val('Review Message & Send');
        }
      */
        /*
         * END OF: HIDING NOTIFICATION FIELDS & LIMIT DEFAULT TEMPLATES
         */





      // Open up the terms of use and link to SAMHSA's privacy policy in another window (not 508-compliant)
      $('.field-type-list-boolean a').attr('target','_blank');




      // Cancel account tweaks
      $form = $('form#user-cancel-confirm-form');
      $formContents = $form.children('div').contents().first()[0];
      if ($formContents != undefined) {
        $formContents.textContent='Your account will be blocked and you will no longer be able to log in. This action cannot be undone.';
        userURL = $form.attr('action').split('/');
        $('a#edit-cancel').text('Changed my mind...').attr('href', '/' + userURL[1] + '/' + userURL[2] + '/edit');
      }





      // Adds "active" to the parent section on a portal page
      $('.section-portal .views-field-view a.active').closest('.views-field-view').prev().find('.field-content a').addClass('active').addClass('parent');




      // Problem with the "role" field and triggering (other)...
      /*if ($('body').hasClass('page-user-register') || $('body').hasClass('page-anon-register') || $('body').hasClass('page-user')) {
        $('#edit-field-role select').chosen().change(function(){
          var selected;
          $chosen_single_selected = $(this).next('.chosen-container').find('a.chosen-single span');
          $(this).next('.chosen-container').find('ul.chosen-results li.result-selected').each(function(){
            if ($(this).text() == $chosen_single_selected.text()) {
              selected = $(this).text();
            }
          });
          $(this).find('option').each(function(){
            if (($(this).text() == selected) && ($(this).val() == '117')) {
              $('#edit-field-other-role').css('display','block');
            }
          });
        });
      }*/

      if ($('#edit-field-role select option[selected="selected"]').val() == '117') {
        $('#edit-field-role select').trigger('chosen:updated');
      }



      // Date picker fix -- if start date updated, make end date match
      $('.field-name-field-date').each(function(){
        var $field = $(this);
        $field.find('.start-date-wrapper .date-padding > .form-item:nth-child(1) input').change(function(){
          $field.find('.end-date-wrapper .date-padding > .form-item:nth-child(1) input').val($(this).val());
        });
      });





//   // Another date picker fix -- bump up end time if start time changed
//   var timeDiff;
//
//   $('.start-date-wrapper .form-type-textfield:nth-child(2) input').on('click', function(){
//
//     var startTimeString = $(this).val();
//     var $endTimeInput = $('.end-date-wrapper .form-type-textfield:nth-child(2) input');
//     var endTimeString = $endTimeInput.val();
//
//     var startTimeAMPM = startTimeString.substring(5,7);
//     var endTimeAMPM = endTimeString.substring(5,7);
//
//     var startTime12 = startTimeString.replace(':','');
//     var endTime12 = startTimeString.replace(':','');
//
//     var startTime24, endTime24;
//
//     if (startTimeAMPM == 'pm') { startTime24 = parseInt(startTime12) + 1200; }
//     else { startTime24 = parseInt(startTime12); }
//
//     if (endTimeAMPM == 'pm') { endTime24 = parseInt(endTime12) + 1200; }
//     else { endTime24 = parseInt(endTime24); }
//
//     timeDiff = endTime24 - startTime24;
//
//   });
//
//   $('.start-date-wrapper .form-type-textfield:nth-child(2) input').on('click', function(){
//
// }


      /*
       * START: FLAG CONFIRMATION PROFILE VIEW/EDIT FUNCTIONALITY
       */

      function getLabelsAndInputs($formItem) {
        var label = $formItem.children('label:not(.option)').clone().children().remove().end().text().trim();
        if ($formItem.hasClass('form-type-textfield')){
          var input = $formItem.find('input').val();
          label = label.replace(' (check all that apply):','');
        }
        else if ($formItem.hasClass('form-type-select')) {
          var input = $formItem.find('.chosen-container span').text();
          label = label.replace(' (check all that apply):','');
        }
        else if ($formItem.hasClass('form-type-radios')) {
          var input = $formItem.find('input:checked').next().text().trim();
          label = label.replace(' (check all that apply):','');
        }
        else if ($formItem.hasClass('form-type-checkboxes')) {
          var input = '';
          label = label.replace(' (check all that apply):','');
          $formItem.children('input:checked').each(function(){
            input = input + ', ' + $(this).next().text().trim();
          });
          input = input.substr(2);
        }

        if (!((label == 'Please specify:') && (input == ''))) {
          return '<div class="item"><span class="label">' + label + ' </span><span class="value">' + input + '</span></div>';
        }
      }

      $('#flag-confirm .panel.profile').each(function(){
        var $panel = $(this);
        var label = '';

        $panel.find('.form-wrapper').each(function(){

          $(this).prepend('<div class="content"></div>');
          $(this).prepend('<div class="editor">Edit</div>');
          $(this).prepend('<div class="saver">Save</div>');

          $initialValue = getLabelsAndInputs($(this).find('.form-item'));
          $(this).find('.content').append($initialValue);
          $(this).find('.form-item').css('display','none');

          $(this).children('.editor').on('click',function(){
            $(this).css('display','none');
            $(this).parent().children('.saver').css('display','block');
            $(this).parent().children('.content').css('display','none');
            var $formItem = $(this).parent().find('.form-item').css('display','block');
          });

          $(this).children('.saver').on('click',function(){
            $(this).css('display', 'none');
            $(this).parent().children('.editor').css('display','block');
            var $formItem = $(this).parent().find('.form-item');
            $(this).parent().children('.content').html(getLabelsAndInputs($formItem)).css('display','block');
            $formItem.css('display','none');
          });

        });

      });

    }
  };
  $(document).ready(function () {
       /*** MassTAPP JS ***/
    function checkBoxes() {
      
      if($('#block-views-materials-block .item-list ul li').text().trim() == '') {
        $('.field-name-materials').remove();
      }
    }
    function checkPublishState() {

       $('form.workflow-transition-form').each(function () {
        if ($(this).hasClass('state-unpublish')) 
           $('.workflow-button-unpublish').hide();
         else 
           $('.workflow-button-publish').hide();
       });
    }
    function mergeTitle($obj) {
           var $event_link = $obj.find('.event-title a');


           var $part_name = $obj.find('.event-part-name');
           if ($part_name.length > 0) {

                $event_link.append(', ' + $part_name.text());
                $part_name.remove();
           }

           if ($event_link.text().length > 50) {
              $event_link.addClass('long-title');
           }

    }
   function addYear(sectionYear, cur_el) {
        var year_el = document.createElement('li');
        year_el.className = 'year-label';
        year_el.textContent = sectionYear;
            
        var parent = cur_el.parentElement;
        parent.insertBefore(year_el,cur_el);
    }
    function formatTitles() {
      var prevYear = '';
     // var numYears = 1;
     
      $('.event-instances li').each(function () {

           var date_string = $(this).find('.date-display-single').attr('content');

           var sectionYear = date_string.substring(0,4);

          if (sectionYear != prevYear)  {
            prevYear = sectionYear;
            //  if (numYears > 1) 
           addYear(sectionYear, $(this)[0]);
            //  numYears++;
           }
           mergeTitle($(this));


          
      });
       $('.event-instances').addClass('visible');
    }
    function formatDateInstances() {
       $('.date-container').each(function () {
           // == abbreviating the date == 
           // get the inner date element.
           var $date_display = $(this).find('.date-display-single');
           // get an array with the element's content.
           var arr = $date_display.text().split(' ');
           // make the date display element say the day
           $date_display.text(arr[1]);
           
           // == adding the month == 
           // convert self into a JS element to make appending with JS easy.
           var self = $(this)[0];
           // create an element for the month.
           var month = document.createElement('span');
           // set the element's month content using the array element.
           month.textContent = arr[0];
           // give it a class name for CSS.
           month.className = 'month';
           // append the span element with the month
           self.appendChild(month);
           // == done adding the month == 

        });
    }
    function showHide() {

      var showText = 'show';
      var hideText = 'hide';
      $(".toggle").prev().append(' <span class="toggleContainer">[<a href="#" class="toggleLink">'+showText+'</a>]</span>');
  
      // hide all of the elements with a class of 'toggle'
      $('.toggle').hide();
  
      // capture clicks on the toggle links
      $('a.toggleLink').click(function() {
  
      // change the link text depending on whether the element is shown or hidden
      if ($(this).text()==showText) {
        $(this).text(hideText);
      }
      else {
        $(this).text(showText);
      }
    
      // toggle the display
      $(this).parent().parent().next('.toggle').toggle('fast');
    
    // return false so any link destination is not followed
      return false;
    
     });

    }
    function setToggle(selector) {    
        $(selector).addClass('toggle');
    }
    function removeColons() {
          // remove colon from label
      $('.field-name-field-materials-groups .field-label').each(function () {
          var txt = $(this).text();
          var newText = txt.substring(0, txt.length-2);
          $(this).text(newText);

      });
    }
        // grab text from field items and append to title. then delete original items.
    function formatPresenterInfo() {
  
      $('.node-event-materials-group').each(function () {
          
          var $title = $(this).children('header').find('h2.title');
          // take away link from the title
          $title.html($title.text()); 
          var suffixes = ['name','position','location'];
          var chars = [', ' ,', ', ' - ']

          $(this).find('.node.node-resource-author').each(function () {
              
            for (var i = 0; i < suffixes.length; ++i) {
            var $el = $(this).find('.field-name-field-author-'+suffixes[i]);

            if ($el.text().length > 0)
              $title.append('<span class="presenter-'+suffixes[i]+'">' + chars[i] + $el.text()+'</span>');
         //   $el.remove();
            }
          });
        
      });
    }
    // add class names to resource links
    function styleLinks() {
       $('.field-name-field-material a,#block-views-materials-block a').each(function () {
         
          var src = $(this).attr('href').split('.');
          var idx = src.length-1;
          var ext = src[idx].toLowerCase();

          if (ext.length < 5 && ext.length > 2)
            $(this).addClass(ext);
          else 
            $(this).addClass('url');


      });
    }
    function countMaterialsBoxes() {
      if ($('.field-name-field-materials-groups').length > 0 &&
          $('.field-name-materials').length > 0) {
        $('.field-name-field-materials-groups .field-label').text('Additional Materials');
      }
    }
    function formatMaterialsGroups() {
       removeColons();
       formatPresenterInfo();
       styleLinks();
    }
    function checkTitleForSplit() {
      var $title = $('h1.page-title');
      var title_text = $title.text();
      if (title_text.search(":") != -1) {
        var arr = title_text.split(":");
        $title.html('');
        for (var i = 0; i < 2; ++i) {
          /*var blurb = (i ==0) ? arr[i]+':' : arr[i];*/
         var html = '<span>'+arr[i]+'</span>';

         $title.html($title.html()+html);
        }


      }
    }
    function checkNumDates() {
      var numDates = $('.field-name-event-date-s- .item-list .views-row').length;

      if (numDates = 1) $('.field-name-event-date-s- h2').text('Event Date');

    }
    function checkForEvents() {
       var loaded = false;
       var classNames = ['events',
                          'upcoming-events',
                          'upcoming-external-events',
                          'my-registered-events',
                          'past-events',
                          'my-archived-events',
                          'past-webinars'];
        // check for all classes in the array
        if ($('body').is(classNames.map(function(className)  { 
              return '.'+className;
            }).join(',')
           )
          ) {
         
               formatDateInstances();
               formatTitles();
               loaded = true;

            $('ul.pager li a').click(function () {
              loaded = false;
            })
            $(document).ajaxComplete(function () {

                 if (loaded == false) {
                     formatDateInstances();
                     formatTitles();
                   }
            });

         

        }
    }
    function checkContent() {
   
      if ($('.group-audience .field-name-field-audience').text() == '' &&
        $('.group-description .field-name-field-description').text() == '')
         {
            $('.group-description').remove();
            $('.group-audience').remove();
            $('.field-name-event-date-s-').detach().appendTo('.group-left');
         }
    }

    function init() {
      if ($('body').hasClass('node-type-event')) {
        checkBoxes();
        checkPublishState();
        formatMaterialsGroups();
        checkTitleForSplit();
        checkNumDates();
        countMaterialsBoxes();
      //  checkContent();
      //  setToggle('.field-name-field-materials-groups > .field-items');
      //  showHide();
      } 
      else {
        checkForEvents();
      }
  }
  init();
  });
 
})(jQuery, Drupal, this, this.document);
