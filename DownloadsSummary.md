## Downloads ##
The Pep/8 computer is a 16-bit complex instruction set computer (CISC).
It is designed to teach computer architecture and assembly language programming principles.
Its [39 instructions](InstructionSet.md) are based on an expanding opcode and are either unary (one byte) or nonunary (three bytes).
The [eight addressing modes](AddressingModes.md) and [eight dot commands](DotCommands.md) are designed for straighforward translation between C/C++ and assembly language.

The Downloads section of this site contains builds and source code for the support software for the textbook.
In addition to the assembler and simulator hosted at this site, the Downloads section includes a CPU simulator and a cache simulator.
Here is a summary of the Downloads software.

### Pep/8 assembler and simulator ###

The assembler features an integrated text editor,
error messages in red type that are inserted within the source code at the place where the error is detected,
student-friendly machine language object code in hexadecimal format,
the ability to code directly in machine language, bypassing the assembler,
and the ability to redefine the mnemonics for the unimplemented opcodes that trigger synchronous traps.

The simulator features simulated ROM that is not altered by store instructions,
a small operating system burned into simulated ROM that includes a loader and a trap handler system,
an integrated debugger that allows for break points, single step execution,
CPU tracing, and memory tracing,
the option to trace an application, the loader, or the operating system,
the ability to recover from endless loops,
and the ability to modify the operating system by designing new trap handlers for the unimplemented opcodes.

  * [Pep812Win.zip](http://pep8-1.googlecode.com/files/Pep812Win.zip): Windows executable build for Pep/8 version 8.1.2

  * [Pep812Mac.zip](http://pep8-1.googlecode.com/files/Pep812Mac.zip): Mac universal binary build for Pep/8 version 8.1.2

  * [Pep812Lin.tar.gz](http://pep8-1.googlecode.com/files/Pep812Lin.tar.gz): Ubuntu Linux build for Pep/8 version 8.1.2

Note: Linux version requires installation of Qt libraries.
If there are version conflicts with the libraries, it is straightforward to download the source code and build the application with Qt Creator.

Debian based systems may support  the Advanced Packaging Tool. In this case, run `sudo apt-get install libqt4-dev g++` to install the Qt libraries.

For Ubuntu users who prefer software downloads via Personal Package Archives, Ezra Reeves has posted a build at his [PPA site](https://launchpad.net/~pep8simulator).

  * [Pep812.tar.gz](http://pep8-1.googlecode.com/files/Pep812.tar.gz): Source code for Pep/8 version 8.1.2

Download the source code and the Qt Creator IDE available from [Nokia](http://qt.nokia.com/).
Choose the LPGL / Free version.
Launch Qt Creator and open the `pep8-1.pro` project file.
When you click the build icon, Qt Creator will automatically construct the makefile and build the application.

  * [Pep8Term.tar.gz](http://pep8-1.googlecode.com/files/Pep8Term.tar.gz): The C++ source of the command-line terminal version.

Latest version uploaded 14 February 2010.

Students write assembler source code in their favorite text editor and invoke the assembler on the command line. After a successful assembly, they run the simulator, which includes run-time debugging facilities.
Input/output is with standard C++ streams so that batch jobs can be scripted with Unix scripting languages.
This feature can be quite useful for grading programming homework problems that are submitted electronically.

## Pep/8 CPU simulator ##

The CPU simulator is an implementation of the data section of the Pep/8 CPU as shown in Figure 12.2 of the textbook.
It features color-coded display paths that trace the data flow depending on control signals to the multiplexers,
a single-cycle mode of operation with GUI inputs for each control signal and instant visual display of the effects of the signal,
and a multi-cycle mode of operation with an integrated text editor for the student to write Mc2 microcode sequences and execute them to implement ISA3 instructions.

  * [Pep8CPU46Win.zip](http://pep8-1.googlecode.com/files/Pep8CPU46Win.zip): Windows executable build for Pep/8 CPU simulator version 46

  * [Pep8CPU46MacPower.zip](http://pep8-1.googlecode.com/files/Pep8CPU46MacPower.zip): PowerPC Mac executable build for Pep/8 CPU simulator version 46

  * [Pep8CPU46MacTel.zip](http://pep8-1.googlecode.com/files/Pep8CPU46MacTel.zip): Intel Mac executable build for Pep/8 CPU simulator version 46

  * [Pep8CPU46.tar.gz](http://pep8-1.googlecode.com/files/Pep8CPU46.tar.gz): Source code for Pep/8 CPU simulator version 46

### Pep/8 cache simulator ###

This contribution by Professor Peter Smith, California State University Channel Islands,
is a command-line interface implementation of the cache shown in Figures 12.32 and 12.33 of the textbook.
The user determines the structure of the cache by specifying the block size, the number of blocks per row, and the number of rows.
A selection of 1 for the number of blocks per row is equivalent to the direct-mapped cache of Figure 12.29,
while a number greater than 1 is equivalent to the set-associative cache of Figure 12.30.

In addition, the user determines whether instructions and data share the cache.
If there are separate caches for instructions and data then half the rows are used for each.

The user can select one of four replacement algorithms: random, LRU, LFU and FIFO.
The discussion of replacement algorithms in Chapter 12.2 in _Computer Systems_ is brief and only mentions the Least Recently Used (LRU) algorithm.
Replacement algorithms for cache line replacement are similar to those for page replacement described in Chapter 9.2, which also describes the first in, first out (FIFO) algorithm.
In addition to these two replacement algorithms, the Pep/8 cache simulator allows the user to select the least frequently used (LFU) algorithm and the Random algorithm.
With LFU, a count is maintained for each line that is hit in the cache, and that line is chosen for replacement that has the smallest count.
With the Random algorithm, a line is selected at random for replacement.

The cache simulator collects performance statistics on Pep/8 machine language programs.
It loads the Pep/8 operating system and runs Pep/8 object programs produced by any of the assembler programs.

  * [Pep8Cache352.zip](http://pep8-1.googlecode.com/files/Pep8Cache352.zip): The C source code and documentation for version 3.5.2 of the Pep/8 cache simulator.

### Papers ###

  * [Pep81Paper.pdf](http://pep8-1.googlecode.com/files/Pep81Paper.pdf): A paper on the Pep/8 symbolic memory trace feature from the 2010 ACM SIGCSE conference

  * [Pep8CPUPaper.pdf](http://pep8-1.googlecode.com/files/Pep8CPUPaper.pdf): A paper on the Pep/8 CPU simulator from the 2007 ACM SIGCSE conference