load "vm_popTEST01.vm",
output-file "vm_popTEST01.cmp",
output-list RAM[302]%D1.6.1 RAM[403]%D1.6.1 RAM[3001]%D1.6.1 RAM[3013]%D1.6.1;

set sp 256,        // stack pointer
set local 300,     // base address of the local segment
set argument 400,  // base address of the argument segment
set this 3000,     // base address of the this segment
set that 3010,     // base address of the that segment
set RAM[302] 55,
set RAM[403] 56, 
set RAM[3001] 57,
set RAM[3013] 58,

repeat 8 {        // Change this number to cover the number of instructions in the VM test file
  vmstep;
}

output;

load "vm_popTEST02.vm",
output-file "vm_popTEST02.cmp",
output-list RAM[18]%D1.6.1 RAM[4]%D1.6.1 RAM[8]%D1.6.1;

set sp 256,        // stack pointer
set local 300,     // base address of the local segment
set argument 400,  // base address of the argument segment
set this 3000,     // base address of the this segment
set that 3010,     // base address of the that segment
set RAM[18] 54,
set RAM[4] 55,
set RAM[8] 2089,

repeat 7 {        // Change this number to cover the number of instructions in the VM test file
  vmstep;
}