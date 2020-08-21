#include "FIFOBuffer.h"
#include "cJSON.h"
#include "stdio.h"
#include "string.h"
char *json_text = "{\"target\": \"STM32F7-Dis\",\"ListTab\": [{\"TabName\": \"LivingRoom\",\"Type\":\"LR\",\"Device\":[{\"name\":\"LED 01\",\"ID\":\"LRLED01\",\"type\":\"LED\"},{\"name\":\"LED 02\",\"ID\":\"LRLED02\",\"type\":\"LED\"},{\"name\":\"TV 01\",\"ID\":\"LRTV01\",\"type\":\"TV\"}]}]}";
int main()
{
    // char text[] = "eeddddddddddddddddddddddeesa";
    // SaveStringToFIFO(text);
    // return 0;
    // char *stringg;
    // printf("Hello World \n");
    // printf("%s",json_text);
    // SaveStringToFIFO(json_text);
    GetDataFromFIFO();
    // printf("\n");
    JSONPreProcessing(json_text);
}
