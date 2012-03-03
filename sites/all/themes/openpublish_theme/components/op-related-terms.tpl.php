<?php if (!empty($taxonomy)): ?>

	<?php foreach($taxonomy as $term): ?>
		<?php if ($term->vid != 43): ?>
			<?php $tags[] = $term; ?>
		<?php endif; ?>
	<?php endforeach; ?>
	
	<?php if (count($tags) > 0): ?>
		<div class="related-terms">
			<span class="related-terms-label"><strong><?php print t('Tags:'); ?></strong></span>
				<?php foreach($taxonomy as $term): ?>
					<?php if (is_object($term) && !empty($term->name) && $term->vid != 43): ?>
						<div class="related-term"><?php print l($term->name, taxonomy_term_path($term), array('attributes' => array('rel' => 'tag'))); ?></div>
					<?php endif; ?>
				<?php endforeach; ?>
				
		</div><!--/ .related-terms-->
	<?php endif; ?>
	
<?php endif; ?>
