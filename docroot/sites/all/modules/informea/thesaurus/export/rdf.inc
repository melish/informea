<?php

class InforMEAThesaurusExportRDF {

  private static $SCHEME = 'http://www.informea.org/terms';

  public static function toXML() {
    $scheme = self::$SCHEME;
    // Start building up a RDF graph
    $voc = taxonomy_vocabulary_machine_name_load('thesaurus_informea');
    $all_terms = taxonomy_get_tree($voc->vid);
    $unique = array();
    $ret = array(
      <<<EOT
<?xml version="1.0" encoding="UTF-8"?>
<rdf:RDF
        xmlns="$scheme"
        xmlns:rdfs="http://www.w3.org/2000/01/rdf-schema#"
        xmlns:owl="http://www.w3.org/2002/07/owl#"
        xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
        xmlns:dct="http://purl.org/dc/terms/"
        xmlns:skos="http://www.w3.org/2004/02/skos/core#"
        xmlns:skosxl="http://www.w3.org/2008/05/skos-xl#"
        xmlns:ann="http://art.uniroma2.it/ontologies/annotation#">

    <rdf:Description rdf:about="$scheme">
        <rdf:type rdf:resource="http://www.w3.org/2004/02/skos/core#ConceptScheme"/>
        <skosxl:prefLabel rdf:resource="$scheme/xl-6e335fdf-dffc-4243-9852-5072f3841217"/>
    </rdf:Description>
    <rdf:Description rdf:about="$scheme/xl-6e335fdf-dffc-4243-9852-5072f3841217">
        <rdf:type rdf:resource="http://www.w3.org/2008/05/skos-xl#Label"/>
        <skosxl:literalForm xml:lang="en">InforMEA glossary scheme</skosxl:literalForm>
    </rdf:Description>
EOT
    );
    foreach ($all_terms as $term_sk) {
      if (in_array($term_sk->tid, $unique)) {
        continue;
      }
      $tid = $term_sk->tid;
      $term_ob = taxonomy_term_load($tid);
      $slug = slugify($term_ob->name_original);
      $uri = 'http://www.informea.org/terms/' . $slug;

      $output =
        <<<EOT
              <rdf:Description rdf:about="$uri">
        <rdf:type rdf:resource="http://www.w3.org/2004/02/skos/core#Concept"/>
        <skos:inScheme rdf:resource="$scheme"/>
EOT;
      $output .= "\n        " . sprintf('<skos:topConceptOf rdf:resource="%s"/>', $scheme);
      $definition = '';
      if (!empty($term_ob->description_field['en'][0]['value'])) {
        $definition = $term_ob->description_field['en'][0]['value'];
        $definition_uri = self::addDefinition($tid, $definition, $output);
        $output .= "\n        " . sprintf('<skos:definition rdf:resource="%s"/>', $definition_uri);
      }
      $prefLabel = '';
      $label_uri = self::addPrefLabel($tid, $term_ob->name_original, $prefLabel);
      $output .= "\n        " . sprintf('<skosxl:prefLabel rdf:resource="%s"/>', $label_uri);

      // skos:narrower
      /*
      $narrower = $thesaurus->get_narrower_terms($term->id);
      foreach($narrower as $n) {
          $n_slug = slugify($n->term);
          $n_uri = 'http://www.informea.org/terms/' . $n_slug;
          $output .= "\n        " .sprintf('<skos:narrower rdf:resource="%s"/>', $n_uri);
      }
      */

      // skos:broader
      $broader = $term_sk->parents;
      foreach ($broader as $ptid) {
        if ($ptid > 0) {
          $pterm = taxonomy_term_load($ptid);
          $b_slug = slugify($pterm->name_original);
          $b_uri = 'http://www.informea.org/terms/' . $b_slug;
          $output .= "\n        " . sprintf('<skos:broader rdf:resource="%s"/>', $b_uri);
        }
      }
      $output .= "\n    </rdf:Description>\n";
      $output .= $prefLabel;
      $output .= $definition;
      $ret[] = $output . "\n";
    }
    $ret[] = '</rdf:RDF>';
    return implode($ret, "\n");
  }


  public static function addDefinition($tid, $definition, &$buffer, $language = 'en') {
    $uri = self::$SCHEME . '/def_' . $tid;
    $description = self::xml_entities($definition);
    $buffer .= <<<EOT
    <rdf:Description rdf:about="$uri">
        <rdf:value xml:lang="$language">$description /n</rdf:value>
    </rdf:Description>
EOT;
    return $uri;
  }

  public static function addPrefLabel($tid, $label, &$buffer, $language = 'en') {
    $uri = self::$SCHEME . '/xl_' . $language . '_' . $tid;
    $title = self::xml_entities($label);
    $buffer .= <<<EOT
    <rdf:Description rdf:about="$uri">
        <rdf:type rdf:resource="http://www.w3.org/2008/05/skos-xl#Label"/>
        <skosxl:literalForm xml:lang="$language">$title</skosxl:literalForm>
    </rdf:Description>\n
EOT;
    return $uri;
  }

  public static function xml_entities($string) {
    return strtr(
      $string,
      array(
        "<" => "&lt;",
        ">" => "&gt;",
        '"' => "&quot;",
        "'" => "&apos;",
        "&" => "&amp;",
      )
    );
  }
}
