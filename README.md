# AbstractVM :+1:
AbstractVM is a machine that uses a stack to compute simple arithmetic expressions. These arithmetic expressions are provided to the machine as basic assembly programs.
## II.1 The assembly language 
### II.1.1 Example
As an example is still better that all the possible explanations in the world, this is an example of an assembly program that machine can to compute:
```
; -------------
; exemple.avm -
; -------------
push int32(42)
push int32(33)
add
push float(44.55)
mul
push double(42.42); comment
push int32(42)
dump
pop
assert double(42.42)
exit
```
### II.1.2 Description
As for any assembly language, the language of AbstractVM is composed of a series of instructions, with one instruction per line. However, AbstractVM’s assembly language has a limited type system, which is a major difference from other real world assembly languages.
* __Comments:__ Comments start with a ’;’ and finish with a newline. A comment can be either at the start of a line, or after an instruction.
* __push `v`:__ Pushes the value `v` at the top of the stack. The value v must have one of the following form:
  * _int8(n):_ Creates an 8-bit integer with value n.
  * _int16(n):_ Creates a 16-bit integer with value n.
  * _int32(n):_ Creates a 32-bit integer with value n.
  * _float(z):_ Creates a float with value z.
  * _double(z):_ Creates a double with value z.
* __pop:__ Unstacks the value from the top of the stack. If the stack is empty, the program execution must stop with an error.
* __dump:__ Displays each value of the stack, from the most recent one to the oldest one WITHOUT CHANGING the stack. Each value is separated from the next one by a newline.
* __assert `v`:__ Asserts that the value at the top of the stack is equal to the one passed as parameter for this instruction. If it is not the case, the program execution must stop with an error. The value v has the same form that those passed as parameters to the instruction `push`.
* __add:__ Unstacks the first two values on the stack, adds them together and stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.
* __sub:__ Unstacks the first two values on the stack, subtracts them, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.
* __mul:__ Unstacks the first two values on the stack, multiplies them, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error.
* __div:__ Unstacks the first two values on the stack, divides them, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error. Moreover, if the divisor is equal to 0, the program execution must stop with an error too. Chatting about floating point values is relevant a this point. If you don’t understand why, some will understand. The linked question is an open one, there’s no definitive answer.
* __mod:__ Unstacks the first two values on the stack, calculates the modulus, then stacks the result. If the number of values on the stack is strictly inferior to 2, the program execution must stop with an error. Moreover, if the divisor is equal to 0, the program execution must stop with an error too. Same note as above about fp values.
* __print:__ Asserts that the value at the top of the stack is an 8-bit integer. (If not, see the instruction assert), then interprets it as an ASCII value and displays the corresponding character on the standard output.
* __exit:__ Terminate the execution of the current program. If this instruction does not appears while all others instruction has been processed, the execution must stop with an error.
###### When a computation involves two operands of different types, the value returned has the type of the more precise operand. Please do note that because of the extensibility of the machine, the precision question is not a trivial one. This is covered more in details later in this document.
### II.1.3 Grammar
The assembly language of AbstractVM is generated from the following grammar (# corresponds to the end of the input, not to the character ’#’):
```
S := INSTR [SEP INSTR]* #
INSTR :=
  push VALUE
| pop | dump
| assert VALUE
| add
| sub
| mul
| div
| mod
| print
| exit
VALUE :=
  int8(N)
| int16(N)
| int32(N)
| float(Z)
| double(Z)
N := [-]?[0..9]+
Z := [-]?[0..9]+.[0..9]+
SEP := '\n'+
```
### II.1.4 Errors
When one of the following cases is encountered, AbstractVM must raise an exception.
* The assembly program includes one or several lexical errors or syntactic errors.
* An instruction is unknown
* Overflow on a value
* Underflow on a value
* Instruction pop on an empty stack
* Division/modulo by 0
* The program doesn’t have an exit instruction
* An assert instruction is not true
* The stack is composed of strictly less that two values when an arithmetic instruction is executed.
Perhaps there are more errors cases.
### II.1.5 Execution
The Machine is able to run programs from a file passed as a parameter and from the standard input.
When reading from the standard input, the end of the program is indicated by the special symbol `;;` otherwise absent.
Now let see some examples of execution:
 
```
$>./avm
push int32(2)
push int32(3)
add
assert int32(5)
dump
exit
;;
5
$>
```

```
$>cat sample.avm
; -------------
; sample.avm -
; -------------
push int32(42)
push int32(33)
add
push float(44.55)
mul
push double(42.42)
push int32(42)
dump pop
assert double(42.42)
exit
$>./avm ./sample.avm
42
42.42
3341.25
$>
```

```
$>./avm
pop
;;
Line 1 : Error : Pop on empty stack
$>
```
