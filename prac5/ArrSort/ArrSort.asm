// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// R3 for i
// R4 for key
// R5 for j

// Put your code here.

// void insertionSort(int arr[], int n)
// {
//    int i, key, j;

@R3 
M=1 //    (i = 1;)
(FORLOOP) //    for (i = 1;i < n; i++) {
@R3
D=M
@R2
D=M-D
@FORSKIP 
D;JLE //    (i < n;)
@R3
D=M 
@R1
A=M+D 
D=M
@R4
M=D //        key = arr[i];
@R3
D=M
@R5 
M=D-1 //        j = i - 1;
//
//        /* Move elements of arr[0..i-1], that are
//          greater than key, to one position ahead
//          of their current position */
(WHILELOOP) //        while (j >= 0 && arr[j] > key) {
@R5
D=M
@WHILESKIP
D;JLT //        (j >= 0 &&)
@R4
D=M
@NEG
D;JLT
@R1 // key >= 0
D=M
@R5
A=D+M
D=M
@WHILESKIP
D;JLT
@R4
D=D-M
@WHILESKIP
D;JLE //        (arr[j] > key)
(IFGREATER)
@R5
D=M
@R1
A=M+D
D=M
A=A+1
M=D //            arr[j + 1] = arr[j];
@R5 
M=M-1 //            j = j - 1;
@WHILELOOP
0;JMP //        }
(WHILESKIP)
@R1
D=M
@R5
D=D+M
D=D+1
@R4
D=D+M
A=D-M
M=D-A //        arr[j + 1] = key;
@R3
M=M+1 //    (i++;)
@FORLOOP 
0;JMP//    }
(FORSKIP)
@R0
M=0
M=M-1
@END
(END)
0;JMP //}

(NEG) // if key < 0
@R1
D=M
@R5
A=D+M
D=M
@IFGREATER
D;JGE
@R4
D=D-M
@IFGREATER
D;JGT
@WHILESKIP
0;JMP