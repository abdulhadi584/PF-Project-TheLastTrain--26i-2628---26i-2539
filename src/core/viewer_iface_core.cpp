#include "viewer_iface.h"
#include "util.h"

// Terminal UI and dashboard rendering using primitive parameters
void renderDashboard(int playerFloor, int playerRoom, int energy, int time, int score,
                     const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                     int emergencyTripsLeft)
                    {
                        cout<<"Current Floor: "<<playerFloor<<endl;
                        cout<<"Current Room: "<<playerRoom<<endl;
                        cout<<"Energy: "<<energy<<endl;
                        cout<<"Time: "<<time<<endl;
                        cout<<"Score: "<<score<<endl;
                        cout<<"Inventory: ";
                        for(int i=0;i<inventoryCount;i++)
                        {
                            cout<<inventory[i]<<" ";
                        }
                        cout<<endl;
                        cout<<"Emergency Trips Left: "<<emergencyTripsLeft<<endl;
                        cout<<"Number of Items in Inventory: "<<inventoryCount<<endl;
                    }

 void renderRoomDetails(int floor, int room,
                       const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                       int entityCount)
                       {
                        cout<<"Room Details for Floor "<<floor<<", Room "<<room<<":"<<endl;
                        if(entityCount==0)
                        {
                            cout<<"No entities in this room."<<endl;
                        }
                        else
                        {
                            cout<<"Entities in the Room: ";
                            for(int i=0;i<entityCount;i++)
                            {
                                cout<<roomEntities[floor-1][room-1][i]<<" ";
                            }
                            cout<<endl;  
                        }
                        }

void renderAsciiBuilding(int playerFloor, int playerRoom)
{
    cout << "Building Layout (Floor " << playerFloor << ", Room " << playerRoom << "):" << endl;
    for (int floor = NUM_FLOORS; floor >= 1; --floor) {
        cout << "Floor " << floor << ": ";
        for (int room = 1; room <= ROOMS_PER_FLOOR; ++room) {
            if (floor == playerFloor && room == playerRoom) {
                cout << "[X] "; // Player's current location
            } else {
                cout << "[ ] "; // Empty room
            }
        }
        cout << endl;
    }
}
//REVISE THE DISPLAINH OF OBJECTIVES NAMES
void renderObjectivesChecklist(const bool objectives[NUM_OBJECTIVES])
{
    cout << "Objectives Checklist:" << endl;
    for (int i = 0; i < NUM_OBJECTIVES; ++i) {
        cout << "Objective " << (i + 1) << ": " << (objectives[i] ? "Completed" : "Incomplete") << endl;
    }
}