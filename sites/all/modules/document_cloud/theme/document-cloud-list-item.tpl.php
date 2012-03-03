<?php
  /**
   *  Available Variables:
   *  $id - The document's document field id
   *  $link - A link to view the document on your site
   *  $thumbnail - A thumbnail image of the document
   *  $title - The title of the document
   *  $description - The document's description from document_cloud
   */
?>
<?php if($link): ?>
<div class="document-link clearfix">
  <a href="<?php print $link; ?>" title="<?php print $link; ?>">
    <table>
      <tr><td><img width="190px" src="<?php print $thumbnail; ?>" alt="Document thumbnail" /></td></tr>
      <tr><td><?php print $title; ?></td></tr>
    </table>
  </a>
</div>
<?php endif; ?>