Joomla to Drupal
----------------
This module enables the import of the following content from a Joomla 1.0.x
website into Drupal.

- Users
- Sections & Categories into Taxonomy Vocabularies and Terms
- Content items to nodes

Configure the module via Administer >> Site Configuration >> Joomla to Drupal,
and run the import from Administer >> Content Management >> Import from Joomla.

Requirements
------------
You will need to be able to connect to the Joomla site database from your
Drupal host.  The two sites do not neeed to be on the same host, however 
the copying of image files to the Drupal site will only work if the Joomla
directory is accessible from the Drupal website.  If this is not the case you
may copy the Joomla image directory to the Drupal host.

Continuous migration
--------------------
It is possible to run the imports automatically via cron.  This will keep most
changes in sync between the Joomla and Drupal site.  Each time a content item
is updated in Joomla, a new revision will be created for the relevant Drupal
content item.

Disabling / un-installing the module
------------------------------------
Once you have completed your content import, it is not necessary to keep the
Joomla to Drupal module enabled.  However, you should be aware of the
following:

- Joomla and Drupal store user passwords differently.  This module provides
  a mechanism to check the users Joomla password and convert it to the Drupal
  format on the first successfull login for that user.  If you disable the
  module, any users who have not logged in to the Drupal site will need to
  request a new password.
- This module stores data mapping each user, taxonomy term and content item
  to it's Joomla equivalent.  If you un-install this module, all this data
  will be lost.  If you then reinstall and configure the module a second time,
  it will reimport all the data it has already imported,

It is therefore recommended that you do not disable this module until you
are sure that all your users have logged in and had their passwords converted,
and that you do not un-install the module until you are absolutely sure you
will not need to run another import.
