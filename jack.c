// Zachary M. Petro
// 2016

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int getNum();
void sendMessage(char *message, int num);

int main(){
    char quote[200];
    int num = getNum();
    
    if(num == 40) num = 57;
    if(num == 50) num = 58;

    FILE *fp;
    fp = fopen("quotes.txt", "r");

    int currNum = 0;
    char temp[20];

    while(currNum != num){
        fscanf(fp, "%s", temp);
        if(isdigit(temp[0]) != 0){
            currNum = atoi(temp);
        }
    }

    fgets(quote, 180, fp);
    fclose(fp);

    int i, len = strlen(quote);

    for(i = 1; i <= len; ++i){
        quote[i-1] = quote[i];
    }
   
    char *pos;
    if((pos=strchr(quote, '\n')) != NULL) *pos = '\0';
    
    sendMessage(quote, num);

    return 0;
}

int getNum(){ 
    int i;
    srand(time(NULL));
    int temp = (rand() % 56) + 1;
    int finalNum = 0;
    FILE *fp3;
    fp3 = fopen("previous.dat", "r");
    int readNums[57] = {0};
    int arrayTemp;

    while(!feof(fp3)){
        fscanf(fp3, "%d", &arrayTemp);
        readNums[arrayTemp] = 1;
    }

    fclose(fp3);

    int nothingLeft = 1;
    for(i = 1; i < 57; ++i){
        if(readNums[i] == 0){
            nothingLeft = 0;
            break;
        }
    }
    
    if(nothingLeft == 1){
        fp3 = fopen("previous.dat", "w");
        fprintf(fp3, "%s", "");
        fclose(fp3);
        for(i = 1; i < 57; ++i){
            readNums[i] = 0;
        }
    }

    int isFinal = 1;

    while(finalNum != temp){
        isFinal = 1;
        for(i = 1; i < 57; ++i){
            if(readNums[temp] == 1){
                isFinal = 0;
                temp = (rand() % 56) + 1;
                break;
            }
        }
        if(isFinal == 1){
            finalNum = temp;
            readNums[finalNum] = 1;
        }
    }

    fp3 = fopen("previous.dat", "w");
    for(i = 1; i < 57; ++i){
        if(readNums[i] == 1){
            fprintf(fp3, "%d\n", i);
        }
    }
    fclose(fp3);

    return finalNum;
}

void sendMessage(char *message, int num){
    FILE *fp2;
    fp2 = fopen("message.dat", "w"); 
    fputs("{\n", fp2);
    fputs("\"bot_id\" : \"insert groupme bot_id here\",\n", fp2);
    if(num < 30){
        fputs("\"text\" : \"", fp2);
        fputs(message, fp2);
        fputs("\"\n", fp2);
    }else{
        fputs("\"attachments\" : [\n{\n", fp2);
        fputs("\"type\" : \"image\",\n", fp2);
        fputs("\"url\" : \"", fp2);
        fputs(message, fp2);
        fputs("\"\n}\n]\n", fp2);
    }
    fputs("}", fp2);
    fclose(fp2);
    system("curl -d @message.dat https://api.groupme.com/v3/bots/post");
}
