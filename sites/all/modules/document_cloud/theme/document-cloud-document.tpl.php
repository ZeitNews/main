<?php
/** 
 *  Available Variables:
 *  $doc - the document object from document_cloud
 *  $title - The document's title
 *  $description - The document's description
 */
?>
<a href="<?php print urldecode($_GET['redirect']); ?>" title="Return to article">&laquo; Back to Article</a> 
<h1><?php print $title; ?></h1>
<p><?php print $description; ?></p>
<div id="viewer"></div>