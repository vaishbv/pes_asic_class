# PES_ASIC_CLASS
This Repository Guides you to complete ASIC flow from scratch (GUIDE : Kunal Ghosh)

## The COURSE files are present under those respective day folders 

### Solutions to frequenty occuring errors are in Error_solution.md

## Install the Prerequisites(for ubuntu)

```
sudo apt update
sudo apt upgrade
chmod +x run_ubuntu.sh
./run_ubuntu.sh
```
The installed contents will be available at ~/riscv_toolchain

# Introduction
### Flow : HLL -> ALP -> Binary -> (HDL) -> GDS
#### 1. HLL -> High level language (c , c++) 
- A high-level programming language is a type of programming language that is designed to be more human-readable and user-friendly compared to low-level languages like assembly or machine code.

#### 2. ALP -> Assembly level program
- Assembly language is a low-level programming language that is closely related to the architecture of a specific computer's central processing unit (CPU). Assembly language programs are written using mnemonic codes that represent specific machine instructions which the machine can understand.

#### 3. HDL -> Hardware Description Language
- It is a specialized programming language used for designing and describing digital hardware circuits. HDLs allow engineers to model and simulate complex digital systems before physical implementation, aiding in the design and verification of integrated circuits and FPGA configurations.
- Verilog, System Verilog, VHDL

#### 4. GDS -> Graphic Data System (layout)
- Format used in the semiconductor industry to represent the layout and design of integrated circuits at a highly detailed level. GDSII files contain information about the geometric shapes, layers, masks, and other essential details that make up the physical layout of a chip.
- Tools : Klayout, Magic

##### The Hardware needs to understand what the Application software is saying it to do.This relation can be eshtablished by System Software

____System Software____
- OS : Operating System : Handles IO, memory allocation, Low level system function
- Compiler : Convert the input to hardware dependent instruction
- Assembler : Convert the instructions provided by compiler to Binary format
- HDL : A program that understands the Binary pattern and map it to a netlist
- GDS : Layout

# COURSE 
<details>
<summary> DAY 1: Introduction to RISCV ISA and GNU Compiler Toolchain</summary>
<br>

## Introduction to Risc-v Basic Keywords
- **Instruction Set Architecture(ISA)**
  - An Instruction Set Architecture (ISA) refers to the set of instructions that a computer's central processing unit (CPU) can understand and execute. It defines the interface between software and hardware, specifying the operations that a CPU can perform, the data types it can manipulate, and the memory addressing modes it supports.

- **Risc-V ISA**
  - Risc-V ISA is an open-source ISA that has simpler and fixed length instructions that allows us to create custom processors for specific needs without being tied to proprietary architectures
 
- **Tools Used for the flow**
  - As we are aware of the flow, we will be using Risc-v ISA ALP and the RTL used will be picorv32a (We will be using rv64i during initial stages)

# Goal : Any High level Program that is written should be able to get executed in our CHIP

### List of well-known extensions present in Risc-V ISA

``` rv32i``` ``` rv64i``` ```rv32imc``` ```rv64imc``` ```rv32imafdc``` ```rv64imafdc``` ```rv32imcb``` ```rv64imcb``` ```rv32imc_sv32``` ```rv64gcv```

### Extensions and their Applications

- **I (Integer)** :The I set includes the base integer instruction set for RISC-V. It provides fundamental integer arithmetic and logical operations, data movement, and control flow instructions.
  - ADD, SUB, AND, OR, XOR, ADDI, SLTI, JAL, BEQ, LW

- **M (Multiply and Divide)** : The M set adds integer multiplication and division instructions to the base integer set. These instructions are particularly useful for arithmetic-heavy computations.
  - MUL, MULH, DIV, REM
  
- **A (Atomic)** : The A set introduces atomic memory access instructions. These instructions enable multiple operations on memory locations to be performed atomically, ensuring that other processors or threads cannot observe intermediate states.
  - LR (Load-Reserved), SC (Store-Conditional), AMO (Atomic Memory Operation)
  
- **F (Single-Precision Floating-Point)**: The F set adds single-precision floating-point instructions. These instructions enable arithmetic operations on 32-bit floating-point numbers.
  - FADD.S, FSUB.S, FMUL.S, FDIV.S, FCVT.W.S, FCVT.S.W

- **D (Double-Precision Floating-Point)** : The D set includes double-precision floating-point instructions. These instructions allow arithmetic operations on 64-bit floating-point numbers.
  - FADD.D, FSUB.D, FMUL.D, FDIV.D, FCVT.W.D, FCVT.D.W

- **C (Compressed)** : The C set introduces a compressed instruction format that reduces the size of code. Compressed instructions maintain the same functionality as their non-compressed counterparts but use shorter encodings.
  - C.ADDI4SPN, C.LWSP, C.ADDI, C.SW, C.JALR, C.BEQZ

- **G (Atomic and Lock-Free Operations)** : The G set, also known as the "GAS Set," is an alternative to the A set. It focuses on providing atomic and lock-free instructions to simplify hardware implementation.
  - LRV (Load-Reserved Variant), SCV (Store-Conditional Variant), AMO (Atomic Memory Operation Variants)

- **V (Vector)** :The V set adds vector instructions to the ISA, enabling Single Instruction, Multiple Data (SIMD) operations. These instructions allow efficient parallel processing of data elements in vectors.
  - VADD, VMUL, VFMADD, VLW, VSW

- **S (Supervisor)** : The S set, often used in privileged modes, includes instructions for managing and interacting with the supervisor-level operations of the system, such as handling exceptions and interrupts.
  - ECALL, EBREAK, SRET, MRET, WFI

- **B (Bit Manipulation)** : The B set introduces instructions for bit manipulation operations, allowing efficient manipulation of individual bits in registers and memory.
  - ANDI, ORI, XORI, SLLI, SRLI, SRAI

## 1. Create a simple C program That calculates sum from 1 to N -> sum_1_to_N.c

_____Compile it using C compiler_____
```
gcc sum1ton.c -o sum1ton.o
./a.out
```
-o allows you to name your output file

![PIC 1](https://github.com/vaishbv/pes_asic_class/assets/79531808/05cce47a-f467-4a17-bb99-f0da573d59a6)


_____compile using riscv compiler and view the output_____
```
riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o sum1ton.o sum1ton.c
spike pk sum1ton.o
```

![PIC2](https://github.com/vaishbv/pes_asic_class/assets/79531808/6ab88d57-069d-456a-9265-e8ebbd7751a9)


- ```-O<number>``` : level of optimisation required
- ```-mabi``` : specifies the ABI (Application Binary Interface) to be used during code generation according to the requirements
- ```-march``` : specifies target architecture

_______We can check the different options available for all these fields using the commands_______ 
go to the directory where riscv64-unkonwn-elf is present
- -O1 : ``` riscv64-unkonwn-elf --help=optimizer```
- -mabi : ```riscv64-unknown-elf-gcc --target-help```
- -march : ```riscv64-unknown-elf-gcc --target-help```

_____To view the disassembled ALP code_____
```
riscv64-unkonwn-elf-objdump -d sum1ton.o
```

_____To debug the ALP generated by the compiler_____
```
spike -d pk sum1ton.o
```
![PIC3](https://github.com/vaishbv/pes_asic_class/assets/79531808/c8741610-6636-4541-ab79-55e6e42d5779)


- press ENTER : shows the first line and successive ENTER shows successive lines
- reg 0 a2 : checks content of register a2 0th core
- q : quit the debug process

##### Difference between the ALP commands when used different optimizers
- use the command ```riscv64-unknown-elf-objdump -d sum1ton.o | less```
- use ``` /instance``` to search for an instance 
- press ENTER
- press ```n``` to search next occurance
- press ```N``` to search for previous occurance. 
- use ```esc :q``` to quit

_____Contents of main when used -O1 optimizer_____

![PIC 4](https://github.com/vaishbv/pes_asic_class/assets/79531808/6b27449f-d7b7-47b2-a6dd-e7e432a8a3a7)

_____contents of main when used -Ofast optimizer_____

![PIC5](https://github.com/vaishbv/pes_asic_class/assets/79531808/d96a78fe-1f7a-4f83-8e19-3a98882c9c40)

## Integer number Representation (n-bit)
- Range of Unsigned numbers : [0, (2^n)-1 ]
* Range of signed numbes : Positive : [0 , 2^(n-1)-1]
                         Negative : [-1 to 2^(n-1)]

## 2. create a C program that shows the maximum and minimum values of 64bit unsigend and signed numbers

```
sign_unsign.c
```
![PIC 6](https://github.com/vaishbv/pes_asic_class/assets/79531808/be3a2f63-bea3-4ed9-88cb-9e21bf99b128)


[Back to COURSE](https://github.com/yagnavivek/PES_ASIC_CLASS/tree/main#course)

</details>
<details>
<summary>DAY 2 : Introduction to ABI and Basic Verification Flow </summary>
<br>

## BASICS :

Instructions that act on signed or unsigned integers are called Base Integer Instructions
There are 47 Base Integer Instructions present in RISC-V ISA

### Types of Instruction based on encoding format

1. **R-Type (Register-Type):**
   - These instructions operate on registers and have a fixed format for their operands.
   - Examples: ADD, SUB, AND, OR, XOR, SLL, SRL, SRA, SLT, SLTU

2. **I-Type (Immediate-Type):**
   - These instructions have an immediate operand and one register operand.
   - Examples: ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI, SRAI, LB, LH, LW, LBU, LHU, JALR

3. **S-Type (Store-Type):**
   - These instructions are used for storing values from registers to memory.
   - Examples: SB, SH, SW

4. **B-Type (Branch-Type):**
   - These instructions perform conditional branching based on comparisons.
   - Examples: BEQ, BNE, BLT, BGE, BLTU, BGEU

5. **U-Type (Upper Immediate-Type):**
   - These instructions have a larger immediate field for encoding larger constants.
   - Examples: LUI, AUIPC

6. **J-Type (Jump-Type):**
   - These instructions are used for unconditional jumps and function calls.
   - Examples: JAL

<img width="1000" height="420" alt="image" src="https://github.com/yagnavivek/PES_ASIC_CLASS/assets/93475824/e69043fb-684e-42eb-9e21-fd51943c1ec1">

**[number]** represents number of bits occupied by that field

1. **Opcode [7] :** The opcode is a field within a machine language instruction that indicates the operation to be performed by the instruction. It defines the type of operation, such as arithmetic, logic, memory access, or control flow. Opcodes are used by the CPU to determine how to execute the instruction.

2. **rd (Destination Register) [5]:** The "rd" field represents the destination register in an assembly language instruction. It indicates the register where the result of the operation will be stored. After executing the instruction, the computed value will be placed in this register.

3. **rs1 (Source Register 1) [5]:** The "rs1" field represents the first source register in an assembly language instruction. It indicates the register that holds the value used in the operation. For instructions that involve two operands, "rs1" typically corresponds to the first operand.

4. **rs2 (Source Register 2) [5]:** The "rs2" field represents the second source register in an assembly language instruction. It indicates the register that holds the value used in the operation. For instructions that involve three operands, "rs2" typically corresponds to the second operand.

5. **func7 and func3 (Function Fields)[7] [3]:** These fields further refine the operation specified by the opcode. The "func7" field is used to distinguish different variations of instructions within the same opcode category. The "func3" field is used to specify a more specific operation within the opcode category. Together, these fields allow for a finer level of instruction differentiation.

6. **imm (Immediate Value):** The "imm" field represents an immediate value that is part of the instruction. Immediate values are constants that are embedded within the instruction itself. They can be used for various purposes, such as specifying offsets, constants, or small data values directly within the instruction.
7. 
#### ABI : Application Binary Interface

The instructions generated by compiler using a target ISA can be accessed by OS and User directly
- The parts of ISA accessible to User : User ISA
- The parts of ISA accessible to OS : system ISA
The access is done using Sysytem calls with the help of ABI

==> If we want to access hardware resources of processor, it has to be done via registers using ABI(names)

### ABI Names : 
- ABI names for registers serve as a standardized way to designate the purpose and usage of specific registers within a software ecosystem. These names play a critical role in maintaining compatibility, optimizing code generation, and facilitating communication between different software components.

<img width="1000" height="600" src="https://github.com/yagnavivek/PES_ASIC_CLASS/assets/93475824/27d13974-1b70-4207-a2fb-05b232027323">

#### Data can be stored in register by 2 methods
1. Directly store in registers
2. Store into registers from memory

To store 64 bits of data from mem to reg, we use 8*8bit stores ie., m[0],m[1]......m[7]. 

- ___RISC-V uses Little Endian format to store the data ie., Least significant Byte is stored in m[0]___

## Simulate a C program using ABI function call (using registers) and execute 

The required program files are under day 2 folder
![PIC 1](https://github.com/vaishbv/pes_asic_class/assets/79531808/77b5ab0b-142f-4284-ade5-541cf4c45502)



![PIC 2](https://github.com/vaishbv/pes_asic_class/assets/79531808/9fb9417f-9583-4662-95aa-4787488dc446)


Here we can observe that at 5th line, inorder to comute the result ,its going to the "load"  function

### Further we will see how to run a C program on on RISC-V CPU

[Back to COURSE](https://github.com/yagnavivek/PES_ASIC_CLASS/tree/main#course)
</details>

<details>
<summary>DAY 3 </summary>
<br>
</details>

