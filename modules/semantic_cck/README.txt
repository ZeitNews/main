
-- REQUIREMENTS --

Content Construction Kit (CCK): http://drupal.org/project/cck


-- INSTALLATION --

Install as usual, see http://drupal.org/node/70151 for further information. 


-- SUMMARY --

Semantic CCK was created to give users the means of customizing the HTML output 
of CCK fields. It was inspired in part by the highly recommended module Semantic 
Views (http://drupal.org/project/semanticviews) which provides the same functionality 
for Views (http://drupal.org/project/views), and as response to the "Semantic CCK" 
feature request on the CCK issue queue (http://drupal.org/node/670040).


-- BENEFITS --

With Semantic CCK enabled, users can specify the HTML elements and classes for:

	- The entire field
	- The labels -- above and inline
	- All field items
	- Each field item

This allows users to quickly create semantically rich and meaningful HTML markup 
from CCK fields such as:

	- Definition Lists
	- Ordered Lists
	- Unordered Lists

The user can also choose to remove all (or some) markup for any CCK field.

By facilitating semantically rich markup, Semantic CCK makes it easy for themers and
developers to increase usability, accessibility and SEO performance of Drupal sites 
without resorting to field overrides (ie. content-field.tpl.php).


-- CONFIGURATION & SETUP --

To use Semantic CCK, simply install the module and go to the configuration form for 
each field. At the bottom will be the Semantic CCK options. 

Make sure that you select the "Use Semantic HTML For Field Output" checkbox, otherwise 
the CCK defaults will be used.


-- USING FIELD TPL OVERRIDES --

For those instances that do require a field template override, it is recommended that 
you not use Semantic CCK for that field (Users have to "opt-in" to use Semantic CCK). 
That way, you can simply override the field using a normal CCK field override, and 
still have the benefits of Semantic CCK for any other fields.