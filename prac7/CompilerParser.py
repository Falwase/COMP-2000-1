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
        if(self.current().getType() == "identifier"):
            return True
        else:
            return False
        
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


        print(self.current())
        pt.addChild(self.mustBe("keyword", "class"))
        print(self.current())

        if(self.isIdentifier() == False):
            raise ParseException("Error Parsing! Not identifier")

        pt.addChild(self.mustBe("identifier", "MyClass"))

        print(self.current())

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
        return None 
    

    def compileSubroutine(self):
        """
        Generates a parse tree for a method, function, or constructor
        @return a ParseTree that represents the method, function, or constructor
        """
        return None 
    
    
    def compileParameterList(self):
        """
        Generates a parse tree for a subroutine's parameters
        @return a ParseTree that represents a subroutine's parameters
        """
        return None 
    
    
    def compileSubroutineBody(self):
        """
        Generates a parse tree for a subroutine's body
        @return a ParseTree that represents a subroutine's body
        """
        return None 
    
    
    def compileVarDec(self):
        """
        Generates a parse tree for a variable declaration
        @return a ParseTree that represents a var declaration
        """
        return None 
    

    def compileStatements(self):
        """
        Generates a parse tree for a series of statements
        @return a ParseTree that represents the series of statements
        """
        return None 
    
    
    def compileLet(self):
        """
        Generates a parse tree for a let statement
        @return a ParseTree that represents the statement
        """
        return None 


    def compileIf(self):
        """
        Generates a parse tree for an if statement
        @return a ParseTree that represents the statement
        """
        return None 

    
    def compileWhile(self):
        """
        Generates a parse tree for a while statement
        @return a ParseTree that represents the statement
        """
        return None 


    def compileDo(self):
        """
        Generates a parse tree for a do statement
        @return a ParseTree that represents the statement
        """
        return None 


    def compileReturn(self):
        """
        Generates a parse tree for a return statement
        @return a ParseTree that represents the statement
        """
        return None 


    def compileExpression(self):
        """
        Generates a parse tree for an expression
        @return a ParseTree that represents the expression
        """
        return None 


    def compileTerm(self):
        """
        Generates a parse tree for an expression term
        @return a ParseTree that represents the expression term
        """
        return None 


    def compileExpressionList(self):
        """
        Generates a parse tree for an expression list
        @return a ParseTree that represents the expression list
        """
        return None 


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
