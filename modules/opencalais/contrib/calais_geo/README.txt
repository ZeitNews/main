
Calais GEO
----------

The Calais GEO module provides mapping functionality based off of Calais 
vocabulary terms. 

From within a Node edit form, the Calais Geomapping fieldset allows a user to 
specify which terms from the various enabled Calais vocabularies should be 
mapped on a Google Map.  The terms coordinated are discovered using the 
GeoNames Web Service. (Soon they will use coordinated returned by the Calais
web service and GeoNames will only be used for terms with no Calais geo information)

Configuration
-------------
Calais Geo can be configured from:

 * Site Configuration -> Calais Configuration -> Calais Geo Settings
 
Here you can specify which Calais Vocabularies should be made available to the
Geomapping interface.  By default it will use the City and ProvinceOrState
vocabulary, but you are free to go add more such as Region, Country, etc.

Setting up the map
------------------
You can specify a whole slew of default mapping values in the GMap module configuration.
Be sure to go there and setup things like which mapping controls, the default map type, etc.

Next, from within a Node edit form, if your Node has any terms in any of the configured 
Calais Geo vocabularies, then you will be presented with a fieldset "Calais Geomapping".
This group allows you to specify the following information:

* Terms - The terms selected here will be placed as markers on the map.
* Term Center - The selection here will determine the center of the map
    + <default> - Will use the default from the GMap configuration.
    + <manual>  - Will use lat/lon coordinates specified in the Manual Center field.
    + A term    - Will center the map on the lat/lon of the selected term.
* Manual Center - Lat/Lon coordinates specified as NN.NNNN,NN.NNNNN
* Map Width - The width of the map. Examples: 50px, 5em, 2.5in, 95%. If not specified
              the default from the GMap configuration will be used.
* Map Height - The height of the map. Examples: 50px, 5em, 2.5in, 95%. If not specified
               the default from the GMap configuration will be used.
* Zoom Level - The Zoom level of the map. If not specified, the default from 
               the GMap configuration will be used.

Theme Marker Text
-----------------
You can theme the information that is put in the marker bubble by implementing

<theme>_calais_geo_marker_text($node, $term)


Map data hooks
--------------
You can implement a hook that will give other modules the ability to make modifications
of map data before it is sent to the gmap theme function for rendering.

<module>_calais_geo_map(&$map_data)

To see the format of the $map_data array, see modules/gmap/GMAP-ARRAY-DICTIONARY.txt

Using the map
-------------
There are 2 ways to use the map, either in a block, or as a property of the node object.

Block - Put the "Calais Geo Block" block on any node page and it will get the map inserted into it.

Node Property - In your template there will be a property $node->calais_geo_map. 

For example: in node.tpl.php

<?php if ($node->calais_geo_map): ?>
  <div class="geo-map">
    <?php print $node->calais_geo_map ?>
  </div>
<?php endif;?>



