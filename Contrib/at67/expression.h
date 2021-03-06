#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>
#include <functional>


namespace Expression
{
    enum ExpressionType {IsInvalid=0x8000, HasNumbers=0x0000, HasStrings=0x0001, HasStrConsts=0x0002, HasStrVars=0x0004, HasStringKeywords=0x0008, IsStringExpression=0x000F,
                         HasOperators=0x0010, HasIntConsts=0x0020, HasIntVars=0x0040, HasKeywords=0x0080, HasFunctions=0x0100, HasOptimisedPrint=0x0200};
    enum NumericType {BadBase=-1, Decimal, HexaDecimal, Octal, Binary};
    enum CCType {BooleanCC, NormalCC, FastCC};
    enum Int16Byte {Int16Both, Int16Low, Int16High};
    enum VarType {Number, String, Constant, TmpVar, IntVar, ArrVar, StrVar, TmpStrVar};

    struct Numeric
    {
        Numeric()
        {
            _value = 0.0; _index = -1; _isValid = false; _varType = Number; _ccType = BooleanCC; _int16Byte = Int16Both; _name = ""; _text = "";
        }

        Numeric(double value, int16_t index, bool isValid, VarType varType, CCType ccType, Int16Byte int16Byte, const std::string& name, const std::string& text)
        {
            _value = value; _index = index; _isValid = isValid; _varType = varType; _ccType = ccType; _int16Byte = int16Byte; _name = name; _text = text;
        }

        double _value = 0.0;
        int16_t _index = -1;
        bool _isValid = false;
        VarType _varType = Number;
        CCType _ccType = BooleanCC;
        Int16Byte _int16Byte = Int16Both;
        std::string _name;
        std::string _text;
        std::vector<Numeric> _parameters;
    };

    using exprFuncPtr = std::function<Numeric (void)>;

    bool getEnableOptimisedPrint(void);
    Numeric& getOutputNumeric(void);

    void setExprFunc(exprFuncPtr exprFunc);
    void setEnableOptimisedPrint(bool enableOptimisedPrint);

    void initialise(void);

    ExpressionType isExpression(const std::string& input);
    bool isVarNameValid(const std::string& varName);
    bool isValidString(const std::string& input);

    bool hasNonStringWhiteSpace(int chr);
    bool hasNonStringEquals(int chr);
    bool hasNonStringColon(int chr);

    std::string::const_iterator findNonStringEquals(const std::string& input);
    std::string::const_iterator findNonStringColon(const std::string& input);
    void stripNonStringWhitespace(std::string& input);
    void stripWhitespace(std::string& input);
    std::string stripStrings(const std::string& input);
    void trimWhitespace(std::string& input);
    std::string collapseWhitespace(const std::string& input);
    std::string collapseWhitespaceNotStrings(const std::string& input);
    std::string removeCommentsNotInStrings(const std::string& input);
    void padString(std::string &str, int num, char pad=' ');
    void addString(std::string &str, int num, char add=' ');
    int tabbedStringLength(const std::string& input, int tabSize);
    void operatorReduction(std::string& input);
    bool findMatchingBrackets(const std::string& input, size_t start, size_t& lbra, size_t& rbra);

    std::string byteToHexString(uint8_t n);
    std::string wordToHexString(uint16_t n);
    std::string& strToLower(std::string& s);
    std::string& strToUpper(std::string& s);
    std::string getSubAlpha(const std::string& s);

    NumericType getBase(const std::string& input, long& result);
    bool stringToI8(const std::string& token, int8_t& result);
    bool stringToU8(const std::string& token, uint8_t& result);
    bool stringToI16(const std::string& token, int16_t& result);
    bool stringToU16(const std::string& token, uint16_t& result);
    void stringToDouble(const std::string& token, double& result);

    std::vector<std::string> tokenise(const std::string& text, const std::string& delimiters, bool toUpper=false);
    std::vector<std::string> tokenise(const std::string& text, char c, bool skipSpaces=true, bool toUpper=false);
    std::vector<std::string> tokenise(const std::string& text, char c, std::vector<size_t>& offsets, bool skipSpaces=true, bool toUpper=false);
    std::vector<std::string> tokeniseLine(const std::string& line, const std::string& delimiters=" \n\r\f\t\v");
    std::vector<std::string> tokeniseLine(const std::string& line, const std::string& delimiters, std::vector<size_t>& offsets);

    void replaceText(std::string& expression, const std::string& text, const std::string& replace);

    char* getExpression(void);
    const char* getExpressionToParse(void);
    std::string& getExpressionToParseString(void);
    int getLineNumber(void);

    void setExpression(const std::string& expression);

    char peek(void);
    char get(void);
    void save(void);
    void restore(void);
    bool advance(uintptr_t n);

    bool find(const std::string& text);

    bool number(int16_t& value);
    Numeric expression(void);
    bool parse(const std::string& expression, int lineNumber, Numeric& numeric);
}

#endif
