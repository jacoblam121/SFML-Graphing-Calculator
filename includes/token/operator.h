// #ifndef operator_h
// #define operator_h

// #include "token.h"
// #include <string>
// #include <cmath>

// using namespace std;

// class Operator:public Token{
//     public:
//     //integer type is 1: these are enums!
//         Operator(const string& op):Token(op, 2)
//         {
//             //or stod
//             _prec = get_prec(op);
//         }
//         int get_prec(const string& op){
//             switch( token()[0])
//             {
//                 case '+':
//                     return 0;
//                     break;
//                 case '-':
//                     return 1;
//                     break;
//                 case '/':
//                     return 2;
//                     break;
//                 case '*':
//                     return 3;
//                     break;
//                 case '^':
//                     return 4;
//                     break;
//                 case '(':
//                     return 5;
//                     break;
//                 case ')':
//                     return 6;
//                     break;
//                 default:
//                     return -1;
//                     break;
//             }

//             return -1;
//         }

//         Token* eval(Token* left, Token* right)
//         {
//             Integer* tokenptr;
            
//             double dleft = stod(left->token());
//             double dright = stod(right->token());
//             double ans;

//             switch(_prec)
//             {
//                 case 0:
//                     ans = dleft + dright;
//                     *tokenptr = to_string(ans);
//                     break;
//                 case 1:
//                     ans = dleft - dright; 
//                     *tokenptr = to_string(ans);
//                     break;
//                 case 2:
//                     ans = dleft * dright;
//                     *tokenptr = to_string(ans);
//                     break;
//                 case 3:
//                     ans = dleft / dright;
//                     *tokenptr = to_string(ans);
//                     break;
//                 case 4:
//                     ans = pow(dleft, dright);
//                     *tokenptr = to_string(ans);
//             }
//             return tokenptr;
//         }
//     private:
//         int _prec;
// };

// #endif