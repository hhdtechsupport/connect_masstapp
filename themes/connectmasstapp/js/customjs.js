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
  Drupal.behaviors.connectmasstapp_custom_behavior = {
    attach: function(context, settings) {

      if($('body.page-403').length > 0) {
		    if($('body.event').length > 0) {
		      if ($("body").hasClass("not-logged-in")) {
	          $('#pagecontent').append('<p class="anon-must-login">You must log-in to view this event and register. Please log-in <a href=/user>here </a>.</p>');
		      } 
		      if($("body").hasClass("logged-in") && !$("body").hasClass("og-context-node")) {
		        $('#pagecontent').append('<p class="other-group-only">We’re sorry, this event is for other group grantees only.</p><p>If you believe this to be an error, please contact <a href="mailto:captconnect@edc.org" rel="nofollow" class="mailto">captconnect@edc.org</a><span class="mailto"><span class="element-invisible"> (link sends e-mail)</span></span> for assistance</p>');
		      }
		    } else {
		      $('#pagecontent').append('<p>If you believe this to be an error, please contact <a href="mailto:captconnect@edc.org" rel="nofollow" class="mailto">captconnect@edc.org</a><span class="mailto"><span class="element-invisible"> (link sends e-mail)</span></span> for assistance</p>');
		    }
		  }
    }
  }
})(jQuery, Drupal, this, this.document);