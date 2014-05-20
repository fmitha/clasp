;;;-*-Mode:LISP; Package:NEWCL; Base:10; Syntax:Common-lisp -*-

;;; This is the file newcl.lisp

;;; Revisions of September 27, 1991 by desRivieres@parc.xerox.com:
;;;  - add clause to make print-unreadable-object work for AKCL
;;;  - standardize on uppercase names in setf-function-symbol

;; newcl package made in init.lsp
;;(make-package 'newcl :nicknames '( "newcl" "NEWCL" ) :use '( :core ) )

(in-package :newcl)

(shadow '(defun fmakunbound fboundp))



(export '(fdefinition defun fmakunbound fboundp print-unreadable-object))

;;; New macros to support function names like (setf foo).

(core:defun setf-function-symbol (function-specifier)
  (if (consp function-specifier)
      (let ((print-name #+formatter(format nil "~:@(~A~)" function-specifier)
			#-formatter(bformat nil "%S" function-specifier)))
        (intern print-name
                (symbol-package (cadr function-specifier))))
      function-specifier))

(core:defun fboundp (function-specifier)
  (if (consp function-specifier)
      (core:fboundp (setf-function-symbol function-specifier))
      (core:fboundp function-specifier)))

(core:defun fdefinition (function-specifier)
  (if (consp function-specifier)
      (core:symbol-function (setf-function-symbol function-specifier))
      (core:symbol-function function-specifier)))

(core:defun fmakunbound (function-specifier)
  (if (consp function-specifier)
      (core:fmakunbound (setf-function-symbol function-specifier))
      (core:fmakunbound function-specifier)))

(defsetf fdefinition (function-specifier) (new-value)
  `(set-fdefinition ,new-value ,function-specifier))

(core:defun set-fdefinition (new-value function-specifier)
  (if (consp function-specifier)
      (progn
        (setf (symbol-function (setf-function-symbol function-specifier))
              new-value)
        (eval `(defsetf ,(cadr function-specifier) 
                        (&rest all-args)
                        (new-value)
                 `(,',(setf-function-symbol function-specifier)
                   ,new-value
                   ,@all-args))))
      (setf (symbol-function function-specifier) new-value)))

(defmacro defun (name formals &body body)
  (cond ((symbolp name)
         `(core:defun ,name ,formals ,@body))
        ((and (consp name) (eq (car name) 'setf))
         `(progn 
            (core:defun ,(setf-function-symbol name) ,formals ,@body)
            (defsetf ,(cadr name) ,(cdr formals) (,(car formals))
              (list ',(setf-function-symbol name) ,@formals))))))

#| Minimal tests:
(macroexpand '(defun (setf foo) (nv x y) (+ x y)))
(defun (setf baz) (new-value arg)  (format t "setting value of ~A to ~A" arg new-value))
(macroexpand '(setf (baz (+ 2 2)) (* 3 3)))
|#

;;;
;;; print-unreadable-object
;;;

;;; print-unreadable-object is the standard way in the new Common Lisp
;;; to generate #< > around objects that can't be read back in.  The option
;;; (:identity t) causes the inclusion of a representation of the object's
;;;  identity, typically some sort of machine-dependent storage address.

(defmacro print-unreadable-object
          ((object stream &key type identity) &body body)
  `(let ((.stream. ,stream)
         (.object. ,object))
     (format .stream. "#<")
     ,(when type
        '(format .stream. "~S" (type-of .object.)))
     ,(when (and type (or body identity))
        '(format .stream. " "))
     ,@body
     ,(when (and identity body)
        '(format .stream. " "))
     ,(when identity
        #+Genera '(format .stream. "~O" (si:%pointer .object.))
        #+Lucid  '(format .stream. "~O" (sys:%pointer .object.))
        #+Excl   '(format .stream. "~O" (excl::pointer-to-fixnum .object.))
        #+:coral '(format .stream. "~O" (ccl::%ptr-to-int .object.))
        #+kcl    '(format .stream. "~O" (si:address .object.))
        #+xlisp  '(format .stream. "~O" (xcore::address-of .object.))
       )
     (format .stream. ">")
     nil))


