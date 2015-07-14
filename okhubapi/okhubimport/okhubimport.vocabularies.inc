<?php
/**
 * @file
 * okhubimport.vocabularies.inc
 */

/**
 * Creates vocabulary definitions for OKHUB categories.
 */
function okhubimport_vocabularies() {
  $vocabularies['okhub_regions'] = array(
      'name' => 'OKHUB Regions',
      'machine_name' => 'okhub_regions',
      'description' => 'Vocabulary for regions imported from the OKHUB collection.',
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
      'name' => 'OKHUB Themes',
      'machine_name' => 'okhub_themes',
      'description' => 'Vocabulary for themes imported from the OKHUB collection.',
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
      'name' => 'OKHUB Subjects',
      'machine_name' => 'okhub_subjects',
      'description' => 'Vocabulary for subjects imported from the OKHUB collection.',
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
      'name' => 'OKHUB Countries',
      'machine_name' => 'okhub_countries',
      'description' => 'Vocabulary for countries imported from the OKHUB collection.',
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
      'name' => 'OKHUB Authors',
      'machine_name' => 'okhub_authors',
      'description' => 'OKHUB Authors',
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
      'name' => 'OKHUB Document type',
      'machine_name' => 'okhub_document_type',
      'description' => 'OKHUB Document type',
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
      'name' => 'OKHUB Keywords',
      'machine_name' => 'okhub_keywords',
      'description' => 'Subject keywords that relate to OKHUB documents.',
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
