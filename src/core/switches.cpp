#include "switches.h"
#include "util.h"


// Door lock mechanics, lifts, and cabinet verification without structures
bool canUseLift1(int fromFloor,int toFloor)
 {
    if((fromFloor==1&&toFloor==2) || (fromFloor==2&&toFloor==1))
    return true;
    else
    return false;
 }

 bool canUseLift2(int fromFloor,int toFloor,bool lift2Operational, int emergencyTripsLeft)
 { 
    if(((fromFloor==2 && (toFloor==4||toFloor==5))||(fromFloor==4 && (toFloor==2||toFloor==5))||(fromFloor==5 && (toFloor==4||toFloor==2))) && (lift2Operational || emergencyTripsLeft>0))
    {
            return true;
        
    }
    else 
    return false;
 }

bool unlockFloor3Door(const char inventory[MAX_INVENTORY_CAPACITY],int inventoryCount)
{ for(int i=0;i<inventoryCount;i++)
    {
        if(inventory[i]=='<')
        return true;
    }
    return false;
}

bool installFuseControlPanel(char inventory[MAX_INVENTORY_CAPACITY],int& inventoryCount,bool objectives[NUM_OBJECTIVES],int& score)
{
  for(int i=0;i<inventoryCount;i++)
    {
        if(inventory[i]=='*')
        { 
            for( ;i+1<inventoryCount;i++)
            inventory[i]=inventory[i+1];
       
            inventoryCount-=1;
            score+=SCORE_INSTALL_FUSE; 
            objectives[7]=true;

        return true;
         }
        
    } 
    return false;  
}

bool verifyCabinetCode(const char* enteredCode,const bool objectives[NUM_OBJECTIVES])
{
    if((objectives[1]&&objectives[2]&&objectives[3])&&(enteredCode[0]=='4'&&enteredCode[1]=='2'&&enteredCode[2]=='7'&&enteredCode[3]=='\0'))
    return true;
    else
    return false;
}