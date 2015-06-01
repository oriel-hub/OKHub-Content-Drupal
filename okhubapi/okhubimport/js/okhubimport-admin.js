
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
		
		function okhubimportStrForSelectedLang(str, lang){
			returnStr = '';
			var langCodeStr = "["+lang+"]";
			if (str.indexOf(langCodeStr) >= 0){
				/* if we have our choosen language in the text string then we want it, but need to check mutiples with same ID */
				if(str.indexOf("|") >= 0){
					/* if we have multiple theme names for this ID split and only get the lang we want */
					nameArr = str.split("|");
					for (var i = 0, len = nameArr.length; i < len; i++) { 
						/* if we have our choosen language in this elements text string then we want it */
						if (nameArr[i].indexOf(langCodeStr) >= 0){
							if(returnStr){
								returnStr += ' | ';
							}
							returnStr += nameArr[i];
						}
					}
				} else {
					returnStr = str;
				}
				returnStr = returnStr.replace(langCodeStr, '');
			}
			return returnStr.trim();
		}
		
		function okhubimportStrSort(a, b) {
			  if (a.text < b.text)
				    return -1;
				  if (a.text > b.text)
				    return 1;
				  return 0;
			}

		$("#edit-okhubimport-default-lang-themes").change(function(){
			var langSelected = $(this).val();
			$("#edit-okhubimport-default-themes").empty();//To reset themes
			var newOptionSet = new Array();
			cnt = 0;
			$.each(Drupal.okhubimport.themeOptionsOriginal, function(key, object) {   
				var newTextValue = object.text;
				if(langSelected != 'all'){
					newTextValue = okhubimportStrForSelectedLang(object.text, langSelected);
				}
				if(newTextValue){
					newOptionSet[cnt] = {value:object.value, text:newTextValue};
					cnt++;
				}
			});
			newOptionSet.sort(okhubimportStrSort);
			for (var i = 0, len = newOptionSet.length; i < len; i++) {
			     $("#edit-okhubimport-default-themes")
		         .append($("<option></option>")
		         .attr("value",newOptionSet[i].value)
		         .text(newOptionSet[i].text));
			}
		});
		$("#edit-okhubimport-default-lang-themes" ).trigger( "change" );
	}
	
	Drupal.okhubimport = Drupal.okhubimport || {};
	
})(jQuery);
