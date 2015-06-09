# Termination of this Google Code site #
Google announced on March 12, 2015 that this Google Code site will be terminated in January 2016.
In the meantime, we will be migrating the code from this site to a new site.
There will be a period of overlap to ease the transition.
Stay tuned for updates that will appear as details become available, probably over the summer.

It has been about five years since the current Pep/8 stable build.
A new edition of the text, _Computer Systems_, is in the works, and it will be based on a new virtual machine, Pep/9, for which we already have a [beta version](https://github.com/StanWarford/pep9.git).
We will continue to support Pep/8 and will post new builds using the latest version of the Qt development tools so the app will play well with the latest versions of the operating systems.

# Computer Systems on iTunes U #
The course, Computer Systems, is now available on iTunes U and can be viewed with Apple's new iTunes U app for the iPad and iPhone.
The course, consisting of 38 video-recorded lectures with lecture slides and homework assignments, covers the first seven chapters of the textbook and includes several demos of the Pep/8 Assembler and Simulator.

[Here](https://itunesu.itunes.apple.com/audit/COFY9WRXRE) is the link, which takes you to the course preview page with your web browser from which you can click to view in the desktop iTunes application and subscribe to the course.
All the course materials including assignments and lectures slides are best viewed on an iOS device
(iPhone, iPad, iPod Touch) with the free iTunes U app.

# Pep/8 Assembler and Simulator **(8.1.3)** #
This repository is for version 8.1 of the source code of the Pep/8 simulator and assembler for use with the textbook _Computer Systems_. The application is written in C++, is GUI-based, and is compiled with the Qt 4 development environment using the Qt Creator IDE available from Digia Plc. at http://www.qt.io/download/.

The current version of the Pep/8 assembler and simulator is **8.1.3**. See [what's new](WhatsNew.md) with this release.

Please send comments, bug reports, and feature requests to [Stan Warford](http://www.cslab.pepperdine.edu/warford/index.html).

# Pep/8 CPU Simulator **(8.0.0)** #
This repository is also for version 8.0 of the source code of the Pep/8 CPU simulator.
The CPU simulator is an implementation of the data section of the Pep/8 CPU as shown in Figure 12.2 of the textbook.
The current version is a complete software rewrite that adds many of the features from the Pep/8 Assembler and Simulator to the Pep/8 CPU simulator.

The current version of the Pep/8 CPU simulator is **8.0.0**. See [what's new](WhatsNewCPU.md) with this release.

Please send comments, bug reports, and feature requests to [Stan Warford](http://www.cslab.pepperdine.edu/warford/index.html).

## Textbooks ##
J. Stanley Warford, _[Computer Systems](http://www.jbpub.com/catalog/9780763771447/)_, fourth edition,
Jones & Bartlett Learning, 2010, ISBN-13: 9780763771447.
See this [errata page](Errata.md) for printing errors in the fourth edition of the textbook.
Please send textbook errata not yet listed to  [Stan Warford](http://www.cslab.pepperdine.edu/warford/index.html).

Pep/8 is also featured in Chapter 6 of _[Computer Science Illuminated](http://www.jblearning.com/catalog/9781284055917/)_, sixth Edition, by Nell Dale and John Lewis, Jones & Bartlett Learning, 2016, ISBN-13: 9781284055917.

## Course syllabi ##
Here are sample course syllabi for
[Chapters 1 - 7](http://www.cslab.pepperdine.edu/warford/cosc330/) and
[Chapters 8 - 12](http://www.cslab.pepperdine.edu/warford/cosc425/)
for _Computer Systems_.
These links also contain support material for the text, such as lecture slides and digital circuit labs.

## Pep/8 at SIGCSE 2010 ##
A paper titled _[The Pep/8 Memory Tracer: Visualizing Activation Records on the Run-Time Stack](http://pep8-1.googlecode.com/files/Pep81Paper.pdf)_ was presented at SIGCSE 2010, the 41st ACM Technical Symposium on Computer Science Education.
The paper in PDF format is now a featured download from this site.

## Downloads ##
The Pep/8 computer is a 16-bit complex instruction set computer (CISC).
It is designed to teach computer architecture and assembly language programming principles.
Its [39 instructions](InstructionSet.md) are based on an expanding opcode and are either unary (one byte) or nonunary (three bytes).
The [eight addressing modes](AddressingModes.md) and [eight dot commands](DotCommands.md) are designed for straightforward translation between C/C++ and assembly language.

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

  * [Pep813Win.zip](http://pep8-1.googlecode.com/files/Pep813Win.zip): Windows executable build for Pep/8 version 8.1.3

  * [Pep813Mac.zip](http://pep8-1.googlecode.com/files/Pep813Mac.zip): Mac universal binary build for Pep/8 version 8.1.3

  * [Pep813Lin.tar.gz](http://pep8-1.googlecode.com/files/Pep813Lin.tar.gz): Ubuntu Linux build for Pep/8 version 8.1.3

Note: Linux version requires installation of Qt libraries.
If there are version conflicts with the libraries, it is straightforward to download the source code and build the application with Qt Creator.
NOTE: The source code should be compiled with the last version of Qt 4, not Qt 5.

Debian based systems may support  the Advanced Packaging Tool. In this case, run `sudo apt-get install libqt4-dev g++` to install the Qt libraries.

For Ubuntu users who prefer software downloads via Personal Package Archives, Ezra Reeves has posted a build at his [PPA site](https://launchpad.net/~pep8simulator).

  * [Pep813.tar.gz](http://pep8-1.googlecode.com/files/Pep813.tar.gz): Source code for Pep/8 version 8.1.3

Download the source code and the Qt Creator IDE available from Digia Plc. at http://qt-project.org/downloads.
Choose the LPGL / Free version.
Launch Qt Creator and open the `pep8-1.pro` project file.
When you click the build icon, Qt Creator will automatically construct the makefile and build the application.

  * [Pep8Term.tar.gz](http://pep8-1.googlecode.com/files/Pep8Term.tar.gz): The C++ source of the command-line terminal version.

Latest version uploaded 14 February 2010.

In the command-line version, users can write assembler source code in their favorite text editor and invoke the assembler on the command line. After a successful assembly, they run the simulator, which includes run-time debugging facilities.
Input/output is done with standard C++ streams so that batch jobs can be scripted with Unix scripting languages.
This feature can be quite useful for grading programming homework problems that are submitted electronically.

### Pep/8 CPU simulator ###

The CPU simulator is an implementation of the data section of the Pep/8 CPU as shown in Figure 12.2 of the textbook.
It features color-coded display paths that trace the data flow depending on control signals to the multiplexers,
a single-cycle mode of operation with GUI inputs for each control signal and instant visual display of the effects of the signal,
and a multi-cycle mode of operation with an integrated text editor for the student to write Mc2 microcode sequences and execute them to implement ISA3 instructions.

The latest version of Pep/8 CPU, 8.0.0, is a complete rewrite with a help system similar to the one in the assembler and simulator.
It features automated unit tests and point-and-click automatic code generation.

  * [Pep8CPU800Win.zip](http://pep8-1.googlecode.com/files/Pep8CPU800Win.zip): Windows executable build for Pep/8 CPU simulator version 8.0.0

  * [Pep8CPU800MacTel.zip](http://pep8-1.googlecode.com/files/Pep8CPU800MacTel.zip): Intel Mac executable build for Pep/8 CPU simulator version 8.0.0

  * [Pep8CPU800Lin.tar.gz](http://pep8-1.googlecode.com/files/Pep8CPU800Lin.tar.gz): Ubuntu Linux executable build for Pep/8 CPU simulator version 8.0.0

  * [Pep8CPU800.tar.gz](http://pep8-1.googlecode.com/files/Pep8CPU800.tar.gz): Source code for Pep/8 CPU simulator version 8.0.0 (NOTE: Compile with the latest version of Qt 4, not Qt 5.)

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