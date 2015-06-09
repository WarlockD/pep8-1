# What's new in Pep/8 version 8.1.3 #

Version 8.1.3 has minor improvements in the user interface for the debugger. The application name is changed to Pep8 from Pep8-1. The byte converter is enhanced with a new display field to show the decoded opcode. The Help system has a new Assembly Language Syntax summary. Cleaned up some code and improved the performance. Fixed a bug (race condition) that manifested itself when the Return/Enter key is held down during debugging. Fixed a bug that could trap the main window off screen when using the app with a projector. Fixed a bug in LDBYTEA and LDBYTEX that modified the left nybble on load.

# What's new in Pep/8 version 8.1.2 #

Version 8.1.2 now traces the fields of global `struct`s and dynamic variables allocated from the heap with the `new` operator. The heap trace draws a frame around a `struct` consisting of, for example, a node in a linked list. The positioning of the graphic elements in the trace pane is fine tuned so that as the stack grows to require scroll bars, the top of the stack is consistently visible at the top of the graphics pane.

# What's new in Pep/8 version 8.1.1 #

Version 8.1.1 has the symbolic tracer using the trace tags described in the Fourth Edition of the text. This version will trace global variables, and local variables and parameters on the run-time stack. It allows accented characters from the extended ASCII character set (ISO 8859-1) to be used and saved in source programs. There is a new Clear Memory menu option. A scrolling option in the memory dump pane lets the user input an address, or view the region of memory pointed to by the stack pointer or program counter by the click of a button. Also included are performance enhancements and bug fixes.

# What's new in Pep/8 version 8.1.0 #

### Deployment ###

The Windows version is now available as a single .exe executable. When you unzip the download there are only two items in the folder -- the license agreement (GPL) and the application. There is no longer a huge collection of dll files and other files to keep track of to install the program.

The Mac version is now available as a single universal binary application that will run at native speed on either a PowerPC or Intel-based Mac. As with the Windows version, previous support files are now invisible to the user and completely contained within the single application.

### Help system ###

The most visible improvement is a vastly expanded help system. It features complete instructions with accompanying screenshots that describe every aspect of the new software.

Whereas previous releases included programs from the text as separate files, with the release of version 8.1.0 every example from the text is built into the help system and is available at the click of a button. The help system displays assembly language programs side-by-side with the corresponding C++ programs from which they are translated. Students can instantly transfer any assembly language example to the main window to try it out.

### The Save interface ###

Previous versions of Pep/8 suffered from a confusing save system that saved a different document based on which pane was the active one. Pep/8 now provides separate menu commands that explicitly indicate which document is being saved. The Print and Open system has been improved similarly.

### Programming interface ###

Assembly language program source code is now syntax highlighted. There is a new assembler listing pane that is separate from the tracing pane. A new feature "Format From Listing" performs pretty-printing formatting of students' programs. Intelligent tabbing is consistent with the standard format.

There is now a Run button on the toolbar to assemble, load, and execute a source program with a single click.

### Debugging tools ###

The debugging tools are considerably enhanced. There is now a consistent visible debug mode that is different from the normal mode. A more convenient "Start Debugging" button on the toolbar initiates debugging.

The Memory Dump pane updates in real time, eliminating the old Refresh button. It now highlights bytes that are changed with store instructions in one color, instruction bytes pointed to by the program counter in another color, and the top of the run-time stack as specified by the stack pointer in yet another color.

This version maintains all the features of the previous version in its ability to set breakpoints and to single step through the application program and, optionally, through the trap handlers of the operating system.

The byte converter has an improved input interface.

### Endless loops ###

Previous versions handled endless loops by imposing a maximum statement execution count on the running program. Pep/8 now imposes no such restriction and instead allows interruption of an executing program in one of two ways -- interrupt with a switch to debugging mode with the ability to single step or resume, or simple termination.

### Aesthetics ###

The program's look and feel has been streamlined and simplified, in particular the CPU pane. The icons on the toolbar are completely revamped, and the application icon sports a new sleek look that is easy to identify on your computer's desktop or taskbar.