## Daxton Johnson CS219 Programming Project 3

## Running
Run make in the terminal, generated executable name is hexAdder. Simply run "./hexAdder" in the terminal. If you want to edit inputs that's fine and shouldn't cause any issues, but "input.txt" is hardcoded, so make sure to put any modifications in that file or another file with that exact name. Otherwise the program will output a file error and terminate. 

## Working Process
In order to make the code as extendable as possible, I created a class called "Number" that accepts a string parameter which represents a hexadecimal number. This number is stored in the class and then used to automatically generate the decimal and binary equivalents, which can then be used to more simply implement arithmetic and logical functions. This allows for a wide range of operations to be easily implemented, as showcased by running the program with the provided input file. The program accepts a variety of OPCODE formatted inputs, and outputs the various states of the 8 registers after each instruction along with new register data. 

## Result
A program which accepts a formatted text file as input and can be used to perform simple functions, and outputs the instruction run, the register states after running the instruction, and the flag states after running the instruction. 