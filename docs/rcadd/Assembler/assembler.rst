.. highlight:: php

Assembler
=========

General Syntax
--------------

Here are described the general assembly directives that are not part of the
Java Assembly mnemonics list. These are internal directives of the assembler
and are here to help the developer

.byte
^^^^^

::

    .byte $identifier [value]

Creates a `byte` constant to be referenced in the assembly code. During the
compilation process the identifier used in the code is replaced by its value.
No new entry in the constant pool is created by this directive.
If *value* is not provided, the identifier is initialized to 0 automatically.

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

    .int $identifier [value]

Creates an `int` constant in the constant pool.
If *value* is not provided, the identifier is initialized to 0 automatically.

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

Below a list of all available mnemonics for the JVM.
Whenever the stack is mentioned or demonstrated, it should be interpreted as
follows:

**Stack**

::

    itemX  <--- This is the top of the stack
    itemY
    itemZ  
    ...    <-- This is the bottom of the stack, means that there are
               many other items on it that are not displayed as they are
               not relevant to current example

In the examples the stack will usually be illustrated like this:

::

    Before:
        index
        arrayref

    After:
        value

Meaning that before the instruction was executed the stack had 2 items on it
and after the execution it has only 1 item.

.. _A:

.. _aconst_null:

aconst_null
^^^^^^^^^^^

::

    aconst_null

Pushes a null value to the stack

.. _aaload:

aaload
^^^^^^

Loads an arrayref from an array into the operand stack.
The stack has to have the index at the top followed by the arrayref prior to
executing this instruction.

**Stack**

::

    Before:
        index
        arrayref

    After:
        value

**Example**

::

    .method main ([Ljava/lang/String;)V
        bipush 10    ; Array size 
        newarray 4   ; Array type is boolean

        ; At this point the arrayref is at the top
        ; of the stack

        bipush 3     ; Index to be retrieved
        aaload       ; Retrieve value from array
        return
    .method_end

.. _B:

.. _bipush:

bipush
^^^^^^
.. _C:

.. _call:

call
^^^^
.. _D:

.. _dconst_0:

dconst_0
^^^^^^^^

.. _dconst_1:

dconst_1
^^^^^^^^

.. _dup:

dup
^^^

::

    dup

Duplicates the top value of the stack

**Stack**

::

    Before:
        value

    After:
        value
        value

**Example**

::

    .method main ([Ljava/lang/String;)V
        bipush 10
        dup
        return
    .method_end

.. _E:

.. _F:

.. _fconst_0:

fconst_0
^^^^^^^^

.. _fconst_1:

fconst_1
^^^^^^^^

.. _fconst_2:

fconst_2
^^^^^^^^

.. _G:

.. _getstatic:

getstatic
^^^^^^^^^

.. _H:

.. _I:

.. _iconst_m1:

iconst_m1
^^^^^^^^^

.. _iconst_0:

iconst_0
^^^^^^^^

.. _iconst_1:

iconst_1
^^^^^^^^

.. _iconst_2:

iconst_2
^^^^^^^^

.. _iconst_3:

iconst_3
^^^^^^^^

.. _iconst_4:

iconst_4
^^^^^^^^

.. _iconst_5:

iconst_5
^^^^^^^^

.. _invokevirtual:

invokevirtual
^^^^^^^^^^^^^

.. _invokestatic:

invokestatic
^^^^^^^^^^^^


.. _J:

.. _K:

.. _L:

.. _lconst_0:

lconst_0
^^^^^^^^

.. _lconst_1:

lconst_1
^^^^^^^^

.. _ldc:

ldc
^^^

.. _ldc_w:

ldc_w
^^^^^

.. _ldc2_w:

ldc2_w
^^^^^^

.. _M:

.. _N:

.. _newarray:

newarray
^^^^^^^^

::

    newarray type

Pops an int from the operand stack and creates a new array in the operand 
stack with type `type` and puts its reference (an arrayref) in the operand 
stack. The size of the array is defined by the poped int.
`type` can be one of the following values:

* 4 - Array of boolean
* 5 - Array of char
* 6 - Array of float
* 7 - Array of double
* 8 - Array of byte
* 9 - Array of short
* 10 - Array of int
* 11 - Array of long

If any other value is passed a runtime error will be thrown and the execution
will be aborted.

**Stack**

::

    Before:
        size

    After:
        arrayref

**Example**

::

    .method main ([Ljava/lang/String;)V
        bipush 10    ; Array size 
        newarray 4   ; Array type is boolean
        return
    .method_end

.. _nop:

nop
^^^

::

    nop

This is the No OPeration opcode.

**Example**

::

    .method main ([Ljava/lang/String;)V
        nop
        return
    .method_end

.. _O:

.. _P:

.. _pop:

pop
^^^

Pops an item from the top of the operand stack.

**Stack**

::

    Before:
        value1
        value2
        ...

    After:
        value2
        ...

**Example**

::

    .method main ([Ljava/lang/String;)V
        bipush 10
        dup
        pop
        return
    .method_end

.. _pop2:

pop2
^^^^

If the operand stack has two or more items on it, pops the 2 items in the top
from it. If only one item is available, then this is poped.

**Stack**

::

    Before:
        value1
        value2
        value3

    After:
        value3

**Example**

::

    .method main ([Ljava/lang/String;)V
        bipush 10
        dup
        pop2
        return
    .method_end

.. _Q:

.. _R:

.. _return:

return
^^^^^^
.. _S:

.. _sipush:

sipush
^^^^^^

.. _T:

.. _U:

.. _V:

.. _W:

.. _X:

.. _Y:

.. _Z:
