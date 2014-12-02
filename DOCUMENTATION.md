Lispy Documentation
===================
* [Arithmetic](#Arithmetic)
* [List](#Lists)
* [Variables](#Variables)
* [Functions](#Functions)
* [Conditionals](#Conditionals)
* [Strings](#Strings)
* [Standard Libarary](#Standard-library)
    * [Math](#Math)
    * [Lists](#Lists)
    * [Boolean](#Boolean)

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
Some examples of variables declaration and use.


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

Functions
---------
Some examples of functions and function declarations.


        lispy> def {add-together} (\ {x y} {+ x y})
        ()
        lispy> add-together 10 20
        30
        lispy> fun {add-together x y} {+ x y}
        ()
        lispy> add-together 10 20
        30
        lispy> curry + {5 6 7}
        18
        lispy> uncurry head 5 6 7
        {5}
        lispy> def {add-curried} (curry +)
        ()
        lispy> add-curried {5 6 7}
        18
        lispy> def {add-uncurried} +
        ()
        lispy> add-uncurried 5 6 7
        18

Conditionals
------------
Some example conditionals.


        lispy> > 10 5
        True
        lispy> <= 88 5>
        True
        lispy> == 5 {}
        False
        lispy> != {} 56
        True
        lispy> == {1 2 3 {5 6}} {1   2  3   {5 6}}
        True
        lispy> def {x y} 100 200
        ()
        lispy> if (== x y) {+ x y} {- x y}
        -100
        lispy> (fun {length l} {if (== l {}) {0} {+ 1 (length (tail l))} })
        ()
        lispy> length 1..20
        20
        lispy> fun {rev l} {if (== l {}) {{}} {join (rev (tail l)) (head l)}}
        ()
        lispy> 1..20
        {1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20}
        lispy> rev 1..20
        {20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1}

Strings
-------


        lispy> "Hello World!"
        "Hello World!"
        lispy> head {"hello" "world"}
        {"hello"}
        lispy> eval (head {"hello" "world"})
        "hello"

Standard Library
----------------
Included in the standard library are some of these nice features:

### Math

        lispy> e
        2.718282
        lispy> pi
        3.141593
        lispy> fact 5
        120
        lispy> sqrt 9
        3.000000
        lispy> ncr 9 3
        84
        lispy> npr 9 3
        504
        lispy> gcd 440 356
        4
        lispy> lcm 440 356
        39160
        lispy> fib 10
        55
        lispy> sum {1 2 3 4 5}
        15
        lispy> product {1 2 3 4 5}
        120


### Lists

        lispy> len 1..20
        20
        lispy> nth 5 1..20
        6
        lispy> take 5 1..20
        {1 2 3 4 5}
        lispy> drop 5 1..20
        {6 7 8 9 10 11 12 13 14 15 16 17 18 19 20}
        lispy> split 5 1..20
        {{1 2 3 4 5} {6 7 8 9 10 11 12 13 14 15 16 17 18 19 20}}
        lispy> elem 5 1..20
        true
        lispy> zip 1..5 5..10
        {{1 5} {2 6} {3 7} {4 8} {5 9}}
        lispy> map - 1..10
        {-1 -2 -3 -4 -5 -6 -7 -8 -9 -10}
        lispy> reverse 1..10
        {10 9 8 7 6 5 4 3 2 1}


### Boolean

        lispy> true
        true
        lispy> false
        false
        lispy> not true
        false
        lispy> and true false
        false
        lispy> and true true
        true
        lispy> or true false
        true
        lispy> or false false
        false
        lispy> xor false true
        true
        lispy> xor true true
        false
