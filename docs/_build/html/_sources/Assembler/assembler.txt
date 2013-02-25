Assembler
=========

.. highlight:: cpp

This document describes the syntax of the assembly language used by the 
assembler in the rcadd tool.


General Syntax
--------------

Here are described the general assembly directives that are not part of the
Java Assembly mnemonics list. These are internal directives of the assembler
and are here to help the developer

.. _.method:

.method
^^^^^^^

::

    .method MethodName (args)ReturnType

This directive allows the programmer to start a method in the code.

*Example*

::

    .method myMethod([Ljava/lang/String;)V
    .method_end



.method_end
^^^^^^^^^^^

::

    .method_end

This directive identifies the end of a method started with the `.method`_
directive

Mnemonics Index
---------------

   `A`_ | `B`_ | `C`_ | `D`_ | `E`_ | `F`_ | `G`_ | `H`_ | `I`_ | `J`_ |
   `K`_ | `L`_ | `M`_ | `N`_ | `O`_ | `P`_ | `Q`_ | `R`_ | `S`_ | `T`_ |
   `U`_ | `V`_ | `W`_ | `X`_ | `Y`_ | `Z`_ 

Mnemonics
---------

.. _A:

add
^^^
.. _B:

bipush

.. _C:

call

.. _D:

delete

.. _E:

.. _F:

.. _G:

.. _H:

.. _I:

.. _J:

.. _K:

.. _L:

.. _M:

.. _N:

.. _O:

.. _P:

.. _Q:

.. _R:

.. _S:

.. _T:

.. _U:

.. _V:

.. _W:

.. _X:

.. _Y:

.. _Z:

