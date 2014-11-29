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
Arithmetic is like the rest of the syntax prefix notation (polish notation).


        lispy> + 2 2
        4
        lispy> * 2 3
        6
        lispy> + 2 (* 7 6) (* 2 5)
        54

Lists
-----
List operators include the builtins `head` `tail` `last` `cons` `take` `drop` etc.


        lispy> {1 2 3 4 5}
        {1 2 3 4 5}
        lispy> {{1 2 3} {4 5}}
        {{1 2 3} {4 5}}
        lispy> head (list 1 2 3 4)
        {1}
        lispy> eval (tail {tail tail {5 6 7}})
        {6 7}
        lispy> head {(+ 1 2) (+ 10 20)}
        {(+ 1 2)}
        lispy> eval (head {(+ 1 2) (+ 10 20)})
        3

Variables
---------
Some examples of variables declaration and use


        lispy> def {x} 100
        ()
        lispy> def {y} 200
        ()
        lispy> x
        100
        lispy> y
        200
        lispy> + x y
        300
        lispy> def {a b} 5 6
        ()
        lispy> + a b
        11
        lispy> def {arglist} {a b x y}
        ()
        lispy> arglist
        {a b x y}
        lispy> def arglist 1 2 3 4
        ()
        lispy> list a b x y
        {1 2 3 4}
        sum (list a b x y)
        10

