 // Renders the navigation sidebar for chapters and annotations.
_.extend(DV.Schema.helpers, {
  renderViewer: function(){
    var doc         = this.viewer.schema.document;
    var pagesHTML   = this.constructPages();
    var description = (doc.description) ? doc.description : null;
    var storyURL = doc.resources.related_article;

    var headerHTML  = JST.header({
      options     : this.viewer.options,
      id          : doc.id,
      story_url   : storyURL,
      title       : doc.title || ''
    });
    var footerHTML = JST.footer({options : this.viewer.options});

    var pdfURL   = doc.resources.pdf;
    pdfURL       = pdfURL ? '<a target="_blank" href="' + pdfURL + '">Original Document (PDF)</a>' : '';

    var viewerOptions = {
      options : this.viewer.options,
      pages: pagesHTML,
      header: headerHTML,
      footer: footerHTML,
      pdf_url: pdfURL,
      story_url: storyURL,
      descriptionContainer: JST.descriptionContainer({ description: description}),
      autoZoom: this.viewer.options.zoom == 'auto'
    };

    if (this.viewer.options.width && this.viewer.options.height) {
      DV.jQuery(this.viewer.options.container).css({
        position: 'relative',
        width: this.viewer.options.width,
        height: this.viewer.options.height
      });
    }

    var container = this.viewer.options.container;
    var containerEl = DV.jQuery(container);
    if (!containerEl.length) throw "Document Viewer container element not found: " + container;
    containerEl.html(JST.viewer(viewerOptions));
  },

  // If there is no description, no navigation, and no sections, tighten up
  // the sidebar.
  displayNavigation : function() {
    var doc = this.viewer.schema.document;
    var missing = (!doc.description && !_.size(this.viewer.schema.data.annotationsById) && !this.viewer.schema.data.sections.length);
    this.viewer.$('.DV-supplemental').toggleClass('DV-noNavigation', missing);
  },

  renderNavigation : function() {
    var me = this;
    var chapterViews = [], bolds = [], expandIcons = [], expanded = [], navigationExpander = JST.navigationExpander({}),nav=[],notes = [],chapters = [];
    var boldsId = this.viewer.models.boldsId || (this.viewer.models.boldsId = _.uniqueId());

    /* ---------------------------------------------------- start the nav helper methods */
    var getAnnotionsByRange = function(rangeStart, rangeEnd){
      var annotations = [];
      for(var i = rangeStart, len = rangeEnd; i < len; i++){
        if(notes[i]){
          annotations.push(notes[i]);
          nav[i] = '';
        }
      }
      return annotations.join('');
    };

    var createChapter = function(chapter){
      var selectionRule = "#DV-selectedChapter-" + chapter.id + " #DV-chapter-" + chapter.id;

      bolds.push(selectionRule+" .DV-first span.DV-trigger");
      return (JST.chapterNav(chapter));
    };

    var createNavAnnotations = function(annotationIndex){
      var renderedAnnotations = [];
      var annotations = me.viewer.schema.data.annotationsByPage[annotationIndex];

      for (var j=0; j<annotations.length; j++) {
        var annotation = annotations[j];
        renderedAnnotations.push(JST.annotationNav(annotation));
        bolds.push("#DV-selectedAnnotation-" + annotation.id + " #DV-annotationMarker-" + annotation.id + " span.DV-trigger");
      }
      return renderedAnnotations.join('');
    };
    /* ---------------------------------------------------- end the nav helper methods */

    for(var i = 0,len = this.models.document.totalPages; i < len;i++){
      if(this.viewer.schema.data.annotationsByPage[i]){
        nav[i]   = createNavAnnotations(i);
        notes[i] = nav[i];
      }
    }

    if(this.viewer.schema.data.sections.length >= 1){
      for(var i=0; i<this.viewer.schema.data.sections.length; i++){
        var chapter        = this.viewer.schema.data.sections[i];
        var range          = chapter.pages.split('-');
        var annotations    = getAnnotionsByRange(range[0]-1,range[1]);
        chapter.pageNumber = range[0];

        if(annotations != ''){
          chapter.navigationExpander       = navigationExpander;
          chapter.navigationExpanderClass  = 'DV-hasChildren';
          chapter.noteViews                = annotations;
          nav[range[0]-1]                  = createChapter(chapter);
        }else{
          chapter.navigationExpanderClass  = 'DV-noChildren';
          chapter.noteViews                = '';
          chapter.navigationExpander       = '';
          nav[range[0]-1]                  = createChapter(chapter);
        }
      }
    }

    // insert and observe the nav
    var navigationView = nav.join('');

    var chaptersContainer = this.viewer.$('div.DV-chaptersContainer');
    chaptersContainer.html(navigationView);
    chaptersContainer.live('click',this.events.compile('handleNavigation'));
    this.viewer.schema.data.sections.length || _.size(this.viewer.schema.data.annotationsById) ?
       chaptersContainer.show() : chaptersContainer.hide();
    this.displayNavigation();

    DV.jQuery('#DV-navigationBolds-' + boldsId, document.head).remove();
    var boldsContents = bolds.join(", ") + ' { font-weight:bold; color:#000 !important; }';
    var navStylesheet = '<style id="DV-navigationBolds-' + boldsId + '" type="text/css" media="screen,print">\n' + boldsContents +'\n</style>';
    DV.jQuery(document.head).append(navStylesheet);
    chaptersContainer = null;
  },

  // Hide or show all of the comoponents on the page that may or may not be
  // present, depending on what the document provides.
  renderComponents : function() {
    // Hide the overflow of the body, unless we're positioned.
    var position = DV.jQuery(this.viewer.options.container).css('position');
    if (position != 'relative' && position != 'absolute' && !this.viewer.options.fixedSize) {
      DV.jQuery(document.body).css({overflow : 'hidden'});
    }

    // Hide annotations, if there are none:
    var showAnnotations = _.any(this.models.annotations.byId);
    var $annotationsView = this.viewer.$('.DV-annotationView');
    $annotationsView[showAnnotations ? 'show' : 'hide']();

    // Hide the searchBox, if it's disabled.
    this.elements.viewer.addClass('DV-searchable');
    this.viewer.$('input.DV-searchInput', this.viewer.options.container).placeholder({
      message: 'Search',
      clearClassName: 'DV-searchInput-show-search-cancel'
    });

    // Hide the entire sidebar, if there are no annotations or sections.
    var showChapters = this.models.chapters.chapters.length > 0;

    // Remove and re-render the nav controls.
    this.viewer.$('.DV-navControls').remove();
    var navControls = JST.navControls({
      totalPages: this.viewer.schema.data.totalPages,
      totalAnnotations: this.viewer.schema.data.totalAnnotations
    });
    this.viewer.$('.DV-navControlsContainer').html(navControls);

    this.viewer.$('.DV-fullscreenControl').remove();
    if (this.viewer.schema.document.canonicalURL) {
      var fullscreenControl = JST.fullscreenControl({});
      this.viewer.$('.DV-fullscreenContainer').html(fullscreenControl);
    }

    if (this.viewer.options.sidebar) {
      this.viewer.$('.DV-sidebar').show();
    }

    // Check if the zoom is showing, and if not, shorten the width of search
    if (this.elements.viewer.width() <= 650) {
      this.viewer.$('.DV-controls').addClass('DV-narrowControls');
    }

    // Set the currentPage element reference.
    this.elements.currentPage = this.viewer.$('span.DV-currentPage');
    this.models.document.setPageIndex(this.models.document.currentIndex());
  },

  // Reset the view state to a baseline, when transitioning between views.
  reset : function() {
    this.resetNavigationState();
    this.cleanUpSearch();
    this.viewer.pageSet.cleanUp();
    this.removeObserver('drawPages');
    this.viewer.dragReporter.unBind();
    this.elements.window.scrollTop(0);
  }

});