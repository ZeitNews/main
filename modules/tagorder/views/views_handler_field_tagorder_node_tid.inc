<?php
/**
 * Field handler for terms.
 */
class views_handler_field_tagorder_node_tid extends views_handler_field_term_node_tid {
  function pre_render($values) {
    $this->field_alias = $this->aliases['vid'];
    $vids = array();
    foreach ($values as $result) {
      if (!empty($result->{$this->aliases['vid']})) {
        $vids[] = $result->{$this->aliases['vid']};
      }
    }

    if ($vids) {
      $voc = '';
      if (!empty($this->options['limit']) && !empty($this->options['vids'])) {
        $voc = " AND td.vid IN (" . implode(', ', array_keys(array_filter($this->options['vids']))) . ")";
      }

      // Fetch the term weight in Tag Order for the selected nodes.
      $weights = array();
      $result = db_query("SELECT vid, tid, weight FROM {tagorder} WHERE vid IN (" . implode(', ', $vids) . ") ORDER BY weight");
      while ($data = db_fetch_object($result)) {
        $weights[$data->vid][$data->tid] = $data->weight;
      }

      // Fetch the terms, group by node vid and taxonomy vid.
      $orig_terms = array();
      $result = db_query("SELECT tn.vid AS node_vid, td.* FROM {term_data} td INNER JOIN {term_node} tn ON td.tid = tn.tid WHERE tn.vid IN (" . implode(', ', $vids) . ")$voc ORDER BY td.weight, td.name");
      while ($term = db_fetch_object($result)) {
        $orig_terms[$term->node_vid][$term->vid][] = $term;
      }

      // Short the terms for each vocabulary.
      $tagorder_vocabids = variable_get('tagorder_vocab', array('tags'));
      foreach ($orig_terms as $node_vid => $node_terms) {
        foreach($node_terms as $vid => $terms) {
          // Only needs reordering if the term is in a Tag Ordered vocabulary.
          if (in_array($vid, $tagorder_vocabids)) {
            foreach ($terms as $term) {
              if (!empty($weights[$node_vid]) && array_key_exists($term->tid, $weights[$node_vid])) {
                $term->weight = $weights[$node_vid][$term->tid];
              }
            }
            usort($terms, "tagorder_cmp");
          }

          // Prepare the terms to be rendered.
          foreach ($terms as $term) {
            if (empty($this->options['link_to_taxonomy'])) {
              $this->items[$term->node_vid][$term->tid] = check_plain($term->name);
            }
            else {
              $this->items[$term->node_vid][$term->tid] = l($term->name, taxonomy_term_path($term), array('attributes' => array('rel' => 'tag', 'title' => $term->name)));
            }
          }
        }
      }
    }
  }
}
