#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <math.h>
#include <vector>
#include <time.h>

#include "debug.hpp"
#include "tokens.hpp"
#include "parser.hpp"
#include "generator.hpp"
#include "tokenizer.hpp"

using namespace std;

#define FILE_OK 0
#define FILE_NOT_EXIST 1
#define FILE_TOO_LARGE 2
#define FILE_READ_ERROR 3



FILE *fptr;

string file_name = "";
string output_file_name = "lang/build/output.asm";


char * c_read_file(const char * f_name, int * err, size_t * f_size) {
    char * buffer;
    size_t length;
    FILE * f = fopen(f_name, "rb");
    size_t read_length;
    
    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        
        // 1 GiB; best not to load a whole large file in one string
        if (length > 1073741824) {
            *err = FILE_TOO_LARGE;
            
            return NULL;
        }
        
        buffer = (char *)malloc(length + 1);
        
        if (length) {
            read_length = fread(buffer, 1, length, f);
            
            if (length != read_length) {
                 free(buffer);
                 *err = FILE_READ_ERROR;

                 return NULL;
            }
        }
        
        fclose(f);
        
        *err = FILE_OK;
        buffer[length] = '\0';
        *f_size = length;
    }
    else {
        *err = FILE_NOT_EXIST;
        
        return NULL;
    }
    
    return buffer;
}

void interpreter_string(int argc, char *argv[]){
    for(int i =1; i< argc; i++){
        string arg = argv[i];
        if(arg == "--debug"){
            is_debug_mode = true;
            printf("Debug mode enabled\n");
        }
        if(arg == "-c"){
            if(i+1 < argc){
                file_name = argv[i+1];
            }
        }
        if(arg == "-o"){
            if(i+1 < argc){
                output_file_name = argv[i+1];
            }
        }
    }
    if(is_debug_mode) printf("File name: %s\n", file_name.c_str());
    if(is_debug_mode) printf("Output file name: %s\n", output_file_name.c_str());
}


int main(int argc, char *argv[]){
    if( argc < 2 ){
        printf("Usage: %s -c <file>\n", argv[0]);
        return 1;
    }
    interpreter_string(argc, argv);
    //interpreter_string(argc, argv);
    printf("Opening file %s\n", file_name.c_str());
    int err;
    size_t f_size;\
    char * f_data;

    f_data = c_read_file( file_name.c_str(), &err, &f_size);

    if (err) {
        printf("Error reading file: %d\n", err);
        exit(err);
    }
    //tokenize the file data
    string file_str_data = f_data;
    Tokenizer tokenizer(file_str_data);
    
    vector<Token> parsed_tokens = tokenizer.tokenize();
    Parser parser(parsed_tokens);

    optional<NodeExit> token_tree = parser.parse();

    Generator generator(token_tree.value());
    {
        fstream file(output_file_name.c_str(),std::ios::out);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << output_file_name << std::endl;
            exit(-1);
        }
        file << generator.generate();
        file.close();
    }

    return 0;
}