Ro'glick
========

A skill-based Rogue-like game.

Building Ro'glick
-----------------

Building Ro'glick depends upon having the `ncurses` library available; on
Debian/Ubuntu this simply requires `apt-get install libncurses5-dev`.

Running `make all` will compile all of the code and build all the programs.
After that, `./bin/RunTests` will execute the test suite, or `./bin/LevelTest`
will run a series of level generation tests; the most interesting, however,
is `./bin/InterfaceTest`, which actually lets you have some modicum of
interaction with what there is so far of the game.
