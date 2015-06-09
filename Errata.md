### Errata for the Fourth Edition, first printing of _Computer Systems_ ###

**Page 38**

In the penultimate paragraph, chang "input" to "output" to read, "You can redirect the output to go ...".

**Page 76**

In Figure 2.38(g), change the number in the bottom box (to which a and b point) from "5" to "3".

**Page 82**

In Exercise 2.8, switch the order of two lines in function main as follows:
```
//ra1
cout << str << endl;
```

**Page 93**

In Figure 3.4(a) The binary number 10110, insert five multiplication signs "x" in the white space gaps.

In Figure 3.4(b) decimal number 58,036, insert five multiplication signs "x" in the white space gaps.

**Page 113**

In Figure 3.21(b), delete four boxes.

**Page 119**

In Figure 3.26, delete eight boxes.

**Page 119**

In Example 3.34, change "101" to "110" to read "The conversion of the whole part gives 110 (bin) to the left ..."

**Page 120**

In Example 3.35, change "011" to "0011" to read "... with the bit pattern 0011 endlessly repeating."

**Page 141**

In Exercises 3.19 and 3.20 in four places, trim the horizontal line to align with the left "ADD".
Also in four places, break the line line and align with the right "ADD".
See Exercises 3.22 and 3.23 on page 142 for the proper break and alignment.

**Page 143**

In Exercises 3.24 and 3.25, add these two sentences to the exercise description, "With ASL, show the effect on the NZVC bits. With ASR show the effect on the NZC bits.".

**Page 165**

Just before Example 4.12, change "Operand" to "Oprnd" to read "byte Oprnd <- r<8..15>".

**Page 187**

In Problem 4.15, add the following two sentences to the problem description, "Store the -3 in hexadecimal. Do not use the subtract, negate, or invert instructions.".

**Page 205**

In the last sentence of the second paragraph, change "000" to "0" and "aaa" to "a" to read "... the assembler will assume immediate addressing and generate 0 for the addressing-a field.".

**Page 216**

Near the middle of the page, correct the spelling of "translation" from "tranlation" in the sentence
"This translation of ...".

**Page 222**

In the last code fragment opposite the margin note "_Legal at level Asmb5_", change "`LOADA`" to "`LDA`" and "`STOREA`" to "`STA`" as follows:
```
LDA y,d
ANDA 0x0007,i
STA y,d
```

**Page 243**

In the first paragraph, change "6" to "4" in two places to read "... that the stack offset for local variable `exam1` is 4." and "... equates the symbol `exam1` to 4.".

**Page 270**

In the caption for Figure 6.35, change "Figure 2.25" to "Figure 2.28".

**Page 282**

In the Assembly Language listing, change "2" to "4" and "0" to "2" as follows:
```
retVal:  .EQUATE 4           ;returned value #2d
a:       .EQUATE 2           ;formal parameter #2d
```

**Page 294**

In Figure 6.39(b), change "0060" to "0063" in the box for `retAddr`.

**Page 301**

In the Assembly Language listing, change "2d" to "2h" in three places as follows:
```
a:       .BLOCK  2           ;global variable #2h
b:       .BLOCK  2           ;global variable #2h
c:       .BLOCK  2           ;global variable #2h
```

**Page 324**

In the caption for Figure 6.49, change "Figure 6.25" to "Problem 6.23".

**Page 338**

In the sentence just before the heading "A Context Sensitive Grammar", change "and" to a right arrow to read "The rule M -> d provides the basis for ..." with the right arrow typeset as in the previous paragraph.

**Page 345**

In Figure 7.9, remove the brackets "<" and ">" around the word "while", and set the letters in "while" to computer font.

**Page 351**

In the first sentence in the section "Multiple Token Recognizers", change "set" to "string" to read, "A token is a string of terminal characters ..."

**Page 364**

In the box labeled "TIdentifier" of Figure 7.30, change the word "int" to "string" to read "- identValue: string", and change "TInteger" to "TIdentifier" to read "+ TIdentifier (str: string)".

**Page 364**

In the first complete sentence, change "TInteger" to "TIdentifier" to read, "Class Identifier has a similar ...".

**Page 366**

On the first line of Figure 7.32, change the font color from blue to black and remove the slant to make consistent with the other lines.

**Page 396**

On the second line of subsection The Trap Mechanism, change "7" to "F" to read "`Temp <-- Mem[FFFA]`".

**Page 416**

Change "8.3" to "8.15" in the figure caption to read "Figure 8.15".

**Page 473**

In the first sentence of the last paragraph, change "Raid" to "RAID" to read, "RAID level 10 is more expensive ...".

**Page 478**

In the first paragraph, change "000000" to "00000" to read, "You could conclude that 00000 was sent ...".

**Page 479**

In the caption for Figure 9.28(b), change "mirros" to "mirrors".

**Page 501**

In Figure 10.13, change " a + b dot c' " to "a + b' dot c " as the expression is in the caption.

**Page 533**

In Figure 10.55, change "0" to "V" in the fourth row from the bottom to read "1100  12  ROLA    N Z V C".

**Page 571**

In the caption for Figure 11.33, change "six" to "five" to read "... the first five bits of the address ...".

**Page 585**

In the last sentence of the third-from-last paragraph, change "0" to "2" to read "... diagram of Figure 11.32.".

**Page 592**

In Exercise 9, change "... as in Figure 11.30" to "... as in Figure 11.31". Add a phrase at the end of the third sentence to read " When Clear is 1, both the master state, Q2, and the slave state, Q, should be forced to 0 regardless of whether the clock is 0 or 1."

**Page 607**

In the second paragraph, change "LDBYTEA" to "STBYTEA" to read "... control sequence for STBYTEA pulse ..."

**Page 613**

In the last paragraph, change "?" to "." to read "... at address 1BD5, which is an odd address."

**Page 614**

In the caption for Figure 12.14, add "memory" to read "The pinout diagram of the Pep/8 memory chip."

**Page 620**

In the third paragraph, "pronounce" to "pronounced" to read "... (RISC, pronounced _risk_)."

**Page 622**

Addendum: Maurice V. Wilkes died on November 29, 2010.

**Page 642**

In the last paragraph, eliminate the comma to read "... is simpler than that of Pep/8 and can be implemented ..."

**Page 645**

In Example 12.10, change "memory" to "register" to read, "... and writes to the register bank, ...".

**Page 645**

In Example 12.10, change "CMux=0" to "CMux=1" in the line numbered 1. on the bottom of the page.

**Page 646**

In Example 12.10 in the first paragraph of the page, change "CMux=0" to "CMux=1" to read "... the result on CBus through CMux with the CMux=1 signal."

**Page 647**

In the first paragraph, change "first" to "third" to read, "... and the wood for the third can be cut."

**Page 660**

In Exercise 12.15 10th line, change "ASL" to "ASLA" to read "You can compute V for the ASLA instruction ...".

**Page 661**

In Exercise 12.23, insert "(a)" at the beginning of the exercise.

**Page 662**

In Exercise 12.27 in the first sentence of part (b), change "implementation" to "connections" and "32" to "128" to read "Draw the connections of the 128 four-input multiplexers."

**Page A6**

Change "14.9" to "A.9" to read, "Figure A.9".

**Page A11**

In the solution for Exercise 3.13(a), change the superscript in the first term from 2 to 1 to read "2x10<sup>1</sup>".

**Page A11**

In the solution for Exercise 3.22, change "N = 0" to "N = 1" in two places for part (e) and for part (f).

**Page A12**

In the solution for Exercise 3.31(a), change "5' TO "4" to read "11,614 (dec)".

**Page A25**

In the solution for Exercise 11.13(a) last line with "Y", keep the bar over "A" and place a bar over the first "X2" in "Y = A X2 + ...".