#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


typedef struct hashtagNode * ptr;

typedef struct hashtagNode{
    char hashtag[32];
    int count;
    ptr next;
}hashtagNode;

int doesHashtagExist(ptr*, char[]);
ptr getHashtagNode(ptr*, char[]);
int createHashtag(ptr*, char[]);
void printList(ptr, FILE*);
void bubbleSort(ptr);
void swap(ptr, ptr);

int main(){
    FILE* output;
    FILE* input;
    char line[1000];
    int count=0;
    ptr h=NULL;
    const char s[2]=" ";
    char* token;

    input = fopen("input.txt","r+");
    output = fopen("top_hashtags.txt","w+");

    while(fgets(line,1000,input)!=NULL){
        ptr temp = NULL;

        token = strtok(line, s);

        while(token != NULL){

            if(temp = getHashtagNode(&h,token)){
                temp->count++;
            }

            else{
                createHashtag(&h,token);
            }

            token = strtok(NULL,s);
        }

    }
    bubbleSort(h);
    printList(h, output);

    fclose(input);
    fclose(output);

    return 0;
}

int doesHashtagExist(ptr* h,char hashtag[]){
    ptr curr = *h;

    while(curr!=NULL){
        if(!strcmp(hashtag,curr->hashtag))
            return 1;
        curr=curr->next;
    }

    return 0;

}

ptr getHashtagNode(ptr* h,char hashtag[]){
    ptr curr = *h;
    int len = strlen(hashtag);

    if (hashtag[len-1]=='\n')
        hashtag[len-1]=0;

    while(curr!=NULL){
        if(!strcmp(curr->hashtag,hashtag))
            return curr;
        curr=curr->next;
    }

    return curr;
}

int createHashtag(ptr *h,char hashtag[]){
    ptr temp = (ptr)malloc(sizeof(hashtagNode));
    ptr curr = *h;
    int len = strlen(hashtag);

    if(hashtag[0]=='@' || hashtag[0]==0)
        return 0;
    
    if (hashtag[len-1]=='\n')
        hashtag[len-1]=0;

    if (doesHashtagExist(h, hashtag))
        return 1;

    strcpy(temp->hashtag, hashtag);
    temp->count=1;
    temp->next=NULL;

    if (*h==NULL){
        *h=temp;
        return 1;
    }

    else{
        while(curr->next!=NULL){
            curr=curr->next;
        }
        curr->next = temp;
        return 1;
    }

    return 0;
}

void printList(ptr h, FILE* output){
    ptr curr = h;

    while(curr!=NULL){
        fprintf(output,"Hashtag: '%s' Count: '%d'\n",curr->hashtag,curr->count);
        curr=curr->next;
    }

}

void bubbleSort(ptr start) 
{ 
    int swapped, i; 
    ptr ptr1; 
    ptr lptr = NULL; 
  
    /* Checking for empty list */
    if (start == NULL) 
        return; 
  
    do
    { 
        swapped = 0; 
        ptr1 = start; 
  
        while (ptr1->next != lptr) 
        { 
            if (ptr1->count < ptr1->next->count) 
            {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
} 

void swap(ptr a, ptr b) 
{ 
    ptr temp;
    temp->count = a->count; 
    strcpy(temp->hashtag,a->hashtag); 
    a->count = b->count;
    strcpy(a->hashtag,b->hashtag); 
    b->count = temp->count;
    strcpy(b->hashtag,temp->hashtag); 
} 