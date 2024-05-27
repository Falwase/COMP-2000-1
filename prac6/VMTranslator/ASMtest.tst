// Example Test file; compares with the results from generated from the VM test file.
// Run using CPUEmulator

load "vm_pushTEST01.asm",
output-file test.out,
compare-to "vm_pushTEST01.cmp",
output-list RAM[256]%D1.6.1 RAM[257]%D1.6.1 RAM[258]%D1.6.1 RAM[259]%D1.6.1;

set RAM[0] 256,        // stack pointer
set RAM[1] 300,     // base address of the local segment
set RAM[2] 400,  // base address of the argument segment
set RAM[3] 3000,     // base address of the this segment
set RAM[4] 3010,     // base address of the that segment
set RAM[302] 55,
set RAM[403] 56, 
set RAM[3001] 57,
set RAM[3013] 58,

repeat 50 {        // Change this number to cover the number of instructions in the asm test file
  ticktock;
}

output;

load "vm_pushTEST02.asm",
output-file test.out,
compare-to "vm_pushTEST02.cmp",
output-list RAM[256]%D1.6.1 RAM[257]%D1.6.1 RAM[258]%D1.6.1 RAM[259]%D1.6.1;

set RAM[0] 256,        // stack pointer
set RAM[1] 300,     // base address of the local segment
set RAM[2] 400,  // base address of the argument segment
set RAM[3] 3000,     // base address of the this segment
set RAM[4] 3010,     // base address of the that segment
set RAM[18] 54,
set RAM[4] 55,
set RAM[8] 56,

repeat 50 {        // Change this number to cover the number of instructions in the asm test file
  ticktock;
}

output;