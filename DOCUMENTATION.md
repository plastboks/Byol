Lispy Documentation
===================
This documentation is meant to be self explanatory using sections and code examples.
It (the documentation) is increasing as new features are added (both trough the core and via the standard library (or other libraries))).
* [Built-ins](#builtins)
    * [Imports](#imports)
    * [Settings](#settings)
    * [Arithmetic](#arithmetic)
    * [Math](#math)
    * [Bitwise operations](#bitwise-operations)
    * [Lists](#lists)
    * [Variables](#variables)
    * [Conditionals](#conditionals)
    * [Strings](#strings)
    * [Other](#other)
* [Standard Library](#standard-library)
    * [Boolean](#boolean)
    * [Lambdas](#lambdas)
    * [Currying](#currying)
    * [Lists operations](#list-operations)
        * [Basic](#basic)
        * [Merge](#merge)
        * [Map](#map)
        * [Filter](#filter)
* [Extended Math Library](#extended-math-library)
    * [Distributions](#distributions)


# Builtins

## Imports

* `load` (local files)
* `include` (global files)

```lisp
[n]> load "filename"
()
[n]> load "filename.lspy"
()
[n]> include "std"
()
[n]> include "math"
()
```

## Settings

* `set`
    * `"dec"` (decimal precision)
* `get`
    * `"dec"`

```lisp
[n]> get "dec"
5
[n]> 4.0
4.00000
[n]> set "dec" 10
()
[n]> 4.0
4.0000000000
[n]> set "dec" 2
()
[n]> 4.0
4.00
[n]> get "dec"
2
```


## Arithmetic

* `*`
* `/`
* `+`
* `-`
* `++`
* `--`

```lisp
[n]> + 2 2
4
[n]> * 2 3
6
[n]> + 2 (* 7 6) (* 2 5)
54
[n]> / 10 2
5
[n]> - 9 2
7
[n]> -- 2
1
[n]> ++ 2
3
[n]> - 10 (++ 2)
7
```

## Math

* `%`
* `ln`
* `log`
* `pow`
* `ceil`
* `floor`
* `rand`
* `max`
* `min`
* `sin`
* `arcsin`
* `cos`
* `arccos`
* `tan`
* `arctan`

```lisp
lisyp> % 10 4
2
[n]> ln e
1.00000
[n]> log 10
1.00000
[n]> pow 2 10
1024
[n]> ceil 3.5
4
[n]> floor 3.5
3
[n]> rand 5
3.68000
[n]> max 1 2 3 4
4
[n]> min 1 2 3 4
1
[n]> sin 30
-0.98803
[n]> arcsin 0.5
1.17520
[n]> cos 30
0.15425
[n]> arccos 0.5
1.54308
[n]> tan 30
-6.40533
[n]> arctan 0.5
0.76159
```

## Bitwise operations

* `&`
* `<<`
* `>>`
* `|`
* `^`

```lisp
[n]> & 10 9
8
[n]> << 10 9
5120
[n]> >> 10 9
0
[n]> | 10 9
11
[n]> ^ 10 9
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
[n]> {1 2 3 4 5}
{1 2 3 4 5}
[n]> {{1 2 3} {4 5}}
{{1 2 3} {4 5}}
[n]> head (list 1 2 3 4)
{1}
[n]> eval (tail {tail tail {5 6 7}})
{6 7}
[n]> head {(+ 1 2) (+ 10 20)}
{(+ 1 2)}
[n]> eval (head {(+ 1 2) (+ 10 20)})
3
[n]> 1..20
{1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20}
[n]> -4..-10
{-4 -5 -6 -7 -8 -9 -10}
[n]> 4..-10
{4 3 2 1 0 -1 -2 -3 -4 -5 -6 -7 -8 -9 -10}
```

## Variables

* `def`

```lisp
[n]> def {x} 100
()
[n]> def {y} 200
()
[n]> x
100
[n]> y
200
[n]> + x y
300
[n]> def {a b} 5 6
()
[n]> + a b
11
[n]> def {arglist} {a b x y}
()
[n]> arglist
{a b x y}
[n]> def arglist 1 2 3 4
()
[n]> list a b x y
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
[n]> > 10 5
True
[n]> <= 88 5
True
[n]> == 5 {}
False
[n]> != {} 56
True
[n]> == {1 2 3 {5 6}} {1   2  3   {5 6}}
True
[n]> def {x y} 100 200
()
[n]> if (== x y) {+ x y} {- x y}
-100
```

## Strings

```lisp
[n]> "Hello World!"
"Hello World!"
[n]> head {"hello" "world"}
{"hello"}
[n]> eval (head {"hello" "world"})
"hello"
```

## Other

* `exit`
* `version`

```lisp
[n]> version()
Version: 0.17, build: 030aced-dirty (2015-06-04 18:58)
[n]> exit()
; this exits lispy
```

# Standard Library
Included in the standard library are some of these nice features:
```lisp
[n]> include "std"
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
[n]> true
true
[n]> false
false
[n]> not true
false
[n]> and true false
false
[n]> and true true
true
[n]> or true false
true
[n]> or false false
false
[n]> xor false true
true
[n]> xor true true
false
```

## Lambdas

* `\`

```lisp
[n]> (\ {x y} {+ x y}) 10 20
30
[n]> def {add-together} (\ {x y} {+ x y})
()
[n]> add-together 10 20
30
[n]> fun {add-together x y} {+ x y}
()
[n]> add-together 10 20
30
```

## Currying

* `curry`
* `uncurry`

```lisp
[n]> curry + {5 6 7}
18
[n]> curry * {1 2 3 4}
24
[n]> uncurry head 5 6 7
{5}
[n]> uncurry reverse 1 2 3 4 5 6 7
{7 6 5 4 3 2 1}
[n]> uncurry prod 1 2 3 4 5
120
[n]> def {factorial} (curry *)
()
[n]> factorial 1..5
120
[n]> def {add-curried} (curry +)
()
[n]> add-curried {5 6 7}
18
[n]> def {add-uncurried} +
()
[n]> add-uncurried 5 6 7
18
```

## Take and drop while

* `take-while`
* `drop-while`

```lisp
[n]> map (\ {x} {pow x 2}) 1..10
{1 4 9 16 25 36 49 64 81 100}
[n]> filter odd (map (\ {x} {pow x 2}) 1..10)
{1 9 25 49 81}
[n]> take-while (\ {x} {< x 50}) (filter odd (map (\ {x} {pow x 2}) 1..10))
{1 9 25 49}
[n]> drop-while (\ {x} {< x 50}) (filter odd (map (\ {x} {pow x 2}) 1..10))
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
[n]> len 1..20
20
[n]> nth 5 1..20
6
[n]> take 5 1..20
{1 2 3 4 5}
[n]> drop 5 1..20
{6 7 8 9 10 11 12 13 14 15 16 17 18 19 20}
[n]> split 5 1..20
{{1 2 3 4 5} {6 7 8 9 10 11 12 13 14 15 16 17 18 19 20}}
[n]> elem 5 1..20
true
[n]> maximum 1..20
20
[n]> minimum 1..20
1
[n]> sort {3 4 9 10 1 -2 3 4 5 100 -30}
{-30 -2 1 3 3 4 4 5 9 10 100}
[n]> range 1 10
{1 2 3 4 5 6 7 8 9 10}
[n]> range 5 -4
{5 4 3 2 1 0 -1 -2 -3 -4}
[n]> reverse 1..10
{10 9 8 7 6 5 4 3 2 1}
```

#### Merge

* `merge`
* `zip`
* `unzip`

```lisp
[n]> merge 1..4 5..11
{1 2 3 4 5 6 7 8 9 10 11}
[n]> zip 1..5 5..10
{{1 5} {2 6} {3 7} {4 8} {5 9}}
[n]> unzip (zip 1..5 5..10)
{{1 2 3 4 5} {5 6 7 8 9}}
```

#### Map

* `map`

```lisp
[n]> map - 1..10
{-1 -2 -3 -4 -5 -6 -7 -8 -9 -10}
[n]> map (\ {x} {+ x 10}) 1..10
{11 12 13 14 15 16 17 18 19 20}
[n]> map (\ {x} {pow 2 x}) 0..10
{1 2 4 8 16 32 64 128 256 512 1024}
[n]> map (\ {x} {+ (* 2 (pow 4 x)) (pow -3 x)}) 0..10
{3 5 41 101 593 1805 8921 30581 137633 504605 2156201}
[n]> map (\ {x} {loga x x}) 2..10
{1.00000 1.00000 1.00000 1.00000 1.00000 1.00000 1.00000 1.00000 1.00000}
[n]> fun {fn x} {+ (* 2 (pow 4 x)) (pow -3 x)}
()
[n]> map fn 0..10
{3 5 41 101 593 1805 8921 30581 137633 504605 2156201}
[n]> map sqrt 1..10
{1 4 9 16 25 36 49 64 81 100}
[n]> sum (map sqrt 1..10)
22.46828
[n]> map fact 1..5
{1 2 6 24 120}
[n]> map isprime 1..10
{false true true false true false true false false false}
```

#### Filter

* `filter`

```lisp
[n]> filter (\ {x} {> x 2}) {5 2 11 -7 8 1}
{5 11 8}
[n]> filter (\ {x} {% x 2}) 1..20
{1 3 5 7 9 11 13 15 17 19}
[n]> filter (\ {x} {== (% x 2) 0}) 1..20
{2 4 6 8 10 12 14 16 18 20}
[n]> filter (\ {x} {== (% x 3) 0}) 1..20
{3 6 9 12 15 18}
[n]> filter odd 1..20
{1 3 5 7 9 11 13 15 17 19}
[n]> filter even 1..20
{2 4 6 8 10 12 14 16 18 20}
[n]> filter isprime 1..30
{2 3 5 7 11 13 17 19 23 29}
```

# Extended Math Library

```lisp
[n]> include "math"
()
```

* `e`
* `pi`
* `fact`
* `loga`
* `sqrt`
* `ncr`
* `npr`
* `gcd`
* `lcm`
* `abs`
* `mod`
* `fib`
* `factors`
* `palindromic`
* `sum`
* `product`
* `odd`
* `even`
* `isprime`

```lisp
[n]> e
2.718282
[n]> pi
3.141593
[n]> fact 5
120
[n]> loga 2 1024
10.00000
[n]> loga 2 2048
11.00000
[n]> sqrt 9
3.000000
[n]> ncr 9 3
84
[n]> npr 9 3
504
[n]> gcd 440 356
4
[n]> lcm 440 356
39160
[n]> abs -5
5
[n]> mod 10 4
2
[n]> fib 10
55
[n]> factors 9232
{2}
[n]> factors 6942
{2 3 13}
[n]> palindromic 9009
true
[n]> sum {1 2 3 4 5}
15
[n]> product {1 2 3 4 5}
120
[n]> odd 3
true
[n]> even 3
false
[n]> isprime 10
false
[n]> isprime 7
true
```

## Distributions

* `union`
* `intersect`
* `subtract`

```lisp
[n]> union 1..10 5..15
{1 2 3 4 5 6 7 8 9 10 11 12 13 14 15}
[n]> intersect 1..10 5..15
{5 6 7 8 9 10}
[n]> subtract 1..10 5..15
{1 2 3 4}
```
