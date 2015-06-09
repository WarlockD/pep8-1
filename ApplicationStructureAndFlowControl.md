## Overall flow ##

Pep/8 uses the mediator design pattern, and flow moves through the mainWindow.

For example, when the "Copy to Source/Object" button is clicked in the helpDialog, the helpDialog emits a signal that the mainWindow is connected to. The mainWIndow then sends the signal to the ObjectCodePane or the SourceCodePane, depending on the example.

The CPU pane is the brains of the simulator, and much of the code to control debugging happens here. However, the CPU pane depends on the other panes for input, and much of the data stored in the other panes is reflected in the Sim class, which contains the machine's memory, and code for the von Neumann step.

## Debugging Details ##

The panes used for debugging memory (MemoryTracePane, MemoryDumpPane) contain a number of data structures used to keep track of bytes modified in each von Neumann step, as well as data structures to keep track of modified bytes since the last GUI update.

These two methods of tracking modified information in the machine is used for efficiency (rather than updating the memory each cycle, when the same bytes are being modified numerous times between breakpoints), as well as allowing us to highlight important bytes (modified bytes, or the program counter, or stack pointer).

The program enforces a debugging mode on it's interface by making panes that shouldn't be modified during the execution of the program read-only, and re-enabling them again when debugging stops.