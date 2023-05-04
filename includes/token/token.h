#ifndef token_h
#define token_h

#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/node/node.h"

#include <string>
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

class Token
{
public:
    //enum for token type
    enum tokentype
    {
        UNKNOWN,    // 0
        INTEGER,    // 1
        OPERATOR,   // 2
        LEFTPAREN,  // 3
        RIGHTPAREN, // 4
    };
    // I know what my type is, I know what my face looks like.
    Token(const string &s = "?", int type = 0) : _token(s), _type(type)
    {
    }
    //print function
    virtual void print()
    {
        cout << _token << endl;
    }
    //return type of token
    virtual int type()
    {
        return _type;
    }
    //returns token as string
    string token()
    {
        return _token;
    }
    //evalulation functions
    virtual Token *eval(Token *left, Token *right)
    {
    }
    virtual Token *trigeval(Token *arg)
    {
    }
    virtual Token *logsqrteval(Token *arg)
    {
    }
    virtual Token *abseval(Token *arg)
    {
    }
    virtual int get_prec(const string &op)
    {
    }
    virtual int getprecval()
    {
    }
    //change type of token
    void changetype(int i)
    {
        _type = i;
    }
    //overload << operator
    friend ostream &operator<<(ostream &outs, const Token &t)
    {
        outs << t._token << " ";
        return outs;
    }

    // friend ostream& operator <<(ostream& outs)
    // {

    //     return outs;
    // }

private:
    int _type;
    string _token;
};
//integer class
class Integer : public Token
{
public:
    // integer type is 1: these are enums!
    Integer(double i = 0) : Token(to_string(i), 1), _value(i)
    {
    }
    Integer(const string &n = "0.0") : Token(n, 1), _value(stod(n))
    {
        // or stod
    }
    void int_only()
    {
        cout << "hello from integer!";
    }

private:
    double _value;
};
//operator class
class Operator : public Token
{
public:
    // integer type is 1: these are enums!
    Operator()
    {
    }
    Operator(const string &op) : Token(op, 2)
    {
        // or stod
        _prec = get_prec(op);
    }
    //get precedence of operator
    int get_prec(const string &op)
    {
        if (token() == "+")
        {
            return 0;
        }
        else if (token() == "-")
        {
            return 0;
        }
        else if (token() == "*")
        {
            return 1;
        }
        else if (token() == "/")
        {
            return 1;
        }
        else if (token() == "^")
        {
            return 2;
        }
        else if (token() == "x")
        {
            return 3;
        }
        else if (token() == "sin")
        {
            return 4;
        }
        else if (token() == "cos")
        {
            return 4;
        }
        else if (token() == "tan")
        {
            return 4;
        }
        else if (token() == "csc")
        {
            return 4;
        }
        else if (token() == "sec")
        {
            return 4;
        }
        else if (token() == "cot")
        {
            return 4;
        }
        else if (token() == "arcsin")
        {
            return 4;
        }
        else if (token() == "arccos")
        {
            return 4;
        }
        else if (token() == "arctan")
        {
            return 4;
        }
        else if (token() == "sinh")
        {
            return 4;
        }
        else if (token() == "cosh")
        {
            return 4;
        }
        else if (token() == "tanh")
        {
            return 4;
        }
        else if (token() == "csch")
        {
            return 4;
        }
        else if (token() == "sech")
        {
            return 4;
        }
        else if (token() == "coth")
        {
            return 4;
        }
        else if (token() == "ln")
        {
            return 5;
        }
        else if (token() == "log")
        {
            return 5;
        }
        else if (token() == "sqrt")
        {
            return 5;
        }
        else if (token() == "abs")
        {
            return 6;
        }
        return -1;
    }
    //evaluation function for normal operators and numbers
    Token *eval(Token *left, Token *right)
    {
        double dleft = stod(left->token());
        double dright = stod(right->token());
        double ans;

        switch (token()[0])
        {
        case '+':
            ans = dleft + dright;
            break;
        case '-':
            ans = dleft - dright;
            break;
        case '*':
            ans = dleft * dright;
            break;
        case '/':
            ans = dleft / dright;
            break;
        case '^':
            if (dleft == 0 || dright == 0)
            {
                break;
            }
            ans = pow(dleft, dright);
            break;
        }
        if (dleft == 0 || dright == 0)
        {
            Token *tokenptr = new Integer(-10000);
            return tokenptr;
        }
        Token *tokenptr = new Integer(ans);
        return tokenptr;
    }
    //trig evaluation function
    Token *trigeval(Token *arg)
    {
        double darg = stod(arg->token());
        double ans;

        if (token() == "sin")
        {
            ans = sin(darg);
        }
        else if (token() == "cos")
        {
            ans = cos(darg);
        }
        else if (token() == "tan")
        {
            ans = tan(darg);
        }
        else if (token() == "csc")
        {
            ans = 1 / sin(darg);
        }
        else if (token() == "sec")
        {
            ans = 1 / cos(darg);
        }
        else if (token() == "cot")
        {
            ans = 1 / tan(darg);
        }
        else if (token() == "arcsin")
        {
            if (darg >= 1 || darg <= -1)
            {
                Token *tokenptr = new Integer(-100000);
                return tokenptr;
            }
            ans = asin(darg);
        }
        else if (token() == "arccos")
        {
            if (darg >= 1 || darg <= -1)
            {
                Token *tokenptr = new Integer(-100000);
                return tokenptr;
            }
            ans = acos(darg);
        }
        else if (token() == "arctan")
        {
            ans = atan(darg);
        }
        else if (token() == "sinh")
        {
            ans = sinh(darg);
        }
        else if(token() == "cosh")
        {
            ans = cosh(darg);
        }
        else if(token() == "tanh")
        {
            ans = tanh(darg);
        }
        else if(token() == "csch")
        {
            ans = 1/sinh(darg);
        }
        else if(token() == "sech")
        {
            ans = 1/cosh(darg);
        }
        else if(token() == "coth")
        {
            ans = 1/tanh(darg);
        }
        Token *tokenptr = new Integer(ans);
        return tokenptr;
    }
    //log and sqrt evaluation function
    Token *logsqrteval(Token *arg)
    {
        double darg = stod(arg->token());
        double ans;

        if (darg <= 0)
        {
            Token *tokenptr = new Integer(-100000);
            return tokenptr;
        }
        if (token() == "ln")
        {
            ans = log(darg);
        }
        else if (token() == "log")
        {
            ans = log10(darg);
        }
        else if (token() == "sqrt")
        {
            ans = sqrt(darg);
        }
        Token *tokenptr = new Integer(ans);
        return tokenptr;
    }
    //abs evaluation function
    Token *abseval(Token *arg)
    {
        double darg = stod(arg->token());
        double ans;

        if (token() == "abs")
        {
            ans = abs(darg);
        }

        Token *tokenptr = new Integer(ans);
        return tokenptr;
    }
    //returns int precedence value
    int getprecval()
    {
        return _prec;
    }

private:
    int _prec;
};

//function class
class Function : public Operator
{
public:
    Function(const string &op) : Operator(op)
    {
    }

private:
};

//leftparen class
class LeftParen : public Token
{
public:
    LeftParen() : Token("(", 3)
    {
    }

private:
};
//rightparen class
class RightParen : public Token
{
public:
    RightParen() : Token(")", 4)
    {
    }

private:
};

class Tokenize : public Token
{
public:
    //tokenize function
    static Queue<Token *> tokenizeinput(const string &input)
    {
        Queue<Token *> tokenqueue;

        string s = "";
        for (int i = 0; i < input.size(); i++)
        {
            char c = input[i];
            if (isdigit(c) || isalpha(c))
            {
                s += c;
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')')
            {
                if (s != "")
                {
                    //if number push as integer
                    if (isdigit(s[0]))
                    {
                        tokenqueue.push(new Integer(s));
                    }
                    //if letter push as function (prec functions later will take care of them)
                    else if (isalpha(s[0]))
                    {
                        tokenqueue.push(new Function(s));
                    }
                    s = "";
                }
                //switch for normal operators + x
                switch (c)
                {
                case '+':
                    tokenqueue.push(new Operator("+"));
                    break;
                case '-':
                    tokenqueue.push(new Operator("-"));
                    break;
                case '*':
                    tokenqueue.push(new Operator("*"));
                    break;
                case '/':
                    tokenqueue.push(new Operator("/"));
                    break;
                case '^':
                    tokenqueue.push(new Operator("^"));
                    break;
                case 'X':
                    tokenqueue.push(new Operator("X"));
                    break;
                case '(':
                    tokenqueue.push(new LeftParen());
                    break;
                case ')':
                    tokenqueue.push(new RightParen());
                    break;
                }
            }
        }

        //push the last token if it exists
        if (s != "")
        {
            if (isdigit(s[0]))
            {
                tokenqueue.push(new Integer(s));
            }
            else if (isalpha(s[0]))
            {
                tokenqueue.push(new Function(s));
            }
        }

        return tokenqueue;
    }

private:
};


/*

    3 + 8  ---->[Shunting Yard ]---> 3 8 +  ------> [RPN] ------->11





*/

#endif