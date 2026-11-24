#include "physics.h"
#include "util.h"

bool isDirectlyConnected(int fromF, int fromR, int toF, int toR,const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],char& outConnType)
 {
    outConnType=CONN_NONE;
     if (fromF<1||fromF>NUM_FLOORS||toF<1||toF>NUM_FLOORS||fromR<1||fromR>ROOMS_PER_FLOOR||toR<1||toR>ROOMS_PER_FLOOR)
         return false;

    if (fromF==toF && fromR==toR)
        return false;


     if(fromF==toF && (toR-fromR==1||toR-fromR==-1 ))
         {
             int floorind,conind=0;
            floorind=fromF-1;

            if (fromR<toR)
            conind=fromR-1;

            else
            conind=toR-1;

            outConnType=horizontalConn[floorind][conind];

            if (outConnType !=CONN_NONE && outConnType != CONN_SOLID_WALL)
            return true;

            else
            outConnType=CONN_NONE;
         }
            
         //stair
         if ((fromF==1&&toF==2&&fromR==1&&toR==1)||(fromF==2&&toF==1&&fromR==1&&toR==1)||(fromF==2&&toF==3&&fromR==1&&toR==1)||(fromF==3&&toF==2&&fromR==1&&toR==1)||(fromF==4&&toF==5&&fromR==1&&toR==1)||(fromF==5&&toF==4&&fromR==1&&toR==1))
         {
            outConnType='S';
            return true;
         }

                     //lift 1
         if ((fromR==2||fromR==3)&&(toR==2||toR==3)) 
         {
            if((fromF==1&&toF==2)||(fromF==2&&toF==1))
            {
                outConnType='1';
                return true;
            }
         }
             //lift 2
         if(fromR==4&&toR==4)
         {
            if((fromF==2&&(toF==4||toF==5)) || (fromF==4&&(toF==2||toF==5)) || (fromF==5&&(toF==2||toF==4)))
            {
                outConnType='2';
                return true;
            }
         }

         return false;
 }





bool canTraverse(int targetFloor, int targetRoom, char connType, const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,int emergencyTripsLeft, bool lift2Operational)
 {

   if(targetFloor<1||targetFloor>NUM_FLOORS||targetRoom<1||targetRoom>ROOMS_PER_FLOOR)
   return false;

if (connType==CONN_DOOR)
{
return true;
}

if (connType==CONN_WINDOW)
return true;

if (connType==CONN_LOCKED_DOOR)
{
if (hasItem(inventory, inventoryCount,ENT_MASTER_KEY))
return true;

else
return false;
}

if (connType==CONN_SOLID_WALL)
return false;

if (connType==CONN_NONE)
return false;

if (connType=='S')
return true;

if (connType=='1')
return true;

if(connType=='2')
{
   if(lift2Operational)
   {
      
    if (hasItem(inventory,inventoryCount,ENT_LIFT_PASS))
    return true;

    else
    return false;
   }
   

   else
   {
    if (hasItem(inventory,inventoryCount,ENT_EMERGENCY_CARD) && emergencyTripsLeft>0)
    return true;

    else
    return false;
}
   

}
 return false;

}

void applyResourceDelta(int& energy, int& time, int deltaEnergy, int deltaTime)
{
energy+=deltaEnergy;
time+=deltaTime;
 energy=clampInt(energy,0,100);
 time=clampInt(time,0,100);
}

void applyScoreDelta(int& score, int deltaScore)
{
score+=deltaScore;
}

bool hasItem(const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, char itemSymbol)
{
    if(inventoryCount>MAX_INVENTORY_CAPACITY||inventoryCount<0)
    return false;
   for(int i=0;i<inventoryCount;i++)
    {
        if(inventory[i]==itemSymbol)
        return true;
    }
    return false;
}  

bool addItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol)
{
    if (inventoryCount>=MAX_INVENTORY_CAPACITY||inventoryCount<0)
    {
        return false;
    }
    inventory[inventoryCount]=itemSymbol;
    inventoryCount+=1;
    return true;

}
bool removeItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol)
{
if(inventoryCount>MAX_INVENTORY_CAPACITY||inventoryCount<0)
return false;

for(int i=0;i<inventoryCount;i++)
    {
        if(inventory[i]==itemSymbol)
        { 
            for( ;i+1<inventoryCount;i++)
            inventory[i]=inventory[i+1];
       
            inventoryCount-=1;
        return true;
         }
        
    } 
    return false;   
}

