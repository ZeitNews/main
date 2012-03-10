// $Id: better_perms.js,v 1.1 2009/04/20 05:37:16 mattman Exp $
/**
 * Permissions javascript.
 * @todo reapply even/odd to module rows instead of transparent css
 */
if (Drupal.jsEnabled) {
  $(document).ready(function() {
      // Store permission rows and module rows to vars
      var permissionRows = $("td.permission").parent("tr");
      var moduleRows = permissionRows.prev("tr");
      var headerTitle = $("table#permissions > thead th:first");
      var headerText = headerTitle.text();
      var stickyTitle = $("table.sticky-header th:first");
      // Hide all the rows - yeah!
      permissionRows.hide();
      // Becase the odd/even class alternates rows, coloring gets jacked up
      // make transparent for now
      moduleRows.css("background-color", "transparent");
      moduleRows.css("cursor", "pointer");
      // Make the td in each tr transparent as well - just in case the theme adds color
      moduleRows.children("td.module").css("background-color", "transparent");
      // Clicking module rows will reveal/hide children permissions
      // only one row open at a time
      $("td.module").click(function(){
         var module_id = $(this).attr('id');
         var module_name = $(this).text();
         var module_permissions = $("td." + module_id).parent("tr");
         var perm_title = headerText + ' for ' + module_name;
         if (module_permissions.css("display") != "none") {
           module_permissions.hide();
           headerTitle.html(headerText);
           stickyTitle.html(headerText);
           return;
         }
         $("td.permission").parent("tr").hide();
         module_permissions.show();
         // headerTitle.html(perm_title);
         stickyTitle.html(perm_title);
      });
      better_perms_add_buttons(moduleRows);
      $("td.better-perms-row").click(function(){
          if ($(this).text() == "Expand All") {
              $(this).text("Collapse All");
              permissionRows.show();
          } else {
              $(this).text("Expand All");
              permissionRows.hide();
          }
      });
  });
}

function better_perms_add_buttons(moduleRows) {
    // Passing in all module rows in case I want to put arrows on them later
    var firstRow = $("td.module:first").parent("tr");
    var buttonRow = firstRow.clone().insertBefore(firstRow);
    buttonRow.removeClass("odd");
    buttonRow.children("td:first").removeAttr("id").text("Expand All").removeClass("module").addClass("better-perms-row");
}