(defvar ht (make-hash-table))
(hash-table-setf-gethash ht 'a 10)
(hash-table-setf-gethash ht 'b 20)
(hash-table-setf-gethash ht 'c 30)
(defvar it (hash-table-iterator ht))
