from ParseTree import *

class CompilerParser :

    def __init__(self,tokens):
        """
        Constructor for the CompilerParser
        @param tokens A list of tokens to be parsed
        """

        self.tokens = tokens
        pass

    def isIdentifier(self):
        if(not self.current().getType() == "identifier"):
            raise ParseException("not identifier")
        else:
            return True

    def isType(self):
        return (self.isIdentifier() or self.have("keyword", "int") or self.have("keyword", "char") or self.have("keyword", "boolean"))
    
    def isOp(self):
        if(self.current().getType() != "symbol"):
            return False

        op = self.current().getValue()

        return (op == "+" or op == "-" or op == "*" or op == "/" or op == "&" or op == "|" or op == "<" or op == ">" or op == "=")

    def compileProgram(self):
        """
        Generates a parse tree for a single program
        @return a ParseTree that represents the program
        """
        return self.compileClass() 
    
    
    def compileClass(self):
        """
        Generates a parse tree for a single class
        @return a ParseTree that represents a class
        """
        pt = ParseTree("class", "Class")

        pt.addChild(self.mustBe("keyword", "class"))

        pt.addChild(self.mustBe("identifier", "MyClass"))

        pt.addChild(self.mustBe("symbol", "{"))

        while(self.have("keyword", "static") or self.have("keyword", "field")):
            pt.addChild(self.compileClassVarDec())

        while(self.have("keyword", "constructor") or self.have("keyword", "function") or self.have("keyword", "method")):
            pt.addChild(self.compileSubroutine())

        pt.addChild(self.mustBe("symbol", "}"))

        return pt

    def compileClassVarDec(self):
        """
        Generates a parse tree for a static variable declaration or field declaration
        @return a ParseTree that represents a static variable declaration or field declaration
        """

        pt = ParseTree("classVarDec", "ClassVarDec")

        pt.addChild(self.current())
        self.next()

        if(not self.isType()):
            raise ParseException("not type")

        pt.addChild(self.current())
        self.next()

        if(not self.current().getType() == "identifier"):
            raise ParseException("not identifier")

        pt.addChild(self.current())
        self.next()

        while(self.have("symbol", ",")):
            pt.addChild(self.current())
            self.isIdentifier()
            pt.addChild(self.current())
            self.next()

        pt.addChild(self.mustBe("symbol", ";"))

        return pt

    def compileSubroutine(self):
        """
        Generates a parse tree for a method, function, or constructor
        @return a ParseTree that represents the method, function, or constructor
        """

        pt = ParseTree("subroutine", "SubroutineDec")

        pt.addChild(self.current())
        self.next()

        if(self.have("keyword", "void") or self.isType()):
            pt.addChild(self.current())
            self.next()

        self.isIdentifier()

        pt.addChild(self.current())
        self.next()

        pt.addChild(self.mustBe("symbol", "("))

        pt.addChild(self.compileParameterList())

        pt.addChild(self.mustBe("symbol", ")"))

        pt.addChild(self.compileSubroutineBody())

        return pt
    
    def compileParameterList(self):
        """
        Generates a parse tree for a subroutine's parameters
        @return a ParseTree that represents a subroutine's parameters
        """

        if(not self.isType()):
            return None

        pt = ParseTree("parameterList", "ParameterList")
        pt.addChild(self.current())
        self.next()

        self.isIdentifier()
        pt.addChild(self.current())
        self.next()

        while(1):
            if(not self.have("symbol", ",")):
                return pt

            pt.addChild(self.mustBe("symbol", ","))

            if(not self.isType()):
                raise ParseException("not type")

            pt.addChild(self.current())
            self.next()

            self.isIdentifier()

            pt.addChild(self.current())
            self.next()
    
    def compileSubroutineBody(self):
        """
        Generates a parse tree for a subroutine's body
        @return a ParseTree that represents a subroutine's body
        """

        pt = ParseTree("subRoutineBody", "SubroutineBody")

        pt.addChild(self.mustBe("symbol", "{"))

        while(self.have("keyword", "var")):
            pt.addChild(self.compileVarDec())

        pt.addChild(self.current())
        self.next()

        pt.addChild(self.mustBe("symbol", "}"))

        return pt
    
    def compileVarDec(self):
        """
        Generates a parse tree for a variable declaration
        @return a ParseTree that represents a var declaration
        """

        pt = ParseTree("varDec", "VarDec")

        pt.addChild(self.mustBe("keyword", "var"))

        if(not self.isType()):
            raise ParseException("not type")
        
        pt.addChild(self.current())
        self.next()

        self.isIdentifier()
    
        pt.addChild(self.current())
        self.next()

        while(1):
            if(not self.have("symbol", ",")) :
                break
        
            pt.addChild(self.mustBe("symbol", ","))

            self.isIdentifier()
        
            pt.addChild(self.current())
            self.next()

        pt.addChild(self.mustBe("symbol", ";"))

        return pt

    def compileStatements(self):
        """
        Generates a parse tree for a series of statements
        @return a ParseTree that represents the series of statements
        """

        pt = ParseTree("statements", "Statements")

        if(self.have("keyword", "let")):
            pt.addChild(self.compileLet())
    
        elif(self.have("keyword", "if")):
            pt.addChild(self.compileIf())
    
        elif(self.have("keyword", "while")):
            pt.addChild(self.compileWhile())
    
        elif(self.have("keyword", "do")):
            pt.addChild(self.compileDo())
    
        elif(self.have("keyword", "return")):
            pt.addChild(self.compileReturn())
    
        else:
            raise ParseException("invalid statement")

        return pt
    
    def compileLet(self):
        """
        Generates a parse tree for a let statement
        @return a ParseTree that represents the statement
        """
        pt = ParseTree("letStatement", "Let")

        pt.addChild(self.mustBe("keyword", "let"))

        self.isIdentifier()
    
        pt.addChild(self.current())
        self.next()

        if(self.have("symbol", "[")):
            pt.addChild(self.mustBe("symbol", "["))
            pt.addChild(self.compileExpression())
            pt.addChild(self.mustBe("symbol", "]"))

        pt.addChild(self.mustBe("symbol", "="))

        pt.addChild(self.compileExpression())

        pt.addChild(self.mustBe("symbol", ";"))

        return pt

    def compileIf(self):
        """
        Generates a parse tree for an if statement
        @return a ParseTree that represents the statement
        """
        pt = ParseTree("ifStatement", "If")

        pt.addChild(self.mustBe("keyword", "if"))

        pt.addChild(self.mustBe("symbol", "("))

        pt.addChild(self.compileExpression())

        pt.addChild(self.mustBe("symbol", ")"))

        pt.addChild(self.mustBe("symbol", "{"))

        pt.addChild(self.compileStatements())

        pt.addChild(self.mustBe("symbol", "}"))

        if(self.have("keyword", "else")):
            pt.addChild(self.mustBe("keyword", "else"))

            pt.addChild(self.mustBe("symbol", "{"))

            pt.addChild(self.compileStatements())

            pt.addChild(self.mustBe("symbol", "}"))

        return pt
    
    def compileWhile(self):
        """
        Generates a parse tree for a while statement
        @return a ParseTree that represents the statement
        """

        pt = ParseTree("whileStatement", "While")

        pt.addChild(self.mustBe("keyword", "while"))

        pt.addChild(self.mustBe("symbol", "("))

        pt.addChild(self.compileExpression())

        pt.addChild(self.mustBe("symbol", ")"))

        pt.addChild(self.mustBe("symbol", "{"))

        pt.addChild(self.compileStatements())

        pt.addChild(self.mustBe("symbol", "}"))

        return pt

    def compileDo(self):
        """
        Generates a parse tree for a do statement
        @return a ParseTree that represents the statement
        """
        pt = ParseTree("doStatement", "Do")

        pt.addChild(self.mustBe("keyword", "do"))

        pt.addChild(self.mustBecompileExpression())

        pt.addChild(self.mustBeself.mustBe("keyword", ";"))

        return pt

    def compileReturn(self):
        """
        Generates a parse tree for a return statement
        @return a ParseTree that represents the statement
        """

        pt = ParseTree("returnStatement", "Return")

        pt.addChild(self.mustBe("keyword", "return"))

        if(self.have("symbol", ";")):
            pt.addChild(self.mustBe("symbol", ";"))
            return pt

        pt.addChild(self.compileExpression())

        pt.addChild(self.mustBe("symbol", ";"))

        return pt


    def compileExpression(self):
        """
        Generates a parse tree for an expression
        @return a ParseTree that represents the expression
        """
        pt = ParseTree("expression", "Expression")

        if(self.have("keyword", "skip")):
            pt.addChild(self.mustBe("keyword", "skip"))
            return pt

        pt.addChild(self.compileTerm())

        while(1):
            if(not self.isOp()):
                return pt

            pt.addChild(self.current())
            self.next()

            pt.addChild(self.compileTerm())

    def compileTerm(self):
        """
        Generates a parse tree for an expression term
        @return a ParseTree that represents the expression term
        """
        pt = ParseTree("term", "Term")

        type = self.current().getType()

        if(type == "integerConstant" or type == "stringConstant"):
            pt.addChild(self.current())
            return pt

        val = self.current().getValue()

        if(val == "true" or val == "false" or val == "null" or val == "this"):
            pt.addChild(self.current())
            return pt

        if(self.have("symbol", "(")):
            pt.addChild(self.mustBe("symbol", "("))

            pt.addChild(self.compileExpression())

            pt.addChild(self.mustBe("symbol", ")"))

            return pt

        if(self.isIdentifier()):
            temp = Token(self.current().getType(), self.current().getValue())
            self.next()

            if(self.have("symbol", "[")):
                pt.addChild(temp)

                pt.addChild(self.mustBe("symbol", "["))

                pt.addChild(self.compileExpression())

                pt.addChild(self.mustBe("symbol", "]"))

                return pt

            if(self.have("symbol", "(")):
                pt.addChild(temp)

                pt.addChild(self.mustBe("symbol", "("))

                pt.addChild(self.compileExpressionList())

                pt.addChild(self.mustBe("symbol", ")"))

                return pt

            if(self.have("symbol", ".")):
                pt.addChild(temp)

                pt.addChild(self.mustBe("symbol", "."))

                self.isIdentifier()
                pt.addChild(self.current())
                self.next()

                pt.addChild(self.mustBe("symbol", "("))

                pt.addChild(self.compileExpressionList())

                pt.addChild(self.mustBe("symbol", ")"))

                return pt

            pt.addChild(temp)
            return pt

        if(self.have("symbol", "-") or self.have("symbol", "~")):
            pt.addChild(self.current())
            self.next()

        return pt

    def compileExpressionList(self):
        """
        Generates a parse tree for an expression list
        @return a ParseTree that represents the expression list
        """
        pt = ParseTree("expressionList", "ExpressionList")

        if(self.have("symbol", ")")):
            return pt

        pt.addChild(self.compileExpression())

        while(1):
            if(not self.have("symbol", ",")):
                return pt

            pt.addChild(self.mustBe("symbol", ","))

            pt.addChild(self.compileExpression())


    def next(self):
        """
        Advance to the next token
        """
        self.tokens.pop(0)
        return


    def current(self):
        """
        Return the current token
        @return the token
        """
        return self.tokens[0]


    def have(self,expectedType,expectedValue):
        """
        Check if the current token matches the expected type and value.
        @return True if a match, False otherwise
        """

        return (self.tokens[0].getType() == expectedType and self.tokens[0].getValue() == expectedValue)


    def mustBe(self,expectedType,expectedValue):
        """
        Check if the current token matches the expected type and value.
        If so, advance to the next token, returning the current token, otherwise throw/raise a ParseException.
        @return token that was current prior to advancing.
        """

        if(self.have(expectedType, expectedValue)):
            return self.tokens.pop(0)
        else:
            raise ParseException("mustBe failed")

if __name__ == "__main__":


    """ 
    Tokens for:
        class MyClass {
        
        }
    """
    tokens = []
    tokens.append(Token("keyword","class"))
    tokens.append(Token("identifier","MyClass"))
    tokens.append(Token("symbol","{"))
    tokens.append(Token("symbol","}"))

    parser = CompilerParser(tokens)
    try:
        result = parser.compileProgram()
        print(result)
    except ParseException:
        print("Error Parsing!")
