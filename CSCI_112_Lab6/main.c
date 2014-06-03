/* 
 * File:   main.c
 * Author: roy.smart
 *
 * Created on June 3, 2014, 11:16 AM
 */

#include <stdio.h>
#include <stdlib.h>

void problem_1();
int read_file(char*, int*);
void print_array(int*, int);
void init_alphabet_array(char*);
int find_letter(int, int*);

int main(){
    problem_1();
    
    return 0;
}

/*
 * problem 1 decodes message based off of cipher file and pushes it to an
 * output file
 */
void problem_1(int argc, char** argv) {
    /*constant string literal paths to input files*/
    char * cipher_path = "cipher.txt";
    char * message_path = "message.txt";
    char * output_path = "decoded.txt";
    
    /*educated guess as to the size of the buffers*/
    int cipher_size = 26;
    int message_size = 100;
    
    /*allocate buffer for alphabet and initialize*/
    char alphabet[26];
    init_alphabet_array(alphabet);
    
    /*allocate buffers for input files to be read into memory*/
    int cipher_buffer[cipher_size];
    int message_buffer[message_size];
    
    /*read input files into memory*/
    cipher_size = read_file(cipher_path, cipher_buffer);
    message_size = read_file(message_path, message_buffer);
    
    /*print file read into memory*/
    print_array(cipher_buffer, cipher_size);
    print_array(message_buffer, message_size);
    
    /*solve cipher and write to output file*/
    FILE * output_file = fopen(output_path, "w");
    int i;
    for(i = 0; i < message_size; i++){
        int letter_index = message_buffer[i];
        int cipher_index = find_letter(letter_index, cipher_buffer);
        char decoded_letter = alphabet[cipher_index];
        fprintf(output_file, "%c", decoded_letter);
        printf("%c", decoded_letter);
    }
    printf("\n");
    fclose(output_file);

}

/*read file reads ints delimited by commas and returns a pointer to the array*/
int read_file(char * pathString, int* file_data){
    FILE * data_file = fopen(pathString, "r");
    
    /*read ints into array*/
    int scan_result = 0;
    int index = 0;
    while(scan_result != EOF){
        scan_result = fscanf(data_file, "%i%*c", file_data + index);
        index++;
    }
    
    return index - 1;       //return number of characters read (-1 for starting at zero)
}

/*print array prints out the specified number of elements of an array*/
void print_array(int * array, int arr_size){
    int i;
    for(i = 0; i < arr_size; i++){
        printf("%i ", array[i]);
    }
    printf("\n");
}

/*initialized the entire alphabet into an array to be decoded*/
void init_alphabet_array(char* alphabet){
    char current_letter = 'a';
    int i;
    for(i = 0; i < 26; i++){
        alphabet[i] = current_letter;
        current_letter++;
    }
}

/*finds the correct letter in the cipher and returns the index of that letter*/
int find_letter(int letter, int * cipher){
    int i;
    for(i = 0; i < 26; i++){
        int check_letter = cipher[i];
        if(letter == check_letter){
            return i;   //Once letter is located return with index;
        }
    }
    return -1; //if no number is found return invalid index
}