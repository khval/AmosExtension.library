# AmosExtension.library

The general idea behind this library is, create some basic routines that allows you to open Amos Extensions in C/C++ programs can call functions from extensions.

Library should be able to open the extension, check if valid.
Find a command by name. Get command number, lookup the command table, and find address to 680x0 relocatable assembler code, then you should be able to call emulate on 680x0 assembler, from AmigaOS4.1 C/C++ program.
There should command info structure, and a command structure, address to assembler, and size of routine. 
