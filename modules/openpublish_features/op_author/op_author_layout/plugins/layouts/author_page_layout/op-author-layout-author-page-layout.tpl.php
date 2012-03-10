<div class="clearfix" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>  

  <div class="header clearfix">  
    <h1><?php print t('Author Bios'); ?></h1>
  </div><!--/header-->

  <div class="top-featured clearfix">
    <div class="inside"><?php print $content['author_brief']; ?></div>
  </div>
  
  <div class="clearfix">
    <div class="inside inner-column-left" ><?php print $content['left_column']; ?></div> 
    <div class="inside inner-column-right"><?php print $content['right_column']; ?></div>
  </div><!--/ .clearfix -->

</div>