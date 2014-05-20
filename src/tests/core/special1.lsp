
(defun foo (x &key key-arg)
  (let (z)
    (declare (special *secret*))
    (values (+ *secret* x) *secret*)))

(defun bar (*secret* a)
  (declare (special *secret*))
  (multiple-value-list (foo a :key-arg t)))

(test-equal (bar 2 3) '(5 2) "defun-let-declare-special")

