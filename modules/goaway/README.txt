$Id

Description
-----------
GoAway is a dirt-simple, light-weight "Ban By IP" module for Drupal 6. It works by redirecting offending anonymous users to a page or URL specified by the admin. The module possesses the following features:

- Separate permissions for (1) settings, (2) banning, and (3) unbanning
- Either a local page or a remote URL may be used as the redirect destination
- Adds display of IP address to anonymous comments for easy tracking
  (only displayed to users with 'ban' permission)


Installation
------------
To install the module:

1. Extract the tarball into your sites/all/modules directory.

2. Enable the module from admin/build/modules

3. Enter your desired redirect destination at admin/settings/goaway

Once the module is enabled, users with proper permissions will see IP addresses listed in all anonymous comments (directly after the name), and ban/unban links will be added to the links section of every anonymous comment.


Use
---
To ban an anonymous user's IP Address, click the "Ban IP" link in the comment itself, or copy the IP address and paste it into the textfield at admin/user/goaway

To unban an anonymous user's IP Address, click the "Unban IP" link in the comment itself (this only appears if the IP is already banned), or click the "unban" link at admin/user/goaway


Author
------
Tod Foley
As If Productions
http://www.asifproductions.com


Thanks To
---------
Tim Ocean http://www.oceanup.com
Vera Sweeney http://www.imnotobsessed.com

