# util-xlab

A small set of utility programs for OSv:
List:
 - cd.so


## template

Main purpose of this program is to ease runtime customization of application
configuration through environment variables.

`template` program takes two paths as arguments. First path should point to
the file that will serve as a template that gets expanded using environment
variables similar to how `bash` expands variables in strings. Second path
should point to the destination file. For example:

    $ cat a.txt
    Name of master is ${MASTER_NAME} and worker is ${WORKER_NAME}.
    $ MASTER_NAME=abc WORKER_NAME=123 ./template a.txt b.txt
    $ cat b.txt
    Name of master is abc and worker is 123.

Template variables that are not found in environment are replaced by empty
string.

Variables that should be expanded are marked with `${VAR}` construct. Note
that `$VAR` will not be expanded and will be copied to the output file
verbatim.
