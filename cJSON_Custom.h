#ifndef CJSON_CUSTOM_H
#define CJSON_CUSTOM_H
#include "cJSON.h"
#define ARRAY_SIZE 5000 //Size of buffer
#define BUFFER_SIZE ARRAY_SIZE-1
// static uint8_t gBuffer[ARRAY_SIZE]__attribute__((at(FLASH_ADDRESS))); //Buffer has a size of 4999
char gBuffer[ARRAY_SIZE];
int pBufferWrite = 1;
int pBufferRead = 0;
/* Available functions */
/* These functions below belong to the FIFO ring Buffer*/
/* 
 * FIFOBufferWrite: Send 1 character to the ring Buffer 
 * pDataIn: the character which will be stored in the buffer
 * Return: None
 * * *
 */
void FIFOBufferWrite(char pDataIn);
/*
 * FIFOBufferRead: Read 1 character from the ring Buffer
 * Return: The character which was read from the buffer
 */
char FIFOBufferRead(void);
/*
 * SaveStringToFIFO: Save a string to the ring Buffer
 * save_str[]: the string which will be put into the buffer
 * Return: None
 */
void SaveStringToFIFO(char save_str[]);
/* 
 * ResetBuffer: Clear all buffer data
 * Return: None
 */
void ResetBuffer();
/*
 * GetDataFromFIFO: Get all data stored in FIFO Buffer and put them to a string
 * Return: the string which was read from buffer*/
char * GetDataFromFIFO();
/*
 * JSONGetStringValue: Get the string value from JSON string given address
 * JSONGetNumberValue: Get the double value from JSON string given address
 * json_text: JSON code in string format
 * These function support <2 class JSON file (root in root). In case the key
 * was stored in the main root, set root2 = "", root1 is the key where stored 
 * the data
 * For example:
 * The JSON file below
 * {
    "root1": [{
        "root2": "ABC",
    "root3" : 100
    }]
    }
    => char * result_string = JSONGetStringVallue(_json_text,"root1","root2");
    => double result_number = JSONGetNumberVallue(_json_text,"root1","");
 * Note: after using JSONGetStringVallue, you may need to free the memory
 * using free(result_string)
 */
char * JSONGetStringValue(char *json_text, char *root1, char *root2);
double JSONGetNumberValue(char *json_text, char *root1, char *root2);
/*Remove any character in a string*/
void  RemoveChar(char a[], char c);
/* Developing function */
void JSONPreProcessing(char json_text[]);
char * H_JSON_FindByKey(char * JSONText,char * ValueAddress);
#endif 