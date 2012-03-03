Purge
The purge module clears urls from reverse proxy caches like Varnish
(http://varnish-cache.org/), Squid (http://www.squid-cache.org/) and Nginx
(http://nginx.net/) by issuing an http PURGE request to them. It works in 
conjunction with the Cache Expiration (http://drupal.org/project/expire)
module to act on events that are likely to expire urls from the proxy cache.
This allows delivering content updates faster to end users.

Requirements:
- One or more reverse proxy caches (http://en.wikipedia.org/wiki/Reverse_proxy)
like Varnish (recommended), Squid or Nginx that point to your webserver(s).
- Varnish needs a modification to its configuration file. See this section in the
Varnish section in the Drupal handbook: http://drupal.org/node/1054886#purge
- Squid needs to have purging enabled in its configuration. See
http://docstore.mik.ua/squid/FAQ-7.html#ss7.5
- Nginx needs an extra module and configuration. See 
http://labs.frickle.com/nginx_ngx_cache_purge/ and the installation hints below.
Also see this issue http://drupal.org/node/1048000 for more background info
- A cachable version of Drupal 6. This can be an official Drupal release with
a patch applied (http://drupal.org/node/466444) or use Pressflow
(http://pressflow.org/), a cachable friendly fork of Drupal.
- PHP with curl(http://php.net/manual/en/book.curl.php) enabled. The Purge
module uses curl for issuing the http PURGE requests.
- Acquia Managed Cloud and Dev Cloud hosting services support Purging. See the 
configuration settings below.
- Purge requires the expire module http://drupal.org/project/expire

Installation:
- Unpack, place and enable just like any other module.
- Navigate to Administration -> Site configuration -> Purge settings
- Set your Varnish or Squid proxy url(s) like "http://localhost" or
"http://192.168.1.23:8080 http://192.168.2.34:8080" for multiple hosts.
- If your using nginx you need to specify the purge path and the get method in
your proxy setting like this:
"http://192.168.1.76:8080/purge?purge_method=get"
- If your site is on one of the Acquia Hosting services configure like:
"http://yoursite.com/?purge_method=ah"

Q&A:
Q: How do I know if its working?
A: Purge reports errors to watchdog. Also when running "varnishlog" on the
proxy your should see PURGE requests scrolling by when you (for instance)
update an existing node.

Q: How can I test this more efficiently?
A: The expire module has drush support so you can issue purge commands from
the command line. See http://drupal.org/node/1054584
You can also test if your proxy is configured correctly by issuing a curl
command in a shell on any machine in the access list of your proxy: 
curl -X PURGE -H "Host: example.com" http://192.168.1.23/node/2

Q: Why choose this over the Varnish module (http://drupal.org/project/varnish)?
A: Purge just issues purge requests to your proxy server(s) over standard http
on every url the expire module detects. It requires modification of your
Varnish configuration file.
The varnish module has more internal logic to purge your Varnish cache
completely, which can be more disruptive then the expire module integration it
also offers. It uses a terminal interface to communicate to varnish instead of
http. This allows for more features but also hands over full control over the
varnish instance to any machine having network access to it. (This is a
limitation of Varnish.) Also firewall or other security policies could pose a
problem. It does not require modification of your config file. If you have the
choice Varnish module is probably your best bet but Purge might help you out in
places where Varnish module is not an option.

Credits:
Paul Krischer / "SqyD" on drupal.org
paul@krischer.nl / sqyd@sqyd.net
Thanks:
Mike Carper / mikeytown2 on drupal.org, Author of Expire
Brian Mercer / brianmercer on drupal.org, nginx testing and debugging

Changelog:
1.0 Initial release. Basic purge functionality in place
1.1 Refactoring for Nginx and future platform support and better error handling
1.2 (Upcoming) Acquia Hosting support, form validation
1.3 Bugfix release. Issue 1235674. Output buffering patch by mauritsl on drupal.org.
