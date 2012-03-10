INSTALLATION
------------

 1. Download IE CSS Optimizer from http://drupal.org/project/ie_css_optimizer

 2. Unpack the downloaded file, take the ie_css_optimizer folder and place it in
    your Drupal installation under one of the following locations:
      sites/all/modules
        making it available to the default Drupal site and to all Drupal sites
        in a multi-site configuration
      sites/default/modules
        making it available to only the default Drupal site
      sites/example.com/modules
        making it available to only the example.com site if there is a
        sites/example.com/settings.php configuration file

    For more information about acceptable module installation directories, read
    the sites/default/default.settings.php file in your Drupal installation.

 3. Log in as an administrator on your Drupal site and go to Administer > Site
    building > Modules (admin/build/modules). Under "Developoment", find and
    enable the "IE CSS Optimizer" module.

 4. Configure your website for CSS development by going to Administer > Site
    configuration > Performance (admin/settings/performance). Under Bandwidth optimizations, you will see a toggle for "Optimize CSS files". Any setting
    except for "Disabled" will work well with Internet Explorer, but choose the
    one best for your situation:

    Disabled
      Not recommended. Internet Explorer is limited to 31 linked stylesheets and disabling CSS optimization can cause your website to display improperly in that browser.

    Partial optimization for theme CSS development
      Optimize all stylesheets except for those in active development. In other
      words, all stylesheets except for those belonging to the active theme will
      be aggregated into one file.

    Partial optimization for module CSS development
      If this option is chosen an additional "Exclude module from CSS
      optimization" option will appear. All stylesheets except for those
      belonging to the selected module will be aggregated into one file.

    Full optimization
      This option can interfere with module/theme development, but should be
      enabled in a production environment.
