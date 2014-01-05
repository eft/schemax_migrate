<?php

/*
 * @file
 * Migration for players
 */

class SchemaxMigrationPages extends SchemaxMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate') . '/csv/pages.csv';

    $this->description = t('Import locations into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), array());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'pgid' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Page ID',
      ),
        ), MigrateDestinationNode::getKeySchema()
    );

    $this->destination = new MigrateDestinationNode('page');

    $this->addFieldMapping(NULL, 'pgid');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('field_summary', 'summary');
    $this->addFieldMapping('body', 'body');

    $this->addUnmigratedDestinations(array(
      'uid',
      'created',
      'changed',
      'status',
      'promote',
      'sticky',
      'revision',
      'log',
      'language',
      'tnid',
      'translate',
      'revision_uid',
      'is_new',
      'path',
      'comment',
    ));
  }

  // Define columns in source CSV file
  protected function csvcolumns() {

    $columns[0] = array('pgid', 'page_id');
    $columns[1] = array('title', 'title');
    $columns[2] = array('summary', 'summary');
    $columns[3] = array('body', 'body');
    return $columns;
  }
}
