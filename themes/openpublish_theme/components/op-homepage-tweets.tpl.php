<?php

/**
  Available variables in the theme include:
  
  1) an array of $tweets, where each tweet object has:
      $tweet->id
      $tweet->username
      $tweet->userphoto
      $tweet->text
      $tweet->timestamp
      
  2) $twitkey string containing initial keyword.
  
  3) $title

*/

?>

<div class="tweets-pulled-listing">
  
  <?php if (!empty($title)): ?>
    <h2><?php print t($title); ?></h2>
  <?php endif; ?>
  
  <?php if (is_array($tweets)): ?>
    <ul class="tweets-pulled-listing">
    <?php foreach ($tweets as $tweet):  ?>
      <li>
         <span class="tweet-author"><?php print l($tweet->username, 'http://twitter.com/' . $tweet->username); ?></span>      
        <span class="tweet-text"><?php print twitter_pull_add_links($tweet->text); ?></span>
        <span class="tweet-time"><?php print l(t("!time ago", array("!time" => format_interval(time() - $tweet->timestamp))), 'http://twitter.com/' . $tweet->username . '/status/' . $tweet->id);?></span>   
      
      </li>
    <?php endforeach; ?>
    </ul>
  <?php endif; ?>
</div>