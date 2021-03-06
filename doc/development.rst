.. _development:

===========
Development
===========

If you intend to contribute to Stechec2 or if you want to write your own game,
here are useful tricks to ease your task. As a general note: you may be
interested in taking look at the help message (``./waf.py --help``) to discover
commands and options.

Now most importantly, add the ``--enable-debug`` option to the configure
command so that Stechec2 is built with debugging information. This will enable
you to run Stechec2 under GDB or any other debugger.


Using Clang
-----------

If you prefer Clang over GCC (for error messages, for instance), you can
configure Stechec2 the following way (assuming you properly installed Clang++):

.. code-block:: bash

  CXX=clang++ ./waf.py configure --with-games=...

Then build the project as usual.


Code coverage
-------------

`Code coverage <http://en.wikipedia.org/wiki/Code_coverage>`_ is basically the
answer to "what part of the code is really executed?". It is particularly
useful in the context of a testsuite. When some code is not covered (i.e. never
executed), two conclusions can be drawed:

* either your testsuite misses testcases;

* either you have code that is useless... and thus that uselessly complexifies
  your codebase.

In order to compute code coverage reports, you have to configure Stechec2 with
the ``--enable-gcov`` option. Then build Stechec2 as usual, execute it somehow
(for instance running the testsuite) and then generate the report with the
``coverage`` command:

.. code-block:: bash

  ./waf.py configure --with-games=... --enable-gcov
  ./waf.py build --check # Build and run the testsuite
  ./waf.py coverage

At this point, you can open the ``build/gcov-report.html`` file in your
favorite browser and discover what parts of your code are not tested/useless!

Note that code coverage does not work very well when using another compiler
than G++. There exists ``llvm-cov``, but our report formatter, ``gcovr``
mysteriously crashes when attempting to use it. So please use G++ when you want
to compute code coverage. :-)


Address sanitizer
-----------------

GCC or LLVM's `address sanitizer
<http://en.wikipedia.org/wiki/AddressSanitizer>`_ is as useful as Valgrind when
programming with manual memory management (such as in C or C++) to detect
various memory issues. Using this feature is very easy in Stechec2: just
use the ``--enable-asan`` configure option. ASAN will output messages on
Stechec2's standard error output if it detects any issue. Note that when this
happens in our testsuite, the corresponding testcases fail (which is good! such
issues must be fixed!).
