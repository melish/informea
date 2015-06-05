<?php
if (!class_exists('UNDataOrgParser')) {
  /**
   * Parse content from UN Data Website results page
   * i.e. http://data.un.org/CountryProfile.aspx?crName=Romania
   */
  class UNDataOrgParser {
    private $url = null;
    private $curl_timeout = 10;

    private $id_country = null;
    private $country_name = null;

    private $html = null;
    private $doc = null;

    public static $WWW_URL = 'http://data.un.org/CountryProfile.aspx?crName=';
    public static $WWW_IMG_URL = 'http://data.un.org/';

    private $img = null;
    private $environment = null;
    private $parsed = false;

    /**
     * @param string $id_country - Country internal ID
     * @param string $country_name - Country name
     */
    public function __construct($id_country, $country_name) {
      $this->id_country = $id_country;
      $this->country_name = $country_name;
      $this->url = self::$WWW_URL . trim($country_name);
    }

    protected function get_remote_dom() {
      //echo "Retrieving the HTML content from {$this->url}\n";
      if ($this->parsed) {
        return $this->doc;
      }
      $ch = curl_init();
      $this->parsed = true;
      $url = str_replace(' ', '%20', $this->url);
      curl_setopt($ch, CURLOPT_URL, $url);
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
      curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $this->curl_timeout);
      curl_setopt($ch, CURLOPT_HTTPHEADER, Array("User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.15) Gecko/20080623 Firefox/2.0.0.15 InforMEA"));
      curl_setopt($ch, CURLOPT_NOBODY, 0);
      $this->html = utf8_decode(curl_exec($ch));
      curl_close($ch);

      //echo "    * Parsing the HTML content\n";
      if (!empty($this->html)) {
        $d = new DOMDocument();
        $d->strictErrorChecking = false;
        $d->recover = true;
        libxml_use_internal_errors(true);
        $d->loadHTML($this->html);
        libxml_use_internal_errors(false);
        $this->doc = $d;
        return $d;
      }
      return null;
    }


    /**
     * Returns the country map image url.
     * @return string URL
     */
    public function get_map_image() {
      if (!empty($this->img)) {
        return $this->img;
      }
      $ret = null;
      $doc = $this->get_remote_dom();
      if ($doc) {
        $cn = $this->doc->getElementById('ctl00_main_MapSection');
        if ($cn) {
          $imgs = $cn->getElementsByTagName('img');
          if ($imgs->length > 0) {
            $ret = $imgs->item(0);
            $ret = self::$WWW_IMG_URL . $ret->getAttribute('src');
            $this->img = $ret;
          }
        }
      }
      return $ret;
    }

    /**
     * Returns the Environment section from country profile
     * @return string HTML
     */
    public function get_environmental_data() {
      $ret = '';
      $cid = 'informea-undata-' . $this->id_country;
      if($cache = cache_get($cid)) {
        $ret = $cache->data;
      }
      else {
        $doc = $this->get_remote_dom();
        if ($doc) {
          $cn = $this->doc->getElementById('Environment');
          if ($cn) {
            $table = $cn->nextSibling->nextSibling;
            if ($table && $table->nodeName == 'table') {
              $newdoc = new DOMDocument();
              $cloned = $table->cloneNode(TRUE);
              $newdoc->appendChild($newdoc->importNode($cloned, TRUE));
              $ret = $newdoc->saveHTML();
              cache_set($cid, $ret, 'cache', date('U') + 3600 * 24 * 5);
            }
          }
        }
      }
      return $ret;
    }

    /**
     * Returns the raw HTML as was loaded from Ecolex website
     */
    public function get_raw_html() {
      $this->parse_html();
      return $this->html;
    }
  }
}
