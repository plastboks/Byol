Lispy Documentation
===================
This documentation is meant to be self explanatory using sections and code examples.
It (the documentation) is increasing as new features are added (both trough the core and via the standard library).
* [Arithmetic](#arithmetic)
* [List](#lists)
* [Variables](#variables)
* [Functions](#functions)
* [Conditionals](#conditionals)
* [Strings](#strings)
* [Standard Libarary](#standard-library)
    * [Math](#math)
    * [Boolean](#boolean)
    * [Lists operations](#list-operators)
        * [Basic](#basic)
        * [Merge](#merge)
        * [Distributions](#distributions)
        * [Map](#map)
        * [Filter](#filter)


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
List operators include the builtins `list` `head` `tail` `cons` `join` `init`

        lispy> {1 2 3 4 5}
        {1 2 3 4 5}
        lispy> {{1 2 3} {4 5}}
        {{1 2 3} {4 5}}
        lispy> 1..10
        {1 2 3 4 5 6 7 8 9 10}
        lispy> head (list 1 2 3 4)
        {1}
        lispy> eval (tail {tail tail {5 6 7}})
        {6 7}
        lispy> head {(+ 1 2) (+ 10 20)}
        {(+ 1 2)}
        lispy> eval (head {(+ 1 2) (+ 10 20)})
        3
        lispy> 1..20
        {1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20}
        lispy> rev 1..20
        {20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1}

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
        lispy> <= 88 5
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
        lispy> odd 3
        true
        lispy> even 3
        false

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

### List operators

#### Basic

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
        lispy> maximum 1..20
        20
        lispy> minimum 1..20
        1
        lispy> range 1 10
        {1 2 3 4 5 6 7 8 9 10}
        lispy> range 5 -4
        {5 4 3 2 1 0 -1 -2 -3 -4}
        lispy> reverse 1..10
        {10 9 8 7 6 5 4 3 2 1}

#### Merge

        lispy> merge 1..4 5..11
        {1 5 2 6 3 7 4 8 9 10 11}
        lispy> zip 1..5 5..10
        {{1 5} {2 6} {3 7} {4 8} {5 9}}
        lispy> unzip (zip 1..5 5..10)
        {{1 2 3 4 5} {5 6 7 8 9}}

#### Distributions

        lispy> union 1..10 5..15
        {1 2 3 4 5 6 7 8 9 10 11 12 13 14 15}
        lispy> intersect 1..10 5..15
        {5 6 7 8 9 10}
        lispy> subtract 1..10 5..15
        {1 2 3 4}

#### Map

        lispy> map - 1..10
        {-1 -2 -3 -4 -5 -6 -7 -8 -9 -10}
        lispy> map (\ {x} {+ x 10}) 1..10
        {11 12 13 14 15 16 17 18 19 20}
        lispy> map (\ {x} {^ 2 x}) 0..10
        {1 2 4 8 16 32 64 128 256 512 1024}
        lispy> map (\ {x} {+ (* 2 (^ 4 x)) (^ -3 x)}) 0..10
        {3 5 41 101 593 1805 8921 30581 137633 504605 2156201}
        lispy> fun {fn x} {+ (* 2 (^ 4 x)) (^ -3 x)}
        ()
        lispy> map fn 0..10
        {3 5 41 101 593 1805 8921 30581 137633 504605 2156201}
        lispy> fun {sq x} {* n n}
        ()
        lispy> map sq 1..10
        {1 4 9 16 25 36 49 64 81 100}
        lispy> sum (map sq 1..10)
        385
        lispy> map fact 1..5
        {1 2 6 24 120}

#### Filter

        lispy> filter (\ {x} {> x 2}) {5 2 11 -7 8 1}
        {5 11 8}
        lispy> filter (\ {x} {% x 2}) 1..20
        {1 3 5 7 9 11 13 15 17 19}
        lispy> filter (\ {x} {== (% x 2) 0}) 1..20
        {2 4 6 8 10 12 14 16 18 20}
        lispy> filter (\ {x} {== (% x 3) 0}) 1..20
        {3 6 9 12 15 18}
        lispy> filter odd 1..20
        {1 3 5 7 9 11 13 15 17 19}
        lispy> filter even 1..20
        {2 4 6 8 10 12 14 16 18 20}
        lispy> filter prime 1..30
        {2 3 5 7 11 13 17 19 23 29}
