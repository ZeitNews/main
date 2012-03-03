CALAIS

INTRO
=====

This module integrates Drupal with the Calais Web-Service. The web
service allows automated content term-extraction and tagging. It also 
provides an API in which any contributed module can interact with Calais.


INSTALLATION
============

1) Before you install Calais for Drupal 6, you need to install the RDF
module (http://drupal.org/project/rdf). With the RDF Module you should
also download the ARC2 library, which is a separate download. Please 
refer to INSTALL.txt that comes with the RDF module for more details.

2) Place this module directory into your Drupal modules directory.

3) Enable the Calais API, and Calais module in Drupal, at:
   administration -> site configuration -> modules (admin/build/modules)

3) Obtain Calais API from their website: 
   http://www.opencalais.com/user/register

4) Add Calais API Key and tune other settings at:
   administration -> site configuration -> modules -> Calais
   (admin/settings/calais-api)

There are some reports that OpenCalais processing can use a lot of memory 
(the RDf data returned can be quite large)  Consider 64MB the minimum PHP
memory allocation needed. You may need more depending on what you have
installed and enabled.

CREDITS
========
Written by
  - Irakli Nadareshvili <irakli at phase2technology dot com>
  - Frank Febbraro <frank at phase2technology dot com>
  
Sponsored by
  - Phase2 Technology <http://www.phase2technology.com>
  - ThomsonReuters <http://www.thomsonreuters.com/>
  
