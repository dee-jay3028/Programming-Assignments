#include "number.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

//Driver File
// Contains all the logic to parse a file of input OPCODE, complete with handling for both immediate and register inputs. Input filename is hardcoded, so be sure to make any changes
// in the same input.txt file or another file of the same name. 

Number movNum(Number&);
Number addNums(Number&, Number&);
Number andNums(Number&, Number&);
//void arithRight(Number&, Number&);
Number logRight(Number&, Number&);
Number logLeft(Number&, Number&);
//Number& bitNot(Number&);
Number bitOrr(Number&, Number&);
Number subNums(Number&, Number&);
Number excluOr(Number&, Number&);

int main(){
    bool N = 0;
    bool Z = 0;
    bool C = 0;
    bool V = 0;
    bool affectsFlags = false;
    Number r0, r1, r2, r3, r4, r5, r6, r7;
    std::ifstream inputFile("input.txt");
    if(inputFile.is_open()){
        std::string inputLine;
        while(std::getline(inputFile, inputLine)){
            std::transform(inputLine.begin(), inputLine.end(), inputLine.begin(), ::toupper);
            std::cout<<inputLine<<std::endl;
            //std::cout<<inputLine<<std::endl;
            std::string operation;
            operation = inputLine.substr(0, inputLine.find_first_of(' '));
            if(operation.back() == 'S'){
                affectsFlags = true;
            } else {
                affectsFlags = false;
            }
            inputLine = inputLine.substr(inputLine.find_first_of(' '));
            inputLine = inputLine.substr(inputLine.find_first_of('R')+1);
            std::string reg1 = inputLine.substr(0, 1);
            //std::cout<<"REG1 VALUE: "<<reg1<<std::endl;
            inputLine = inputLine.substr(2);
            int regNum = std::stoi(reg1);
            Number* destinationReg;
            switch (regNum) {
                case 0: 
                    destinationReg = &r0;
                    break;
                case 1: 
                    destinationReg = &r1;
                    break;
                case 2: 
                    destinationReg = &r2;
                    break;
                case 3: 
                    destinationReg = &r3;
                    break;
                case 4: 
                    destinationReg = &r4;
                    break;
                case 5:
                    destinationReg = &r5;
                    break;
                case 6:
                    destinationReg = &r6;
                    break;
                case 7: 
                    destinationReg = &r7;
                    break;
                default:
                    std::cout<<"Something went wrong!"<<std::endl;
                    return 1;
            }
            //std::cout<<"PAST SWITCH 1"<<std::endl;
            inputLine = inputLine.substr(1);
            //std::cout<<"CURRENT INPUTLINE:"<<inputLine<<std::endl;
            Number* num1;
            bool twoOps = false;
            if(inputLine.front() == 'R'){
                inputLine = inputLine.substr(1);
                std::string reg2 = inputLine.substr(0, 1);
                //std::cout<<"REG2 VALUE: "<<reg2<<std::endl;
                int temp = std::stoi(reg2);
                switch (temp) {
                case 0: 
                    num1 = &r0;
                    break;
                case 1: 
                    num1 = &r1;
                    break;
                case 2: 
                    num1 = &r2;
                    break;
                case 3: 
                    num1 = &r3;
                    break;
                case 4: 
                    num1 = &r4;
                    break;
                case 5:
                    num1 = &r5;
                    break;
                case 6:
                    num1 = &r6;
                    break;
                case 7: 
                    num1 = &r7;
                    break;
                default:
                    std::cout<<"Something went wrong!"<<std::endl;
                    return 1;
                }
            } else if (inputLine.front() == '#'){
                //std::cout<<"HASHTAG DETECTED"<<std::endl;
                twoOps = true;
                inputLine = inputLine.substr(3);
                //std::cout<<"INPUT LINE BEING PASSED AS HEX:"<<inputLine<<std::endl;
                num1 = new Number(inputLine);
            }
            Number* num2;
            //std::cout<<"NUM2 PORTION REACHED"<<std::endl;
            if(!twoOps){
                inputLine = inputLine.substr(inputLine.find_first_of(' ')+1);
                if(inputLine.front() == 'R'){
                    inputLine = inputLine.substr(1);
                    std::string reg3 = inputLine.substr(0, 1);
                    //std::cout<<"REG3 VALUE: "<<reg3<<std::endl;
                    int temp2 = std::stoi(reg3);
                    switch (temp2) {
                    case 0: 
                        num2 = &r0;
                        break;
                    case 1: 
                        num2 = &r1;
                        break;
                    case 2: 
                        num2 = &r2;
                        break;
                    case 3: 
                        num2 = &r3;
                        break;
                    case 4: 
                        num2 = &r4;
                        break;
                    case 5:
                        num2 = &r5;
                        break;
                    case 6:
                        num2 = &r6;
                        break;
                    case 7: 
                        num2 = &r7;
                        break;
                    default:
                        std::cout<<"Something went wrong!"<<std::endl;
                        return 1;
                    }
                } else if (inputLine.front() == '#'){
                    inputLine = inputLine.substr(1);
                    std::string newHex = inputLine.substr(0, inputLine.find_first_of(' '));
                    num2 = new Number(newHex);
                }
            }
            //std::cout<<number2<<std::endl;
            /*std::cout<<num1.getHexNum()<<std::endl;
            std::cout<<num1.getBinNum()<<std::endl;
            std::cout<<num1.getDecNum()<<std::endl;*/
            /*std::cout<<num2.getHexNum()<<std::endl;
            std::cout<<num2.getBinNum()<<std::endl;
            std::cout<<num2.getDecNum()<<std::endl;*/
            if(operation == "ADD" || operation == "ADDS"){
                *destinationReg = addNums(*num1, *num2);
            } else if (operation == "AND" || operation == "ANDS"){
                *destinationReg = andNums(*num1, *num2);
            } else if (operation == "ASR" || operation == "ASRS"){
                //*destinationReg = arithRight(num1, num2);
            } else if (operation == "LSR" || operation == "LSRS"){
                *destinationReg = logRight(*num1, *num2);
            } else if (operation == "LSL" || operation == "LSLS"){
                *destinationReg = logLeft(*num1, *num2);
            } else if (operation == "NOT" || operation == "NOTS"){
                //bitNot(*num1);
            } else if (operation == "ORR" || operation == "ORRS"){
                *destinationReg = bitOrr(*num1, *num2);
            } else if (operation == "SUB" || operation == "SUBS"){
                *destinationReg = subNums(*num1, *num2);
            } else if (operation == "XOR" || operation == "XORS"){
                *destinationReg = excluOr(*num1, *num2);
            } else if (operation == "MOV" || operation == "MOVS"){
                *destinationReg = movNum(*num1);
            }
            if(affectsFlags){
                if(destinationReg->getBinNum().front() == '1'){
                    N = true;
                } else {
                    N = false;
                }
                if(destinationReg->getDecNum() == 0){
                    Z = true;
                } else {
                    Z = false;
                }
                if(operation == "SUB" || operation == "SUBS"){
                    if(N || num2->getDecNum() < num1->getDecNum()){
                        C = true;
                    }
                    if(num1->getBinNum().front() != num2->getBinNum().front() && destinationReg->getBinNum().front() != num1->getBinNum().front()){
                        V = true;
                    }
                } else if (operation == "ADD" || operation == "ADDS"){
                    if(destinationReg->getDecNum() < num1->getDecNum() || destinationReg->getDecNum() < num2->getDecNum()){
                        C = true;
                    }
                    if(destinationReg->getBinNum().front() == '1' && num1->getBinNum().front() == '0' && num2->getBinNum().front() == '0'){
                        V = true;
                    }
                }
            }
            std::cout<<"R0:0x"<<r0.getHexNum()<<" R1:0x"<<r1.getHexNum()<<" R2:0x"<<r2.getHexNum()<<" R3:0x"<<r3.getHexNum()<<std::endl;
            std::cout<<"R4:0x"<<r4.getHexNum()<<" R5:0x"<<r5.getHexNum()<<" R6:0x"<<r6.getHexNum()<<" R7:0x"<<r7.getHexNum()<<std::endl;
            std::cout<<"N = "<<N<<" Z = "<<Z<<" C = "<<C<<" V = "<<V<<std::endl<<std::endl;
        }
    } else {
        std::cout<<"File error!"<<std::endl;
    }
    return 0;
}

Number movNum(Number& num1){
    Number result;
    result.setNewHex(num1.getHexNum());
    return result;
}

Number addNums(Number& num1, Number& num2){
    //std::cout<<"NUM1: "<<num1.getHexNum()<<std::endl;
    //std::cout<<"NUM2: "<<num2.getHexNum()<<std::endl;
    std::stringstream conv;
    bool overflow = num1.getDecNum()+num2.getDecNum() == 0;
    if(overflow){
        uint64_t realSum = 0;
        realSum += num1.getDecNum();
        realSum += num2.getDecNum();
        conv << std::hex << realSum;
        std::string hexResult = conv.str();
        hexResult = hexResult.substr(hexResult.length()-8, hexResult.length());
        Number result(hexResult);
        return result;
        //std::cout<<"0x"<<hexResult<<std::endl;
        //std::cout<<"REAL NUM: "<<realSum<<std::endl;
        //std::cout<<"Overflow: Yes"<<std::endl;
        //std::cout<<std::endl;
    } else {
        //std::cout<<"ADD ELSE BLOCK TRIGGERED"<<std::endl;
        uint32_t sum = num1.getDecNum() + num2.getDecNum();
        //std::cout<<sum<<std::endl;
        conv << std::hex << sum;
        std::string hexResult = conv.str();
        //hexResult = hexResult.substr(hexResult.length()-8, hexResult.length());
        Number result(hexResult);
        return result;
        //std::string hexResult = conv.str();
        //std::cout<<"0x"<<hexResult<<std::endl;
        //std::cout<<"Overflow: No"<<std::endl;
        //std::cout<<std::endl;
    }
}

Number andNums(Number& num1, Number& num2){
    uint32_t result = num1.getDecNum() & num2.getDecNum();
    std::stringstream conv;
    conv << std::hex << result;
    std::string hexResult = conv.str();
    Number resultHex(hexResult);
    return resultHex;
    //std::cout<<"0x"<<hexResult<<std::endl<<std::endl;
}

/*
void arithRight(Number& num1, Number& num2){
    int new1 = num1.getDecNum();
    int new2 = num2.getDecNum();
    int result = new1 >> new2;
    std::stringstream conv;
    conv << std::hex << result;
    std::string hexResult = conv.str();
    std::cout<<"0x"<<hexResult<<std::endl<<std::endl;
}
*/

Number logRight(Number& num1, Number& num2){
    uint32_t result = num1.getDecNum() >> num2.getDecNum();
    std::stringstream conv;
    conv << std::hex << result;
    std::string hexResult = conv.str();
    Number output(hexResult);
    return output;
    //std::cout<<"0x"<<hexResult<<std::endl<<std::endl;
}

Number logLeft(Number& num1, Number& num2){
    uint32_t result = num1.getDecNum() << num2.getDecNum();
    std::stringstream conv;
    conv << std::hex << result;
    std::string hexResult = conv.str();
    Number output(hexResult);
    return output;
    //std::cout<<"0x"<<hexResult<<std::endl<<std::endl;
}

/*void bitNot(Number& num1){
    uint32_t result = ~ num1.getDecNum();
    std::stringstream conv;
    conv << std::hex << result;
    std::string hexResult = conv.str();
    std::cout<<"0x"<<hexResult<<std::endl<<std::endl;
}*/

Number bitOrr(Number& num1, Number& num2){
    uint32_t result = num1.getDecNum() | num2.getDecNum();
    std::stringstream conv;
    conv << std::hex << result;
    std::string hexResult = conv.str();
    Number output(hexResult);
    return output;
    //std::cout<<"0x"<<hexResult<<std::endl<<std::endl;
}

Number subNums(Number& num1, Number& num2){
    int new1 = num1.getDecNum();
    int new2 = num2.getDecNum();
    int result = new1 - new2;
    std::stringstream conv;
    conv << std::hex << result;
    std::string hexResult = conv.str();
    Number output(hexResult);
    return output;
    //std::cout<<"0x"<<hexResult<<std::endl<<std::endl;
}

Number excluOr(Number& num1, Number& num2){
    uint32_t result = num1.getDecNum() ^ num2.getDecNum();
    std::stringstream conv;
    conv << std::hex << result;
    std::string hexResult = conv.str();
    Number output(hexResult);
    return output;
    //std::cout<<"0x"<<hexResult<<std::endl<<std::endl;
}