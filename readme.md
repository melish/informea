#Status#

[![Code Climate](https://codeclimate.com/github/InforMEA/informea/badges/gpa.svg)](https://codeclimate.com/github/InforMEA/informea)

#Installation#


##Pre-requisites##

1. Drush (7.0-dev)
2. Virtual host for your Drupal instance that points to the docroot/ directory from this repo

##Quick start##

1. Copy [conf/config.template.json](https://github.com/EU-OSHA/osha-website/blob/master/conf/config.template.json)
to `config.json` and customize to suit your environment

2. Copy the following code into `~/.drush/drushrc.php` (create if necessary)

    ```php
        <?php
            $repo_dir = drush_get_option('root') ? drush_get_option('root') : getcwd();
            $success = drush_shell_exec('cd %s && git rev-parse --show-toplevel 2> ' . drush_bit_bucket(), $repo_dir);
            if ($success) {
                $output = drush_shell_exec_output();
                $repo = $output[0];
                $options['config'] = $repo . '/drush/drushrc.php';
                $options['include'] = $repo . '/drush/commands';
                $options['alias-path'] = $repo . '/drush/aliases';
            }
    ```
3. Run ```install.sh```
