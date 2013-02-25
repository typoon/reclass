Reclass
=======

Reclas is a set of tools and also a library related to Java .class 
decompilation and modification.
The rcdump tool can be used to decompile .class files to their assembly 
directives, grab information about the file sections (number of items in the 
constant pool, contents of the constant pool, list of methods and so on).
With the rcmerge tool one can merge a .class file into another, overriding 
methods of the original class file or simply adding new ones.
The rcadd tool lets the user add its own assembly directives into a .class
without the need to have a java compiler in the machine. This is a powerfull
tool because there is no Java code compiling involved at all. 

TODO
====

The project started just as something to have fun with and to understand how
a .class file is organized and so it was not very well written from the 
begining (shame on me). At this point the project needs some crucial things:
    * Have its functions rewritten following a development pattern
    * Reorganize code
    * Change functions that take a char* as a parameter to start taking an 
    utf8
    * Document the assembler directives
    * Write a better Makefile

At this point, if you want to be sure that decompiling works, your code should
be limited to JAVA SE 2 features.
The following represents some of the things that are missing implementation:

    * Change function readAttributeInfo from classfile.c to be able to read
    and parse the following attributes:
        StackMapTable
        EnclosingMethod
        Signature
        SourceDebugExtension
        LocalVariableTypeTable
        RuntimeVisibleAnnotations
        RuntimeInvisibleAnnotations
        RuntimeVisibleParameterAnnotations
        RuntimeInvisibleParameterAnnotations
        AnnotationDefault
    * Add validation routines to function readInterfaces to make sure methods
    match the .class format specification
    * Add validation routines to function readFields to make sure methods 
    match the .class format specification
    * Add validation routines to function readMethods to make sure methods 
    match the .class format specification
    * Add validation routines to function readAttributeInfo to make sure 
    methods match the .class format specification


Helping
=======

If you want to help, feel free to push the code and have a look around. When 
you have something you are ready to help with or if you just want to make a 
suggestion or comment, email me: typoon_at_gmail.com

