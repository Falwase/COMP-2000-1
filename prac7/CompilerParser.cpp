#include "CompilerParser.h"

#include <iostream>

bool CompilerParser::isIdentifier() {
    if(self.current()->getType() == "identifier") {
        return true;
    }
    return false;
}

bool CompilerParser::isType() {
    return (isIdentifier() || have("keyword", "int") || have("keyword", "char") || have("keyword", "boolean"));
}

bool CompilerParser::isOp() {
    if(self.current()->getType() != "symbol") {
        return false;
    }

    std::string op = self.current()->getValue();

    return (op == "+" || op == "-" || op == "*" || op == "/" || op == "&" || op == "|" || op == "<" || op == ">" || op == "=");
}

/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {
    this->tokens = tokens;
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    return compileClass();
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    ParseTree* pt = new ParseTree("class", "Class");

    pt->addChild(mustBe("keyword", "class"));

    if(!isIdentifier()) {
        throw ParseException();
    }
    pt->addChild(mustBe("identifier", "MyClass"));

    if(self.current()->getType() != "stringConstant") {
        throw ParseException();
    }
    pt->addChild(self.current());
    next();

    pt->addChild(mustBe("symbol", "{"));

    while(have("keyword", "static") || have("keyword", "field")) {
        pt->addChild(compileClassVarDec());
    }

    while(have("keyword", "constructor") || have("keyword", "function") || have("keyword", "method")) {
        pt->addChild(compileSubroutine());
    }

    pt->addChild(mustBe("symbol", "}"));

    return pt;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree* pt = new ParseTree("classVarDec", "ClassVarDec");

    pt->addChild(self.current());
    next();

    if(!isType()) {
        throw ParseException();
    }
    pt->addChild(self.current());
    next();

    if(!isIdentifier()) {
        throw ParseException();
    }
    pt->addChild(self.current());
    next();

    while(have("symbol", ",")) {
        pt->addChild(self.current());
        isIdentifier();
        pt->addChild(self.current());
        next();
    }

    pt->addChild(mustBe("symbol", ";"));

    return pt;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    ParseTree* pt = new ParseTree("subroutine", "SubroutineDec");

    pt->addChild(self.current());
    next();

    if(have("keyword", "void") || isType()) {
        pt->addChild(self.current());
        next();
    }

    if(!isIdentifier()) {
        throw ParseException();
    }
    pt->addChild(self.current());
    next();

    pt->addChild(mustBe("symbol", "("));

    pt->addChild(compileParameterList());

    pt->addChild(mustBe("symbol", ")"));

    pt->addChild(compileSubroutineBody());

    return pt;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    
    if(!isType()) {
        return NULL;
    }

    ParseTree* pt = new ParseTree("parameterList", "ParameterList");
    pt->addChild(self.current());
    next();
    if(!isIdentifier()) {
        throw ParseException();
    }
    pt->addChild(self.current());
    next();

    while(1) {

        if(!have("symbol", ",")) {
            return pt;
        }
        pt->addChild(mustBe("symbol", ","));

        if(!isType()) {
            throw ParseException();
        }
        pt->addChild(self.current());
        next();

        if(!isIdentifier()) {
            throw ParseException();
        }
        pt->addChild(self.current());
        next();
    }
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree* pt = new ParseTree("subRoutineBody", "SubroutineBody");

    pt->addChild(mustBe("symbol", "{"));

    while(have("keyword", "var")) {
        pt->addChild(compileVarDec());
    }

    pt->addChild(self.current());
    next();

    pt->addChild(mustBe("symbol", "}"));

    return pt;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* pt = new ParseTree("varDec", "VarDec");

    pt->addChild(mustBe("keyword", "var"));

    if(!isType()) {
        throw ParseException();
    }
    pt->addChild(self.current());
    next();

    if(!isIdentifier()) {
        throw ParseException();
    }
    pt->addChild(self.current());
    next();

    while(1) {

        if(!have("symbol", ",")) {
            break;
        }
        pt->addChild(mustBe("symbol", ","));

        if(!isIdentifier()) {
            throw ParseException();
        }
        pt->addChild(self.current());
        next();
    }

    pt->addChild(mustBe("symbol", ";"));

    return pt;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    ParseTree* pt = new ParseTree("statements", "Statements");

    if(have("keyword", "let")) {
        pt->addChild(compileLet());
    }
    else if(have("keyword", "if")) {
        pt->addChild(compileIf());
    }
    else if(have("keyword", "while")) {
        pt->addChild(compileWhile());
    }
    else if(have("keyword", "do")) {
        pt->addChild(compileDo());
    }
    else if(have("keyword", "return")) {
        pt->addChild(compileReturn());
    }
    else {
        throw ParseException();
    }

    return pt;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    ParseTree* pt = new ParseTree("letStatement", "Let");

    pt->addChild(mustBe("keyword", "let"));

    if(!isIdentifier()) {
        throw ParseException();
    }
    pt->addChild(self.current());
    next();

    if(have("symbol", "[")) {
        pt->addChild(mustBe("symbol", "["));
        pt->addChild(compileExpression());
        pt->addChild(mustBe("symbol", "]"));
    }

    pt->addChild(mustBe("symbol", "="));

    pt->addChild(compileExpression());

    pt->addChild(mustBe("symbol", ";"));

    return pt;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    ParseTree* pt = new ParseTree("ifStatement", "If");

    pt->addChild(mustBe("keyword", "if"));

    pt->addChild(mustBe("symbol", "("));

    pt->addChild(compileExpression());

    pt->addChild(mustBe("symbol", ")"));

    pt->addChild(mustBe("symbol", "{"));

    pt->addChild(compileStatements());

    pt->addChild(mustBe("symbol", "}"));

    if(have("keyword", "else")) {
        pt->addChild(mustBe("keyword", "else"));

        pt->addChild(mustBe("symbol", "{"));

        pt->addChild(compileStatements());

        pt->addChild(mustBe("symbol", "}"));   
    }

    return pt;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    ParseTree* pt = new ParseTree("whileStatement", "While");

    pt->addChild(mustBe("keyword", "while"));

    pt->addChild(mustBe("symbol", "("));

    pt->addChild(compileExpression());

    pt->addChild(mustBe("symbol", ")"));

    pt->addChild(mustBe("symbol", "{"));

    pt->addChild(compileStatements());

    pt->addChild(mustBe("symbol", "}"));

    return pt;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    ParseTree* pt = new ParseTree("doStatement", "Do");

    pt->addChild(mustBe("keyword", "do"));

    pt->addChild(compileExpression());

    pt->addChild(mustBe("keyword", ";"));

    return pt;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    ParseTree* pt = new ParseTree("returnStatement", "Return");

    pt->addChild(mustBe("keyword", "return"));

    if(have("symbol", ";")) {
        pt->addChild(mustBe("symbol", ";"));
        return pt;
    }

    pt->addChild(compileExpression());

    pt->addChild(mustBe("symbol", ";"));

    return pt;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    ParseTree* pt = new ParseTree("expression", "Expression");

    if(have("keyword", "skip")) {
        pt->addChild(mustBe("keyword", "skip"));
        return pt;
    }

    pt->addChild(compileTerm());

    while(1) {
        if(!isOp()) {
            return pt;
        }

        pt->addChild(self.current());
        next();

        pt->addChild(compileTerm());
    }
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    ParseTree* pt = new ParseTree("term", "Term");

    std::string type = self.current()->getType();

    if(type == "integerConstant" || type == "stringConstant") {
        pt->addChild(self.current());
        return pt;
    }

    std::string val = self.current()->getValue();

    if(val == "true" || val == "false" || val == "null" || val == "this") {
        pt->addChild(self.current());
        return pt;
    }

    if(have("symbol", "(")) {
        pt->addChild(mustBe("symbol", "("));

        pt->addChild(compileExpression());

        pt->addChild(mustBe("symbol", ")"));

        return pt;
    }

    if(isIdentifier()) {
        Token* temp = new Token(self.current()->getType(), self.current()->getValue());
        next();

        if(have("symbol", "[")) {
            pt->addChild(temp);

            pt->addChild(mustBe("symbol", "["));

            pt->addChild(compileExpression());

            pt->addChild(mustBe("symbol", "]"));

            return pt;
        }

        if(have("symbol", "(")) {
            pt->addChild(temp);

            pt->addChild(mustBe("symbol", "("));

            pt->addChild(compileExpressionList());

            pt->addChild(mustBe("symbol", ")"));

            return pt;
        }

        if(have("symbol", ".")) {
            pt->addChild(temp);

            pt->addChild(mustBe("symbol", "."));

            if(!isIdentifier()) {
                throw ParseException();
            }
            pt->addChild(self.current());
            next();

            pt->addChild(mustBe("symbol", "("));

            pt->addChild(compileExpressionList());

            pt->addChild(mustBe("symbol", ")"));

            return pt;
        }

        pt->addChild(temp);
        return pt;
    }

    if(have("symbol", "-") || have("symbol", "~")) {
        pt->addChild(self.current());
        next();
    }

    return pt;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    ParseTree* pt = new ParseTree("expressionList", "ExpressionList");

    if(have("symbol", ")")) {
        return pt;
    }

    pt->addChild(compileExpression());

    while(1) {
        if(!have("symbol", ",")) {
            return pt;
        }

        pt->addChild(mustBe("symbol", ","));

        pt->addChild(compileExpression());
    }
}

/**
 * Advance to the next token
 */
void CompilerParser::next(){
    tokens.pop_front();
    return;
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::self.current(){
    return tokens.front();
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){  
    Token* t = self.current();
    return (t->getType() == expectedType) && (t->getValue() == expectedValue);
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    if(!(have(expectedType, expectedValue))) {
        throw ParseException();
    }
    Token* t = new Token(expectedType, expectedValue);
    next();
    return t;
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}
