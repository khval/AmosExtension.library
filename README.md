# AmosExtension.library

The general idea behind this library is, create some basic routines that allows you to open Amos Extensions in C/C++ programs can call functions from extensions.

Library should be able to open the extension, check if it is a valid extension.
Find a command by name. Get command by token number, lookup the command table, 
and find address to 680x0 relocatable assembler code, then you should be able to call emulate on 680x0 assembler, from AmigaOS4.1 C/C++ program.
There should be a command info structure, and a command list structure with address to assembler, and size of routine.

A more direct way to use library is using defines to tell the offset in command table.
this can be extracted from extensions to create .h files.

Tools that use this library
Amos2Ascii, AmosExtentions2Ascii.