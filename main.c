#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "head.h"

int main(){
    //Initial input from user
    printf("How many units of time will the simulation run? ");
    int runtime;
    scanf("%d", &runtime);

    printf("Expected number of arrivals per unit time: ");
    float lrate;
    scanf("%f",&lrate);

    printf("Expected number of departures per unit time: ");
    float trate;
    scanf("%f",&trate);

    // Queues
    Queue *landQue = createQ();               //landing queue
    Queue *takeoffQue = createQ();            //takeoff queue
    Queue *runwayQue = createQ();             //holds the plane currently landing/taking off 

    // Runway status
    bool planeisLanding = false;              //tells if a plane is currently landing
    bool planeisTakingOff = false;            //tells if a plane is currently taking off

    int planeID = 1;                          //sequential plane ID's beginning at 1000  

    // Sizes of queues
    //LQ = landing queue; TQ = takeoff queue
    int maxLQ = 5;                          //max planes in landing queue
    int maxTQ = 5;                          //max planes in takeoff queue
    int LQsize = 0;                         //Planes in landing queue currrently
    int TQsize = 0;                         //Planes in takeoff queue currently            

    // Time counting variables
    float landingQTime = 0;                  //total minutes spent in landing queue (all planes)
    float takeoffQTime = 0;                  //total minutes spent in takeoff queue (all planes)
    float idleTime = 0;                      // Amount of time runway was idle

    // Plane counting variables
    int planesLanded = 0;                   //# of planes landed
    int planesTakenOff = 0;                 //# of planes taken off
    int planesRefusedUse = 0;               // Number of planes refused landing or taking off


    /* Simulation START */
    for(int i = 0; i <= runtime; i++){
        float land = (rand()%100 + 1)/100.0;    // Random landing probability
        float toff = (rand()%100 + 1)/100.0;    //Random takeoff probability
        printf("Time: %d\n",i);

        /* Adding planes to landing/take off queues based on probability*/
        //First landing queue
        while(lrate > land){
            // Check if landing queue is full
            if(LQsize == maxLQ)
            {
                printf("Plane %d redirected to another airport\n", planeID);
                planesRefusedUse++;
                break;
            }

            printf("Plane %d ready to land\n", planeID);
            enQueue(landQue, planeID, 0);
            landQue->rear->key = planeID;

            planeID++;
            LQsize++;
            land = (rand()%100 + 1)/100.0;
        }
        //Takeoff queue
        while(trate > toff){
            // Check if landing queue is full
            if(TQsize == maxTQ)
            {
                printf("Plane %d told to try later\n", planeID);
                planesRefusedUse++;
                break;
            }

            printf("Plane %d ready to takeoff\n", planeID);
            enQueue(takeoffQue, planeID, 0);
            takeoffQue->rear->key = planeID;

            planeID++;
            TQsize++;
            toff = (rand()%100 + 1)/100.0;
        }


        /*Landing/taking off flights in the queue*/
        // Runway not empty
        if(!empty(runwayQue))
        {
            if(planeisLanding){
                // Plane takes 1 minute to land. If it was added to queue in previous minute, remove from queue now 
                planesLanded++;
                planeisLanding = false;
                printf("Plane %d landed; in queue %d units\n", runwayQue->front->key, runwayQue->front->time);
                deQueue(runwayQue);
            }

            else if(planeisTakingOff){
                planesTakenOff++;
                planeisTakingOff = false;
                printf("Plane %d took off; in queue %d units\n", runwayQue->front->key, runwayQue->front->time);
                deQueue(runwayQue);
            }
        }
        // Runway empty
        if(empty(runwayQue)){
            if(LQsize!=0){
                enQueue(runwayQue, landQue->front->key, landQue->front->time);
                deQueue(landQue);
                LQsize--;
                planeisLanding = true;
            }
            else if(TQsize!=0){
                enQueue(runwayQue, takeoffQue->front->key, takeoffQue->front->time);
                deQueue(takeoffQue);
                TQsize--;
                planeisTakingOff = true;
            }
        }


        /* Incrementing total times spent in landing and taking off queues*/
        if(i!=runtime)                   
        {
            landingQTime+= size(landQue);
            takeoffQTime+= size(takeoffQue);
            //Increment time for each plane
            incrementTime(landQue);
            incrementTime(takeoffQue);
        }

        // Finally, increment the idle time of runway, if runway idle
        if(empty(runwayQue))
            idleTime+= 1;
    
        printf("\n");
    }  //End of for
    // Simulation ENDS

    // Printing out the conclusion 
    printf("\n\nSimulation has ended\nTotal number of planes processed: %d\n",planeID - 1);
    printf("Number of planes landed: %d\n",planesLanded);
    printf("Number of planes taken off: %d\n",planesTakenOff);
    printf("Number of planes refused use: %d\n", planesRefusedUse);
    printf("Number left ready to land: %d\n", LQsize);
    printf("Number left ready to take off: %d\n",TQsize);
    printf("Percentage of time runway idle: %.2f\n", (idleTime/runtime)*100);
    printf("Average wait time to land: %.2f\n", landingQTime/planesLanded);
    printf("Average wait time to take off: %.2f\n", takeoffQTime/planesTakenOff);
}