// Example VM Test file; does not compare, but generates a .cmp file for the given .vm file
// Run using VMEmulator

load "vm_pushTEST01.vm",
output-file "vm_pushTEST01.cmp",
output-list RAM[256]%D1.6.1 RAM[257]%D1.6.1 RAM[258]%D1.6.1 RAM[259]%D1.6.1;

set sp 256,        // stack pointer
set local 300,     // base address of the local segment
set argument 400,  // base address of the argument segment
set this 3000,     // base address of the this segment
set that 3010,     // base address of the that segment
set RAM[302] 55,
set RAM[403] 56, 
set RAM[3001] 57,
set RAM[3013] 58,

repeat 4 {        // Change this number to cover the number of instructions in the VM test file
  vmstep;
}

output;

load "vm_pushTEST02.vm",
output-file "vm_pushTEST02.cmp",
output-list RAM[256]%D1.6.1 RAM[257]%D1.6.1 RAM[258]%D1.6.1 RAM[259]%D1.6.1;

set sp 256,        // stack pointer
set local 300,     // base address of the local segment
set argument 400,  // base address of the argument segment
set this 3000,     // base address of the this segment
set that 3010,     // base address of the that segment
set RAM[18] 54,
set RAM[4] 55,
set RAM[8] 56,

repeat 4 {        // Change this number to cover the number of instructions in the VM test file
  vmstep;
}

output;






