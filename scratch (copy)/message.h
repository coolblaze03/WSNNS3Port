#pragma once
#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

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


        enum MESSAGE_TYPES{
	        TREESETUP = 0,
	        MYPATH = 1,
	        HELLO = 2,
	        DATA = 3,
	        MAXLEVELANNOUNCE = 4,
	        MAXLEVELRESET = 5,
	        LOST = 6,
	        LIFEPROBE = 7,
	        LIFERESPONSE = 8,
	        SINKSHIFT = 9
        };

class message{
        public:
	        message(){
		        networkResetTime = -1;

		        this->alive = true;
		        this->flooding =false;
		        this->maxLevel = -1;
		        this->networkResetTime = -1;
		        this->nextSink = -1;
		        this->oldLevel = -1;
		        this->originator = -2;
		        this->originatorLevel = -2;
		        this->path.clear();
		        this->receiver =  -2;
		        this->sender = -2;
		        this->sequence = -2;
		        this->suspect = -2;
		        this->finalReceiver = -2;
		        this->type = HELLO;
		        this->data = "";
		        sinkAddress = Ipv4Address("000.000.000.001");
		        update=false;
		        x = -1;
		        y = -1;
		        skip = false;
		        newParent = -2;
	        }

            message(uint8_t * packetdata){

            	message();

            	string out(reinterpret_cast<const char *>(packetdata));
            	int counter = 0;

            	int stringlength = out.length();
            	stringlength = stringlength + 1 - 1;
            	char * test = (char*)out.c_str();
            	test[0] = test[0];



					if (atoi(out.substr(counter,1).c_str()) == 0) //1
							this->alive = false;
					else
							this->alive = true;

					counter += 1;//1

					if (atoi(out.substr(counter,1).c_str()) == 0) //1
							this->flooding = false;
					else
							this->flooding = true;

					counter += 1;

					this->maxLevel = atoi(out.substr(counter,3).c_str());

					counter += 3;

					this->networkResetTime =  atoi(out.substr(counter,3).c_str());

					counter += 3;

					this->nextSink =  atoi(out.substr(counter,3).c_str());

					counter += 3;

					this->oldLevel =  atoi(out.substr(counter,3).c_str());

					counter += 3;

					this->originator =  atoi(out.substr(counter,3).c_str());

					counter += 3;

					this->originatorLevel =  atoi(out.substr(counter,3).c_str());

					counter += 3;

					this->receiver =  atoi(out.substr(counter,3).c_str());

					counter += 3;

					this->sender =  atoi(out.substr(counter,3).c_str());

					counter += 3;

					this->sequence =  atoi(out.substr(counter,6).c_str());

					counter += 6;

					this->suspect =  atoi(out.substr(counter,3).c_str());

					counter += 3;

					int mytype = (atoi(out.substr(counter,2).c_str()));

					switch (mytype){

					case 0:
						type = TREESETUP;
						break;
					case 1:
						type = MYPATH;
						break;
					case 2:
						type = HELLO;
						break;
					case 3:
						type = DATA;
						break;
					case 4:
						type = MAXLEVELANNOUNCE;
						break;
					case 5:
						type = MAXLEVELRESET;
						break;
					case 6:
						type = LOST;
						break;
					case 7:
						type = LIFEPROBE;
						break;
					case 8:
						type = LIFERESPONSE;
						break;
					case 9:
						type = SINKSHIFT;
						break;

					}

					counter += 2;

					this->finalReceiver =  atoi(out.substr(counter,3).c_str());

					counter += 3;

					if (atoi(out.substr(counter,1).c_str()) == 0) //1
							this->update = false;
					else
							this->update = true;

					counter += 1;

					this->x = atoi(out.substr(counter,3).c_str());

					counter += 3;

					this->y = atoi(out.substr(counter,3).c_str());

					counter += 3;

					if (atoi(out.substr(counter,1).c_str()) == 0) //1
							this->skip = false;
					else
							this->skip = true;

					counter += 1;

					this->newParent = atoi(out.substr(counter,3).c_str());

					counter += 3;

					int pathsize = atoi(out.substr(counter,4).c_str());

					counter += 4;

					if (pathsize > 0){

						for (int i = 0; i < pathsize ; i++){

							int step = atoi(out.substr(counter,3).c_str());
							counter += 3;
							path.push_back(step);
						}

					}



					int childrensize = atoi(out.substr(counter,4).c_str());

					counter += 4;

					if (childrensize > 0){

						for (int i = 0; i < childrensize ; i++){

							int step = atoi(out.substr(counter,3).c_str());
							counter += 3;
							children.insert(step);
						}

					}

					int neighborsize = atoi(out.substr(counter,4).c_str());

					counter += 4;

					if (neighborsize > 0){

						for (int i = 0; i < neighborsize ; i++){

							int step = atoi(out.substr(counter,3).c_str());
							counter += 3;
							neighbors.insert(step);
						}

					}



					this->sinkAddress =  Ipv4Address(out.substr(counter,15).c_str());
					counter += 15;


					data = out.substr(counter);

	        }

	        bool alive;
	        bool flooding;
	        int maxLevel;
	        int networkResetTime;
	        int nextSink;
	        int oldLevel;
	        int originator;
	        int originatorLevel;
	        //int path[30];
	        vector<NODE_ID> path;
	        int receiver; //ALL == -1
	        int sender; 
	        int sequence; //Random num for message id
	        int suspect;
	        string data;
	        int finalReceiver;
	        bool update;
	        int x;
	        int y;
	        int newParent;
	        bool skip;
	        Ipv4Address sinkAddress;
	        MESSAGE_TYPES type;
	        set<NODE_ID> children;
	        set<NODE_ID> neighbors;

	        message& operator=(const message &rhs){
		        this->alive = rhs.alive;
		        this->flooding = rhs.flooding;
		        this->maxLevel = rhs.maxLevel;
		        this->networkResetTime = rhs.networkResetTime;
		        this->nextSink = rhs.nextSink;
		        this->oldLevel = rhs.oldLevel;
		        this->originator = rhs.originator;
		        this->originatorLevel = rhs.originatorLevel;
		        this->path.clear();

		        /*vector<int>::iterator it;
				it = rhs.path.begin();
				for (it = rhs.path.begin(); it != rhs.path.end(); it++){
					this->path.push_back((*it));
				}*/

		        this->path = rhs.path;
		        this->receiver = rhs.receiver;
		        this->sender = rhs.sender;
		        this->sequence = rhs.sequence;
		        this->suspect = rhs.suspect;
		        this->type = rhs.type;
		        this->data = rhs.data;
		        this->finalReceiver = rhs.finalReceiver;
		        update = rhs.update;
		        x = rhs.x;
		        y = rhs.y;
		        children = rhs.children;
		        skip = rhs.skip;
		        newParent = rhs.newParent;
		        neighbors = rhs.neighbors;
		        sinkAddress = rhs.sinkAddress;
		        return *this;
	        }

                string ZeroPadNumber(int num, int len)
                {
	                stringstream ss;
	
	                // the number is converted to string with the help of stringstream
	                ss << num; 
	                string ret;
	                ss >> ret;
	
	                // Append zero chars
	                int str_length = ret.length();
	                for (int i = 0; i < len - str_length; i++)
		                ret = "0" + ret;

	                int fin_str_length = ret.length();
	                if (fin_str_length != len){
	                	int sdkfsdf= 0;
	                	sdkfsdf+=0;
	                }
	                return ret;
                }

                string formatAddy(uint32_t ad32){
                	std::ostringstream os;
                	string out = "";
                	os << ZeroPadNumber(((ad32 >> 24) & 0xff),3) << "."
                	<< ZeroPadNumber(((ad32 >> 16) & 0xff),3) << "."
                	<< ZeroPadNumber(((ad32 >> 8) & 0xff),3) << "."
                	<< ZeroPadNumber(((ad32 >> 0) & 0xff),3);
                	out = os.str();
                	return out;

                }

                string Output(){
                        string out = "";
                        
                        if (this->alive == true) //1 0
                                out += "1";
                        else
                                out += "0";

                        if (this->flooding == true) //1 1
                                out += "1";
                        else
                                out += "0";
                        
                        if (this->maxLevel >= 0) //3 2
                                 out += ZeroPadNumber(this->maxLevel,3); 
                        else
                                 out += ZeroPadNumber(0,3);
                        
                        if (this->networkResetTime >= 0) //3 5
                                 out += ZeroPadNumber(this->networkResetTime,3); 
                        else
                                 out += ZeroPadNumber(0,3);

                        if (this->nextSink >= 0) //3 8
                                 out += ZeroPadNumber(this->nextSink,3); 
                        else
                                 out += ZeroPadNumber(0,3);
                        
                        if (this->oldLevel >= 0) //3 12
                                 out += ZeroPadNumber(this->oldLevel,3); 
                        else
                                 out += ZeroPadNumber(0,3);

                        if (this->originator >= 0) //3 15
                                 out += ZeroPadNumber(this->originator,3); 
                        else
                                 out += ZeroPadNumber(0,3);

                        if (this->originatorLevel >= 0) //3 18
                                 out += ZeroPadNumber(this->originatorLevel,3); 
                        else
                                 out += ZeroPadNumber(0,3);

                        if (this->receiver >= 0) //3 21
                                 out += ZeroPadNumber(this->receiver,3); 
                        else
                                 out += ZeroPadNumber(0,3);

                        if (this->sender >= 0) //3 24
                                 out += ZeroPadNumber(this->sender,3); 
                        else
                                 out += ZeroPadNumber(0,3);

                        if (this->sequence >= 0) //6 27
                                 out += ZeroPadNumber(this->sequence,6); 
                        else
                                 out += ZeroPadNumber(0,6);

                        if (this->suspect >= 0) //3 33
                                 out += ZeroPadNumber(this->suspect,3); 
                        else
                                 out += ZeroPadNumber(0,3);

                        if (this->type >= 0) //2 36
                                 out += ZeroPadNumber(this->type,2); 
                        else
                                 out += ZeroPadNumber(0,2);

                        if (this->finalReceiver >= 0) //3 38
                                 out += ZeroPadNumber(this->finalReceiver,3); 
                        else
                                 out += ZeroPadNumber(0,3);
		        
                        if (this->update == true) //1 41
                                out += "1";
                        else
                                out += "0";

                        if (this->x >= 0) //3 42
                                 out += ZeroPadNumber(this->x,3); 
                        else
                                 out += ZeroPadNumber(0,3);

                        if (this->y >= 0) //3 45
                                 out += ZeroPadNumber(this->y,3); 
                        else
                                 out += ZeroPadNumber(0,3);
                
                        if (this->skip == true) //1 49
                                out += "1";
                        else
                                out += "0";

                        if (this->newParent >= 0) //3 50
                                 out += ZeroPadNumber(this->newParent,3); 
                        else
                                 out += ZeroPadNumber(0,3);


                        //Path
                        if (this->path.size() >= 0) //4 length of path data number of entries * 3       4 53
                                 out += ZeroPadNumber(this->path.size(),4);
                        else
                                 out += ZeroPadNumber(0,4);

                        int p = path.size();

	                for (int i = 0; i < p ; i++){
		                int val = path[i];
		                out += ZeroPadNumber(val,3);
	                }

                        
                        //Children
                        if (this->children.size() >= 0) //4 length of path data number of entries * 3
                                 out += ZeroPadNumber(this->children.size(),4);
                        else
                                 out += ZeroPadNumber(0,4);

                        p = children.size();

                        set<NODE_ID>::iterator it;

                        if (p > 0){

							for( it = children.begin(); it != children.end(); it++ ) {
									//cout << it-＞num << "\t" << it-＞name << endl;
									int val = *it;
							out += ZeroPadNumber(val,3);
							}
                        }

	               // for (int i = 0; i < p ; i++){
		        //        int val = children[i];
		        //        out += ZeroPadNumber(val,3);
	                //}

                        //Neighbors
                        if (this->neighbors.size() >= 0) //4 length of path data number of entries * 3
                                 out += ZeroPadNumber(this->neighbors.size(),4);
                        else
                                 out += ZeroPadNumber(0,4);

                        p = neighbors.size();

	                //for (int i = 0; i < p ; i++){
		        //        int val = neighbors[i];
		        //        out += ZeroPadNumber(val,3);
	                //}
                        if (p > 0){
							for( it = neighbors.begin(); it != neighbors.end(); it++ ) {
									//cout << it-＞num << "\t" << it-＞name << endl;
									int val = *it;
							out += ZeroPadNumber(val,3);
							}
                        }

                        //if (sinkAddress != Ipv4Address("000.000.000.000")){
                        	out += formatAddy(sinkAddress.Get());
                        //}else{
                        	//out += ZeroPadNumber(0,3) + "." + ZeroPadNumber(0,3)+ "." + ZeroPadNumber(0,3)+ "." + ZeroPadNumber(0,3) ;
                        //}

                        //Data
                        //if (this->data >= 0) //4 length of path data number of entries * 3
                       //          out += ZeroPadNumber(this->data.size(),4); 
                        //else
                         //        out += ZeroPadNumber(0,4);

                        //p = neighbors.size();

	                //for (int i = 0; i < p ; i++){
		                //int val = neighbors[i];
		        out += data;
	                //}


                        return out;


                }                


        };

}

#endif

