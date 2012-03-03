<?php
//dsm($row);
?>
<h2><?php //print $rdfa_title ?><?php print l(ucwords($output), 'user/' . $row->uid, array('attributes' => array('title' => 'View user profile.', 'content' => $row->users_name, 'typeof' => 'foaf:person', 'rel' => 'foaf:publications', 'property' => 'dc:contributor'))); ?></h2>