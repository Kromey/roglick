About this directory
====================

Within this directory you will find 4 separate source trees:

main
----

This contains the main source for Ro'glick. Source files are roughly
grouped into directories following logical groups.

Sources in this tree are automatically built.

test
----

Unit tests are found here, and this directory mirrors the main tree.
Tests for a given object are found in a file of the same name in the
same sub-tree.

Sources in this tree are automatically built.

lib
---

Third-party libraries are found in here. They require build targets
to be added to the Makefile to be built properly.

bin
---

This directory contains the "main" files that ultimately produce the
binaries. They require build targets to produce them.
