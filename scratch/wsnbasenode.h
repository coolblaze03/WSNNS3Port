#pragma once
#ifndef WSNBASENODE_H_INCLUDED
#define WSNBASENODE_H_INCLUDED

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

using namespace ns3;

namespace ns3 {  

  class WSNBaseNode: public Node{
        public:
        	WSNBaseNode(){
        		if (seedset == false){
					seedset = true;
					srand ( time(NULL) );
				}

				x = getRandomNumber() % FIELD_WIDTH;
				y = getRandomNumber() % FIELD_HEIGHT;
				seqint = 0;
        	}
        	int NodeID;
            int x;
            int y;
            vector<int> processedSeq;
            int seqint;
            set<NODE_ID> duplicated;
            set<string> d;//data
            int maxLevel;
            double networkResetTime;//-1
            clock_t universalClock;

            int getNewSeq(){
            		stringstream ss;
            		ss << NodeID  << seqint;
            		long int n3 = strtol(ss.str().c_str(), NULL, 10);
            		seqint++;
            		return n3;
            	}

        	void countdown(double miliseconds){
        		clock_t endwait;
        	    endwait = clock () + miliseconds * (CLOCKS_PER_SEC/1000) ;
        	    while (clock() < endwait) {}
        	}

        	int getRandomNumber(){
        		return rand();
        	}

        	string virtual getNodeType(){
        		return "";
        	}

        	NODE_ID virtual getParent(){
        		return -2;
        	}
			int virtual getPower(){
				return -2;
			}

			vector<neighbor> oneHopNeighbors;
			set<NODE_ID> children;
		    NodeContainer childrenNodes;
		    NodeContainer neighbors;

        };

}

#endif
