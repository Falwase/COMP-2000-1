load ADDTest01.vm,
output-file ADDTest01.cmp,
output-list RAM[300]%D1.6.1;

set sp 256,        // stack pointer
set local 300,     // base address of the local segment
set argument 400,  // base address of the argument segment
set this 3000,     // base address of the this segment
set that 3010,     // base address of the that segment

set RAM[300] 0,

repeat 4 {        // Change this number to cover the number of instructions in the VM test file
  vmstep;
}

output;

load ADDTest02.vm,
output-file ADDTest02.cmp,
output-list RAM[300]%D1.6.1;

set sp 256,        // stack pointer
set local 300,     // base address of the local segment
set argument 400,  // base address of the argument segment
set this 3000,     // base address of the this segment
set that 3010,     // base address of the that segment

set RAM[300] 0,

repeat 5 {        // Change this number to cover the number of instructions in the VM test file
  vmstep;
}

output;