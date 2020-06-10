#lang racket
;Joshua Stuifbergen
;Lab 4
;2/15/19
;CSCI 301

;The Sum1 function
(define (Sum1 n)
  ;Set base case to 0. Reduce n by 1 until 0.
   (if (= n 0)
       0
       ;(3k + 1)
       (+ (+ 1 (* 3 n)) (Sum1 (- n 1)))))
         
;The Sum2 function
(define (Sum2 n)
  ;Set base case to 0. Reduce n by 1 until 0.
   (if (= n 0)
       0
       ;(k^2 - (k - 1)^2)^2
       (+ (* (- (* n n) (* (- n 1) (- n 1))) (- (* n n) (* (- n 1) (- n 1))))
       (Sum2 (- n 1)))))

;The Sum3helper function. Assists with the functionality of Sum3.
(define (Sum3helper n)
  ;Set base case to 1. Reduce n by 1 until 1.
  (if (= n 1)
      1
      (+ n (Sum3helper (- n 1)))))

;The Sum3 function
(define (Sum3 n)
  ;Set base case to 1. Reduce n by 1 until 1.
   (if (= n 1)
       (Sum3helper 1)
       ; If n = 2, then output would = (1) + (1 + 2) = 4 
       (+ (Sum3helper n) (Sum3 (- n 1)))))

;The Sum4helper function. Assists with the functionality of Sum4.
(define (Sum4helper n)
  ;Set base case to 1. Reduce n by 1 until 1.
  (if (= n 1)
      1
      (+ n (Sum4helper (- n 1)))))

;The Sum4 function
(define (Sum4 n)
  ;Set base case to 1. Reduce n by 1 until 1.
   (if (= n 1)
       (Sum4helper 1)
       ; If n = 2, then output would = (1) + (1 + 2) = 4 
       (+ (Sum4helper n) (Sum4 (- n 1)))))


(Sum1 3)
(Sum2 2)
(Sum3 2)
(Sum4 2)
