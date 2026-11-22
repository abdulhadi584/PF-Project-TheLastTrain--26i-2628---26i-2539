#include "util.h"
#include <iostream>
#include <cstring>
using namespace std;

int clampInt(int val,int minVal,int maxVal)
{
if (val>maxVal)
return maxVal;

else if (val<minVal)
return minVal;

else
return val; 
} 

void trimWhitespace(char* str)
{
int start=0,i=0,end;
while (str[start]==' '|| str[start]=='\n'|| str[start]=='\t'||str[start]=='\r')
start++;

 end=strlen(str) -1;

 while(end>start && (str[end]==' '|| str[end]=='\n' || str[end]=='\t' || str[end]=='\r'))
 end--;

 while (end>=start)
 {
    str[i]=str[start];
    i++;
    start++;
 }

 str[i]='\0';
}

bool stringEquals(const char* a, const char* b)
{
    if (strcmp(a,b)==0)
    return true;

    else 
    return false;
}

void printHeader(const char* title)
{
cout<<"==========";
cout<<title;
cout<<"=========="<<endl;

}

void clearScreen()
{
    cout<<"\n\n\n\n\n\n\n\n";
}




// Primitive helper utilities, clamping, and screen control
