<?php
// $Id;

/* --------------------------------- Fetchers --------------------------------- */
/**
 * OkhubContentFetcherResult Class
 */
class OkhubContentFetcherResult extends FeedsFetcherResult {

  // Object of type OkhubApiResponse that holds the results of the API call.
  public $okhub_api_response;

 /**
  * Constructor. Makes the call to the OKhub API.
  */
  public function __construct($fetcher) {
    $this->okhub_api_response = $fetcher->okhub_api_wrapper->makeRequest();
  }

}

/*
 * OkhubAssetsFetcher Class
 */
class OkhubAssetsFetcher extends FeedsHTTPFetcher {

  // Object of type OkhubApiWrapper that performs the API request.
  public $okhub_api_wrapper;
  
	public function setOffset($start_offset){
		$this->okhub_api_wrapper->setOffset($start_offset);
	}

  /**
   * Overrides parent::__construct().
   */
  public function __construct() {
    $this->okhub_api_wrapper = new OkhubApiWrapper();
    $this->okhub_api_wrapper->setApiKey(variable_get('okhubapi_api_key', ''));
    $this->okhub_api_wrapper->setSite(variable_get('okhubimport_default_dataset', OKHUB_API_DEFAULT_DATASET));
    $this->okhub_api_wrapper->setNumRequested(variable_get('okhubimport_number_assets', OKHUB_IMPORT_NUM_ASSETS));
    $this->okhub_api_wrapper->setAgeResults(variable_get('okhubimport_age_new_assets', OKHUB_IMPORT_AGE_NEW_ASSETS));
    $this->okhub_api_wrapper->setPriorityDatasource(variable_get('okhubimport_priority_datasource', ''));
    $this->okhub_api_wrapper->setPriorityLanguage(variable_get('okhubimport_priority_language', ''));
    $this->okhub_api_wrapper->setFormat('full');
    if ($query_string = variable_get('okhubimport_query_string')) {
      $this->okhub_api_wrapper->setQueryString($query_string);
    }
  }

  /**
   * Overrides parent::fetch().
   */
  public function fetch(FeedsSource $source) {
    $this->okhub_api_wrapper->setObjectType($this->config['asset_type']);
    $datasources = _okhubapi_get_datasources_param();
    if($datasources) {
      $this->okhub_api_wrapper->setParam('source', $datasources);
    }
    $themes = _okhubapi_get_themes_param();
    if($themes) {
      $this->okhub_api_wrapper->setParam('theme_id', $themes);
    }
    $lang = _okhubapi_get_lang_param();
    if($lang) {
      $this->okhub_api_wrapper->setParam('lang', $lang);
    }

   	if((variable_get('okhubimport_get_assets_older_content', OKHUB_IMPORT_GET_ASSETS_OLDER_CONTENT_NONE) != OKHUB_IMPORT_GET_ASSETS_OLDER_CONTENT_NONE)){
 	  	$batch_amount = variable_get('okhubimport_number_assets', OKHUB_IMPORT_NUM_ASSETS);
     	$source_config = $source->getConfigFor($this);
     	//$config = $source_config['crawler'];
    	
 	    $state = $source->state(FEEDS_FETCH);
 	    if ($state->total == 0) {
 	      $state->total = (variable_get('okhubimport_get_assets_older_content', OKHUB_IMPORT_GET_ASSETS_OLDER_CONTENT_NONE) == OKHUB_IMPORT_GET_ASSETS_OLDER_CONTENT_ALL) ? $this->getTotalResults() : variable_get('okhubimport_number_assets_older_content', OKHUB_IMPORT_NUM_ASSETS_OLDER_CONTENT);
 	      $state->count = $state->total;
 	    }
 	    $this->okhub_api_wrapper->setOffset($state->count);
 		
 	    $fetcher_result = new OkhubContentFetcherResult($this);

 	    if ($state->count > 0) {
 	      $state->count -= $batch_amount;
	      $statecount = ($state->count < 0) ? 0:$state->count;
	      $state->progress($state->total, $state->total - $statecount);
 	    }
 	    else {
 	      $state->progress($state->total, $state->total);
 	    }
 	    return $fetcher_result;
     } else {
 	  	$fetcher_result = new OkhubContentFetcherResult($this);
 	    return $fetcher_result;
     }    
    
  }
  
  private function getTotalResults() {
   	    $fetcher_result = new OkhubContentFetcherResult($this);
   	    return $fetcher_result->okhub_api_response->total_results;	
  }
  
  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    return array(
      'asset_type' => 'documents',
    );
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = array();
    $form['asset_type'] = array(
      '#title' => t('Type of asset'),
      '#type' => 'select',
      '#options' => array(
        'documents' => t('Documents'),
        'organisations' => t('Organisations'),
       ),
      '#required' => TRUE,
      '#default_value' => $this->config['asset_type'],
      '#description' => t('Please indicate the type of asset that you want to import.'),
    );
    return $form;
  }

}

/*
 * OkhubCategoriesFetcher Class
 */
class OkhubCategoriesFetcher extends FeedsFetcher {

  public $okhub_api_wrapper;

  /**
   * Overrides parent::__construct().
   */
  public function __construct() {
  	
    $this->okhub_api_wrapper = new OkhubApiWrapper();
    $this->okhub_api_wrapper->setApiKey(variable_get('okhubapi_api_key', ''));
    $this->okhub_api_wrapper->setSite(variable_get('okhubimport_default_dataset', OKHUB_API_DEFAULT_DATASET));
    $this->okhub_api_wrapper->setPriorityDatasource(variable_get('okhubimport_priority_datasource', ''));
    $this->okhub_api_wrapper->setPriorityLanguage(variable_get('okhubimport_priority_language', ''));
    $this->okhub_api_wrapper->setFormat('full');
    if ($query_string = variable_get('okhubimport_query_string')) {
      $this->okhub_api_wrapper->setQueryString($query_string);
    }
  }

  /**
   * Overrides parent::fetch().
   * Note: The defined default dataset is used.
   */
  public function fetch(FeedsSource $source) {

    $this->okhub_api_wrapper->setObjectType($this->config['category_type']);
    if (($this->config['category_type'] == 'themes') || ($this->config['category_type'] == 'subjects') || ($this->config['category_type'] == 'regions')) {
   /*   if ($levels = variable_get('okhubimport_levels_categories')) {
        $this->okhub_api_wrapper->setParam('level', $levels);
      }*/
    }
    $datasources = _okhubapi_get_datasources_param();
    if ($datasources) {
      $this->okhub_api_wrapper->setParam('source', $datasources);
    }
      	
    $fetcher_result = new OkhubContentFetcherResult($this);
    return $fetcher_result;
  }
  
  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    return array(
      'category_type' => 'themes',
    );
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = array();
    $form['category_type'] = array(
      '#title' => t('Type of category'),
      '#type' => 'select',
      '#options' => array(
        'themes' => t('Themes'),
        'subjects' => t('Subjects'),
        'regions' => t('Regions'),
        'countries' => t('Countries'),
       ),
      '#required' => TRUE,
      '#default_value' => $this->config['category_type'],
      '#description' => t('Please indicate the type of category that you want to import.'),
    );
    return $form;
  }

}

/* --------------------------------- Parsers --------------------------------- */

/*
 * OkhubAssetsParser Class
 */
class OkhubAssetsParser extends FeedsParser {

  /**
   * Defines mapping sources.
   */
  public function getMappingSources() {
    return array(
      'object_id' => array(
        'name' => t('Item ID'),
        'description' => t('ID of the item in the OKhub collection.'),
      ),
      'object_type' => array(
        'name' => t('Item Type'),
        'description' => t('Type of the item'),
      ),
      'title' => array(
        'name' => t('Title'),
        'description' => t('Title of the item'),
      ),
      'metadata_url' => array(
        'name' => t('Metadata URL'),
        'metadata_url' => t('URL with the OKhub API metadata of the item'),
      ),
    );
  }

  /**
   * Calls the fetcher and parses the results.
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    $result = new FeedsParserResult();
    $response = $fetcher_result->okhub_api_response;
    if ($response instanceof OkhubApiResponse) {
      $results = $response->getResults();
      foreach($results as $asset) {
        $item = array(
          'object_id' => $asset->get_value(OKHUB_API_FN_ITEM_ID),
          'object_type' => $asset->get_value(OKHUB_API_FN_ITEM_TYPE),
          'title' => $asset->get_value(OKHUB_API_FN_TITLE),
          'metadata_url' => $asset->get_value(OKHUB_API_FN_METADATA_URL),
        );
        $result->items[] = $item;
      }
    }
    return $result;
  }

}

/*
 * OkhubDocumentsParser Class
 */
class OkhubDocumentsParser extends FeedsParser {

  /**
   * Defines mapping sources.
   */
  public function getMappingSources() {
    return array(
      'object_id' => array(
        'name' => t('Item ID'),
        'description' => t('Unique identifier of this item (for example, A1417).'),
      ),
      'object_type' => array(
        'name' => t('Item type'),
        'description' => t('Type of item. (Document, Publication, Theme, Subject, Region, Country).'),
      ),
      'title' => array(
        'name' => t('Title'),
        'description' => t('Readable identifier of this item.'),
      ),
      'site' => array(
        'name' => t('Site'),
        'description' => t('Dataset (hub).'),
      ),
      'sources' => array(
        'name' => t('Sources'),
        'description' => t('Dataset (eldis, bridge, ccccc etc...).'),
      ),
      'metadata_url' => array(
        'name' => t('Metadata URL'),
        'description' => t('Web-accessible uri for this item.'),
      ),
      'timestamp' => array(
        'name' => t('Timestamp'),
        'description' => t('Indicates when record was indexed in the API.'),
      ),
      'website_url' => array(
        'name' => t('Website URL'),
        'description' => t('URL for the asset on the collection website.'),
      ),
      'document_type' => array(
        'name' => t('Document Type'),
        'description' => t('The type of document this item is.'),
      ),
/*      'name' => array(
        'name' => t('Name'),
        'description' => t('Name of the item.'),
      ),*/
/*      'asset_id' => array(
        'name' => t('Asset ID'),
        'description' => t('Asset identifier (for example, 12345).'),
      ),*/
      'date_created' => array(
        'name' => t('Date created'),
        'description' => t('Creation date. (Example: 2012-02-09 14:36:21). Date in which the item was added to the collection.'),
      ),
      'date_updated' => array(
        'name' => t('Date updated'),
        'description' => t('Modification date. (Example: 2012-02-09 14:36:21). Date in which the item was last modified.'),
      ),
      'category_theme_array' => array(
        'name' => t('Themes'),
        'description' => t('Thematic categories which apply to the document.'),
      ),
      'category_subject_array' => array(
        'name' => t('Subjects'),
        'description' => t('Subject categories which apply to the document.'),
      ),
      'category_region_array' => array(
        'name' => t('Regions'),
        'description' => t('Regions that apply to the document.'),
      ),
      'country_focus_array' => array(
        'name' => t('Countries'),
        'description' => t('Countries that apply to the document.'),
      ),
      'keywords' => array(
        'name' => t('Keywords'),
        'description' => t('Subject keywords that relate to the asset.'),
      ),
      'description' => array(
        'name' => t('Description'),
        'description' => t('Description of the document.'),
      ),
      'authors' => array(
        'name' => t('Authors'),
        'description' => t('Authors (First initial. Surname).'),
      ),
      'language_name' => array(
        'name' => t('Language'),
        'description' => t('The language in which the title, headline and description are written.'),
      ),
      'publication_date' => array(
        'name' => t('Publication date'),
        'description' => t('Year when the research document was first published.'),
      ),
      'publisher' => array(
        'name' => t('Publisher'),
        'description' => t('Name of the organisation that published the research.'),
      ),
/*      'publisher_id' => array(
        'name' => t('Publisher ID'),
        'description' => t('Item ID of the organisation that published the research.'),
      ),*/
      'licence_type' => array(
        'name' => t('Licence type'),
        'description' => t('Licence type.'),
      ),
      'urls' => array(
        'name' => t('External URLs'),
        'description' => t('External URLs of the full text document.'),
      ),
      'headline' => array(
        'name' => t('Headline'),
        'description' => t('Headline or short description of title of the document.'),
      ),
    );
  }

  /**
   * Calls the fetcher and parses the results.
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    $result = new FeedsParserResult();
    $response = $fetcher_result->okhub_api_response;
    if ($response instanceof OkhubApiResponse) {
      $results = $response->getResults();
      foreach($results as $asset) {
        $item = array(
          'object_id' => $asset->get_value(OKHUB_API_FN_ITEM_ID),
          'object_type' => $asset->get_value(OKHUB_API_FN_ITEM_TYPE),
          'document_type' => $asset->get_value(OKHUB_API_FN_DOCUMENT_TYPE),
          'title' => $asset->get_value(OKHUB_API_FN_TITLE),
          'site' => $asset->get_value(OKHUB_API_FN_SITE),
          'sources' => $asset->get_value(OKHUB_API_FN_SOURCES),
          'metadata_url' => $asset->get_value(OKHUB_API_FN_METADATA_URL),
          'timestamp' => $asset->get_value(OKHUB_API_FN_TIMESTAMP),
          'website_url' => $asset->get_value(OKHUB_API_FN_WEBSITE_URL),
/*          'name' => $asset->get_value(OKHUB_API_FN_NAME),*/
/*          'asset_id' => $asset->get_value(OKHUB_API_FN_ITEM_ID),*/
          'date_created' => $asset->get_value(OKHUB_API_FN_DATE_CREATED),
          'date_updated' => $asset->get_value(OKHUB_API_FN_DATE_UPDATED),
          'category_theme_array' => $asset->get_value(OKHUB_API_FN_THEME_DATA),
          'category_subject_array' => $asset->get_value(OKHUB_API_FN_SUBJECT_DATA),
          'category_region_array' => $asset->get_value(OKHUB_API_FN_REGION_DATA),
          'country_focus_array' => $asset->get_value(OKHUB_API_FN_COUNTRY_DATA),
          'keywords' => $asset->get_value('keywords'),
          'description' => $asset->get_value(OKHUB_API_FN_DESCRIPTION),
          'authors' => $asset->get_value('author'),
          'language_name' => $asset->get_value(OKHUB_API_FN_METADATA_LANGAUAGES),
          'publication_date' => $asset->get_value('publication_date'),
          'publisher' => $asset->get_value('publisher'),
/*          'publisher_id' => $asset->get_value('publisher_id'),*/
          'licence_type' => $asset->get_value('licence_type'),
          'urls' => $asset->get_value(OKHUB_API_FN_URLS),
        );
        $result->items[] = $item;
      }
    }
    return $result;
  }

}

/*
 * OkhubOrganisationsParser Class
 */
class OkhubOrganisationsParser extends FeedsParser {

  /**
   * Defines mapping sources.
   */
  public function getMappingSources() {
    return array(
      'object_id' => array(
        'name' => t('Item ID'),
        'description' => t('Unique identifier of this item (for example, A1417).'),
      ),
      'object_type' => array(
        'name' => t('Item type'),
        'description' => t('Type of item. (Document, Publication, Theme, Subject, Region, Country).'),
      ),
      'title' => array(
        'name' => t('Title'),
        'description' => t('Readable identifier of this item.'),
      ),
      'site' => array(
        'name' => t('Site'),
        'description' => t('Dataset (hub).'),
      ),
      'sources' => array(
        'name' => t('Sources'),
        'description' => t('Dataset (eldis, bridge, ccccc etc...).'),
      ),
      'metadata_url' => array(
        'name' => t('Metadata URL'),
        'description' => t('Web-accessible uri for this item.'),
      ),
      'timestamp' => array(
        'name' => t('Timestamp'),
        'description' => t('Indicates when record was indexed in the API.'),
      ),
      'website_url' => array(
        'name' => t('Website URL'),
        'description' => t('URL for the asset on the collection website.'),
      ),
      'name' => array(
        'name' => t('Name'),
        'description' => t('Name of the item.'),
      ),
/*      'asset_id' => array(
        'name' => t('Asset ID'),
        'description' => t('Asset identifier (for example, 12345).'),
      ),*/
      'date_created' => array(
        'name' => t('Date created'),
        'description' => t('Creation date. (Example: 2012-02-09 14:36:21). Date in which the item was added to the collection.'),
      ),
      'date_updated' => array(
        'name' => t('Date updated'),
        'description' => t('Modification date. (Example: 2012-02-09 14:36:21). Date in which the item was last modified.'),
      ),
      'category_theme_array' => array(
        'name' => t('Themes'),
        'description' => t('Thematic categories which apply to the organisation.'),
      ),
      'category_subject_array' => array(
        'name' => t('Subjects'),
        'description' => t('Subject categories which apply to the organisation.'),
      ),
      'category_region_array' => array(
        'name' => t('Regions'),
        'description' => t('Regions that apply to the organisation.'),
      ),
      'country_focus_array' => array(
        'name' => t('Countries'),
        'description' => t('Countries that apply to the organisation.'),
      ),
      'keywords' => array(
        'name' => t('Keywords'),
        'description' => t('Subject keywords that relate to the organisation.'),
      ),
      'description' => array(
        'name' => t('Description'),
        'description' => t('Description of the organisation.'),
      ),
      'acronym' => array(
        'name' => t('Acronym'),
        'description' => t('Acronym of organisation.'),
      ),
      'alternative_acronym' => array(
        'name' => t('Alternative acronym'),
        'description' => t('Alternative acronym of organisation.'),
      ),
      'alternative_name' => array(
        'name' => t('Alternative name'),
        'description' => t('Alternative name of organisation.'),
      ),
      'organisation_type' => array(
        'name' => t('Organisation type'),
        'description' => t('Primary function or role of the organisation in relation to international development.'),
      ),
      'organisation_url' => array(
        'name' => t('Organisation URL'),
        'description' => t('Link to the organisation website.'),
      ),
      'location_country' => array(
        'name' => t('Location country'),
        'description' => t('Country where the organisation is located.'),
      ),
    );
  }

  /**
   * Calls the fetcher and parses the results.
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    $result = new FeedsParserResult();
    $response = $fetcher_result->okhub_api_response;
    if ($response instanceof OkhubApiResponse) {
      $results = $response->getResults();
      foreach($results as $asset) {
        $item = array(
          'object_id' => $asset->get_value(OKHUB_API_FN_ITEM_ID),
          'object_type' => $asset->get_value(OKHUB_API_FN_ITEM_TYPE),
          'title' => $asset->get_value(OKHUB_API_FN_TITLE),
          'site' => $asset->get_value(OKHUB_API_FN_SITE),
          'sources' => $asset->get_value(OKHUB_API_FN_SOURCES),
          'metadata_url' => $asset->get_value(OKHUB_API_FN_METADATA_URL),
          'timestamp' => $asset->get_value(OKHUB_API_FN_TIMESTAMP),
          'website_url' => $asset->get_value(OKHUB_API_FN_WEBSITE_URL),
          'name' => $asset->get_value(OKHUB_API_FN_NAME),
          'date_created' => $asset->get_value(OKHUB_API_FN_DATE_CREATED),
          'date_updated' => $asset->get_value(OKHUB_API_FN_DATE_UPDATED),
          'category_theme_array' => $asset->get_value(OKHUB_API_FN_THEME_DATA),
          'category_subject_array' => $asset->get_value(OKHUB_API_FN_SUBJECT_DATA),
          'category_region_array' => $asset->get_value(OKHUB_API_FN_REGION_DATA),
          'country_focus_array' => $asset->get_value(OKHUB_API_FN_COUNTRY_DATA),
          'keywords' => $asset->get_value('keywords'),
          'description' => $asset->get_value(OKHUB_API_FN_DESCRIPTION),
          'acronym' => $asset->get_value('acronym'),
          'alternative_acronym' => $asset->get_value('acronym'),
          'alternative_name' => $asset->get_value(OKHUB_API_FN_NAME),
          'organisation_type' => $asset->get_value('organisation_type'),
          'organisation_url' => $asset->get_value('organisation_url'),
          'location_country' => $asset->get_value('country'),
        );
        $result->items[] = $item;
      }
    }
    return $result;
  }

}

/*
 * OkhubCategoriesParser Class
 */
class OkhubCategoriesParser extends FeedsParser {

  public function getMappingSources() {
    return array(
      'name' => array(
        'name' => t('Name'),
        'description' => t('Name of the category.'),
      ),  
      'title' => array(
        'name' => t('Title'),
        'description' => t('Title of the category.'),
      ),    
      'category_id' => array(
        'name' => t('Category ID'),
        'description' => t('ID of the category in the OKhub collection.'),
      ),
      'cat_parent' => array(
        'name' => t('Parent category'),
        'description' => t('ID of the parent category in this vocabulary.'),
      ),
      'cat_superparent' => array(
        'name' => t('Root category'),
        'description' => t('ID of the root category in this vocabulary.'),
      ),
      'site' => array(
        'name' => t('Site'),
        'description' => t('Name of the collection to which this category belongs.'),
      ),
      'sources' => array(
        'name' => t('Sources'),
        'description' => t('Names of the sources to which this category belongs'),
      ),
      'website_url' => array(
        'name' => t('Website URL'),
        'description' => t('Link to the region page on the site URL, where applicable.'),
      ),
      'metadata_url' => array(
        'name' => t('Metadata URL'),
        'description' => t('Web-accessible OKhub API URI for this object.'),
      ),
      'object_id' => array(
        'name' => t('Item ID'),
        'description' => t('Unique identifier of this item in the OKhub collection.'),
      ),
      'object_type' => array(
        'name' => t('Item Type'),
        'description' => t('The type of the category in the OKhub collection.'),
      ),
      'timestamp' => array(
        'name' => t('Timestamp'),
        'description' => t('Indicates when record was indexed in the OKhub collection. Timestamp is in ISO 8601 format: YYYY-MM-DD hh:mm:ss.'),
      ),
    /*  'archived' => array(
        'name' => t('Archived'),
        'description' => t('Indicates if the category is archived. Archived categories are not imported as taxonomy terms.'),
      ),*/
    );
  }

  /**
   * Call the fetcher and parses the results.
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    $result = new FeedsParserResult();
    $response = $fetcher_result->okhub_api_response;
    if ($response instanceof OkhubApiResponse) {
      $results = $response->getResults();
      foreach($results as $category) {
        $item = array(
          'name' => $category->get_value(OKHUB_API_FN_NAME),
          'title' => $category->get_value(OKHUB_API_FN_TITLE),
          'category_id' => $category->get_value(OKHUB_API_FN_ITEM_ID),
          'cat_superparent' => FALSE,
          'parent_object_id' => FALSE,
          'site' => $category->get_value(OKHUB_API_FN_SITE),
          'sources' => $category->get_value(OKHUB_API_FN_SOURCES),
          'website_url' => $category->get_value(OKHUB_API_FN_WEBSITE_URL),
          'metadata_url' => $category->get_value(OKHUB_API_FN_METADATA_URL),
          'object_id' => $category->get_value(OKHUB_API_FN_ITEM_ID),
          'object_type' => $category->get_value(OKHUB_API_FN_ITEM_TYPE),
          'timestamp' => $category->get_value(OKHUB_API_FN_TIMESTAMP),
        );
    /*    if (isset($category->archived) && ($category->archived === 'true')) {
          $item['archived'] = 1;
        }
        else {
          $item['archived'] = 0;
        }*/
/*        if (($category->cat_parent == 1) || ($category->cat_parent == 2)){
          $item['cat_parent'] = 0;
        }
        else {
          $item['cat_parent'] = $category->cat_parent;
        }*/
        $result->items[] = $item;
      }
    }
    return $result;
  }

}

/*
 * OkhubCountriesParser Class
 */
class OkhubCountriesParser extends FeedsParser {

  /**
   * Defines mapping sources.
   */
  public function getMappingSources() {
    return array(
      'object_id' => array(
        'name' => t('Item ID'),
        'description' => t('Unique identifier of this item (for example, A1417).'),
      ),
      'object_type' => array(
        'name' => t('Item type'),
        'description' => t('Type of item. (Document, Publication, Theme, Subject, Region, Country).'),
      ),
      'title' => array(
        'name' => t('Title'),
        'description' => t('Readable identifier of this item.'),
      ),
      'site' => array(
        'name' => t('Site'),
        'description' => t('Dataset (eldis or bridge).'),
      ),
      'sources' => array(
        'name' => t('Sources'),
        'description' => t('Dataset (eldis, bridge, ccccc etc...).'),
      ),
      'metadata_url' => array(
        'name' => t('Metadata URL'),
        'description' => t('Web-accessible uri for this item.'),
      ),
      'timestamp' => array(
        'name' => t('Timestamp'),
        'description' => t('Indicates when record was indexed in the API.'),
      ),
      'website_url' => array(
        'name' => t('Website URL'),
        'description' => t('URL for the asset on the collection website.'),
      ),
      'name' => array(
        'name' => t('Name'),
        'description' => t('Name of the country.'),
      ),
      'alternative_name' => array(
        'name' => t('Alternative name'),
        'description' => t('Alternative name of the country.'),
      ),
/*      'asset_id' => array(
        'name' => t('Asset ID'),
        'description' => t('Country identifier (for example, 12345).'),
      ),*/
      'iso_number' => array(
        'name' => t('ISO number'),
        'description' => t('ISO number. Example: 50 (Bangladesh).'),
      ),
      'iso_three_letter_code' => array(
        'name' => t('ISO three-letter code'),
        'description' => t('ISO three-letter code. Example: BGD (Bangladesh).'),
      ),
      'iso_two_letter_code' => array(
        'name' => t('ISO two-letter code'),
        'description' => t('ISO two-letter code. Example: BD (Bangladesh).'),
      ),
      'category_region_array' => array(
        'name' => t('Regions'),
        'description' => t('Regions to which this country belongs..'),
      ), 
    );
  }

  /**
   * Calls the fetcher and parses the results.
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    $result = new FeedsParserResult();
    $response = $fetcher_result->okhub_api_response;
    if ($response instanceof OkhubApiResponse) {
      $results = $response->getResults();
      foreach($results as $country) {
        $item = array(
          'object_id' => $country->get_value(OKHUB_API_FN_ITEM_ID),
          'object_type' => $country->get_value(OKHUB_API_FN_ITEM_TYPE),
          'title' => $country->get_value(OKHUB_API_FN_TITLE),
          'site' => $country->get_value(OKHUB_API_FN_SITE),
          'sources' => $country->get_value(OKHUB_API_FN_SOURCES),
          'metadata_url' => $country->get_value(OKHUB_API_FN_METADATA_URL),
          'timestamp' => $country->get_value(OKHUB_API_FN_TIMESTAMP),
          'website_url' => $country->get_value(OKHUB_API_FN_WEBSITE_URL),
          'name' => $country->get_value(OKHUB_API_FN_NAME),
          'alternative_name' => $country->get_value('alternative_name'),
/*          'asset_id' => $country->get_value(OKHUB_API_FN_ITEM_ID),*/
          'iso_number' => $country->get_value('iso_number'),
          'iso_three_letter_code' => $country->get_value('iso_three_letter_code'),
          'iso_two_letter_code' => $country->get_value('iso_two_letter_code'),
          'category_region_array' => $country->get_value('category_region_array'),  
        );
        $result->items[] = $item;
      }
    }
    return $result;
  }

}

/* --------------------------------- Processors -------------------------------- */

/*
 * OkhubAssetsProcessor Class
 */
class OkhubAssetsProcessor extends FeedsNodeProcessor {

  public $parsed_items;

  /**
   * Make hash and newItemInfo methods public
   */
  public function generateHash($item) {
    return $this->hash($item);
  }

  public function newOkhubItemInfo($entity, $feed_nid, $hash) {
    $this->newItemInfo($entity, $feed_nid, $hash);
  }

  /**
   * Allows to override default author.
   */
  public function setAuthor($uid) {
    $this->config['author'] = $uid;
  }

  /**
   * Allows to override default expire period.
   */
  public function setExpirePeriod($period) {
    $this->config['expire'] = $period;
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = parent::configForm($form_state);
    $author_id = $this->config['author'];
    $author = user_load($author_id);
    $form['author'] = array(
      '#type' => 'textfield',
      '#title' => t('Author'),
      '#description' => t('Imported OKhub content will be assigned to this user. If the user does not exist, it will be created.'),
      '#autocomplete_path' => 'user/autocomplete',
      '#default_value' =>  empty($author->name) ?  'anonymous' : check_plain($author->name),
    );
    $form['expire'] = array(
      '#title' => t('Expire content'),
      '#type' => 'select',
      '#options' => array(
        '-1' => t('Never'),
        '3600' => t('After one hour'),
        '10800' => t('After three hours'),
        '21600' => t('After six hours'),
        '43200' => t('After twelve hours'),
        '86400' => t('After one day'),
        '259200' => t('After three days'),
        '604800' => t('After one week'),
        '2592000' => t('After one month'),
        '7776000' => t('After three months'),
        '15552000' => t('After six months'),
        '31536000' => t('After one year'),
       ),
      '#default_value' => $this->config['expire'],
      '#description' => t('Select after how much time imported OKhub content should expire and be deleted from the database.'),
    );
    return $form;
  }

  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    $author = variable_get('okhubimport_new_user_id', 0);
    $expire = variable_get('okhubimport_expire_period_assets', OKHUB_IMPORT_EXPIRE_PERIOD_ASSETS);
    return array(
      'author' => $author,
      'expire' => $expire,
    ) + parent::configDefaults();
  }

  /**
   * Override parent::configFormValidate().
   */
  public function configFormValidate(&$values) {
    $author_name = $values['author'];
    $author_id = okhubimport_new_user($author_name);
    $values['author'] = $author_id;
    $expire_period = $values['expire'];
    variable_set('okhubimport_new_user_id', $author_id);
    variable_set('okhubimport_new_user', $author_name);
    variable_set('okhubimport_expire_period_assets', $expire_period);
  }
  
  /**
   * Override parent::process().
   *
   * Processes the imported assets and updates the taxonomy hierarchy.
   */
  public function process(FeedsSource $source, FeedsParserResult $parser_result) {
    // Keep a copy of the parsed items (which are consumed in the processing).
    $this->parsed_items = $parser_result->items;
    parent::process($source, $parser_result);
  }
}

/*
 * OkhubCategoriesProcessor Class
 */
class OkhubCategoriesProcessor extends FeedsTermProcessor {

  /**
   * Override parent::process().
   */
  public function process(FeedsSource $source, FeedsParserResult $parser_result) {
    parent::process($source, $parser_result);
  }

  /**
   * Make hash and newItemInfo methods public
   */
  public function generateHash($item) {
    return $this->hash($item);
  }

  public function newOkhubItemInfo($entity, $feed_nid, $hash) {
    $this->newItemInfo($entity, $feed_nid, $hash);
  }

}

/*
 * OkhubCountriesProcessor Class
 */
class OkhubCountriesProcessor extends OkhubCategoriesProcessor {

  public $parsed_items;

  /**
   * Override parent::process().
   */
  public function process(FeedsSource $source, FeedsParserResult $parser_result) {
    $this->parsed_items = $parser_result->items;
    parent::process($source, $parser_result);
  }

}

