/**
 * Search krumo
 */
$(function() {
  // Define krumo root.
  var k = $('.krumo-root');
  
  // Check if there is a krumo.
  if ($(k).length > 0) {
    var form  = '<div class="search-krumo">';
    form     += '  <form id="search-krumo">';
    form     += '    <input type="text" name="search-query" />';
    // If there are more than one krumo's.
    if ($(k).length > 1) {
      form   += '    <select name="search-option">';
      form   += '      <option value="all">search all</option>';
      // For each krumo.
      $(k).each(function(i) {
        i++;
        form += '      <option value="'+ i +'">search krumo #'+ i +'</option>';
        
      });
      form   += '    </select>';
    }
    form     += '    <input type="submit" value="submit" name="submit" />';
    form     += '  </form>';
    form     += '</div>';
    form     += '<div class="search-krumo-results"></div>';
    
    // Insert the form before the first krumo.
		k.eq(0).before(form);
  }
  
  // On submit execute the following.
  $('form#search-krumo').submit(function() {
    // Remove result and classes from previous query.
    $('.krumo-element.krumo-query-result').removeClass('krumo-query-result');
    $('.krumo-nest').hide().prev().removeClass('krumo-opened');
    $('.search-krumo-results').html('');
    
    // Get query value and option value as variables.
    var q = $('input[name=search-query]', this).val();
    var o = $('select[name=search-option]', this).val();
    // If the query is not empty, we can proceed.
    if (q) {
      var k;
      if (o && o != 'all') {
        k = $('.messages.status ul li:nth-child('+ o +') .krumo-root');
      }
      else {
        k = $('.krumo-root');
      }
      $('.krumo-get-path').remove();
      // Find all elements with the query.
      $('.krumo-element:contains('+ q +')', k).each(function(i) {
        // Show result overview.
        $('.search-krumo-results').html('Found '+ $('.krumo-element:contains('+ q +')', k).length +' elements');
        // Add result class.
        $(this).addClass('krumo-query-result').append(Drupal.t('<span class="krumo-get-path"><a href="#">Get path</a></span>'));

        // Expand parents until the query result is layed open before the user.
        $(this).parents(".krumo-nest").show().prev().addClass('krumo-opened');
      });
    }
    else {
      $('.search-krumo-results').html('Empty query');
    }
    
    return false;
  });
  
  // The function to return the path
	$('.krumo-get-path').live("click", function(){
		// Function for getting a path to an element in php
		var pathItems = [];
		// Array which will hold all the pieces of the trail					
		var currentItem = ['Tail', $(this).parent().children('.krumo-name').text()]; 					
		// Last item	
		pathItems.push(currentItem);						 					
		
		// Filling the trail array
		$(this).parents('.krumo-nest').each(function(i) {
			var elType = $(this).prev('.krumo-element').children('.krumo-type').text().toString().split(' ');
			if (elType[0] == 'Object') {
				var currentItem = ['Object', $(this).prev('.krumo-element').children('.krumo-name').text()];
			} else if (elType[0] == 'Array,') {
				var currentItem = ['Array', $(this).prev('.krumo-element').children('.krumo-name').text()];							
			}
			pathItems.push(currentItem);						
		});
	
		// The string which will be returned
		var trail = '';
		// For each item in the trail array
	  $.each(pathItems, function(i) {
			if (pathItems[i +1] && pathItems[i +1][0] == 'Array') {
				if (parseInt($(this)[1])) {
					trail = "[" + $(this)[1] + "]" + trail;
				} else {
					trail = "['" + $(this)[1] + "']" + trail;								
				}
			} else if (pathItems[i +1] && pathItems[i +1][0] == 'Object') {
				trail = "->" + $(this)[1] + trail;
			} else {
				// We are at the first item
				trail = "$var" + trail;							
			}
		});
		alert(trail);					
		return false;
  });    
});
