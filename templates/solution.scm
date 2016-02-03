#lang racket
(let loop ((n (read)))
  (when (> n 0)
    (let ((index (read))
      (woord (read)))
      (display (string-ref (symbol->string woord) (- index 1)))
      (newline)
      (loop (- n 1)))))