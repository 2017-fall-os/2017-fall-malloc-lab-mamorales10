# os-malloc
This directory contains:

* myAllocator.c: a first-fit/best-fit allocator
* myAllocator.h: its header file

* myAllocatorTest1.c: a first-fit test program for my allocator

* myAllocatorTest2.c: my test program for the malloc lab assignment

* malloc.c: a replacement for malloc that uses my allocator
* test1.c: a test program that uses this replacement malloc

There are two different testers as some implementations of printf
call malloc to allocate buffer space. This causes test1 to behave
improperly as it uses myAllocator as a malloc replacement. In this
case myAllocatorTest1 will function correctly. The only difference
between the programs is that test1 uses myAllocator as a malloc
replacement and myAllocatorTest1 uses myAllocator directly.

Makefile: a fairly portable "makefile", targets "all" and "clean"

To compile:
~~~
$ make
~~~
To run malloc lab test program:
~~~
$ ./myAllocatorTest2
~~~
To clean:
~~~
$ make clean
~~~

The cygwin runtime uses malloc() and brk() extensively.  It is
interesting to compare the output of test1 & myAllocatorTest1.  All
those extra allocated regions are being used by cygwin's libraries!

## References
Jose Cabrera and I discussed a possible way to approach the resizeRegion part of the lab and how to make it so that the function doesn't take unnecessary space when making the larger region size. I used this approach in this lab and, according to my test cases, I got it to work.

