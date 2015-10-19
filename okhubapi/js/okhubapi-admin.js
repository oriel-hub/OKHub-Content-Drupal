
/**
 * @file
 * Enhancements for select list configuration options.
 */

(function ($) {
	Drupal.behaviors.okhubapiAdmin = {};
	Drupal.behaviors.okhubapiAdmin.attach = function(context) {
	    $('.form-item-okhubimport-default-datasources .form-type-checkbox, .form-item-okhubimport-default-not-datasources .form-type-checkbox').mouseover(function(){
		$(this).find('.okhub-source-option-moreinfo').addClass('okhub-show-me');
	    });
	    $('.form-item-okhubimport-default-datasources .form-type-checkbox, .form-item-okhubimport-default-not-datasources .form-type-checkbox').mouseout(function(){
		$(this).find('.okhub-source-option-moreinfo').removeClass('okhub-show-me');
	    });
	}
	
	Drupal.okhubapi = Drupal.okhubapi || {};
	
})(jQuery);
