#pragma once
#ifndef WSNSINKNODE_H_INCLUDED
#define WSNSINKNODE_H_INCLUDED

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
#include "tree.hh"
#include "neighbor.h"

#define NODE_ID int

using namespace ns3;


namespace ns3 {  



 class WSNSinkNode : public WSNBaseNode{
           public:
           WSNSinkNode(){
           
              Active = false;

				if (sinkID >= NUMBER_OF_SINKS + NUMBER_OF_NODES){
					sinkID = SINK_START_ID;
				}
				this->NodeID = sinkID++;
				this->survivedRate=1;
				this->minCircleCalculated = false;
				this->minCircleX = -1;
				this->minCircleY = -1;
				this->minRadius = 0;
				this->runCount = 0;
				allSinks.clear();
				active = false;
				markAsNotActive = false;
				sinkShiftTimer = -1;
				levelUpdateTimer = -1;
				this->runTreeSetup	= false;
				shiftCycleCountdown = -1;
				dataMessagesRecieved = 0;
				this->sensorNeighbors.clear();


           }



           int NodeID;
           bool Active;

           int dataMessagesRecieved;


           tree<customTreeNode> pathSet;
           vector<customTreeNode> nodesintree;



           int nextSink;
			neighbor s;
			bool active;
			bool markAsNotActive;

			set<int> deletedPaths;
			set<int> curdeletedPaths;
			vector<WSNSinkNode*> allSinks;
			int setupSequence;
			double sinkSetupTimer; //-1
			int survivedRate;
			int tempCounter;
			bool minCircleCalculated;
			double minCircleX;
			double minCircleY;
			double minRadius;
			bool atest[NUMBER_OF_NODES + NUMBER_OF_SINKS];
			double treeAdjustTimer;
			int runCount;

			int sinkShiftTimer;
			int levelUpdateTimer;
			bool runTreeSetup;
			int shiftCycleCountdown;
			SHIFT_METHOD sm;
			vector< vector<int> > testpath;
			vector<cluster> clusters;
			vector< tree<customTreeNode> > currenttrees;
			map<int, set<int> > sensorChildren;
			static map<int, set<int> > sensorNeighbors;
			int initalTreeSize;

			int getDataMessageCount(){
				return this->dataMessagesRecieved;
			}

			void addSink(WSNSinkNode* sink){
				this->allSinks.push_back(sink);
			}

			bool isSinkActive(){
				return active;
			}

			void setSinkActiveStatus(bool isactive){
				this->active = isactive;
			}

			int getFoundSensorNodesCount(){
				return testpath.size();
			}

			string getNodeType(){
				return "Sink";
			}

			int getMaxLevel(){
				return this->maxLevel;
			}

			int getNumberOfChildren(){
				return children.size();
			}

			int getNextSinkID(){
				return this->nextSink;
			}

			void removeNodeID(int dID){
				set<int>::iterator it = this->children.find(dID);
				if (it != this->children.end()){
					this->children.erase(it);
				}
				deletedPaths.insert(dID);
				curdeletedPaths.insert(dID);//remove later
			}



           private:



        };






}

#endif
