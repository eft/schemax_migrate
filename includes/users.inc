<?php

/*
 * @file
 * Migration for players
 */

class SchemaxMigrationUsers extends SchemaxMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate') . '/csv/users.csv';

    $this->description = t('Import users into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), $this->fields());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'user_id' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'User ID',
      ),
        ), MigrateDestinationUser::getKeySchema()
    );

    $this->destination = new MigrateDestinationUser();

    $this->addFieldMapping(NULL,'user_id');// pkey
   //         ->issueGroup(t('DNM'));
    $this->addFieldMapping('name', 'name');
    $this->addFieldMapping('mail', 'mail');
    $this->addFieldMapping('status', 'status')
        ->defaultValue(1);// 1 = active
    $this->addFieldMapping('role_names', 'role_names')
      ->separator(',')
      ->defaultValue('authenticated user');

    $this->addUnmigratedDestinations(array(
      'uid',
      'pass',
      'created',
      'access',
      'login',
      'roles',
      'picture',
      'signature',
      'signature_format',
      'timezone',
      'language',
      'theme',
      'init',
      'data',
      'is_new',
    ));
  }

  // Define columns in source CSV file
  protected function csvcolumns() {
    $columns[0] = array('user_id', 'User ID');
    $columns[1] = array('name', 'Username');
    $columns[2] = array('mail', 'Email');
    $columns[3] = array('role_names', 'Roles');
    return $columns;
  }

  // Define fields
  protected function fields() {
    // use empty array by default
    return array();
  }
}
