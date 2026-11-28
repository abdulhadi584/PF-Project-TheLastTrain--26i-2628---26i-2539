#include "level.h"
#include "util.h"
#include <fstream>
#include<cstring>
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
                        while(file.getline(line,256))
                        {
                            if(strstr(line,"F1-R")!=nullptr || strstr(line,"F2-R")!=nullptr || strstr(line,"F3-R")!=nullptr || strstr(line,"F4-R")!=nullptr || strstr(line,"F5-R")!=nullptr)
                            {
                                for(int i=0;line[i]!='\0';i++)
                                {
                                        
                                    if((line[i]=='F')&&(line[i+1]>='1' && line[i+1]<='5')&&(line[i+2]=='-')&&(line[i+3]=='R')&&(line[i+4]>='1' && line[i+4]<='4'))
                                    {
                                        int floor,room;
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
                                
                            }





                           roomEntities[floor][room][entityCounts[floor][room]]=entitySymbol;
                           entityCounts[floor][room]++; 
                        }