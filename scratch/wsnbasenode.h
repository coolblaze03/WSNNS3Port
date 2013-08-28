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
#include <map>
#include <exception>

#include "constants.h"

using namespace ns3;

namespace ns3 {  

class MessageGenerator{
  public:

  	MessageGenerator(int nodecount, const char * filename){//loads set of numbers from a file instead of randomly. For testing
  		this->nodecount = nodecount;
  		srand ( time(NULL) );

  		fn = (char*)filename;
  		myfile.open(filename);

  		//myfile = ifstream (filename);

  	}


  	map<int, bool>  generateRandomMessages(){

  		return generatemessages();

  	}

  static ifstream  myfile;

  private:
  	int nodecount;
  	map<int, bool> generatemessages(){
  		int num_mess_gen = int((double(5)/(double)nodecount) * double(nodecount));
  		map<int, bool> datamap;

  		for (int i = 0; i < num_mess_gen; i++){
  			int rand_node = rand() % NUMBER_OF_NODES;

  			rand_node = getNextint();
  		    datamap[rand_node] = true;

  		}

  		return datamap;
  	}


  	char * fn;

  	int getNextint(){
  		string line;
  		int data = -1;
  		if (myfile.is_open())
  		{
  			if ( myfile.good() )
  			{
  				getline (myfile,line);
  				data = atoi(line.c_str());//istringstream ( line ) >> data;// = (int)line;
  			}else{
  				myfile.close();
  				myfile.open(fn);// = ifstream (fn);
  				data = getNextint();
  			}
  			return data;

  		}
  		return -1;
  	}

  };

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

			static MessageGenerator MG;
			static int CurRunCount;
			static map<int, bool> datamap;
			bool GenerateMessage(int runcount){
				if (CurRunCount == runcount){
					//Already configured for this run
					return datamap[NodeID];
				}else{
					//getvals for this run
					datamap = MG.generateRandomMessages();
					CurRunCount = runcount;
					return datamap[NodeID];
				}

				return false;
			}

			vector<neighbor> oneHopNeighbors;
			set<NODE_ID> children;
		    NodeContainer childrenNodes;
		    NodeContainer neighbors;

        };





  ifstream MessageGenerator::myfile;
  MessageGenerator WSNBaseNode::MG(100,"/home/chabli/RandomNodalOutput.txt");
  int WSNBaseNode::CurRunCount = -1;
  map<int, bool> WSNBaseNode::datamap;


}

#endif
