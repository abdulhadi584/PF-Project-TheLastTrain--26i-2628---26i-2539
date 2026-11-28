#include "simulator.h"
#include "physics.h"
#include "switches.h"
#include "logger.h"
#include "viewer_iface.h"
#include "util.h"

bool handleMoveCommand(int targetFloor, int targetRoom,int& currentFloor, int& currentRoom,int& energy, int& time,
    const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],const char inventory[MAX_INVENTORY_CAPACITY],
     int inventoryCount,int& emergencyTripsLeft, bool lift2Operational)
     {
        if (targetFloor>NUM_FLOORS||targetFloor<1|| currentFloor>NUM_FLOORS||currentFloor<1 ||targetRoom>ROOMS_PER_FLOOR||targetRoom<1||currentRoom>ROOMS_PER_FLOOR||currentRoom<1||
        energy<0||energy>100||time<0||time>100||inventoryCount<0||inventoryCount>MAX_INVENTORY_CAPACITY||emergencyTripsLeft<0||emergencyTripsLeft>3)
        return false;

        if(targetFloor==currentFloor&&targetRoom==currentRoom)
        return false;

        char conntype;
        
        if (!isDirectlyConnected(currentFloor,currentRoom,targetFloor,targetRoom,horizontalConn,conntype))
        return false;

        if (!canTraverse(targetFloor,targetRoom,conntype,inventory,inventoryCount,emergencyTripsLeft,lift2Operational))
        return false;

        if(conntype=='D'||conntype=='L'||conntype=='S')
        {
            applyResourceDelta(energy,time,COST_MOVE_ORDINARY_ENERGY,COST_MOVE_ORDINARY_TIME);
        }

        else if(conntype=='W')
        {
            applyResourceDelta(energy,time,COST_MOVE_WINDOW_ENERGY,COST_MOVE_WINDOW_TIME); 
        }

        else if(conntype=='1'||conntype=='2')
        {
            applyResourceDelta(energy,time,COST_MOVE_LIFT_ENERGY,COST_MOVE_LIFT_TIME);
        }
        else
        return false;

        if(conntype=='2'&&!lift2Operational)
        emergencyTripsLeft-=1;

        currentFloor=targetFloor;
        currentRoom=targetRoom;

        return true;


       }

       bool handleInspectCommand(int currentFloor, int currentRoom,int& energy, int& time,const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
int entityCount,bool objectives[NUM_OBJECTIVES], int& score)
{
if (currentFloor>NUM_FLOORS||currentFloor<1||currentRoom>ROOMS_PER_FLOOR||currentRoom<1||energy<0||energy>100||time<0||time>100||entityCount<0||entityCount>MAX_ENTITIES_PER_ROOM)
return false;
char entity;



    for(int i=0;i<entityCount;i++)
    {
        entity=roomEntities[currentFloor-1][currentRoom-1][i];
       if (entity==ENT_CLUE_4&&!objectives[OBJ_CLUE_4])
       {
        objectives[OBJ_CLUE_4]=true;
        applyScoreDelta(score,SCORE_CLUE_FOUND);
        }

        if (entity==ENT_CLUE_2&&!objectives[OBJ_CLUE_2])
       {
        objectives[OBJ_CLUE_2]=true;
        applyScoreDelta(score,SCORE_CLUE_FOUND);
       }

       if (entity==ENT_CLUE_7&&!objectives[OBJ_CLUE_7])
       {
        objectives[OBJ_CLUE_7]=true;
        applyScoreDelta(score,SCORE_CLUE_FOUND);
       }
    }
    applyResourceDelta(energy,time,COST_INSPECT_ENERGY,COST_INSPECT_TIME);
    

    return true;
  
}
