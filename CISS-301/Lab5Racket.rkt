#lang racket
;Joshua Stuifbergen
;CISS 301
;Lab 5
;2/25/19

;Remove Duplicate functions assists other functions
(define Remove-Duplicate
  (lambda (L)
    (cond ((null? L) '())
          ;If the same element in the lists remove duplicate.
          ((Member? (car L) (cdr L))
           (Remove-Duplicate (cdr L)))
          ;Else add to new list.
          (else
           (cons (car L) (Remove-Duplicate (cdr L)))))))

;Member function assists other functions
(define Member?
  (lambda (a L)
    (cond ((empty? L) #f)
          ((equal? a (car L)) #t)
          (else
           (Member? a (cdr L))))))

;1) Reflexive Function------------------------------
(define Reflexive?
  (lambda (L S)
    (cond ((empty? S) #t)
          ((Member? (list (car S) (car S)) L)
           (Reflexive? L (cdr S)))
           (else #f))))

;2) Symmetric Function----------------------------
(define Symmetric?
  (lambda (L)
    (helperSym L L)))

;The helper function for Symmetric
(define helperSym
  (lambda (L L2)
    (cond ((empty? L) #t)
          ((Member? (list (cadr(car L)) (caar L)) L2)
          (helperSym (cdr L) L2))
    (else #f))))
  
;3) Transitive Function----------------------------
(define Transitive?
  (lambda (L)
    (helperTran L L)))

;The helper function for Transitive
(define helperTran
  (lambda (L L2)
    (cond ((empty? L) #t)
          ((Member? (list (cadr L)) (cdar (car L2)))
          (helperTran (cdr L) L2))
    (else #f))))

;4) Reflexive-Closure Function--------------------
(define Reflexive-Closure
  (lambda (L S)
    (cond ((empty? S) L)
          ((Member? (list (car S) (car S)) L)
           (Reflexive-Closure L (cdr S)))
          (else (cons (list (car S) (car S))
          (Reflexive-Closure L (cdr S)))))))

;5) Symmetric-Closure Function-----------------------
(define Symmetric-Closure
  (lambda (L)
    (helperSymmetric-Closure L L)))

;Symmetric-Closure helper function
(define helperSymmetric-Closure
  (lambda (L L2)
    (cond ((empty? L) L2)
          ((Member? (list (cadr(car L)) (caar L)) L2)
           (helperSymmetric-Closure (cdr L) L2))
          (else (cons (list (cadr(car L)) (caar L))
          (helperSymmetric-Closure (cdr L) L2))))))

;The helper function for Transitive-Closure
(define helperTransClosure
(lambda (n L)
(cond ((empty? L) L)
    (else(equal? (cadr n) (caar L))
         (cons (list (car n) (cadr (car L)))
               (helperTransClosure n (cdr L)))))))

;6) Transitive-Closure Function---------------------
(define Transitive-Closure
(lambda (L n)
    (cond ((empty? L) '())
          ((Member? (car L) L) (Remove-Duplicate(append L(helperTransClosure(car L) L))))
            (else (Transitive-Closure (cdr L))))))



;(Member? '1 '(2 2))
(Reflexive? '((1 1)(2 1)(2 2)(3 3)) '(1 2 3))
(Symmetric? '((1 2)(2 1)))
;(Transitive? '((1 2)(2 3)(1 3)))
(Reflexive-Closure '((1 1)(2 2)) '(1 2 3))
(Symmetric-Closure '((1 2)(1 3)(1 5)))
(Transitive-Closure '((1 2)(2 3)(1 5)) 5)
