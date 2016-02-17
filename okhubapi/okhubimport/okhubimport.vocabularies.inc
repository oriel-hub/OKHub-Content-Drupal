<?php
/**
 * @file
 * okhubimport.vocabularies.inc
 */

/**
 * Creates vocabulary definitions for OKhub categories.
 */
function okhubimport_vocabularies() {
  $vocabularies['okhub_regions'] = array(
      'name' => 'OKhub Regions',
      'machine_name' => 'okhub_regions',
      'description' => 'Vocabulary for regions imported from the OKhub collection.',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
      'bc_entity_type' => 'taxonomy_term',
    );

  $vocabularies['okhub_themes'] = array(
      'name' => 'OKhub Themes',
      'machine_name' => 'okhub_themes',
      'description' => 'Vocabulary for themes imported from the OKhub collection.',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
      'bc_entity_type' => 'taxonomy_term',
    );

  $vocabularies['okhub_subjects'] = array(
      'name' => 'OKhub Subjects',
      'machine_name' => 'okhub_subjects',
      'description' => 'Vocabulary for subjects imported from the OKhub collection.',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
      'bc_entity_type' => 'taxonomy_term',
    );


  $vocabularies['okhub_countries'] = array(
      'name' => 'OKhub Countries',
      'machine_name' => 'okhub_countries',
      'description' => 'Vocabulary for countries imported from the OKhub collection.',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
      'bc_entity_type' => 'taxonomy_term',
    );

  $vocabularies['okhub_authors'] = array(
      'name' => 'OKhub Authors',
      'machine_name' => 'okhub_authors',
      'description' => 'OKhub Authors',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
      'bc_entity_type' => 'taxonomy_term',
    );
    
  $vocabularies['okhub_document_type'] = array(
      'name' => 'OKhub Document type',
      'machine_name' => 'okhub_document_type',
      'description' => 'OKhub Document type',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
      'bc_entity_type' => 'taxonomy_term',
    );
    
  $vocabularies['okhub_keywords'] = array(
      'name' => 'OKhub Keywords',
      'machine_name' => 'okhub_keywords',
      'description' => 'Subject keywords that relate to OKhub documents.',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
      'bc_entity_type' => 'taxonomy_term',
    );

  return $vocabularies;

}
