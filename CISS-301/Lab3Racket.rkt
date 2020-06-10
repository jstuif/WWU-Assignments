#lang racket
;Joshua Stuifbergen
;2/5/19
;CS301
;Lab 3

;Member function. Checks if the atom a if part of the function L.
(define Member?
  (lambda (a L)
    (cond ((null? L) #f)
          ;if the first element is equal to the atom then True.
          ((eq? a (car L)) #t)
            ;else the next element is equal to the atom then True.
          (else
           (Member? a(cdr L))))))

;Helper function to remove duplicates for Union function. 
(define Rem-Dup
  (lambda (L)
    (cond ((null? L) '())
          ;If the same element in the lists remove duplicate.
          ((Member? (car L) (cdr L))
           (Rem-Dup (cdr L)))
          ;Else add to new list.
          (else
           (cons (car L) (Rem-Dup (cdr L)))))))

;Union function. Combines each element into list and removes duplicates.
(define Union
  (lambda (L1 L2)
    (Rem-Dup (append L1 L2))))

;Instersection? function. Creates new list of elements that are in both lists.
(define Intersection?
  (lambda (L1 L2)
    (cond ((null? L1) '())
          ((Member? (car L1) L2)
           ;If a memeber of both lists add to new list. 
           (cons (car L1) (Intersection? (cdr L1) L2)))
          (else
           (Intersection? (cdr L1) L2)))))

;Symmetric-Difference function. Combines elements that are not shared between
;both lists.
(define Symmetric-Difference
  (lambda (L1 L2)
    (cond ((null? L1) '())
          ((Member? (car L1) L2)
           ;If first element from L1 matches L2, then compare vice versa.
           (Symmetric-Difference (cdr L2) L1))
           (else
            ;If they do not match, add to new list.
            (cons (car L1) (Symmetric-Difference (cdr L1) L2))))))


(Member? 'a '(c b))
(Union '(1 2 3) '(2 3 4 5))
(Intersection? '(1 2 3) '(2 3 4 5))
(Symmetric-Difference '(1 2 3 6) '(3 4 5 6))
