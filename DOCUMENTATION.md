Lispy Documentation
===================
This documentation is meant to be self explanatory using sections and code examples.
It (the documentation) is increasing as new features are added (both trough the core and via the standard library (or other libraries))).
* [Built-ins](#builtins)
    * [Imports](#imports)
    * [Arithmetic](#arithmetic)
    * [Bitwise operations](#bitwise-operations)
    * [Lists](#lists)
    * [Variables](#variables)
    * [Conditionals](#conditionals)
    * [Strings](#strings)
* [Standard Library](#standard-library)
    * [Boolean](#boolean)
    * [Lambdas](#lambdas)
    * [Currying](#currying)
    * [Lists operations](#list-operations)
        * [Basic](#basic)
        * [Merge](#merge)
        * [Map](#map)
        * [Filter](#filter)
* [Math Library](#math)
    * [Distributions](#distributions)


# Builtins

## Imports

* `load` (local files)
* `include` (global files)

```lisp
lispy> load "filename"
()
lispy> load "filename.lspy"
()
lispy> include "std"
()
lispy> include "math"
()
```

## Arithmetic

* `*`
* `/`
* `+`
* `-`
* `++`
* `--`

```lisp
lispy> + 2 2
4
lispy> * 2 3
6
lispy> + 2 (* 7 6) (* 2 5)
54
lispy> / 10 2
5
lispy> - 9 2
7
lispy> -- 2
1
lispy> ++ 2
3
lispy> - 10 (++ 2)
7
```

## Bitwise operations

* `&`
* `<<`
* `>>`
* `|`
* `^`

```lisp
lispy> & 10 9
8
lispy> << 10 9
5120
lispy> >> 10 9
0
lispy> | 10 9
11
lispy> ^ 10 9
3
```

## Lists

* `list`
* `head`
* `tail`
* `cons`
* `eval`
* `join`
* `init`
* `..`

```lisp
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
lispy> 1..20
{1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20}
lispy> -4..-10
{-4 -5 -6 -7 -8 -9 -10}
lispy> 4..-10
{4 3 2 1 0 -1 -2 -3 -4 -5 -6 -7 -8 -9 -10}
```

## Variables

* `def`

```lisp
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
```

## Conditionals

* `>`
* `<`
* `==`
* `!=`

```lisp
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
```

## Strings

```lisp
lispy> "Hello World!"
"Hello World!"
lispy> head {"hello" "world"}
{"hello"}
lispy> eval (head {"hello" "world"})
"hello"
```

## Standard Library
Included in the standard library are some of these nice features:
```lisp
lispy> include "std"
()
```

## Boolean

* `true`
* `false`
* `not`
* `and`
* `or`
* `xor`

```lisp
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
```

## Lambdas

* `\`

```lisp
lispy> (\ {x y} {+ x y}) 10 20
30
lispy> def {add-together} (\ {x y} {+ x y})
()
lispy> add-together 10 20
30
lispy> fun {add-together x y} {+ x y}
()
lispy> add-together 10 20
30
```

## Currying

* `curry`
* `uncurry`

```lisp
lispy> curry + {5 6 7}
18
lispy> curry * {1 2 3 4}
24
lispy> uncurry head 5 6 7
{5}
lispy> uncurry reverse 1 2 3 4 5 6 7
{7 6 5 4 3 2 1}
lispy> uncurry prod 1 2 3 4 5
120
lispy> def {factorial} (curry *)
()
lispy> factorial 1..5
120
lispy> def {add-curried} (curry +)
()
lispy> add-curried {5 6 7}
18
lispy> def {add-uncurried} +
()
lispy> add-uncurried 5 6 7
18
```

## Take and drop while

* `take-while`
* `drop-while`

```lisp
lispy> map (\ {x} {pow x 2}) 1..10
{1 4 9 16 25 36 49 64 81 100}
lispy> filter odd (map (\ {x} {pow x 2}) 1..10)
{1 9 25 49 81}
lispy> take-while (\ {x} {< x 50}) (filter odd (map (\ {x} {pow x 2}) 1..10))
{1 9 25 49}
lispy> drop-while (\ {x} {< x 50}) (filter odd (map (\ {x} {pow x 2}) 1..10))
{81}
```

### List operations
#### Basic

* `len`
* `nth`
* `take`
* `drop`
* `split`
* `head`
* `tail`
* `elem`
* `maximum`
* `minimum`
* `sort`
* `range`
* `reverse`

```lisp
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
lispy> sort {3 4 9 10 1 -2 3 4 5 100 -30}
{-30 -2 1 3 3 4 4 5 9 10 100}
lispy> range 1 10
{1 2 3 4 5 6 7 8 9 10}
lispy> range 5 -4
{5 4 3 2 1 0 -1 -2 -3 -4}
lispy> reverse 1..10
{10 9 8 7 6 5 4 3 2 1}
```

#### Merge

* `merge`
* `zip`
* `unzip`

```lisp
lispy> merge 1..4 5..11
{1 2 3 4 5 6 7 8 9 10 11}
lispy> zip 1..5 5..10
{{1 5} {2 6} {3 7} {4 8} {5 9}}
lispy> unzip (zip 1..5 5..10)
{{1 2 3 4 5} {5 6 7 8 9}}
```

#### Map

* `map`

```lisp
lispy> map - 1..10
{-1 -2 -3 -4 -5 -6 -7 -8 -9 -10}
lispy> map (\ {x} {+ x 10}) 1..10
{11 12 13 14 15 16 17 18 19 20}
lispy> map (\ {x} {pow 2 x}) 0..10
{1 2 4 8 16 32 64 128 256 512 1024}
lispy> map (\ {x} {+ (* 2 (pow 4 x)) (pow -3 x)}) 0..10
{3 5 41 101 593 1805 8921 30581 137633 504605 2156201}
lispy> fun {fn x} {+ (* 2 (pow 4 x)) (pow -3 x)}
()
lispy> map fn 0..10
{3 5 41 101 593 1805 8921 30581 137633 504605 2156201}
lispy> map sqrt 1..10
{1 4 9 16 25 36 49 64 81 100}
lispy> sum (map sqrt 1..10)
22.46828
lispy> map fact 1..5
{1 2 6 24 120}
lispy> map isprime 1..10
{false true true false true false true false false false}
```

#### Filter

* `filter`

```lisp
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
lispy> filter isprime 1..30
{2 3 5 7 11 13 17 19 23 29}
```

# Math Library

```lisp
lispy> include "math"
()
```

* `e`
* `pi`
* `fact`
* `pow`
* `ceil`
* `floor`
* `loga`
* `%`
* `sqrt`
* `ncr`
* `npr`
* `gdc`
* `lcm`
* `fib`
* `sum`
* `product`
* `odd`
* `even`
* `isprime`

```lisp
lispy> e
2.718282
lispy> pi
3.141593
lispy> fact 5
120
lispy> pow 2 10
1024
lispy> ceil 3.5
4
lispy> floor 3.5
3
lispy> loga 2 1024
10.00000
lispy> loga 2 2048
11.00000
lisyp> % 10 4
2
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
lispy> isprime 10
false
lispy> isprime 7
true
```

## Distributions

* `union`
* `intersect`
* `subtract`

```lisp
lispy> union 1..10 5..15
{1 2 3 4 5 6 7 8 9 10 11 12 13 14 15}
lispy> intersect 1..10 5..15
{5 6 7 8 9 10}
lispy> subtract 1..10 5..15
{1 2 3 4}
```
