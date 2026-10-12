// Steps: (for each machine code file (.obj))
//  1. Provided hex number
//  2. Convert from hex to binary form
//  3. Parse last 7 digits to get opcode
//  4. Use opcode to determine instruction type
//  5. Depending on instruction type, parse other bits to get other info (use separate functions for each instruction type)
// 6. Create new .s file in assembly output folder

#include "disassembler.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// global variables
//  get number of lines in the file
int numLines = 0;
// create vector to store each line
std::vector<std::string> machineCodeVec;
// type of instruction (R, I, S, B, U, J)
std::string type = "";

int main()
{
    readFile();
    hexToBin();
    getOpcode();
    getInstructionType();
    return 0;
}
// go through .obj file and parse line by line to put values in an array of strings
void readFile()
{
    std::ifstream file("machine_code.obj"); // open file
    std::string line;
    // to store each line in an array of strings
    while (std::getline(file, line))
    {
        machineCodeVec.push_back(line); // store each line in the vector
        numLines++;                     // update number of lines
    }
}

std::string hexToBin()
{
    // get hex line from vector as a string
    std::string sampleHex = machineCodeVec[0];
    int hexLength = sampleHex.length(); // get length of hex number
    std::string binNum = "";
    if (hexLength == 8)
    {

        for (int i = 0; i < hexLength; i++)
        {
            if (sampleHex[i] == '0')
            {
                binNum += "0000";
            }
            else if (sampleHex[i] == '1')
            {
                binNum += "0001";
            }
            else if (sampleHex[i] == '2')
            {
                binNum += "0010";
            }
            else if (sampleHex[i] == '3')
            {
                binNum += "0011";
            }
            else if (sampleHex[i] == '4')
            {
                binNum += "0100";
            }
            else if (sampleHex[i] == '5')
            {
                binNum += "0101";
            }
            else if (sampleHex[i] == '6')
            {
                binNum += "0110";
            }
            else if (sampleHex[i] == '7')
            {
                binNum += "0111";
            }
            else if (sampleHex[i] == '8')
            {
                binNum += "1000";
            }
            else if (sampleHex[i] == '9')
            {
                binNum += "1001";
            }
            else if (sampleHex[i] == 'A' || sampleHex[i] == 'a')
            {
                binNum += "1010";
            }
            else if (sampleHex[i] == 'B' || sampleHex[i] == 'b')
            {
                binNum += "1011";
            }
            else if (sampleHex[i] == 'C' || sampleHex[i] == 'c')
            {
                binNum += "1100";
            }
            else if (sampleHex[i] == 'D' || sampleHex[i] == 'd')
            {
                binNum += "1101";
            }
            else if (sampleHex[i] == 'E' || sampleHex[i] == 'e')
            {
                binNum += "1110";
            }
            else if (sampleHex[i] == 'F' || sampleHex[i] == 'f')
            {
                binNum += "1111";
            }
            // invalid hex number
            else
            {
                std::cout << "Invalid hex number: ";
            }
        }
    }
    else
    {
        std::cout << "Invalid hex number length.";
    }
    return binNum;
}

std::string getOpcode()
{
    std::string binNum = hexToBin();
    // get last 7 digits of binary number for opcode
    std::string opcode = binNum.substr(binNum.length() - 7);
    return opcode;
}

void getInstructionType()
{
    std::string opcode = getOpcode();
    if (opcode == "0110011")
    {
        dissassembleRType();
        type = "R";
    }
    else if (opcode == "0010011")
    {
        dissassembleIType1();
        type = "I";
    }
    else if (opcode == "0000011")
    {
        dissassembleIType2();
        type = "I";
    }
    else if (opcode == "0100011")
    {
        dissassembleSType();
        type = "S";
    }
    else if (opcode == "1100011")
    {
        //dissassembleBType();
        type = "B";
    }
    else if (opcode == "1101111")
    {
        //dissassembleJType();
        type = "J";
    }
    else if (opcode == "1100111")
    {
        dissassembleIType3();
        type = "I";
    }
    else if (opcode == "0110111")
    {
        //dissassembleUType1(); // lui
        type = "U";
    }
    else if (opcode == "0010111")
    {
        //dissassembleUType2(); // auipc
        type = "U";
    }
    else
    {
        std::cout << "Invalid opcode.";
    }
}

// convert binary bits of registers to register names (x0-x31)
std::string convertBinToRegName(std::string regBinaryBits)
{
    if (regBinaryBits == "00000")
        return "x0";
    else if (regBinaryBits == "00001")
        return "x1";
    else if (regBinaryBits == "00010")
        return "x2";
    else if (regBinaryBits == "00011")
        return "x3";
    else if (regBinaryBits == "00100")
        return "x4";
    else if (regBinaryBits == "00101")
        return "x5";
    else if (regBinaryBits == "00110")
        return "x6";
    else if (regBinaryBits == "00111")
        return "x7";
    else if (regBinaryBits == "01000")
        return "x8";
    else if (regBinaryBits == "01001")
        return "x9";
    else if (regBinaryBits == "01010")
        return "x10";
    else if (regBinaryBits == "01011")
        return "x11";
    else if (regBinaryBits == "01100")
        return "x12";
    else if (regBinaryBits == "01101")
        return "x13";
    else if (regBinaryBits == "01110")
        return "x14";
    else if (regBinaryBits == "01111")
        return "x15";
    else if (regBinaryBits == "10000")
        return "x16";
    else if (regBinaryBits == "10001")
        return "x17";
    else if (regBinaryBits == "10010")
        return "x18";
    else if (regBinaryBits == "10011")
        return "x19";
    else if (regBinaryBits == "10100")
        return "x20";
    else if (regBinaryBits == "10101")
        return "x21";
    else if (regBinaryBits == "10110")
        return "x22";
    else if (regBinaryBits == "10111")
        return "x23";
    else if (regBinaryBits == "11000")
        return "x24";
    else if (regBinaryBits == "11001")
        return "x25";
    else if (regBinaryBits == "11010")
        return "x26";
    else if (regBinaryBits == "11011")
        return "x27";
    else if (regBinaryBits == "11100")
        return "x28";
    else if (regBinaryBits == "11101")
        return "x29";
    else if (regBinaryBits == "11110")
        return "x30";
    else if (regBinaryBits == "11111")
        return "x31";
    else
        return "Invalid register";
}
// convert register names (x0-x31) to ABI names
std::string convertRegNameToABI(std::string regName)
{
    if (regName == "x0")
        return "zero";
    else if (regName == "x1")
        return "ra";
    else if (regName == "x2")
        return "sp";
    else if (regName == "x3")
        return "gp";
    else if (regName == "x4")
        return "tp";
    else if (regName == "x5")
        return "t0";
    else if (regName == "x6")
        return "t1";
    else if (regName == "x7")
        return "t2";
    else if (regName == "x8")
        return "s0";
    else if (regName == "x9")
        return "s1";
    else if (regName == "x10")
        return "a0";
    else if (regName == "x11")
        return "a1";
    else if (regName == "x12")
        return "a2";
    else if (regName == "x13")
        return "a3";
    else if (regName == "x14")
        return "a4";
    else if (regName == "x15")
        return "a5";
    else if (regName == "x16")
        return "a6";
    else if (regName == "x17")
        return "a7";
    else if (regName == "x18")
        return "s2";
    else if (regName == "x19")
        return "s3";
    else if (regName == "x20")
        return "s4";
    else if (regName == "x21")
        return "s5";
    else if (regName == "x22")
        return "s6";
    else if (regName == "x23")
        return "s7";
    else if (regName == "x24")
        return "s8";
    else if (regName == "x25")
        return "s9";
    else if (regName == "x26")
        return "s10";
    else if (regName == "x27")
        return "s11";
    else if (regName == "x28")
        return "t3";
    else if (regName == "x29")
        return "t4";
    else if (regName == "x30")
        return "t5";
    else if (regName == "x31")
        return "t6";
    else
        return "Invalid register";
}

void dissassembleRType()
{
    std::string output = "";
    std::string binNum = hexToBin();
    std::string funct7 = binNum.substr(0, 7);
    std::string rs2 = convertRegNameToABI(convertBinToRegName(binNum.substr(7, 5)));
    std::string rs1 = convertRegNameToABI(convertBinToRegName(binNum.substr(12, 5)));
    std::string funct3 = binNum.substr(17, 3);
    std::string rd = convertRegNameToABI(convertBinToRegName(binNum.substr(20, 5)));
    // add
    if (funct7 == "0000000" && funct3 == "000")
    {
        output += "add" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + rs2;
    }
    // sub
    else if (funct7 == "0100000" && funct3 == "000")
    {
        output += "sub" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + rs2;
    }
    // xor
    else if (funct7 == "0000000" && funct3 == "100")
    {
        output += "xor" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + rs2;
    }
    // or
    else if (funct7 == "0000000" && funct3 == "110")
    {
        output += "or" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + rs2;
    }
    // and
    else if (funct7 == "0000000" && funct3 == "111")
    {
        output += "and" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + rs2;
    }
    // sll
    else if (funct7 == "0000000" && funct3 == "001")
    {
        output += "sll" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + rs2;
    }
    // srl
    else if (funct7 == "0000000" && funct3 == "101")
    {
        output += "srl" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + rs2;
    }
    // sra
    else if (funct7 == "0100000" && funct3 == "101")
    {
        output += "sra" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + rs2;
    }
    // slt
    else if (funct7 == "0000000" && funct3 == "010")
    {
        output += "slt" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + rs2;
    }
    // sltu
    else if (funct7 == "0000000" && funct3 == "011")
    {
        output += "sltu" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + rs2;
    }
    else
    {
        std::cout << "Invalid instruction";
        return; // end function if invalid instruction
    }
    output += " # R";
    std::cout << output;
}

void dissassembleIType1()
{
    std::string output = "";
    std::string binNum = hexToBin();
    std::string funct3 = binNum.substr(17, 3);
    std::string rs1 = convertRegNameToABI(convertBinToRegName(binNum.substr(12, 5)));
    std::string rd = convertRegNameToABI(convertBinToRegName(binNum.substr(20, 5)));
    std::string immediateBinBits = binNum.substr(0, 12);
    int immediate = std::stoi(immediateBinBits, nullptr, 2); // immediate in decimal form
    if (immediateBinBits[0] == '1')                          // check if negative
    {
        immediate -= 4096; // if negative subtract 2^12 = 4096
    }
    std::string immediateStr = std::to_string(immediate);                           // convert immediate to string
    std::string funct7 = binNum.substr(0, 7);                                       // for slli, srli, srai
    std::string shift = std::to_string(std::stoi(binNum.substr(7, 5), nullptr, 2)); // shift in decimal for slli, srli, srai
    // addi
    if (funct3 == "000")
    {
        output += "addi" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + immediateStr;
    }
    // xori
    else if (funct3 == "100")
    {
        output += "xori" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + immediateStr;
    }
    // ori
    else if (funct3 == "110")
    {
        output += "ori" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + immediateStr;
    }
    // andi
    else if (funct3 == "111")
    {
        output += "andi" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + immediateStr;
    }
    // slli
    else if (funct3 == "001" && funct7 == "0000000")
    {
        output += "slli" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + shift;
    }
    // srli
    else if (funct3 == "101" && funct7 == "0000000")
    {
        output += "srli" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + shift;
    }
    // srai
    else if (funct3 == "101" && funct7 == "0100000")
    {
        output += "srai" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + shift;
    }
    // slti
    else if (funct3 == "010")
    {
        output += "slti" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + immediateStr;
    }
    // sltiu
    else if (funct3 == "011")
    {
        output += "sltiu" + std::string(" ") + rd + std::string(", ") + rs1 + std::string(", ") + immediateStr;
    }
    else
    {
        std::cout << "Invalid instruction";
        return; // end function if invalid instruction
    }
    output += " # I";
    std::cout << output;
}
void dissassembleIType2()
{
    std::string output = "";
    std::string binNum = hexToBin();
    std::string funct3 = binNum.substr(17, 3);
    std::string rs1 = convertRegNameToABI(convertBinToRegName(binNum.substr(12, 5)));
    std::string rd = convertRegNameToABI(convertBinToRegName(binNum.substr(20, 5)));
    std::string immediateBinBits = binNum.substr(0, 12);
    int immediate = std::stoi(immediateBinBits, nullptr, 2); // immediate in decimal form
    if (immediateBinBits[0] == '1')                          // check if negative
    {
        immediate -= 4096; // if negative subtract 2^12 = 4096
    }
    std::string immediateStr = std::to_string(immediate); // convert immediate to string
    // lb
    if (funct3 == "000")
    {
        output += "lb" + std::string(" ") + rd + std::string(", ") + immediateStr + std::string("(") + rs1 + std::string(")");
    }
    // lh
    else if (funct3 == "001")
    {
        output += "lh" + std::string(" ") + rd + std::string(", ") + immediateStr + std::string("(") + rs1 + std::string(")");
    }
    // lw
    else if (funct3 == "010")
    {
        output += "lw" + std::string(" ") + rd + std::string(", ") + immediateStr + std::string("(") + rs1 + std::string(")");
    }
    // lbu
    else if (funct3 == "100")
    {
        output += "lbu" + std::string(" ") + rd + std::string(", ") + immediateStr + std::string("(") + rs1 + std::string(")");
    }
    // lhu
    else if (funct3 == "101")
    {
        output += "lhu" + std::string(" ") + rd + std::string(", ") + immediateStr + std::string("(") + rs1 + std::string(")");
    }
    else
    {
        std::cout << "Invalid instruction";
        return; // end function if invalid instruction
    }
    output += " # I";
    std::cout << output;
}
void dissassembleIType3()
{
    std::string output = "";
    std::string binNum = hexToBin();
    std::string funct3 = binNum.substr(17, 3);
    std::string rs1 = convertRegNameToABI(convertBinToRegName(binNum.substr(12, 5)));
    std::string rd = convertRegNameToABI(convertBinToRegName(binNum.substr(20, 5)));
    std::string immediateBinBits = binNum.substr(0, 12);
    int immediate = std::stoi(immediateBinBits, nullptr, 2); // immediate in decimal form
    if (immediateBinBits[0] == '1')                          // check if negative
    {
        immediate -= 4096; // if negative subtract 2^12 = 4096
    }
    std::string immediateStr = std::to_string(immediate); // convert immediate to string
    // jalr
    if (funct3 == "000")
    {
        output += "jalr" + std::string(" ") + rd + std::string(", ") + immediateStr + std::string("(") + rs1 + std::string(")");
    }
    else
    {
        std::cout << "Invalid instruction";
        return; // end function if invalid instruction
    }
    output += " # I";
    std::cout << output;
}

void dissassembleSType()
{
    std::string output = "";
    std::string binNum = hexToBin();
    std::string immediateBinBits = binNum.substr(0, 7) + binNum.substr(20, 5);
    int immediate = std::stoi(immediateBinBits, nullptr, 2); // immediate in decimal form
    if (immediateBinBits[0] == '1')                          // check if negative
    {
        immediate -= 4096; // if negative subtract 2^12 = 4096
    }
    std::string immediateStr = std::to_string(immediate); // convert immediate to string
    std::string rs2 = convertRegNameToABI(convertBinToRegName(binNum.substr(7, 5)));
    std::string rs1 = convertRegNameToABI(convertBinToRegName(binNum.substr(12, 5)));
    std::string funct3 = binNum.substr(17, 3);
    // sb
    if (funct3 == "000")
    {
        output += "sb" + std::string(" ") + rs2 + std::string(", ") + immediateStr + std::string("(") + rs1 + std::string(")");
    }
    // sh
    else if (funct3 == "001")
    {
        output += "sh" + std::string(" ") + rs2 + std::string(", ") + immediateStr + std::string("(") + rs1 + std::string(")");
    }
    // sw
    else if (funct3 == "010")
    {
        output += "sw" + std::string(" ") + rs2 + std::string(", ") + immediateStr + std::string("(") + rs1 + std::string(")");
    }
    else
    {
        std::cout << "Invalid instruction";
        return; // end function if invalid instruction
    }
    output += " # S";
    std::cout << output;
}
