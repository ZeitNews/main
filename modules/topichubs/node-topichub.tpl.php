<?php if (topichubs_render_plugin()) {
  print $node->body; 
}
else {?>

<div id="topichub">
  <div class="hub-left-col section">
    <div class="section overview">
      <h3>Overview</h3>
      <p><?php print $node->body; ?></p>
    </div>
    <div class="section">
      <h3>Most Recent</h3>
      <?php print $node->topichub->data['most_recent']['#view']; ?>
    </div>
  </div>
  <div class="hub-wide-right-col section">
    <div class="section map">
      <h3>Locations Mentioned</h3>
      <?php print $node->topichub->data['calais_geo']['#view']; ?>
    </div>
    <div class="hubleft section">
      <div class="section">
        <h3>Most Read</h3>
        <?php print $node->topichub->data['most_viewed']['#view']; ?>
      </div>
      <div class="section">
        <h3>Related Topics</h3>
        <?php print $node->topichub->data['related_topics']['#view']; ?>
      </div>
    </div>
    <div class="hubleft section">
      <div class="section">
        <h3>Recent Comments</h3>
        <?php print $node->topichub->data['recent_comments']['#view']; ?>
      </div>
      <div class="section">
        <h3>Most Comments</h3>
        <?php print $node->topichub->data['most_comments']['#view']; ?>
      </div>
      <div class="section">
        <h3>Contributors</h3>
        <?php print $node->topichub->data['contributors']['#view']; ?>
      </div>
      <!--
      <div class="section">More Articles Like This</div>
      <div class="section">More Photos Like This</div>
      -->
    </div>
  </div>
</div>
<?php } ?>