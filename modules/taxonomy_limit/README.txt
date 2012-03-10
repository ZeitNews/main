----------------------------------------------------------------

This module allows an admin to set limits on the number of terms that a node
can have per vocabulary.  It also allows setting this per content type as
well.  For example, a page could allow unlimited terms in a category, but a
story could limit the same category to four choices.

Settings for this module are in admin/settings/taxonomy_limit

The settings page does attempt to be as informative as possible regarding the
choices you make.  There are redundant checks for the categories you select so
that changes to how the category is configured don't cause errors.

This module requires categories to have the multiple option enabled.
Freetagging categories are supported and have this option enabled implicitly.

Upgrading from Drupal 5
-----------------------

Older versions of this module stored error messages differently (in the same
variable as the taxonomy limit).  This has been changed to allow users to
translate error messages.  As a result, you will need to reset your custom
error messages after upgrading.

Ideally this would be handled via an upgrade hook.  Patches for this would be
very welcome.

Translating Error Messages
--------------------------

Like taxonomy limits, error messages are set per vocabulary and content type.
They are stored as Drupal variables and so can be translated by declaring them
to be multilingual variables.  To do this, first install the
Internationalization module (i18n).  Next, for each content type whose error
messages you wish to translate, add the variable 'taxonomy_limit_type_error'
to the $conf['i18n_variables'] in settings.php, where 'type' is the content
type.  Note that you must use Drupal's internal type name (the 'Type' column
at admin/content/types) and not the human-readable type name (the 'Name'
column at the above page).

For example, to translate error messages for the story and page content types,
you would add this to settings.php:

  $conf['i18n_variables'] = array(
      'taxonomy_limit_story_error',
      'taxonomy_limit_page_error',
  );

Finally, load the taxonomy limit settings page while the site is set to each
language you have enabled, and enter the appropriate translation of your error
message.  Note that you will also need to reset the error message for the
site's default language (this is a consequence of how multilingual variables
work and is not specific to this module.)

For more information on multilingual variables, see this handbook page:
http://drupal.org/node/313272

Contributors
------------

Gord Christmas (Drupal 4.7 & 5)
http://drupal.org/user/40977
gord@northstudio.com
http://www.northStudio.com/

Matt Corks (Drupal 6)
http://drupal.org/user/15016
matt@koumbit.org
http://www.openflows.com/
