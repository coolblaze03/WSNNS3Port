#pragma once
#ifndef WSNSENSORNODE_H_INCLUDED
#define WSNSENSORNODE_H_INCLUDED

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store-module.h"
#include "ns3/wifi-module.h"
#include "ns3/energy-module.h"
#include "ns3/internet-module.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <exception>

#include "constants.h"
#include "wsnbasenode.h"
#include "neighbor.h"


#define NODE_ID int

using namespace ns3;


namespace ns3 {  

        class WSNSensorNode : public WSNBaseNode
        {

           public:     

           WSNSensorNode(){
           
              //Test
              dead = false;
              level = -1;

              	power = -1;
              	seqint = 0;
              	disconnected = true;
              	runcycles = false;
              	pathFromSink.clear();
              	//sleep = false;
                
           }
           Ipv4Address sinkAdd;

           bool dead;

           Ptr<WSNBaseNode> Parent;
           int parent;
           int level;
           vector<neighbor> backupParents;
           vector<NODE_ID> pathFromSink;
           bool disconnected;
           int power;

       	double nodeSetupTimer;
       	double wakeUpTimer;
       	double childrenTransimissionTimer;
       	double parentTransmissionTimer;
       	double parentReceptionTimer;
       	double childernReceptionTimer;
       	double sleepTimer;
       	set<NODE_ID> returnedChildren;
           neighbor h;
           neighbor s;
           int cnum;
           int MaxLevelAnnounceCountDown;
           bool runcycles;



                int getNewSeq(){
                        return 999999; //should be a random int.
                }

                string getNodeType(){
					return "Sensor";
				}

                bool isCycleRunning(){
                		return runcycles;
                	}

        };

}

#endif
