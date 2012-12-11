/* $Id: README.txt,v 1.1 2009/11/09 15:04:57 alduya Exp $ */

-- SUMMARY --

The Language select module provides the functionality to:
 - Disable the 'Language neutral' option for nodetypes in multilanguage sites.
 - Choose a default language for nodetypes in multilanguage sites.

For a full description of the module, visit the project page:
  http://drupal.org/project/language_select

To submit bug reports and feature suggestions, or to track changes:
  http://drupal.org/project/issues/language_select

-- REQUIRMENTS --

None.

-- INSTALLATION --

* Install as usual, see http://drupal.org/node/70151 for further information.

-- CONFIGURATION --

* Customize settings per nodetype in Administer >> Content >> Content types >> Nodetype, choose 'Edit', go to 'Workflow settings'
* Select default language:
  - Dynamic:
    User language	= The language of the user creating the node as set at My account >> Edit
    Interface language	= The language of the interface the user is viewing
                          (e.g. www.example.com/node/add/page -> English, www.example.com/nl/node/add/page -> Dutch)
  - Fixed
    All languages enabled for the site
    No default language	= Sets the dropdown to '- Please choose -'
    Language neutral	= Falls back to No default language if Disable Language neutral is selected
    

__ CONTACT __
Current maintainer:
* Sander Vleugels (alduya) - http://drupal.org/user/355915

This project has been sponsored by:
* Desk02 Drupal Development
  Visit http://www.desk02.be for more information.