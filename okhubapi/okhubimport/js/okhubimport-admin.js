
/**
 * @file
 * Enhancements for select list configuration options.
 */

(function ($) {
	Drupal.behaviors.okhubimportAdmin = {};
	Drupal.behaviors.okhubimportAdmin.attach = function(context) {
		var themeOptionsOriginalArr = new Array();
		$("#edit-okhubimport-default-themes option").each(function(){
			themeOptionsOriginalArr[$(this).val()] = $(this).text();
		});
		Drupal.okhubimport.themeOptionsOriginal = themeOptionsOriginalArr;
		$("#edit-okhubimport-default-lang-themes").change(function(){
			$("#edit-okhubimport-default-themes").empty();//To reset themes
			$.each(themeOptionsOriginalArr, function(key, value) {   
			     $("#edit-okhubimport-default-themes")
			         .append($("<option></option>")
			         .attr("value",key)
			         .text(value)); 
			});
		});
	}
	
	Drupal.okhubimport = Drupal.okhubimport || {};
	


})(jQuery);
