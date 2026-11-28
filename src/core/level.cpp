#include "level.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
using namespace std;

// Modular implementation using primitive arrays for map parsing and verification
bool loadBuildingMap(const char* filename,
                     char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
                     char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                     int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR])
                    {
                        ifstream file;
                        file.open(filename);
                        if (!file)
                        return false;   
                    
                        for(int i=0;i<NUM_FLOORS;i++)
                            {
                                for(int j=0;j<ROOMS_PER_FLOOR-1;j++)
                                {
                                    horizontalConn[i][j]=CONN_NONE;
                                }
                            }

                        for (int i=0;i<NUM_FLOORS;i++)
                        {
                            for (int j=0;j<ROOMS_PER_FLOOR;j++)
                                { for(int k=0;k<MAX_ENTITIES_PER_ROOM;k++)
                                    {
                                        roomEntities[i][j][k]=ENT_NONE;
                                    }
                                }
                        }
                        for (int i=0;i<NUM_FLOORS;i++)
                        {
                            for (int j=0;j<ROOMS_PER_FLOOR;j++)
                            {
                                entityCounts[i][j]=0;
                            }
                        
                        }
                        char line[256];
                        int currentFloor = -1;
                        while(file.getline(line,256))
                        {
                            if(strstr(line,"F1-R")!=nullptr || strstr(line,"F2-R")!=nullptr || strstr(line,"F3-R")!=nullptr || strstr(line,"F4-R")!=nullptr || strstr(line,"F5-R")!=nullptr)
                            {
                                for(int i=0;line[i]!='\0';i++)
                                {
                                        
                                    if(strlen(line)-i>=5 &&(line[i]=='F')&&(line[i+1]>='1' && line[i+1]<='5')&&(line[i+2]=='-')&&(line[i+3]=='R')&&(line[i+4]>='1' && line[i+4]<='4'))
                                    {
                                        int floor=0,room=0;
                                        switch(line[i+1])
                                        {
                                            case '1':
                                                floor=0;
                                                break;
                                            case '2':
                                                floor=1;
                                                break;
                                            case '3':
                                                floor=2;
                                                break;
                                            case '4':
                                                floor=3;
                                                break;
                                            case '5':
                                                floor=4;
                                                break;
                                            default:
                                                return false;
                                        }
                                        currentFloor=floor;
                                        switch(line[i+4])
                                        {
                                            case '1':
                                                room=0;
                                                break;
                                            case '2':
                                                room=1;
                                                break;
                                            case '3':
                                                room=2;
                                                break;
                                            case '4':
                                                room=3;
                                                break;
                                            default:
                                                return false;
                                        }  
                                        char connection = CONN_NONE;
                                        for(int j=i+5;line[j]!='\0';j++)
                                    {
                                        if(line[j]=='F')
                                            break;
                                        if(line[j]=='D'||line[j]=='W'||line[j]=='L'||line[j]=='#')
                                        {    
                                         connection=line[j];  
                                         break;  
                                        } 
                                    }   if(room<ROOMS_PER_FLOOR-1)
                                        switch(connection)
                                        { 
                                            case'D':
                                                horizontalConn[floor][room]=CONN_DOOR;
                                                break;
                                            case 'W':
                                                horizontalConn[floor][room]=CONN_WINDOW;
                                                break;
                                            case 'L':
                                                horizontalConn[floor][room]=CONN_LOCKED_DOOR;
                                                break;
                                            case '#':
                                                horizontalConn[floor][room]=CONN_SOLID_WALL;
                                                break;
                                        }

                                        
                                    
                                        
                                    }
                              
                             
                               }   
                           
                  char itemLine[256];           
            if (currentFloor != -1 && file.getline(itemLine, 256))
            {
                int len = strlen(itemLine);
                int startCols[4] = {9, 21, 33, 45};
                int endCols[4] = {19, 31, 43, 55};

                for (int r = 0; r < ROOMS_PER_FLOOR; r++)
                {
                    for (int col = startCols[r]; col <= endCols[r] && col < len; col++)
                    {
                        char ch = itemLine[col];
                        if (ch != ' ' && ch != '|' && ch != '\r' && ch != '\n')
                        {
                            if (entityCounts[currentFloor][r] < MAX_ENTITIES_PER_ROOM)
                            {
                                roomEntities[currentFloor][r][entityCounts[currentFloor][r]] = ch;
                                entityCounts[currentFloor][r] += 1;
                            }
                            // F1-R4 has 2 Energy Packs per the PDF
                            if (ch == ENT_ENERGY_PACK && currentFloor == 0 && r == 3)
                            {
                                if (entityCounts[currentFloor][r] < MAX_ENTITIES_PER_ROOM)
                                {
                                    roomEntities[currentFloor][r][entityCounts[currentFloor][r]] = ENT_ENERGY_PACK;
                                    entityCounts[currentFloor][r] += 1;
                                }
                            }
                        }
                    }
                }
            }
                        }
                   }
    
   
    file.close();
    return true;
}

bool loadInitialState(const char* filename,
                      int& playerFloor, int& playerRoom,
                      int& energy, int& time, int& score,
                      char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                      bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft)
{
    ifstream file;
    file.open(filename);
    if (!file)
        return false;

    playerFloor = 1;
    playerRoom = 1;
    energy = INITIAL_ENERGY;
    time = INITIAL_TIME;
    score = INITIAL_SCORE;
    inventoryCount = 0;
    emergencyTripsLeft = 0;

    for (int i = 0; i < MAX_INVENTORY_CAPACITY; i++)
    {
        inventory[i] = ENT_NONE;
    }

    for (int i = 0; i < NUM_OBJECTIVES; i++)
    {
        objectives[i] = false;
    }

    char line[256];
    while (file.getline(line, 256))
    {
        trimWhitespace(line);

        if (strncmp(line, "INITIAL_ENERGY:", 15) == 0)
        {   
            energy = atoi(line + 15);
            if (energy < 0 || energy > MAX_ENERGY)
            return false;
        }
        else if (strncmp(line, "INITIAL_TIME:", 13) == 0)
        {
            time = atoi(line + 13);
            if (time < 0 || time > MAX_TIME)
                return false;
        }
        else if (strncmp(line, "INITIAL_SCORE:", 14) == 0)
         {   score = atoi(line + 14);
            if (score < 0 )
                return false;
        }
    }

    file.close();
    return true;
}

bool validateStartingRoom(int startFloor, int startRoom,
                          const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1])
                          {
                            if (startFloor<1||startFloor>NUM_FLOORS||startRoom<1||startRoom>ROOMS_PER_FLOOR)
                            return false;

                            int conn=0;

                            //left connectioms
                            if(startRoom>1&&(horizontalConn[startFloor-1][startRoom-2]!=CONN_NONE && horizontalConn[startFloor-1][startRoom-2]!=CONN_SOLID_WALL))
                            conn=1;
                            
                            //right connections
                            if(startRoom<ROOMS_PER_FLOOR &&(horizontalConn[startFloor-1][startRoom-1]!=CONN_NONE && horizontalConn[startFloor-1][startRoom-1]!=CONN_SOLID_WALL))
                            conn=1;

                            if (conn==0)
                            return false;

                            return true;


                          }


const char* getEntityName(char entitySymbol)
{
    if (entitySymbol==ENT_MASTER_KEY)
    return "master key";
        
    else if (entitySymbol==ENT_ENERGY_PACK)
        return "energy pack";
        
    else if (entitySymbol ==ENT_EMERGENCY_TOOLKIT)
        return "emergency toolkit";
        
    else if (entitySymbol==ENT_CLUE_4)
        return "clue digit 4";
        
    else if (entitySymbol==ENT_FUSE)
        return "fuse";
        

    else if (entitySymbol== ENT_CAT)
        return "cat";
        
    else if (entitySymbol==ENT_CONTROL_PANEL)
            return "control panel";
        
    else if (entitySymbol==ENT_LIFT_PASS)
        return "lift pass";
        
    else if (entitySymbol==ENT_PASSENGER)
        return "injured passenger";
        
    else if (entitySymbol==ENT_MEDICAL_KIT)
        return "medical kit";
        
    else if (entitySymbol==ENT_EMERGENCY_CARD)
        return "emergency access card";
        
    else if (entitySymbol==ENT_CLUE_2)
        return "clue digit 2";
        
    else if (entitySymbol==ENT_CLUE_7)
        return "clue digit 7";
        

    else if (entitySymbol==ENT_CABINET_TRAIN_KEY)
        return "cabinet /train key";
        
    else if (entitySymbol==ENT_CAT_CARRIER)
            return "cat carrier";
        
    else if (entitySymbol== ENT_OBSERVATION_TOKEN)
        return "observation token";
        
    else

        return "unknown";
}
