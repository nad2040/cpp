(load "stdlib.scm")

(define out (open-output-port "a.txt"))

(define board 
    '(
        (1 2 3 4 5 6 7 8)
        (0 1 0 0 0 0 0 0)
        (0 0 1 0 0 0 0 0)
        (0 0 0 1 0 0 0 0)
        (0 0 0 0 1 0 0 0)
        (0 0 0 0 0 1 0 0)
        (0 0 0 0 0 0 1 0)
        (0 0 0 0 0 0 0 1)
    )
)

(define (row-n list num)
    (inrange num list)
    (define (iter l c)
        (if (= c num)
            (car l)
            (iter (cdr l) (+ 1 c))
        )
    )
    (iter list 0)
)

(define (cell board row col)
    (inrange row board)
    (inrange col (car board))
    (define (iter n val l)
        (if (= n val)
            (car l)
            (iter (+ n 1) val (cdr l))
        )
    )
    (iter 0 col (iter 0 row board))
)

(row-n board 7)

(cell board 0 1)
;(write (car board) out)
;(write #\newline out)
;(write board out)

;(load "scm_files/run-meta-circular.scm")