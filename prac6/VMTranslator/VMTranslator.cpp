#include <string>

#include "VMTranslator.h"

using namespace std;

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}

/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset){

    if(segment == "local") {
        return "@LCL\nD=M\n@" + to_string(offset) + "\nA=A+D" + "\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
    }
    else if(segment == "argument") {
        return "@ARG\nD=M\n@" + to_string(offset) + "\nA=A+D" + "\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
    }
    else if(segment == "this") {
        return "@THIS\nD=M\n@" + to_string(offset) + "\nA=A+D" + "\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
    }
    else if(segment == "that") {
        return "@THAT\nD=M\n@" + to_string(offset) + "\nA=A+D" + "\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
    }
    else if(segment == "pointer") {
        return "@" + to_string(3+offset) + "\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
    }
    else if(segment == "temp") {
        return "@" + to_string(5+offset) + "\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
    }
    else if(segment == "static") {
        return "@" + to_string(16+offset) + "\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
    }
    else if(segment == "constant") {
        return "@" + to_string(offset) + "\nD=A\n@SP\nAM=M+1\nA=A-1\nM=D\n";
    }

    return "";
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){
    if(segment == "local") {
        return "@LCL\nD=M\n@" + to_string(offset) + "\nD=A+D\n@13\nM=D\n@SP\nAM=M-1\nD=M\n@13\nA=M\nM=D\n";
    }
    else if(segment == "argument") {
        return "@ARG\nD=M\n@" + to_string(offset) + "\nD=A+D\n@13\nM=D\n@SP\nAM=M-1\nD=M\n@13\nA=M\nM=D\n";
    }
    else if(segment == "this") {
        return "@THIS\nD=M\n@" + to_string(offset) + "\nD=A+D\n@13\nM=D\n@SP\nAM=M-1\nD=M\n@13\nA=M\nM=D\n";
    }
    else if(segment == "that") {
        return "@THAT\nD=M\n@" + to_string(offset) + "\nD=A+D\n@13\nM=D\n@SP\nAM=M-1\nD=M\n@13\nA=M\nM=D\n";
    }
    else if(segment == "pointer") {
        return "@SP\nAM=M-1\nD=M\n@" + to_string(3+offset) + "\nM=D\n";
    }
    else if(segment == "temp") {
        return "@SP\nAM=M-1\nD=M\n@" + to_string(5+offset) + "\nM=D\n";
    }
    else if(segment == "static") {
        return "@SP\nAM=M-1\nD=M\n@" + to_string(16+offset) + "\nM=D\n";
    }
    else if(segment == "constant") {
        return "@SP\nAM=M-1\n";
    }

    return "";
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){
    /*
    @SP
    AM=M-1
    D=M
    A=A-1
    M=D+M
    */
    return "@SP\nAM=M-1\nD=M\nA=A-1\nM=D+M\n";
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    return "";
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    return "";
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq(){
    return "";
}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){
    

    return "@SP\nAM=M-1\nA=A-1\nD=M\nA=A+1\nD=D-M\n@GREATER\nD;JGT\n@SP\nA=M-1\nM=0\n@EXIT\n0;JMP\n(GREATER)\n@SP\nA=M-1\nM=0\nM=M-1\n(EXIT)\n";
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){

    return "@SP\nAM=M-1\nA=A-1\nD=M\nA=A+1\nD=D-M\n@LESSER\nD;JLT\n@SP\nA=M-1\nM=0\n@EXIT\n0;JMP\n(LESSER)\n@SP\nA=M-1\nM=0\nM=M-1\n(EXIT)\n";

}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
    return "";
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    return "";
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    return "";
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    return "(" + label + ")\n";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    return "@" + label + "\n0;JMP\n";
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    /*
    @SP
    AM=M-1
    D=M
    @(label)
    D;JNE
    */
    return "@SP\nAM=M-1\nD=M\n@" + label + "\nD;JNE\n";
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
/*
((function_name))
@0
D=A

repeat n_vars times
@SP
AM=M+1
A=A-1
M=D
*/
    string varPusher = "";

    for(int i = 0; i < n_vars; i++) {
        varPusher = varPusher + "@SP\nAM=M+1\nA=A-1\nM=D\n";
    }

    return "(" + function_name + ")\n@0\nD=A\n" + varPusher;
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){

    string lbl = function_name + "a";

    /*
    @lbl
    D=A
    @SP
    AM=M+1
    A=A-1
    M=D
    */

    /*
    @SP
    D=A
    @5
    D=D-A
    @(n_args)
    D=D-A
    */

    return "@" + lbl + "\nD=A\n@SP\nAM=M+1\nA=A-1\nM=D\n" +
           "@LCL\nD=A\n@SP\nAM=M+1\nA=A-1\nM=D\n" +
           "@ARG\nD=A\n@SP\nAM=M+1\nA=A-1\nM=D\n" +
           "@THIS\nD=A\n@SP\nAM=M+1\nA=A-1\nM=D\n" +
           "@THAT\nD=A\n@SP\nAM=M+1\nA=A-1\nM=D\n" +
           "SP\nD=A\n@5\nD=D-A\n@" + to_string(n_args) + "\nD=D-A\n" +
           "@SP\nD=M\n@LCL\nM=D\n" +
           "@" + function_name + "\n0;JMP\n" +
           "(" + lbl + ")\n";
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){

    return "@LCL\nD=M\n@13\nM=D\n@13\nD=M\n@5\nD=D-A\nA=D\nD=M\n@14\nM=D\n@SP\nA=M-1\nD=M\n@ARG\nA=M\nM=D\n@ARG\nD=A+1\n@SP\nM=D\n@13\nD=M\n@1\nD=D-A\nA=D\nD=M\n@THAT\nM=D\n@13\nD=M\n@2\nD=D-A\nA=D\nD=M\n@THIS\nM=D\n@13\nD=M\n@3\nD=D-A\nA=D\nD=M\n@ARG\nM=D\n@13\nD=M\n@4\nD=D-A\nA=D\nD=M\n@LCL\nM=D\n@14\nA=M\n0;JMP\n";
}