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
    // #150454682: Implement checkbox group mirroring for all instances of "MassTAPP teams" on event creation form
    if(($('body.page-node-add-event').length > 0) || ($('body.node-type-event.page-node-edit').length > 0)) {

      // add loader
      if(jQuery('.js-ajax-loader').length==0 && jQuery('.ief-entity-operations').length!=0) {
        jQuery('<div class="js-ajax-loader"></div>').prependTo('.node-event-form');
        jQuery('.js-ajax-loader').css({
          'background': 'rgba(255, 255, 255, 0.85) url(../../misc/throbber-active.gif) no-repeat center 80px',
           'position': 'absolute',
           'top': 0,
           'left': 0,
            'width': '100%',
            'height': '100%',
            'z-index': 100
        });
      }
      // var checkboxesWrap = jQuery('[id*="edit-field-date-instance"] :checkbox, #edit-og-group-ref-und :checkbox');
      $(document).on('change', '[class$="form-og-group-ref-und-0-default"] :checkbox, #edit-og-group-ref-und :checkbox', function(){
        var t = $(this),
            c = t.prop("checked"),
            val = t.attr('value'),
            p = $(this).closest('fieldset').attr('id');
          // console.log(p);
        // console.log(t,c,val);
        // if(p == 'edit-og-group-ref-und') {
        // } else {
        // }
        $('[class$="form-og-group-ref-und-0-default"]').find($('input[type="checkbox"][value="'+val+'"]')).prop("checked", c );
        $('#edit-og-group-ref-und').find($('input[type="checkbox"][value="'+val+'"]')).prop("checked", c );
      });

      
      // Define selectors
      var visibilitySelectBoxes = jQuery('select[name*="[group_content_access][und]');
      var visibilitySelectBoxMain = jQuery('select[name="group_content_access[und]"]');
      var iefEditSubmitButotns = jQuery('.ief-entity-operations').find('[id*="actions-ief-entity-edit"]');


      // Trigger edit IEF edit forms
      iefEditSubmitButotns.mousedown();

      // Debugging - remove later;
      // if(typeof window.refreshIntervalId === 'undefined') {
      //   console.log('undefined', typeof window.refreshIntervalId);
      // }
      // else {
      //   console.log('defined', typeof window.refreshIntervalId);
      // }
      // end of Debugging - remove later;

      if(jQuery('.ief-entity-operations').length!=0 && typeof refreshIntervalId === 'undefined') {
        // console.log('run');
        window.refreshIntervalId = setInterval(function() {

          if(jQuery('.ief-entity-operations').length==0) {
            clearInterval(window.refreshIntervalId);
            window.refreshIntervalId = false;
            // console.log('clear',jQuery('.ief-entity-operations').length);
            jQuery('.js-ajax-loader').remove();
          }
          // else {
          //   console.log('not clear',jQuery('.ief-entity-operations').length);
          // }
          
          // console.log(new Date(jQuery.now()));

        }, 2000);
      }


      // Bind init visibility
      function checkGroupVisibility(groupVisiblity) {
        if(!arguments.length) {
          var groupVisiblity = jQuery('[name="field_external_or_internal[und]"]:checked').val();
        }
        if(groupVisiblity == 'internal') {
          $('[class$="form-og-group-ref-und-0-default"], #edit-og-group-ref-und').find(':checkbox').prop('checked', false);
          $('[class$="form-og-group-ref-und-0-default"], #edit-og-group-ref-und').show();
        }
        else {
          $('[class$="form-og-group-ref-und-0-default"], #edit-og-group-ref-und').find(':checkbox').prop('checked', true);
          $('[class$="form-og-group-ref-und-0-default"], #edit-og-group-ref-und').hide();          
        }
        // console.log(groupVisiblity);
      }

      checkGroupVisibility();

      // Bind change events
      jQuery(document).on('change','[name="field_external_or_internal[und]"]',function(){
        if(this.value == 'internal') {
          visibilitySelectBoxes.find('option:selected').prop('selected', false);
          visibilitySelectBoxes.find('option[value="2').prop('selected', 'selected');
          visibilitySelectBoxMain.find('option:selected').prop('selected', false);
          visibilitySelectBoxMain.find('option[value="2').prop('selected', 'selected');

          checkGroupVisibility('internal');
        }
        else {
          visibilitySelectBoxes.find('option:selected').prop('selected', false);
          visibilitySelectBoxes.find('option[value="1').prop('selected', 'selected');
          visibilitySelectBoxMain.find('option:selected').prop('selected', false);
          visibilitySelectBoxMain.find('option[value="1').prop('selected', 'selected');

          checkGroupVisibility('external');
        }
        visibilitySelectBoxes.trigger("chosen:updated");
        visibilitySelectBoxMain.trigger("chosen:updated");
        // console.log(visibilitySelectBoxes.find('option:selected').text());
      });
    }

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