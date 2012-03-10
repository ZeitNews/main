
Drupal.behaviors.topichub = function (context) {

  // Display term select for chosen vocab
  $("#vocabulary-selector:not(.topichubs-processed)").each(function() {
		$(this).change(function(){
	    var vid = $(this).val();
	    if(vid != "") {
	      $(".topichub-term-selector").hide();
	      $("#terms-" + vid + "-selector-wrapper").show();
	    }
		});
		$(this).addClass('topichubs-processed');
  });

	// Add selected term to the specified condition 
  $("#topichub-add-term:not(.topichubs-processed)").each(function(){
		$(this).click(function(){
	    var vid = $("#vocabulary-selector").val();
	    if(vid != "") {
		    var vocab = $("#vocabulary-selector option:selected").text();
	      var tid = $("#term-" + vid + "-selector").val();
	      var term = $("#term-" + vid + "-selector option:selected").text();
	      var condition = $("#condition-selector").val();

	      // Add Label and delete image
				var termSpan = document.createElement("span");
				$(termSpan).addClass('condition-term');
				$(termSpan).append(vocab + ": <span class='term-name'>" + term + '</span>');			

				var remove = document.createElement("a");
				$(remove).addClass("topichub-term-remove");
				$(remove).attr({ 
	         href: "javascript:void(0);",
	         title: "Remove",
	         tid: tid,
	         condition: condition,
				});
				$(remove).html(Drupal.settings.topichubs.delete_img[0]);
				$(termSpan).append(remove);
     
	      // Add to hidden
	      var terms = $("#conditions-" + condition).val();
	      if(terms == "") {
	        terms = tid;
	      }
	      else {
	        terms += "," + tid;
		      $(termSpan).prepend("<span class='operator'>AND</span>");
	      }
	      $("#conditions-" + condition).val(terms);
	      $("#condition-wrapper-" + condition).append(termSpan);	
				Drupal.attachBehaviors(termSpan);		
	      return false;
	    }
	  });
		$(this).addClass('topichubs-processed');
	});

  $("a.topichub-term-remove:not(.topichubs-processed)").each(function(){
		$(this).click(function() {
			var tid = $(this).attr('tid');
			var condition = $(this).attr('condition');
      var terms = $("#conditions-" + condition).val();

			if(terms.indexOf(',') == -1) {
				termsArray = new Array(terms);
			}
			else {
				termsArray = terms.split(",");
			}			
			
			for(index in termsArray) {
				if(termsArray[index] == tid) {
					termsArray.splice(index, 1);
					break;
				}
				index++;
			}
			$("#conditions-" + condition).val(termsArray.join(','));
			
			// Remove from the UI
			$(this).parent("span.condition-term").remove();
			
			// Remove leading AND if one exists.
      var firstChildInSpan = $("#condition-wrapper-" + condition + " span:first span:first-child");
			if($(firstChildInSpan).hasClass('operator')) {
				$(firstChildInSpan).remove();
			}
		});
		$(this).addClass('topichubs-processed');
  });

	// UI for Plugin Settings
  $("div.plugin-label:not(.topichubs-processed)").each(function(){
		if($(this).is(':first-child')) {
			$(this).addClass('plugin-label-active');
		}
		$(this).click(function() {
			var id = $(this).attr('id');
			$("div.plugin-settings").hide();
			$("#" + id + "-form").show();
			$("div.plugin-label").removeClass('plugin-label-active');
			$(this).addClass('plugin-label-active');
		});
		$(this).addClass('topichubs-processed');
  });

  $("div.plugin-settings:not(.topichubs-processed)").each(function(){
		if(!$(this).is(':first-child')) {
			$(this).hide();
		}
		$(this).addClass('topichubs-processed');
  });

};