#include "linkedStack.h"
#include "arrayStack.h"
#include <iostream>
#include <string>

std::string parseInfix(std::string);

int order(char);

float evaluatePost(std::string);

int main() {
    std::string input;
    std::string postfix;
    std::cout<<"Please enter expression (NO SPACES) or enter DEFAULT to use (5+6)*(4/3)."<<std::endl;
    std::getline(std::cin, input);
    if(input == "DEFAULT"){
        postfix = parseInfix("(5+6)*(4/3)");
    } else {
        postfix = parseInfix(input);
    }
    std::cout<<postfix<<std::endl;
    std::cout<<evaluatePost(postfix)<<std::endl;
}

std::string parseInfix(std::string input){
    std::string post;
    linkedStack<char> chars;
    for(int i = 0; i < input.length(); i++){
        char cur = input[i];
        if(std::isdigit(cur)){
            post.push_back(cur);
        } else if (cur == '('){
            chars.push(cur);
        } else if (cur == ')'){
            while(!chars.isEmpty() && chars.peek() != '('){
                post.push_back(chars.peek());
                chars.pop();
            }
            chars.pop();
        } else {
            while(!chars.isEmpty() && (order(chars.peek()) >= order(cur))){
                post.push_back(chars.peek());
                chars.pop();
            }
            chars.push(cur);
        }
    }
    while(!chars.isEmpty()){
        post.push_back(chars.peek());
        chars.pop();
    }
    return post;
}

int order(char c){
    int o = 0;
    if(c == '+' || c == '-'){
        o = 1;
    } else if (c == '*' || c == '/'){
        o = 2;
    } else if (c == '^'){
        o = 3;
    }
    return o;
}

float evaluatePost(std::string post){
    linkedStack<float> numbers;
    float num1;
    float num2;
    for(int i = 0; i < post.length(); i++){
        char cur = post[i];
        if(std::isdigit(cur)){
            numbers.push(cur - '0');
        } else {
            num2 = numbers.peek();
            numbers.pop();
            num1 = numbers.peek();
            numbers.pop();
            //std::cout<<"NUM1: "<<num1<<std::endl;
            //std::cout<<"NUM2: "<<num2<<std::endl;
            //std::cout<<"OPERATOR: "<<cur<<std::endl;
            switch(cur){
                case('+'):
                    numbers.push(num1 + num2);
                    //std::cout<<"RESULT: "<<numbers.peek()<<std::endl;
                    break;
                case('-'):
                    numbers.push(num1 - num2);
                    //std::cout<<"RESULT: "<<numbers.peek()<<std::endl;
                    break;
                case('*'):
                    numbers.push(num1 * num2);
                    //std::cout<<"RESULT: "<<numbers.peek()<<std::endl;
                    break;
                case('/'):
                    numbers.push(num1 / num2);
                    //std::cout<<"RESULT: "<<numbers.peek()<<std::endl;
                    break;
                default:
                    //std::cout<<"something's wrong!"<<std::endl;
                    break;
            }
        }
    }
    return numbers.peek();
}