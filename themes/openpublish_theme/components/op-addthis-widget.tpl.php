<div id="facebook-like" style="display:inline-block;">  
  <?php if (1>2) { ?>
    <fb:like layout="button_count" width="80" show_faces="false" action="like"></fb:like>
  <?php } ?>
  <iframe src="http://www.facebook.com/plugins/like.php?href=<?php global $base_root;
print $base_root . request_uri(); ?> &amp;layout=button_count&amp;show_faces=true&amp;width=80&amp;action=like&amp;colorscheme=light&amp;height=21" scrolling="no" frameborder="0" style="border:none; overflow:hidden; width:95px; height:21px;" allowTransparency="true"></iframe>

</div>


<script type="text/javascript">
var addthis_config =
{
   ui_508_compliant: true,
   services_compact: 'print,favorites,email,facebook,twitter,digg,delicious,myspace,google,more'
}
</script>
<div class="addthis_toolbox addthis_default_style">
<a addthis:title="<?php print $addthis_link_title; ?>" href="http://addthis.com/bookmark.php?v=250" class="addthis_button_compact"><?php print t('Share'); ?></a>
<span class="addthis_separator">|</span>
<a class="addthis_button_print"></a>
<a class="addthis_button_email"></a>
<a class="addthis_button_twitter"></a>
<a class="addthis_button_facebook"></a>
</div>
<script type="text/javascript" src="http://s7.addthis.com/js/250/addthis_widget.js"></script>
