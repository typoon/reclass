.. Reclass documentation master file, created by
   sphinx-quickstart on Thu Feb 21 08:20:54 2013.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.


What is Reclass?
================

Reclass is a set of tools and an API that let's you play around with `.class`
files.
Currently it is composed of the following 3 tools:

* `rcdump`_
* `rcmerge`_
* `rcadd`_

It also provides a nice C API to access `.class` internals and make changes to
such files.

rcdump
------

This is a tool that is used to dump information about a `.class` file such as
its constant pool, methods assembly codes, exception handlers, inherited 
classes, implemented interfaces and so on...

See the :ref:`rcdumpDoc` documentation for more details.

rcmerge
-------

This is a tool that is used to merge two `.class` files.

rcadd
-----

This is a tool that let's you write JVM assembly code and have this code added
into a `.class` file of your preference.

With this tool you do not need any of the original build scripts of a class in
order to change it. You can change existing methods, add new methods and so 
on. With the help of rcdump and rcmerge this can be a really powerful tool.

Check the :ref:`rcaddDoc` documentation for more details on how to use it and on the
assembler directive (and also some code examples).

API
---

Check the `API` documentation

.. toctree::
	:maxdepth: 4

	rcdump/index
	rcadd/index
