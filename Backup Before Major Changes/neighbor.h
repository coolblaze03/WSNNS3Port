#pragma once
#ifndef NEIGHBOR_H_INCLUDED
#define NEIGHBOR_H_INCLUDED

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
        class neighbor{
                public:
	                neighbor(){
                        }
	                
                        int ID;
	                int level;
	                int parent;
	                vector <NODE_ID> pathFromSink;
	
	                neighbor& operator=(const neighbor &rhs){
		                this->ID = rhs.ID;
		                this->level = rhs.level;
		                this->parent = rhs.parent;
		                this->pathFromSink = rhs.pathFromSink;
		                return *this;
	                }

	                inline bool operator == (const neighbor &rhs){
		                return (this->ID == rhs.ID);
	                }




                };

}

#endif
