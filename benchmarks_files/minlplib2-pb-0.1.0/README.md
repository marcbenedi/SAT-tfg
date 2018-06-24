MINLPLIB2-PB
============

Pseudo boolean optimization problems converted from MINLPLIB2 [1].

Some notes on instances
-----------------------

### sporttournament*.opb

The objective functions are scaled by -1 to turn maximization
problems into minimization problems.

### cardqp_iqp.opb

The objective function is scaled by 200000000 to turn fractional
coefficients into integers.

### cardqp_inlp.opb

The objective function is scaled by 200000000 to turn fractional
coefficients into integers.

### faclay80.opb

The objective function is scaled by 2 to turn fractional coefficients
into integers.

Refernces
---------

* [1] GAMS Development Corp. and GAMS Software GmbH, MINLP (Mixed-Integer
  Nonlinear Programming) Library 2, revision 282.
  <http://www.gamsworld.org/minlp/minlplib2/html/>
  Accessed: 2015-06-19.
