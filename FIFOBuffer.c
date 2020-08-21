#include "FIFOBuffer.h"
#include "cJSON.h"
#include "string.h"
#include "stdio.h"
#include <stdlib.h>
#include <excpt.h>
#include <windows.h>
// char *json_text = "{\"target\": \"STM32F7-Dis\",\"ListTab\": [{\"TabName\": \"LivingRoom\",\"Type\":\"LR\",\"Device\":[{\"name\":\"LED 01\",\"ID\":\"LR-LED-01\",\"type\":\"LED\"},{\"name\":\"LED 02\",\"ID\":\"LR-LED-02\",\"type\":\"LED\"},{\"name\":\"TV 01\",\"ID\":\"LR-TV-01\",\"type\":\"TV\"}]}]}";
// char *json_text = "{\"target\": \"STM32F7-Dis\",\"ListTab\": [{\"TabName\": \"LivingRoom\",\"Type\":\"LR\",\"Device\":\"LR-LED-01,LR-LED-02,LR-TV-01\"}]}";
char * json_text = "{\"target\": \"STM32F7-Dis\",\"ListRoom\": [{\"LivingRoom\": \"LR-LED-01,LR-LED-02,LR-TV-01\",\"BathRoom\": \"BAR-LED-01,BAR-LED-02\",\"BedRoom\": \"BER-LED-01,BER-LED-02,BER-TV-01\"}]}";
char * tst_txt = "{\"target\": \"STM32F7-Dis\",\"ListRoom\": [{\"Root1\": [{\"Root2\":[{\"LivingRoom\":\"LR-LED-01,LR-LED-02,LR-TV-01\"}]}]}]}";
void FIFOBufferWrite(char pDataIn)
{
    if(pBufferWrite == pBufferRead)
    {
        // Buffer is full, do nothing or return error message.
        printf("Buffer is full");
    }
    else
    {
        // Write and increase pBufferWrite
        gBuffer[pBufferWrite] = pDataIn;
        // printf("Wrote");
        if (pBufferWrite < BUFFER_SIZE)
        {
            pBufferWrite++;
        }
        else
        {
            pBufferWrite = 0;
        }
    }
}

char FIFOBufferRead(void)
{
    char dataOut = 0x00;
    char tempBufferRead = pBufferRead + 1;
    if(tempBufferRead == pBufferWrite)
    {
        // Buffer is empty, do nothing or return error message.
    }
    else
    {
        // Increase pBufferRead and read data from buffer
        if (pBufferRead < BUFFER_SIZE)
        {
            pBufferRead++;
        }
        else
        {
            pBufferRead = 0;
        }
        dataOut = gBuffer[pBufferRead];
    }
    return dataOut;
}

void SaveStringToFIFO(char save_str[])
{
    int lenofstr;
    lenofstr = strlen(save_str);
    // printf("lenofstr = %d \n", lenofstr);
    int j;
    for (j = 0; j<lenofstr;j++)
    {
        // printf("%c",save_str[j]);
        FIFOBufferWrite(save_str[j]);
    }
}
void ResetBuffer()
{
    pBufferWrite = 1;
    pBufferRead = 0;
    for(int i = 0; i <ARRAY_SIZE ; i++)
    {
        gBuffer[i] = 0;
    }
}
char * GetDataFromFIFO()
{
    char tmp[pBufferWrite-1];
    char *output = malloc(pBufferWrite-1);
    // printf("\npBufferWrite =%d \n",pBufferWrite);
    // printf("\n");
    for (int i = 0; i<=pBufferWrite;i++)
    {
        tmp[i] = FIFOBufferRead();
    }
    // JSONPreProcessing(tmp);
    strcpy(output,tmp);
    // printf("\nOutput %s\n",output);
    return output;
}
void JSONPreProcessing(char *json_text)
{
    printf("\nlength of text = %d\n",strlen(json_text));
    printf("\njson_text = %s\n", json_text);
    cJSON *root = cJSON_Parse(json_text);
    // cJSON_AddStringToObject(root,"target",json_text);
    char *item = cJSON_GetObjectItem(root,"target")->valuestring;
    //char * cJp = cJSON_Print(item);
    printf("\nTarget = %s",item);
    cJSON *ListRoom = cJSON_GetObjectItem(root,"ListRoom")->child;
    char * LivingRoom = cJSON_GetObjectItem(ListRoom,"LivingRoom")->valuestring;
    char * BathRoom = cJSON_GetObjectItem(ListRoom,"BathRoom")->valuestring;
    char * BedRoom = cJSON_GetObjectItem(ListRoom,"BedRoom")->valuestring;
    printf("\nLivingRoom = %s",LivingRoom);
    printf("\nBathRoom = %s",BathRoom);
    printf("\nBedRoom = %s",BedRoom);
}
char * H_JSON_FindByKey(char * JSONText,char ValueAddress[])
{
    printf("\nInput JSON: %s", JSONText);
    printf("\nFinding at ValueAdress: %s", ValueAddress);
    cJSON *root = cJSON_Parse(JSONText);
    // Get specify key
    int str_index[strlen(ValueAddress)];
    int j = 0;
    char * Value = "";
    // printf("\nstrlen(ValueAddress) = %d",strlen(ValueAddress));
    for(int i = 0; i < strlen(ValueAddress);i++)
    {
        // printf("\n-------> %c",ValueAddress[i]);
        if (ValueAddress[i] == '/')
        {
            str_index[j] = i;
            j++;
            // printf("\nj= %d",j);
        }
    }
    printf("\nstr_index[0] = %d",str_index[0]);
    printf("\nstr_index[1] = %d",str_index[1]);
    printf("\nstr_index[2] = %d",str_index[2]);
    printf("\n-------------");
    for (int k = 0; k<=j;k++)
    {
        cJSON * root_tmp;
        if (k == 0)
        {
            // Get string
            char str_[strlen(ValueAddress)] = ValueAddress;
            // memcpy(str_ + 0 ,ValueAddress,strlen(ValueAddress));
            printf("\nstr_ = %s",str_);
            int str_2 = 32;
            memset(str_ + str_index[0],str_2,strlen(ValueAddress));
            char ttt = ' ';
            RemoveChar(str_,ttt);
            printf("\nRoot 0 %s",str_);
            printf("\nlen of str_ = %d",strlen(str_));
            root_tmp = cJSON_GetObjectItem(root,str_)->child;
        }
        printf("\nstr_index[0] = %d",str_index[0]);
        printf("\nstr_index[1] = %d",str_index[1]);
        printf("\nstr_index[2] = %d",str_index[2]);
        if (j > 0 && k > 0)
        {
            if (k == j)
            {
                char str_[strlen(ValueAddress)];
                memcpy(str_ + 0 ,ValueAddress,strlen(ValueAddress));
                printf("\nstr_ = %s",str_);
                int str_2 = 32;
                memset(str_ + 0,str_2,str_index[j-1]+1);
                char ttt = ' ';
                RemoveChar(str_,ttt);
                printf("\nfinal str_ = %s",str_);
                printf("\nlen of str_ = %d",strlen(str_));
                char * root_final = cJSON_GetObjectItem(root_tmp,str_)->valuestring;
                Value = root_final;
                printf("\nValue = %s",Value);
            }
            else
            {
                printf("\nk= %d",k);
                char str_[strlen(ValueAddress)];
                char ttt = ' ';
                memset(str_ + 0 ,32,strlen(ValueAddress)+4);
                memcpy(str_ + 0 ,ValueAddress,strlen(ValueAddress));
                RemoveChar(str_,ttt);
                printf("\nroot str_ = %s",str_);
                int str_2 = 32;
                printf("\nstr_index[k] = %d",str_index[2]);
                memset(str_ + str_index[k],str_2,strlen(ValueAddress)-str_index[k]);
                printf("\nroot 1 str_ = %s",str_);
                memset(str_ + 0,str_2,str_index[k-1]+1);
                printf("\nroot 2 str_ = %s",str_);
                RemoveChar(str_,ttt);
                printf("\nRoot n %s",str_);
                root_tmp = cJSON_GetObjectItem(root_tmp,str_)->child;
            }
        }
        
    }
    char *output = malloc(strlen(Value)-1);
    strcpy(output,Value);
    return output;
}
void  RemoveChar(char a[], char c)
{
    int n= strlen(a);
     for(int i=0;i<n;i++)
      {
         if(a[i]==c)
         {
            for(int j=i; j<n;j++)
              a[j]=a[j+1];
              a[n--]='\0';
              i--;
          }
      }
}
void main() 
{
    // char *stringg;
    // printf("Hello World \n");
    // printf("%s",json_text);
    char * t_json;
    SaveStringToFIFO(json_text);
    t_json = GetDataFromFIFO();
    // JSONPreProcessing(t_json);
    char * test_value;
    char test_src[] = "ListRoom/Root1/Root2/LivingRoom";
    test_value = H_JSON_FindByKey(tst_txt,test_src);
    printf("\nTest Value = %s",test_value);
    free(test_value);
    free(t_json);
}