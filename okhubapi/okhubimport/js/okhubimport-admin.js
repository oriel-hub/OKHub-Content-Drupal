
/**
 * @file
 * Enhancements for select list configuration options.
 */

(function ($) {
	Drupal.behaviors.okhubimportAdmin = {};
	Drupal.behaviors.okhubimportAdmin.attach = function(context) {
		Drupal.okhubimport.themeOptionsOriginal = new Array();
		var cnt = 0;
		$("#edit-okhubimport-default-themes option").each(function(){
			Drupal.okhubimport.themeOptionsOriginal[cnt] = {value:$(this).val(), text:$(this).text()};
			cnt++;
		});
		Drupal.okhubimport.themeOptionsOriginal.sort(okhubimportStrSort);
		$("#edit-okhubimport-default-lang-themes").change(function(){
			var langSelected = $(this).val();
			$("#edit-okhubimport-default-themes").empty();//To reset themes
			$.each(Drupal.okhubimport.themeOptionsOriginal, function(key, object) {   
				var newTextValue = object.text;
				if(langSelected != 'all'){
					newTextValue = okhubimportStrForSelectedLang(object.text, langSelected);
				}
				if(newTextValue){
				     $("#edit-okhubimport-default-themes")
				         .append($("<option></option>")
				         .attr("value",object.value)
				         .text(newTextValue));
				}
			});
		});
		function okhubimportStrSort(a, b) {
		  if (a.text < b.text)
			    return -1;
			  if (a.text > b.text)
			    return 1;
			  return 0;
		}
		function okhubimportStrForSelectedLang(str, lang){
			returnStr = '';
			if (str.indexOf("["+lang+"]") >= 0){
				/* if we have our choosen language in the text string then we want it, but need to check mutiples with same ID */
				if(str.indexOf("|") >= 0){
					/* if we have multiple theme names for this ID split and only get the lang we want */
					nameArr = str.split("|");
					for (i = 0, len = nameArr.length, text = ""; i < len; i++) { 
						/* if we have our choosen language in this elements text string then we want it */
						if (nameArr[i].indexOf("["+lang+"]") >= 0){
							if(returnStr){
								returnStr += ' | ';
							}
							returnStr += nameArr[i];
						}
					}
				} else {
					returnStr = str;
				}
			}
			return returnStr;
		}
	}
	
	Drupal.okhubimport = Drupal.okhubimport || {};
	
})(jQuery);
