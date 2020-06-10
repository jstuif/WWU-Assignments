#lang racket
;Joshua Stuifbergen
;3/7/19
;CISS 301
;Lab 6

;helper member function
(define Member?
  (lambda (a L)
    (cond ((null? L) #f)
          ((eq? a (car L)) #t)
          (else
           (Member? a(cdr L))))))

;helper remove-duplicates function
(define Remove-Duplicates
  (lambda (L)
    (cond ((null? L) '())
          ((Member? (car L) (cdr L))
           (Remove-Duplicates (cdr L)))
          (else
           (cons (car L) (Remove-Duplicates (cdr L)))))))

;collect-prop-variables function
(define collect-prop-variables
 (lambda (L)
   (pv L '())))

;The pv function passes the atom and empty list to compare-pv
(define pv
 (lambda (L L2)
   (cond ( (null? L)L)
         ((list? (car L)) (Remove-Duplicates (append (pv(car L) L2) (pv (cdr L)L2))))
         (else
          (append (compare-pv (car L) L2) (pv(cdr L) L2))))))

;compare-pv function
(define compare-pv
 (lambda (a L2)
   (cond ( (equal? a 'and)L2)
         ( (equal? a 'or)L2)
         ( (equal? a 'implies)L2)
         ( (equal? a 'not)L2)
         ( (equal? a 'iff)L2)
         (else
          (list a)))))

;substitute function
;Takes in truth expression, a variable, and element of any type.
(define substitute
 (lambda (L A1 A2)
   (cond ((null? L) L)
         ((list? (car L)) (append (list (substitute(car L) A1 A2)) (substitute (cdr L)A1 A2)))
         ((equal? (car L) A1) (cons A2 (substitute (cdr L) A1 A2)))
         (else
          (cons (car L) (substitute (cdr L) A1 A2))))))

;Evaluate-WFF function
;Takes in prepositional logic with only truth values.
(define Evaluate-WFF
 (lambda (L)
   (cond ((not(list? L)) L)
         ((equal? (length L)3)
          (cond ((equal? (cadr L) 'or) (or (Evaluate-WFF (car L)) (Evaluate-WFF (cdr(cdr L)))))
                ((equal? (cadr L) 'and) (and (Evaluate-WFF (car L)) (Evaluate-WFF (cdr(cdr L)))))
                ((equal? (cadr L) 'implies) (implies (Evaluate-WFF (car L)) (Evaluate-WFF (cdr(cdr L)))))
                ((equal? (cadr L) 'iff) (and (implies (Evaluate-WFF (car L))
                                                      (Evaluate-WFF (cdr(cdr L)))) (implies (Evaluate-WFF (cdr(cdr L))) (Evaluate-WFF (car L)))))))
         ((equal? (length L)2) (not (Evaluate-WFF (cdr L))))
         (else
          (Evaluate-WFF(car L))))))


(collect-prop-variables '((B iff (A or C)) implies (not (C implies A))))
(substitute '((B iff (A or C)) implies (not (C implies A))) 'A 'z )
(Evaluate-WFF '((#t iff (#f or #t)) implies (not (#f implies #t))))
