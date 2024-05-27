load "vm_popTEST01.asm",
output-file test.out,
compare-to "vm_popTEST01.cmp",
output-list RAM[302]%D1.6.1 RAM[403]%D1.6.1 RAM[3001]%D1.6.1 RAM[3013]%D1.6.1;

set RAM[0] 256,        // stack pointer
set RAM[1] 300,     // base address of the local segment
set RAM[2] 400,  // base address of the argument segment
set RAM[3] 3000,     // base address of the this segment
set RAM[4] 3010,     // base address of the that segment
set RAM[302] 55,
set RAM[403] 56, 
set RAM[3001] 57,
set RAM[3013] 58,

repeat 100 {        // Change this number to cover the number of instructions in the VM test file
  ticktock;
}

output;

load "vm_popTEST02.asm",
output-file test.out,
compare-to "vm_popTEST02.cmp",
output-list RAM[18]%D1.6.1 RAM[4]%D1.6.1 RAM[8]%D1.6.1;

set RAM[0] 256,        // stack pointer
set RAM[1] 300,     // base address of the local segment
set RAM[2] 400,  // base address of the argument segment
set RAM[3] 3000,     // base address of the this segment
set RAM[4] 3010,     // base address of the that segment
set RAM[18] 54,
set RAM[4] 55,
set RAM[8] 2089,

repeat 100 {        // Change this number to cover the number of instructions in the VM test file
  ticktock;
}