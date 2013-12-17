<?php

/*
 * You must implement hook_migrate_api(), setting the API level to 2, for
 * your migration classes to be recognized by the Migrate module.
 */

function schemax_migrate_migrate_api() {
  $api = array(
    'api' => 2,
    // Date module doesn't register handler according to new Migrate 2.6 requirements
    // that's why we register it here.
    'field handlers' => array(
      'DateMigrateFieldHandler',
      'MigrateAddressFieldHandler',
    ),
    'groups' => array(
      'users' => array(
        'title' => t('User Imports'),
      ),
    ),
    'migrations' => array(
      'Users' => array(
        'class_name' => 'SchemaxMigrationUsers',
        'group_name' => 'users',
      ),
    ),
  );

  return $api;
}
