load ADDTest01.asm,
output-file test.out,
compare-to ADDTest01.cmp,
output-list RAM[300]%D1.6.1;

set RAM[0] 256,        // stack pointer
set RAM[1] 300,     // base address of the local segment
set RAM[2] 400,  // base address of the argument segment
set RAM[3] 3000,     // base address of the this segment
set RAM[4] 3010,     // base address of the that segment

set RAM[300] 0,

repeat 40 {        // Change this number to cover the number of instructions in the VM test file
  ticktock;
}

output;

load ADDTest02.asm,
output-file test.out,
compare-to ADDTest02.cmp,
output-list RAM[300]%D1.6.1;

set RAM[0] 256,        // stack pointer
set RAM[1] 300,     // base address of the local segment
set RAM[2] 400,  // base address of the argument segment
set RAM[3] 3000,     // base address of the this segment
set RAM[4] 3010,     // base address of the that segment

set RAM[300] 0,

repeat 40 {        // Change this number to cover the number of instructions in the VM test file
  ticktock;
}

output;