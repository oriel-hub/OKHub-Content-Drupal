
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
			var imSelected = ($(this).is("[selected]")) ? true:false;
			Drupal.okhubimport.themeOptionsOriginal[cnt] = {value:$(this).val(), selected:imSelected, text:$(this).text()};
			cnt++;
		});
		
		function okhubimportJqueryVersionCheck(a,b,c){
			if (typeof a === "undefined" || a === null) { a = 0; }
			if (typeof b === "undefined" || b === null) { b = 0; }
			if (typeof c === "undefined" || c === null) { c = 0; }
			var versionCheckPass = false;
			var vernums = $.fn.jquery.split('.');
			if (parseInt(vernums[0]) >= a && parseInt(vernums[1]) >= b && parseInt(vernums[2]) >= c) {
				versionCheckPass = true;
			}
			return versionCheckPass;
		}
		
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
					newOptionSet[cnt] = {value:object.value, selected:object.selected, text:newTextValue};
					cnt++;
				}
			});
			newOptionSet.sort(okhubimportStrSort);
			for (var i = 0, len = newOptionSet.length; i < len; i++) {
			    var newOption = $("<option></option>")
		         .attr("value",newOptionSet[i].value)
		         .text(newOptionSet[i].text); 
			    
			    newOption.removeAttr('selected');
			    if(newOptionSet[i].selected){
			    	newOption.attr("selected","selected");
			    }
			    
				$("#edit-okhubimport-default-themes")
		         .append(newOption);
			}
			if(okhubimportJqueryVersionCheck(1,6)){
				/* Tokenize requires jQuery 1.6 */
				$('.form-item-okhubimport-default-themes').find(".Tokenize").remove();
				$('#edit-okhubimport-default-themes').tokenize({
					displayDropdownOnFocus: true,
					newElements:false
				});
			}
		});
		$("#edit-okhubimport-default-lang-themes" ).trigger( "change" );
	}
	
	Drupal.okhubimport = Drupal.okhubimport || {};
	
})(jQuery);
