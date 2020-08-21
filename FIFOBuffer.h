#ifndef FIFO_BUFFER_H
#define FIFO_BUFFER_H
#include "cJSON.h"
#define ARRAY_SIZE 5000 //Size of buffer
#define BUFFER_SIZE ARRAY_SIZE-1
// static uint8_t gBuffer[ARRAY_SIZE]__attribute__((at(FLASH_ADDRESS))); //Buffer has a size of 4999
char gBuffer[ARRAY_SIZE];
int pBufferWrite = 1;
int pBufferRead = 0;
void FIFOBufferWrite(char pDataIn);
char FIFOBufferRead(void);
void SaveStringToFIFO(char save_str[]);
void ResetBuffer();
char * GetDataFromFIFO();
void JSONPreProcessing(char json_text[]);
char * H_JSON_FindByKey(char * JSONText,char * ValueAddress);
void  RemoveChar(char a[], char c);
#endif 