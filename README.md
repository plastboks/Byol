Byol
====
Build your own Lisp.

![Screenshot](screenshot/lispy-0.14.png)

About
=====
This is just a small pet project following the fantastic tutorial @ [Build your own Lisp](http://www.buildyourownlisp.com)

Docker
======
Now with a docker automated build. See [the registry](https://registry.hub.docker.com/u/plastboks/byol/) for details.
* change directory into `./docker`
* run: `build` (need superuser)
* run: `run` (need superuser)

Status
======
Currently the code is at chapter 15. `src/lispy.c` is the main and only source file used for all chapters.

Compilation and running
=======================
* run: `make`
* run: `./lispy`

Manual
======

Arithmetic
----------
Lispy's arithmetic is like the rest of the syntax prefix notation (polish notation).
* `lispy> + 2 2`
* `lispy> * 2 3`
* `lispy> + 2 (* 7 6) (* 2 5)`

Lists
-----
List operators include the builtins `head` `tail` `last` `cons` `take` `drop` etc.
        `lispy> {1 2 3 4 5}`
        `lispy> {{1 2 3} {4 5}}`
