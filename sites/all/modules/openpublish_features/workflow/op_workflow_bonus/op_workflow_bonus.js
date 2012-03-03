$("document").ready(function() {
  if (Drupal.settings.op_workflow_bonus) {  
    var state_name = Drupal.settings.op_workflow_bonus.node_state;
    var state_color = Drupal.settings.op_workflow_bonus.status_color;
    if (state_name) {
      $('<li><span id="op-workflow-node-state-' + state_color + '">' + state_name + '</span></li>').insertBefore('div#drupal-control-bar > ul li:first');      
    }
  }
});