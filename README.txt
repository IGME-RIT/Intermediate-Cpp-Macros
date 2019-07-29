Documentation Author: Niko Procopi 2019

This tutorial was designed for Visual Studio 2017 / 2019
If the solution does not compile, retarget the solution
to a different version of the Windows SDK. If you do not
have any version of the Windows SDK, it can be installed
from the Visual Studio Installer Tool

Welcome to the Macro Tutorial!
Prerequesites: None

A macro is a chunk of code that can be inserted anywhere
in our program, and our compilers will think that the macro
was written originally.

If we were to write:
int x = 5;

or if we were to write:
#define number 5
int x = number;

Not only would there be no difference in the compiled program,
but the compiler would view both of 
those ^^ examples as EXACTLY the same.

In addition to variable values, we can use macros to write functions:

If we were to write:
#define Average(a, b) (a + b) / 2
Average(4, 7)

or if we were to write:
(4 + 7) / 2

The compile would see no difference, the compiler would think
we originally typed (4 + 7) / 2 all along
