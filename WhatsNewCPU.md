# What's new in Pep/8 CPU version 8.0.0 #

### Deployment ###

The Windows version is now available with a standard Windows installer. When you unzip the download and execute the installer the install wizard confirms your acceptance of the license (GPL). An app shortcut is installed on the user's desktop. The app is now removed with the standard Windows uninstall utility.

### Help system ###

The most visible improvement is a vastly expanded help system modeled after the new help system on the Pep/8 Assembler and Simulator. It features complete instructions with accompanying screenshots that describe every aspect of the new software.

Whereas previous releases included programs from the text as separate files, with the release of version 8.0.0 every example from the text is built into the help system and is available at the click of a button.  Students can instantly transfer any microcode example to the main window to try it out.

### Unit tests ###

The most significant improvement is the incorporation of automated unit tests within the microcode language. In previous versions, students needed to manually set specific values in memory cells or CPU registers. Then they executed their microcode and observed the final values in memory cells or registers. If the final values were consistent with the predicted values the microcode passed the test.

In version 8.0.0, students can program the unit tests into the microcode itself. If the microcode line begins with the keyword **UnitPre:** the remainder of the line causes the simulator to _initialize_ specific values in memory cells or CPU registers automatically _before_ the microcode executes. If the microcode line begins with the keyword **UnitPost:** the remainder of the line causes the simulator to _test_ specific values in memory cells or CPU registers automatically _after_ the microcode executes. The simulator then issues a pass/fail message.

The real payoff for the students is the combination of the enhanced help system with the automated unit tests. The help system not only has all the examples from the text built in, it also has all 28 exercises from the text as well. Each exercise is documented with a register transfer language description of the assembly language statement and with at least one unit test (possibly several) specified with **UnitPre:** and **UnitPost:** statements. As with the examples, at the click of a button the unit tests for an exercise are transferred to the microcode editing pane. After students write their microcode, the unit tests run automatically when they execute their microcode.

### Debugging tools ###

The debugging tools are considerably enhanced. Two types of errors can occur -- programming errors and unit test failures.

When a programming error occurs, the error message is inserted at the end of the line that contains the error. These error messages are handled similarly to the way they are handled in the Pep/8 Assembler and Simulator.

When a unit test fails, the error message is appended at the end of the microprogram and identifies which memory cell or CPU register differs from the predicted value.

The byte converter has the improved input interface from the Pep/8 Assembler and Simulator.

### Programming interface ###

The programming interface sports three new features --  automatic code generation, automatic un/commenting, and automatic formatting.

With automatic code generation, students click on the control signal input widgets in the CPU pane. Each change of a control signal gives instant visual feedback in the CPU pane. Students can see the data flow resulting from their signals. Once they are satisfied with the control settings for a single cycle, they can click the Copy to Microcode button. The result is that a syntactically correct microcode statement corresponding to their control settings is automatically inserted in the microcode editor pane. No typing required!

Automatic un/commenting is a keyboard shortcut to insert or delete double slashes // at the beginning of a group of microcode lines. This feature is especially handy for multiple unit tests. When more than one unit test is present, the first test is uncommented and the others are commented out. After passing the first unit test, students can select the first and second unit test in the microcode editor. With the press of a single key the first unit test will be commented out and the second unit test will be uncommented and ready to execute.

After a program translates successfully, the object code appears in the Object Code pane. Students can then select the Format From Object Code menu item and their source code will be replaced with standard formatted source code extracted from the object code.

### Aesthetics ###

The program's look and feel has been streamlined and simplified. The icons on the toolbar are completely revamped to conform as much as possible with the icons in the Pep/8 Assembler and Simulator. The new application icon sports a new sleek look that also matches the style of the icon for the Pep/8 Assembler and Simulator.