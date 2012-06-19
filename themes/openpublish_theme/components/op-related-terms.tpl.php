<?php if (!empty($taxonomy)): ?>

	<?php foreach($taxonomy as $term): ?>
		<?php if ($term->vid != 43): ?>
			<?php $tags[] = $term; ?>
		<?php endif; ?>
	<?php endforeach; ?>
	
	<?php if (count($tags) > 0): ?>
		<?php foreach($taxonomy as $term): ?>
			<?php if (is_object($term) && !empty($term->name) && $term->vid != 43): ?>
				<?php $node_tags[] = l($term->name, taxonomy_term_path($term), array('attributes' => array('rel' => 'tag'))); ?>
			<?php endif; ?>
		<?php endforeach; ?>
		
		<?php print '
			<div class="related-terms"><span class="related-terms-label"><strong>Tags: </strong></span>
			' . implode(', ', $node_tags) . '
			</div><!--/ .related-terms-->
		' ?>
	<?php endif; ?>
	
<?php endif; ?>
