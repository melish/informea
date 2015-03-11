<?php
/**
 * Author: Cristian Romanescu <cristi _at_ eaudeweb dot ro>
 * Created: 201411171151
 */

class InforMEAExportRDF {

  private static $SCHEME = 'http://www.informea.org/terms';

  public static function toXML($terms) {
    $scheme = self::$SCHEME;
    // Start building up a RDF graph
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
    foreach($terms as $tid => $meta) {
      $w = entity_metadata_wrapper('taxonomy_term', $tid);
      $label = $w->name_field->value();
      if (!empty($label)) {
        $description = $w->description_field->value();

        $slug = self::slugify($label);
        $uri = $scheme . '/' . $slug;

        $output =
          <<<EOT
              <rdf:Description rdf:about="$uri">
        <rdf:type rdf:resource="http://www.w3.org/2004/02/skos/core#Concept"/>
        <skos:inScheme rdf:resource="$scheme"/>
EOT;
        $output .= "\n        " . sprintf('<skos:topConceptOf rdf:resource="%s"/>', $scheme);
        $definition = '';
        if (!empty($description)) {
          $definition_uri = self::addDefinition($tid, $description, $definition);
          $output .= "\n        " . sprintf('<skos:definition rdf:resource="%s"/>', $definition_uri);
        }
        $prefLabel = '';
        $label_uri = self::addPrefLabel($tid, $label, $prefLabel);
        $output .= "\n        " . sprintf('<skosxl:prefLabel rdf:resource="%s"/>', $label_uri);

        // skos:narrower
        /*
        $narrower = $thesaurus->get_narrower_terms($term->id);
        foreach($narrower as $n) {
            $n_slug = self::slugify($n->term);
            $n_uri = $scheme . '/' . $n_slug;
            $output .= "\n        " .sprintf('<skos:narrower rdf:resource="%s"/>', $n_uri);
        }
        */

        // skos:broader
        /*
        $broader = $thesaurus->get_broader_terms_full($tid);
        foreach ($broader as $b) {
          $b_slug = self::slugify($b->term);
          $b_uri = $scheme . '/' . $b_slug;
          $output .= "\n        " . sprintf('<skos:broader rdf:resource="%s"/>', $b_uri);
        }
        */

        $output .= "\n    </rdf:Description>\n";
        $output .= $prefLabel;
        $output .= $definition;
        $ret[] = $output . "\n";
      }
    }
    $ret[] = '</rdf:RDF>';
    return implode($ret, "\n");
  }


  public static function addDefinition($tid, $description, &$buffer, $language = 'en') {
    $uri = self::$SCHEME . '/def_' . $tid;
    $description = self::xml_entities($description);
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

  public static function addPrefLabelEcolex($term, &$buffer, $language = 'en') {
    $slug = self::slugify($term, '_');
    $uri = self::$SCHEME . '/xl_' . $language . '_' . $slug;
    $title = self::xml_entities($term);
    $buffer .= <<<EOT
    <rdf:Description rdf:about="$uri">
        <rdf:type rdf:resource="http://www.w3.org/2008/05/skos-xl#Label"/>
        <skosxl:literalForm xml:lang="$language">$title</skosxl:literalForm>
    </rdf:Description>\n
EOT;
    return $uri;
  }

  public static function toEcolexXML() {
    $scheme = 'http://www.ecolex.org/glossary';
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
        <skosxl:literalForm xml:lang="en">ECOLEX glossary</skosxl:literalForm>
    </rdf:Description>
EOT
    );

    $handle = fopen(dirname(__FILE__) . "/ecolex.txt", "r");
    if ($handle) {
      while (($term = fgets($handle)) !== false) {
        $slug = self::slugify($term);
        $uri = $scheme . '/' . $slug;

        $output =
          <<<EOT
    <rdf:Description rdf:about="$uri">
        <rdf:type rdf:resource="http://www.w3.org/2004/02/skos/core#Concept"/>
        <skos:inScheme rdf:resource="$scheme"/>
EOT;
        $output .= "\n        " . sprintf('<skos:topConceptOf rdf:resource="%s"/>', $scheme);
        $prefLabel = '';
        $label_uri = self::addPrefLabelEcolex($term, $prefLabel);
        $output .= "\n        " . sprintf('<skosxl:prefLabel rdf:resource="%s"/>', $label_uri);

        $output .= "\n    </rdf:Description>\n";
        $output .= $prefLabel;
        $ret[] = $output . "\n";
      }
    }
    fclose($handle);
    $ret[] = '</rdf:RDF>';
    return implode($ret, "\n");
  }

  function xml_entities($string) {
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

  /**
   * Slugify a string.
   *
   * @param string $phrase Text to slugify
   * @param int $maxLength Maximum slug length
   * @return string Slugified string
   */
  function slugify($phrase, $replace = "-") {
    $result = strtolower($phrase);
    $result = preg_replace("/[^a-z0-9\s-]/", "", $result);
    $result = trim(preg_replace("/[\s-]+/", " ", $result));
    $result = preg_replace("/\s/", $replace, $result);
    return $result;
  }
}
