<?php

/*
 * @file
 * Migration for default images
 */

class SchemaxMigrationDefaultFiles extends SchemaxMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate') . '/csv/default_files.csv';

    $this->description = t('Import default files into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), array());

    $this->destination = new MigrateDestinationFile('file');

    $this->map = new MigrateSQLMap($this->machineName,
        array('file_id' => array(
              'type' => 'int',
              'unsigned' => TRUE,
              'not null' => TRUE,
              'description' => 'File ID.'
              )
           ),
        MigrateDestinationFile::getKeySchema()
    );

    // Map file URI
    $this->addFieldMapping('value', 'file_name')
         ->description('A file URI');

    // Define where the incoming images are stored
    $source_images_path = drupal_get_path('module', 'schemax_migrate') . '/files';

    // Map source location
    $this->addFieldMapping('source_dir')
      ->defaultValue($source_images_path);

    // Map destination location
    $this->addFieldMapping('destination_dir','destination_dir');

    // Map destination filename
    $this->addFieldMapping('destination_file','file_name');

    // Unmapped destination fields
    $this->addUnmigratedDestinations(array(
      'fid',
      'file_replace',
      'preserve_files',
      'timestamp',
    ));
  }

  // Define columns in source CSV file
  protected function csvcolumns() {

    $columns[0] = array('file_id', 'file_id');
    $columns[1] = array('file_name', 'file_name');
    $columns[2] = array('destination_dir', 'destination_dir');
    return $columns;
  }

  // Run code after migration complete
  public function postImport() {
    parent::postImport();
    // Code to execute after the last file has been imported
    schemax_personUpdateDefaultImagePerson();
  }

}
