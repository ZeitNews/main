
Drupal.behaviors.calais = function(context) {

	$('.calais_keyword').click(function() {
		var tags = $('#' + $(this).attr('for'));
		var keyword = $(this).text();
		
		// TODO: When we move to a recent jQuery, replace is() with hasClass()
		if($(this).is('.calais_keyword_selected')) {
			calaisRemoveKeyword(tags, keyword);
			$(this).removeClass('calais_keyword_selected');
		}
		else {
			calaisAddKeyword(tags, keyword);
			$(this).addClass('calais_keyword_selected');
		}
	});

	$('.calais_keyword').each( function() {
		var tags = $('#' + $(this).attr('for'));
		var keyword = $(this).text();
		
		if (tags.val().indexOf(keyword) != -1) {
			$(this).addClass('calais_keyword_selected');
		}		
	});
}

/**
 * Insert keyword, adding a comma if necessary
 */
function calaisAddKeyword(tags, keyword) {
  keyword = cleanKeyword(keyword);
	var current = $.trim(tags.val());
  var regexp = keywordRegexp(keyword);

	if(!regexp.test(current)) {
		if(current == '') {
			tags.val(keyword);				
		}
		else{
			tags.val(current + ',' + keyword);
		}				
	}
}

/**
 * Remove the keyword and cleanup any comma nonsense
 */
function calaisRemoveKeyword(tags, keyword) {
  keyword = cleanKeyword(keyword);
	var current = $.trim(tags.val());
	var regexp = keywordRegexp(keyword);
	
	if(regexp.test(current)) {
		current = current.replace(regexp, '$1$2');
		
		// Deal with a remaining extra comma
		current = current.replace(/^\s*,/, '');
		current = current.replace(/,\s*$/, '');
		current = current.replace(/,\s*,/, ',');
		tags.val(current);
	}
}

/**
 * Get a regular expression that matches a WHOLE term and not a term within another term.
 * Example: United Refugee Rights and Refugee Rights
 *
 * A whole term will:
 *    - start with either the beginning of the line (^) or a comma
 *    - end with either a comma or the end of the line ($)
 *    - it can also be padded with whitespace
 */
function keywordRegexp(keyword) {
  return new RegExp('(^|,)\\s*' + keyword + '\\s*(,|$)');
}


/**
 * Perform any necessary functions to cleanup the keyword
 */
function cleanKeyword(keyword) {
  // If it has a comma IN it, surround with quotes
	if(keyword.indexOf(',') != -1) {
    keyword = '"' + keyword + '"'
	}
  return keyword;
}
