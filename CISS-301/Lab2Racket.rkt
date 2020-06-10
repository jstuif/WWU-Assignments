#lang racket
;LHS function decreases by 1 until it equals base case 1. It squares its value
;and adds to the next de
(define (LHS n)
  (if (= n 1)
      1
    (+ (* n n) (LHS (- n 1)))))
   
(define RHS
  (lambda (n)
   (/ (* (* n (+ n 1)) (+ 1 (* 2 n))) 6)))

(define NLHS
  (lambda (n)
    (expt (apply + (build-list (+ n 1) values)) 2)))

(define (NRHS n)
  (if (= n 1)
      1
    (+ (* n n n) (LHS (- n 1)))))


(LHS 3)
(RHS 1)
(NLHS 3)
(NRHS 3)
