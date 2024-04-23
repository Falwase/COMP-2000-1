load AddSub.asm,
output-file AddSub02.out,
compare-to AddSub02.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[3]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] 1,  // Set R1
set RAM[2] 1,  // Set R2
set RAM[3] 3;  // Set R3

repeat 10 {
  ticktock;
}

output;        // Output to file


