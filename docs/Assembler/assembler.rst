Assembler
=========

.. highlight:: php

This document describes the syntax of the assembly language used by the 
assembler in the rcadd tool.


General Syntax
--------------

Here are described the general assembly directives that are not part of the
Java Assembly mnemonics list. These are internal directives of the assembler
and are here to help the developer

.byte
^^^^^

::

    .byte $identifier value

Creates a `byte` constant to be referenced in the assembly code. During the
compilation process the identifier used in the code is replaced by its value.
No new entry in the constant pool is created by this directive

**Example**

::

    .byte $myByte    0x10
    .byte $otherByte 200

    .method myMethod ()V
        ldc $myByte
    .method_end


.int
^^^^

::

    .int $identifier value

Creates an `int` constant in the constant pool.

**Example**

::

    .int $myInt    0x1000
    .int $otherInt 102934

.double
^^^^^^^

.string
^^^^^^^

.. _.method:

.method
^^^^^^^

::

    .method MethodName (args)ReturnType

This directive allows the programmer to start a method in the code.

**Example**

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

.. _aconst_null:

aconst_null
^^^^^^^^^^^

::

    aconst_null

Pushes a null value to the stack

.. _add:

add
^^^
.. _B:

.. _bipush:

bipush
^^^^^^
.. _C:

.. _call:

call
^^^^
.. _D:

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

