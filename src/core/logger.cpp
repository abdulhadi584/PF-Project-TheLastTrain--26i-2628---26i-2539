#include "logger.h"
#include "util.h"
#include <fstream>
#include <iostream>
using namespace std;

bool saveGameStateToFile(const char* filename,
                         int playerFloor, int playerRoom,
                         int energy, int time, int score,
                         const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                         const bool objectives[NUM_OBJECTIVES], int emergencyTripsLeft,
                         const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                         const int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR])
                        {
                            ofstream file;
                            file.open(filename);

                            if (!file)
                            return false;

                            if (inventoryCount>MAX_INVENTORY_CAPACITY||inventoryCount<0)
                            return false;

                            
                            file<<playerFloor<<endl;

                             
                            file<<playerRoom<<endl;

                             
                            file<<energy<<endl;

                             
                            file<<time<<endl;

                             
                            file<<score<<endl;

                            

                            file<<inventoryCount<<endl;
                            for (int i=0;i<inventoryCount;i++)
                            {
                                
                                file<<inventory[i];
                            }
                            file<<endl;
                             
                             

                            for (int i=0;i<NUM_OBJECTIVES;i++)
                            {
                                
                                file<<objectives[i]<<" ";
                            }
                            file<<endl;

                            
                            file<<emergencyTripsLeft<<endl;

                            for (int i=0;i<NUM_FLOORS;i++)
                            {
                                for (int j=0;j<ROOMS_PER_FLOOR;j++)
                                {
                                    for (int k=0;k<MAX_ENTITIES_PER_ROOM;k++)
                                    {
                                
                                    file<<(int)roomEntities[i][j][k]<<endl; }
                                }
                            }

                            for (int i=0;i<NUM_FLOORS;i++)
                            {
                                for (int j=0;j<ROOMS_PER_FLOOR;j++)
                                {
                                    
                                    file<<entityCounts[i][j]<<endl;
                                }
                            }
                            file.close();

                            if (!file)
                            return false;

                            return true;

                        }


bool loadGameStateFromFile(const char* filename,
                           int& playerFloor, int& playerRoom,
                           int& energy, int& time, int& score,
                           char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                           bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft,
                           char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                           int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR])
{

    ifstream file;
    file.open(filename);

    if (!file)
    return false;
    int entval;

    file>>playerFloor;
    file>>playerRoom;
    file>>energy;
    file>>time;
    file>>score;

    if (!file)
    return false;

    if(playerFloor<1||playerFloor>NUM_FLOORS||playerRoom<1|| playerRoom>ROOMS_PER_FLOOR||energy<0||energy>MAX_ENERGY ||time< 0||time>MAX_TIME ||score<0||score>520)
    return false;

    file>>inventoryCount;
    if (!file)
    return false;

     if (inventoryCount>MAX_INVENTORY_CAPACITY||inventoryCount<0)
     return false;

    for (int i=0;i<inventoryCount;i++)
    {
        file>>inventory[i];
    }
    if (!file)
    return false;

    for (int i=0;i<NUM_OBJECTIVES;i++)
    {
    file>>objectives[i];
    }
    if (!file)
    return false;

    file>>emergencyTripsLeft;
    if (!file)
    return false;

    if (emergencyTripsLeft<0||emergencyTripsLeft>3)
     return false;

    for (int i=0;i<NUM_FLOORS;i++)
    {
        for (int j=0;j<ROOMS_PER_FLOOR;j++)
        {
            for (int k=0;k<MAX_ENTITIES_PER_ROOM;k++)
                {   
                    file>>entval;
                    if (!file)
                    return false;
                    roomEntities[i][j][k]=(char)entval; 
                }
        }
    }

    for (int i=0;i<NUM_FLOORS;i++)
    {
         for (int j=0;j<ROOMS_PER_FLOOR;j++)
         {
            file>>entityCounts[i][j];
            if (!file)
            return false;
            
        }
     }
     if (!file)
    return false;
    

return true;
}

void writeGameSummaryReport(const char* filename,
                            int score, int remainingEnergy, int remainingTime,
                            const bool objectives[NUM_OBJECTIVES], bool victory)
{
   ofstream file; 
   file.open(filename);

   if(!file)
   return;

   file<<"score is"<<score<<endl;
   file<<"remaining energy is"<<remainingEnergy<<endl;
   file<<"remaining tine is"<<remainingTime<<endl;

   if (objectives[OBJ_MASTER_KEY])
    file<<"master key collected"<<endl;

    else
    file<<"master key not collected"<<endl;

    if(objectives[OBJ_CLUE_4])
    file<<"clue 4 found"<<endl;
    else
file<<"clue 4 not found"<<endl;


    if (objectives[OBJ_CLUE_2])
    file<<"clue 2 found"<<endl;
    else
    file<<"clue 2 not found"<<endl;

    if (objectives[OBJ_CLUE_7])
    file<<"clue 7 found"<< endl;
    else
    file<<"clue 7 not found"<<endl;

    
    if (objectives[OBJ_CABINET_UNLOCKED])
    file<<"cabinet unlocked"<<endl;


    else
    file<<"cabinet not unlocked"<<endl;

    if (objectives[OBJ_TRAIN_KEY])
    file<<"train key acquired"<<endl;
else
file<<"train key not acquired"<<endl;

    if (objectives[OBJ_FUSE_COLLECTED])
    file<<"fuse collected"<<endl;
    else
    
    file<<"fuse not collected"<<endl;

    if (objectives[OBJ_FUSE_INSTALLED])
    file<<"fuse installed"<<endl;
    else
    
    file<<"fuse not installed"<<endl;

    if (objectives[OBJ_LIFT_PASS])
    file<<"lift pass collected"<<endl;
    else
    file<<"lift pass not collected"<<endl;



    if (objectives[OBJ_LIFT2_ACTIVE])
    file<<"lift 2 active"<<endl;
    else
    
    file<<"lift 2 not active"<<endl;

    if (objectives[OBJ_PASSENGER_RESCUED])
    file<<"passenger rescued"<<endl;
    else
    file<<"passenger not rescued"<<endl;


    if (objectives[OBJ_CAT_CARRIER])
   file<<"cat carrier collected"<<endl;

    else
    file<<"cat carrier not collected"<<endl;


    if (objectives[OBJ_CAT_SECURED])
    file<<"cat secured"<<endl;
    else

    file<<"cat not secured"<<endl;

 if (objectives[OBJ_TRAIN_PREPARED])
   file<<"train prepared and boarded"<<endl;
    else
    file<<"train not prepared and boarded"<<endl;

    if (objectives[OBJ_MISSION_WON])
    file<<"mission won"<<endl;
    else
    file<<"mission not won"<<endl;

    if (objectives[OBJ_MISSION_FAILED])
    file<<"mission failed"<<endl;
    
    else
    file<<"mission not failed"<<endl;

    if (victory)
    file<<"victory"<<endl;
    else
    file<<"defeat"<<endl;

    file.close();

   
}
