#include <iostream>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#define MEMSIZE 1024
inline bool matches(const char* program, std::vector<int8_t> seq) {
    if(seq.size()==0) {
        return true;
    }
    std::vector<int8_t>::iterator seqhead=seq.begin();

    const char* instruction_counter=program;
    std::vector<const char*> stack;

    int8_t memory[MEMSIZE];
    memset(memory,0,sizeof(memory));
    int8_t* memptr=memory;

    unsigned int steps_since_output=0;
    while(*instruction_counter && steps_since_output<50) {
        switch(*instruction_counter) {
        case 'a':
            steps_since_output=0;
            //printf("%d ",*memptr);
            if(*seqhead == *memptr) {
                seqhead++;
                if(seqhead==seq.end()){
                    return true;
                }
            } else {
                return false;
            }
            break;
        case 'b':
            (*memptr)++;
            break;
        case 'c':
            (*memptr)--;
            break;
        case 'd':
            memptr--;
            if(memptr<memory) {
                memptr+=MEMSIZE;
            }
            break;
        case 'e':
            memptr++;
            if(memptr>=memory+MEMSIZE) {
                memptr-=MEMSIZE;
            }
            break;
        case 'f':
            if(*memptr) {
                stack.push_back(instruction_counter);
            } else {
                int bracecount=1;
                while(bracecount && *instruction_counter) {
                    instruction_counter++;
                    if(*instruction_counter=='[') bracecount++;
                    if(*instruction_counter==']') bracecount--;
                }
                if(!*instruction_counter) {
                    return false;
                }
            }
            break;
        case 'g':
            if(stack.empty()) {
                return false;
            }
            if(*memptr) {
                instruction_counter=stack.back();
            } else {
                stack.pop_back();
            }
            break;
        default:
            std::cerr <<"Error! Unidentified instruction "<< (*instruction_counter) << std::endl;
        }
        instruction_counter++;
        steps_since_output++;
    }
    return false;
}
inline void increment_program(char* &program) {
    char* ind=program;
    while(*ind=='g') {
        *(ind++)='a';
    }
    if(*ind=='\0') {
        *(--program)='a';
    } else {
        (*ind)++;
    }
}

//Ordering is   .=a
//              +=b
//              -=c
//              <=d
//              >=e
//              [=f
//              ]=g

int main(int argc, char** argv)
{
    std::vector<int8_t> sequence;
    for(int i=1; i<argc; i++) {
        sequence.push_back(atoi(argv[i]));
    }
    char programbuff[100];
    programbuff[99]='\0';
    char* program=&programbuff[99];
    while(true) {
        increment_program(program);
        if(matches(program,sequence)){
            std::cout << "Found match!" <<std::endl;
            std::string programstr(program);
            std::replace( programstr.begin(), programstr.end(), 'a', '.');
            std::replace( programstr.begin(), programstr.end(), 'b', '+');
            std::replace( programstr.begin(), programstr.end(), 'c', '-');
            std::replace( programstr.begin(), programstr.end(), 'd', '<');
            std::replace( programstr.begin(), programstr.end(), 'e', '>');
            std::replace( programstr.begin(), programstr.end(), 'f', '[');
            std::replace( programstr.begin(), programstr.end(), 'g', ']');
            std::cout << "New program "<< programstr << std::endl;
            return 0;
        }
    }
    return 0;
}

