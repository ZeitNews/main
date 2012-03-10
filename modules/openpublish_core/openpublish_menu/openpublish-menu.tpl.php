<ul class="links primary-links clearfix op-primary-links">
  <?php if (is_array($expanded_primary_links)): ?>
    <?php foreach ($expanded_primary_links as $top_item): ?>
      <?php 
        $html_title = t($top_item->title);
        $title_link = l($html_title, $top_item->href, array('html' => TRUE, 
                                    'attributes' => array('class' => "first-level")));
      ?>
      <li class="first-level <?php print ($top_item->active ? $top_item->active : "off"); ?> <?php if ($top_item->position_class) print $top_item->position_class; ?>">
        <?php print $title_link; ?>
                
        <?php if (is_array($top_item->sublinks) && sizeof($top_item->sublinks) > 0): ?>
          <ul class="second-level">          
            <?php foreach ($top_item->sublinks as $submenu): ?>
              <li><?php print l(t($submenu->html_title), $submenu->href, array('html' => TRUE)); ?></li>
            <?php endforeach; ?>
          </ul>
        <?php endif; ?>
        
      </li>
    <?php endforeach; ?>
  <?php endif; ?>
</ul>