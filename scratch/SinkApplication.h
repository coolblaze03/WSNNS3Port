#pragma once
#ifndef SINKAPPLICATION_H_INCLUDED
#define SINKAPPLICATION_H_INCLUDED

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store-module.h"
#include "ns3/wifi-module.h"
#include "ns3/energy-module.h"
#include "ns3/internet-module.h" 
#include "ns3/olsr-routing-protocol.h"

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
#include "wsnsinknode.h"
#include "wsnsensornode.h"
#include "neighbor.h"
#include "circle.h"



using namespace ns3;


namespace ns3 {  

//NS_LOG_COMPONENT_DEFINE ("SinkApp");

class SinkApplication:public Application{
                
        protected:
          virtual void DoDispose (void){
                Application::DoDispose ();
          }

        private:
          std::map< Ptr<Socket>, Ipv4InterfaceAddress > m_socketAddresses;

          Ptr<WSNSinkNode> SinkNodePtr;



          virtual void StartApplication (void){
                
		    
		    
		    if (m_socket == 0)
                    {
                      NS_LOG_INFO ("Sink Make Socket");
                      TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
                      m_socket = Socket::CreateSocket (GetNode (), tid);
                      m_socket->SetAllowBroadcast(true);
                      InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
                      m_socket->Bind (local);

                      Ptr<Ipv4> m_ipv4 = DynamicCast <WSNSinkNode> (GetNode())->GetObject<Ipv4>();
                      m_socket->BindToNetDevice (m_ipv4->GetNetDevice (1));
                      m_socketAddresses[m_socket] = m_ipv4->GetAddress (1, 0);
                      NS_LOG_INFO ("Sink End Socket");
                    }

               

                  SinkNodePtr = DynamicCast <WSNSinkNode> (GetNode());
		  
                  NS_LOG_INFO (SinkNodePtr->NodeID <<  " Startring: " <<Simulator::Now ().GetSeconds());


                  Ptr<WSNSinkNode> SinkNode = SinkNodePtr;

		//Ptr<Socket> sock = SinkNode->GetObject<Socket>(); 

		    //if (sock == 0){
			//NS_LOG_INFO ("Sink Sock Nothing");
		   // }else{
			//NS_LOG_INFO ("Sink Sock Something");
			//m_socket = sock;
		    //}

   m_socket->SetRecvCallback (MakeCallback (&ns3::SinkApplication::HandleReceive, this));

                  if (SinkNode->Active == true){

                	  NS_LOG_INFO ("Power On: "<<SinkNode->NodeID);
                	  powerOn();
                	  	/*message m;
						m.type = TREESETUP;
						m.sender = SinkNode->NodeID;
						m.originator = m.sender;
						m.flooding = true;
						m.sequence = 1;
						m.path.push_back(SinkNode->NodeID);
						SendToChildren(m);*/
                  }


                  double delta = 0.1;//seconds
                  Simulator::Schedule(Seconds(0.0), &ns3::SinkApplication::runCycle,this, delta);
                  Simulator::Schedule(Seconds(0.0), &ns3::SinkApplication::PrintMessageCount,this);

                 
          }

          void runCycle( double deltaTime)
			{


			  //Simulator::Schedule(Seconds(0.0), &ns3::SinkApplication::runCycle,this, deltaTime);
			  Simulator::Schedule(Seconds(deltaTime), &ns3::SinkApplication::runCycle,this, deltaTime);

			  run();
			}

			void run(){

				//NS_LOG_INFO ("Running Run Sink");
				//decrements the sink shift timer if shink shift has been initiated. once it gets to 0 then all nodes have sinkshift and
					//the next sink will be informed that it should proceed. This will be moved to its own function.
					if (SinkNodePtr->sinkShiftTimer > 0){
						SinkNodePtr->sinkShiftTimer--;
					}else if(SinkNodePtr->sinkShiftTimer == 0){
						message m;
						m.type = SINKSHIFT;
						m.originator  = SinkNodePtr->NodeID;
						m.receiver = SinkNodePtr->nextSink;
						m.nextSink = SinkNodePtr->nextSink;
						m.networkResetTime = SinkNodePtr->networkResetTime;
						m.flooding = true;
						SendToChildren(m);
						SinkNodePtr->markAsNotActive = true;
						SinkNodePtr->sinkShiftTimer = -1;
						//processQueues();
						return;//get out early because we still want to go one more loop.

					}

					//once 50 iterations has passed the sink will send out the maxlevelannounce. There is no reason the tree is not setup by then. Maybe.
					if (SinkNodePtr->active && SinkNodePtr->runCount == 51){
						a4();
						SinkNodePtr->initalTreeSize = SinkNodePtr->pathSet.size();
					}

					//if nodes not active then skip normal checks
					if (SinkNodePtr->active == true)
						systemCheck();

					//the node will still process its own queues for messages.
					//processQueues();

					//dont change count if not active.
					if (SinkNodePtr->active == true)
						SinkNodePtr->runCount++;

			}


			void systemCheck(){

				//if it has been marked to not active then active will be set to false.
				if (SinkNodePtr->markAsNotActive == true){
					SinkNodePtr->active = false;
					SinkNodePtr->markAsNotActive = false;
					return;
				}

				if (SinkNodePtr->runTreeSetup == true && SinkNodePtr->shiftCycleCountdown == -1){
					SinkNodePtr->runTreeSetup = false;
					broadcastTreeSetup();
				}else if (SinkNodePtr->runTreeSetup == true){
					SinkNodePtr->shiftCycleCountdown--;
				}


				if (SinkNodePtr->levelUpdateTimer > -1)
					SinkNodePtr->levelUpdateTimer -= 1;

				//once 50 iterations have passed we know whe have the tree. so next we calculate the sink based off of all nodes in tree.
				if ( SinkNodePtr->minCircleCalculated == false){
					calculateNextSink();
				}

				//shifts sink based off of shift rate.
				double val = ((double)SinkNodePtr->curdeletedPaths.size()/ (double)SinkNodePtr->initalTreeSize);// ((double)deletedPaths.size()/ (double)initalTreeSize);//double val = ((double)deletedPaths.size()/ (double)NUMBER_OF_NODES);//initalTreeSize
				if (val > SHIFT_RATE && SinkNodePtr->sinkShiftTimer == -1 && SinkNodePtr->levelUpdateTimer == -1){
			                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              						a7();
				}

			}

          virtual void StopApplication (void){
                  if (m_socket != 0) 
                  {
                    m_socket->Close ();
                    m_socket->SetRecvCallback (MakeNullCallback<void, Ptr<Socket> > ());
                  }
          }

          void SendToChildren (message m){
                Ptr<WSNSinkNode> SinkNode = SinkNodePtr;

                Ptr<Ipv4> cipv4 = SinkNode->GetObject<Ipv4>(); 
                Ipv4InterfaceAddress ciaddr = cipv4->GetAddress (1,0);
               
                for (unsigned int i = 0; i < SinkNode->childrenNodes.GetN(); i++){
                	Ptr<WSNBaseNode> cnode = DynamicCast <WSNBaseNode> (SinkNode->childrenNodes.Get(i));

                     Ptr<Ipv4> ipv4 = SinkNode->childrenNodes.Get(i)->GetObject<Ipv4>(); 
                     Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0);
                     NS_LOG_INFO (SinkNode->NodeID <<  " Sending Packet to: "<< cnode->NodeID);
                     m.receiver = cnode->NodeID;

                     m_socket->Connect (InetSocketAddress (iaddr.GetLocal(),80)); 

                     string mess_output = m.Output();
                     Ptr<Packet> pkt1 = Create<Packet> (reinterpret_cast<const uint8_t*> (mess_output.c_str()), mess_output.length());


                     m_socket->Send (pkt1);
                }
          }

	void SendToNeighbor(message m){


/*
		  Ptr<Ipv4> stack = SinkNodePtr->GetObject<Ipv4> ();
		  Ptr<Ipv4RoutingProtocol> rp_Gw = (stack->GetRoutingProtocol ());
		  Ptr<Ipv4ListRouting> lrp_Gw = DynamicCast<Ipv4ListRouting> (rp_Gw);

		  Ptr<olsr::RoutingProtocol> olsrrp_Gw;

		  for (uint32_t i = 0; i < lrp_Gw->GetNRoutingProtocols ();  i++)
		    {
		      int16_t priority;
		      Ptr<Ipv4RoutingProtocol> temp = lrp_Gw->GetRoutingProtocol (i, priority);
		      if (DynamicCast<olsr::RoutingProtocol> (temp))
			{
			  olsrrp_Gw = DynamicCast<olsr::RoutingProtocol> (temp);
			  vector< RoutingTableEntry > rte = olsrrp_Gw->GetRoutingTableEntries();
			  vector<RoutingTableEntry>::iterator iter;
			  for(iter = rte.begin(); iter != rte.end(); iter++){

				if ((iter)->distance == 1){
					NS_LOG_INFO (SinkNodePtr->NodeID <<  " Sending Packet to: "<< (iter)->destAddr.Get());
					m_socket->Connect (InetSocketAddress ((iter)->destAddr,80));
					string mess_output = m.Output();
					Ptr<Packet> pkt1 = Create<Packet> (reinterpret_cast<const uint8_t*> (mess_output.c_str()), mess_output.length());
					m_socket->Send (pkt1);
				}
				
		          }

			}
		    }

*/


		/*
		          Ptr<Ipv4> stack = SinkNodePtr->GetObject<Ipv4> ();
				  Ptr<Ipv4RoutingProtocol> rp_Gw = (stack->GetRoutingProtocol ());
				  Ptr<Ipv4ListRouting> lrp_Gw = DynamicCast<Ipv4ListRouting> (rp_Gw);

				  Ptr<olsr::RoutingProtocol> olsrrp_Gw;

				  for (uint32_t i = 0; i < lrp_Gw->GetNRoutingProtocols ();  i++)
				    {
				      int16_t priority;
				      Ptr<Ipv4RoutingProtocol> temp = lrp_Gw->GetRoutingProtocol (i, priority);
				      if (DynamicCast<olsr::RoutingProtocol> (temp))
					{

				    	  OlsrState Ols = DynamicCast<olsr::RoutingProtocol> (temp)->GetOlsrState();
				    	  //Ptr<OlsrState> Ols = SinkNodePtr->GetObject<OlsrState> ();
						  NeighborSet CnSet = Ols.GetNeighbors();
						  NeighborSet::iterator iter;
						  for(iter = CnSet.begin(); iter != CnSet.end(); iter++){


								NS_LOG_INFO (SinkNodePtr->NodeID <<  " Sending Packet to: "<< (iter)->neighborMainAddr);//.Get());
								m_socket->Connect (InetSocketAddress ((iter)->neighborMainAddr,80));
								string mess_output = m.Output();
								Ptr<Packet> pkt1 = Create<Packet> (reinterpret_cast<const uint8_t*> (mess_output.c_str()), mess_output.length());
								m_socket->Send (pkt1);


				          }

					}else if (){

					}


				 }

				 */

		  for (std::map<Ptr<Socket>, Ipv4InterfaceAddress>::const_iterator j =
		  m_socketAddresses.begin (); j != m_socketAddresses.end (); j++)
		  {
			string mess_output = m.Output();
			Ptr<Packet> pkt1 = Create<Packet> (reinterpret_cast<const uint8_t*> (mess_output.c_str()), mess_output.length());


			 Ptr<Socket> socket = j->first;
			 Ipv4InterfaceAddress iface = j->second;

			 Ipv4Address destination;
			 if (iface.GetMask () == Ipv4Mask::GetOnes ())
			  {
				destination = Ipv4Address ("255.255.255.255");
			  }
			 else
			  {
				destination = iface.GetBroadcast ();
			  }
			 socket->SendTo (pkt1, 0, InetSocketAddress (destination, 80));

			//Ipv4Address bcast = i->second.GetLocal ().GetSubnetDirectedBroadcast (i->second.GetMask ());
			//NS_LOG_INFO(bcast);
			//m_socket->Connect (InetSocketAddress ((iter)->neighborMainAddr,80));
			//m_socket->Connect (InetSocketAddress (bcast, 80));
			//m_socket->Connect (InetSocketAddress (bcast, 80));
			//m_socket->Send (pkt1);
			//i->first->SendTo (pkt1, 0, InetSocketAddress (bcast, 80));
		  }

	}

	void SendToEveryone(message m){

		  Ptr<Ipv4> stack = SinkNodePtr->GetObject<Ipv4> ();
		  Ptr<Ipv4RoutingProtocol> rp_Gw = (stack->GetRoutingProtocol ());
		  Ptr<Ipv4ListRouting> lrp_Gw = DynamicCast<Ipv4ListRouting> (rp_Gw);

		  Ptr<olsr::RoutingProtocol> olsrrp_Gw;

		  for (uint32_t i = 0; i < lrp_Gw->GetNRoutingProtocols ();  i++)
		    {
		      int16_t priority;
		      Ptr<Ipv4RoutingProtocol> temp = lrp_Gw->GetRoutingProtocol (i, priority);
		      if (DynamicCast<olsr::RoutingProtocol> (temp))
			{
			  olsrrp_Gw = DynamicCast<olsr::RoutingProtocol> (temp);
			  vector< RoutingTableEntry > rte = olsrrp_Gw->GetRoutingTableEntries();
			  vector<RoutingTableEntry>::iterator iter;
			  for(iter = rte.begin(); iter != rte.end(); iter++){
				  NS_LOG_INFO (SinkNodePtr->NodeID <<  " Sending Packet to: "<< (iter)->destAddr.Get());
			        m_socket->Connect (InetSocketAddress ((iter)->destAddr,80));
			     	string mess_output = m.Output();
				Ptr<Packet> pkt1 = Create<Packet> (reinterpret_cast<const uint8_t*> (mess_output.c_str()), mess_output.length());
				m_socket->Send (pkt1);
				
		          }

			}
		    }


	}

          void SendToChildren (void){
                message m;               
                SendToChildren (m);
                 
          }

          void SendToOther (message m){
                                       Ptr<WSNSensorNode> SensorNode = DynamicCast <WSNSensorNode> (GetNode());
                                  Ptr<Ipv4> cipv4 = SensorNode->GetObject<Ipv4>();
                                  Ipv4InterfaceAddress ciaddr = cipv4->GetAddress (1,0);

                                  for (unsigned int i = 0; i < SensorNode->childrenNodes.GetN(); i++){


                                  	Ptr<WSNBaseNode> cnode = DynamicCast <WSNBaseNode> (SensorNode->childrenNodes.Get(i));

                                  	if (cnode->NodeID != m.receiver){
                                  		continue;
                                  	}

                                  	NS_LOG_INFO (SensorNode->NodeID <<  " Sending Packet to: "<< cnode->NodeID);

                                       Ptr<Ipv4> ipv4 = SensorNode->childrenNodes.Get(i)->GetObject<Ipv4>();
                                       Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0);
                                          //NS_LOG_INFO (ciaddr.GetLocal()<<  " Sending Packet to: "<<iaddr.GetLocal());
                                          m_socket->Connect (InetSocketAddress (iaddr.GetLocal(),80));

                                          string mess_output = m.Output();
                  						Ptr<Packet> pkt1 = Create<Packet> (reinterpret_cast<const uint8_t*> (mess_output.c_str()), mess_output.length());


                  						m_socket->Send (pkt1);
                                       //m_socket->Send (Create<Packet> (200));
                                  }

                                  for (unsigned int i = 0; i < SensorNode->neighbors.GetN(); i++){


                                 	 Ptr<WSNBaseNode> cnode = DynamicCast <WSNBaseNode> (SensorNode->neighbors.Get(i));

         							 if (cnode->NodeID != m.receiver){
         									continue;
         						     }
         							 NS_LOG_INFO (SensorNode->NodeID <<  " Sending Packet Parent: "<< cnode->NodeID);


         							 Ptr<Ipv4> ipv4 = SensorNode->Parent->GetObject<Ipv4>();
         							 Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0);
         							 m_socket->Connect (InetSocketAddress (iaddr.GetLocal(),80));
         							 //m_socket->Send (Create<Packet> (200));

         							 string mess_output = m.Output();
         							 Ptr<Packet> pkt1 = Create<Packet> (reinterpret_cast<const uint8_t*> (mess_output.c_str()), mess_output.length());


         							 m_socket->Send (pkt1);
         							 //m_socket->Send (Create<Packet> (200));
                                   }
                            }


          //broadcast of treesetup to neighbors
          void broadcastTreeSetup(){

        	  SinkNodePtr->pathSet.clear();
          	tree<customTreeNode>::iterator top;
          	top=SinkNodePtr->pathSet.begin();
          	customTreeNode tn(SinkNodePtr->NodeID, SinkNodePtr->x, SinkNodePtr->y);
          	SinkNodePtr->nodesintree.push_back(tn);
          	//pathSet.insert(top, 0);
          	SinkNodePtr->pathSet.insert(top, tn);

          	Ptr<Ipv4> myipv4 = SinkNodePtr->GetObject<Ipv4> ();
          	Ipv4InterfaceAddress iaddr = myipv4->GetAddress (1,0);
          	Ipv4Address addri = iaddr.GetLocal ();

          	message m;

          	m.type = TREESETUP;
          	m.originator = SinkNodePtr->NodeID;
          	m.sender  = SinkNodePtr->NodeID;
          	m.receiver = ALL;
          	m.path.clear();
          	m.path.push_back(SinkNodePtr->NodeID);
          	m.flooding = true;
          	m.sequence = SinkNodePtr->setupSequence;
          	m.MiscAddress = addri;
          	SendToNeighbor(m);

          }


          void removeNodeID(int dID){
          	set<int>::iterator it = SinkNodePtr->children.find(dID);
          	if (it != SinkNodePtr->children.end()){
          		SinkNodePtr->children.erase(it);
          	}
          	SinkNodePtr->deletedPaths.insert(dID);
          	SinkNodePtr->curdeletedPaths.insert(dID);//remove later
          }

          //inital clearing of nodes
          void a1(bool sinkShifted = false){
	NS_LOG_INFO ("In A1");

          	if (sinkShifted == false){
          		SinkNodePtr->oneHopNeighbors.clear();
          		SinkNodePtr->children.clear();
          	}

          	//clearQueue(this->childrenInQueue);
          	//clearQueue(this->childrenOutQueue);
          	//SinkNodePtr->pathSet.clear();
          	SinkNodePtr->maxLevel = -1;
          	SinkNodePtr->networkResetTime = -1;
          	SinkNodePtr->setupSequence = SinkNodePtr->getNewSeq();
          	SinkNodePtr->sinkSetupTimer = SINK_SETUP_TIME;
          	SinkNodePtr->countdown(SinkNodePtr->sinkSetupTimer);
          	SinkNodePtr->treeAdjustTimer = -1;
          	SinkNodePtr->testpath.clear();

          	//SinkNodePtr->currenttrees.clear();


          	//SinkNodePtr->curdeletedPaths.clear();

          	SinkNodePtr->runCount = 0;
          	SinkNodePtr->initalTreeSize = -1;

          	for (int i = 0; i<NUMBER_OF_NODES + NUMBER_OF_SINKS;i++)
          		SinkNodePtr->atest[i] = false;

          	if (sinkShifted == false){
          		//broadcastTreeSetup();
          	}else{
          		SinkNodePtr->runTreeSetup = true;
          		SinkNodePtr->shiftCycleCountdown = 5;
          		set<NODE_ID>::iterator it;
          		for ( it = SinkNodePtr->children.begin(); it != SinkNodePtr->children.end(); it++){
          			message m;

          			//Send to Children
          			m.type = SINKSHIFT;
          			m.originator  = SinkNodePtr->NodeID;
          			m.receiver = (*it);
          			m.nextSink = SinkNodePtr->nextSink;
          			m.networkResetTime = SinkNodePtr->networkResetTime;
          			m.flooding = true;
          			SendToChildren(m);


          		}
          	}

          }


          //hello processor
          void a2(message m){

          	vector<neighbor>::iterator it;

          	bool found = false;

          	for (it = SinkNodePtr->oneHopNeighbors.begin(); it != SinkNodePtr->oneHopNeighbors.end();it++){
          		if (((neighbor)*it).ID == m.sender ){
          			found = true;
          			break;
          		}
          	}

          	if (found == false){
          		neighbor t;
          		SinkNodePtr->s = t;
          		SinkNodePtr->s.ID = m.sender;
          		SinkNodePtr->oneHopNeighbors.push_back(SinkNodePtr->s);

          	}else{
          		SinkNodePtr->duplicated.insert(m.sender);
          	}

          }


          //Mypath processor
          void a3(message m){

          	if (m.path[0] != SinkNodePtr->NodeID)
          		return;

          	int ml=SinkNodePtr->maxLevel ;
          	int ps=m.path.size();
          	if (ml< ps){
          		SinkNodePtr->maxLevel = m.path.size();
          	}


          	vector< vector<int> >::iterator findit = find (SinkNodePtr->testpath.begin(), SinkNodePtr->testpath.end(), m.path);

          	if (findit != SinkNodePtr->testpath.end())
          		return;//exits if whats coming in is already in testpath

          	SinkNodePtr->testpath.push_back(m.path);

          	///need to check messages update status to see if it is an updated tree part
          	if (m.update && m.path.size() > 0){

          		int SensorNodeParent = m.newParent;
          		int SensorNode = m.originator;

          		customTreeNode cn;
          		cn.ID = SensorNodeParent;

          		tree<customTreeNode>::iterator treeit = find(SinkNodePtr->pathSet.begin(), SinkNodePtr->pathSet.end(), cn);

          		if (treeit != SinkNodePtr->pathSet.end()){

          			//find in currenttrees
          			vector< tree<customTreeNode> >::iterator vtit;
          			for (vtit = SinkNodePtr->currenttrees.begin(); vtit != SinkNodePtr->currenttrees.end(); vtit++){
          				tree<customTreeNode> curtree = *vtit;
          				tree<customTreeNode>::iterator tsib=curtree.begin();
          				//int cfnid = (*tsib).ID;
          				if ((*tsib).ID == SensorNode){
          					//then append currenttrees entry to treeit

          					customTreeNode dummy;
          					dummy.ID = -999;
          					tree<customTreeNode>::iterator dummyit = SinkNodePtr->pathSet.append_child(treeit,dummy);


          					SinkNodePtr->pathSet.replace(dummyit, curtree.begin());//replaces dummy with tree

          					//int testsize = curtree.size();

          					//undelete subtree from deletednodes;
          					tree<customTreeNode>::breadth_first_iterator delit ;
          					for (delit = curtree.begin_breadth_first(); delit != curtree.end_breadth_first(); delit++){
          						//int tid = (*delit).ID;
          						SinkNodePtr->deletedPaths.erase((*delit).ID);
          						SinkNodePtr->curdeletedPaths.erase((*delit).ID);


          					}

          					SinkNodePtr->currenttrees.erase(vtit);

          					SinkNodePtr->sensorChildren[m.originator] = m.children;
          					SinkNodePtr->sensorNeighbors[m.originator] = m.neighbors;

          					break;
          				}

          			}


          		}else{

          			//SinkNodePtr->childrenInQueue.push(m);
          			SendToChildren(m);

          		}





                  calculateNextSink();//Recalculate clusters.
          		return;

          	}




          	tree<customTreeNode>::iterator top;
          	top=SinkNodePtr->pathSet.begin();

          	vector<int>::iterator vit;
          	vit = m.path.begin();
          	for (vit = m.path.begin(); vit != m.path.end(); vit++){
          		customTreeNode tn(*vit,-1 , -1);
          		SinkNodePtr->atest[*vit] = true;
          		bool found = false;

          		if (tn == *top){
          			found = true;
          			if (tn.ID == m.originator && tn.x == -1 && tn.y == -1){
          				(*top).x = m.x;
          				(*top).y = m.y;
          			}
          			continue;
          		}else{

          			tree<customTreeNode>::sibling_iterator sib=SinkNodePtr->pathSet.begin(top);

          			while(sib!=SinkNodePtr->pathSet.end(top)) {

          				if (*sib == tn){
          					found = true;
          					top = sib;
          					if (tn.ID == m.originator && tn.x == -1 && tn.y== -1){
          						(*top).x = m.x;
          						(*top).y = m.y;
          					}
          					break;
          				}else{
          					found = false;
          				}
          				++sib;

          			}

          			if (found == false)
          			{
          				if (tn.ID == m.originator && tn.x == -1 && tn.y == -1){
          						tn.x = m.x;
          						tn.y = m.y;
          				}
          				SinkNodePtr->nodesintree.push_back(tn);
          				SinkNodePtr->pathSet.append_child(top,tn);
          			}
          		}

          	}

          	SinkNodePtr->sensorChildren[m.originator] = m.children;
          	SinkNodePtr->sensorNeighbors[m.originator] = m.neighbors;


          }


          //Sends max level announce.
          void a4(){


          		message m;

          		m.type = MAXLEVELANNOUNCE;
          		m.originator = SinkNodePtr->NodeID;
          		m.sender  = SinkNodePtr->NodeID;
          		m.receiver = ALL;
          		m.maxLevel = SinkNodePtr->maxLevel;
          		m.flooding = true;
          		m.sequence = SinkNodePtr->setupSequence;
          		SendToChildren(m);
          }

          //lost processor
          void a5(message m){

          	//find
          	markNodesDeleted(m.originator);
          	if (SinkNodePtr->treeAdjustTimer == -1){
          		SinkNodePtr->treeAdjustTimer = TREE_ADJUST_TIME;
          		SinkNodePtr->countdown(SinkNodePtr->treeAdjustTimer);
          	}


          }

          ////tree adjust timer == 0
          void a6(){

        	  SinkNodePtr->networkResetTime = SinkNodePtr->universalClock + TREE_ADJUST_TIME;

				set<NODE_ID>::iterator it;

				//broadcasting to all childern.

				for ( it = SinkNodePtr->children.begin(); it != SinkNodePtr->children.end(); it++){
					message m;

					m.type = MAXLEVELRESET;
					m.sender  = SinkNodePtr->NodeID;
					m.receiver = (*it);
					m.maxLevel = SinkNodePtr->maxLevel;
					m.networkResetTime = SinkNodePtr->networkResetTime;
					m.flooding = true;
					m.sequence = SinkNodePtr->setupSequence;

					SendToChildren(m);
				}



          }

          //Initiates sink shift.
          void a7(){

          	calculateNextSink();

          	if (SinkNodePtr->nextSink == -1)
          		return;


          	SinkNodePtr->networkResetTime = SinkNodePtr->universalClock + TREE_ADJUST_TIME;

          	set<NODE_ID>::iterator it;

          	//broadcasting to all childern.

          	for ( it = SinkNodePtr->children.begin(); it != SinkNodePtr->children.end(); it++){
          		message m;

          		//Send to Children
          		m.type = SINKSHIFT;
          		m.originator  = SinkNodePtr->NodeID;
          		m.receiver = (*it);
          		m.nextSink = SinkNodePtr->nextSink;
          		m.networkResetTime = SinkNodePtr->networkResetTime;
          		m.flooding = true;
          		//SinkNodePtr->childrenOutQueue.push(m);
          		SendToChildren(m);


          	}
          	//This sink shift timer gives children and childrens children ect time for the message to propagate through the tree.
          	SinkNodePtr->sinkShiftTimer = SinkNodePtr->maxLevel;
          }

          void a8(message m){

          	if (m.nextSink != SinkNodePtr->NodeID){
          		return;
          	}


          	if (SinkNodePtr->Active == true)
          		return; //Duplicate Message from network

          	SinkNodePtr->Active = true;



          	char buffer[33];
          	sprintf(buffer, "%d",SinkNodePtr->NodeID);
          	//itoa(ID, buffer, 10);
          	cout<<"New Sink: "<<SinkNodePtr->NodeID<<endl;
          	a1(true);

          }

          void PrintMessageCount(){
        	  Simulator::Schedule(Seconds(120), &ns3::SinkApplication::PrintMessageCount,this);

        		  NS_LOG_UNCOND("NodeID: "<<SinkNodePtr->NodeID << " MessagesR:" << SinkNodePtr->dataMessagesRecieved << " Time:" <<Simulator::Now ().GetSeconds());


          }

          //processes data messages received from nodes.
          void dataProcessor(message m){

          	//vector<int>::iterator seqiterator = find(SinkNodePtr->processedSeq.begin(),SinkNodePtr->processedSeq.end(),m.sequence);
          	//if (seqiterator != SinkNodePtr->processedSeq.end()){
          	//	return;//it should not find it or it has been processed
          	//}

          	//SinkNodePtr->processedSeq.push_back(m.sequence);
          	SinkNodePtr->dataMessagesRecieved++;

          	NS_LOG_INFO("Got data message. originator: "<<m.originator<<" sender:"<<m.sender);


          	//cout<<"Got data message. originator: "<<m.originator<<" sender:"<<m.sender<<endl;
          }


          //power on
          void powerOn(){
          	a1();
          }

          void calcNoSinkShift(){
        	  SinkNodePtr->nextSink = -1;
          }

          //calculates next sink.
          void calculateNextSink(){

          	if (SinkNodePtr->Active){


          		switch (SinkNodePtr->sm){
          			case SHIFT_SINK_NO_SHIFT:
          				calcNoSinkShift();
          				break;
          			case SHIFT_SINK_CIRCLE:
          				calcSinkCircleMethod();
          				break;
          			case SHIFT_SINK_CLUSTER:
          				calcSinkRevisedClusterMethod();
          				break;
          			default:
          				calcSinkCircleMethod();
          				break;

          		}


          	}


          }

          void calcSinkClusterMethod(){
          	//step 1 Calculate nodes below number and inital clusters
          	tree<customTreeNode>::iterator top;
          	top=SinkNodePtr->pathSet.begin();

          	tree<customTreeNode>::iterator sib=SinkNodePtr->pathSet.begin();

          	while(sib!=SinkNodePtr->pathSet.end(top)) {

          		//calc nodes below.
          		(*sib).num_nodes_below = SinkNodePtr->pathSet.size(sib);
          		//int testcount =  (*sib).num_nodes_below;
          		int childcount = sib.number_of_children();
          		if (childcount > 1 && sib != top){
          			//Add Cluster
          			cluster newcluster;
          			newcluster.values.push_back((*sib).ID);

          			tree<customTreeNode>::iterator cpos = sib.node->first_child;

          			while (cpos != sib.node->last_child){
          				newcluster.values.push_back((*cpos).ID);
          				cpos=cpos.node->next_sibling;
          			}

          			SinkNodePtr->clusters.push_back(newcluster);
          		}
          		++sib;

          	}

          	//Adding currenttrees to cluster also. these are trees in which the parent node has been deleted.
          	for (unsigned int i = 0; i < SinkNodePtr->currenttrees.size(); i++){
          		tree<customTreeNode> curtree = SinkNodePtr->currenttrees[i];
          		tree<customTreeNode>::iterator sib=curtree.begin();
          		while(sib!=curtree.end()) {
          			//calc nodes below.
          			(*sib).num_nodes_below = SinkNodePtr->pathSet.size(sib);
          			//int testcount =  (*sib).num_nodes_below;
          			int childcount = sib.number_of_children();
          			if (childcount > 1 && (*sib).ID != (*top).ID){
          				//Add Cluster
          				cluster newcluster;
          				newcluster.values.push_back((*sib).ID);

          				tree<customTreeNode>::iterator cpos = sib.node->first_child;

          				while (cpos != sib.node->last_child){
          					newcluster.values.push_back((*cpos).ID);
          					cpos=cpos.node->next_sibling;
          				}

          				SinkNodePtr->clusters.push_back(newcluster);
          			}
          			++sib;

          		}
          	}

          	//Combine clusters
          	//step two combine parents and kids
          	if (SinkNodePtr->clusters.size() > 1){
          		vector<cluster>::iterator cit = SinkNodePtr->clusters.begin();
          		while(cit != SinkNodePtr->clusters.end()){
          			vector<cluster>::iterator cit2 = SinkNodePtr->clusters.begin();

          			while(cit2 != SinkNodePtr->clusters.end()){

          				if ((*cit).values[0] != ((*cit2).values[0]) && (*cit).isActive() && (*cit2).isActive()){

          					vector<int>::iterator valit = (*cit).values.begin();
          					while(valit != (*cit).values.end()){
          						if ((*cit2).contains(*valit)){
          							(*cit2).combine(*cit);
          							(*cit).setActive(false);
          							break;
          						}
          						valit++;
          					}

          				}
          				cit2++;
          			}
          			cit++;
          		}
          	}

          	clearNotActiveClusters();

          	//step three combine clusters who has a node referenced twice in another clusters children.
          	if (SinkNodePtr->clusters.size() > 1){
          		vector<cluster>::iterator cit = SinkNodePtr->clusters.begin();
          		while(cit != SinkNodePtr->clusters.end()){
          			vector<cluster>::iterator cit2 = SinkNodePtr->clusters.begin();

          			while(cit2 != SinkNodePtr->clusters.end()){

          				if ((*cit).values[0] != ((*cit2).values[0]) && (*cit).isActive() && (*cit2).isActive()){

          					vector<int>::iterator valit = (*cit).values.begin();
          					while(valit != (*cit).values.end()){
          						vector<int>::iterator valit2 = (*cit2).values.begin();
          						int links = 0;
          						while(valit2 != (*cit2).values.end()){
          							if (SinkNodePtr->sensorChildren[*valit2].find(*valit) != SinkNodePtr->sensorChildren[*valit2].end()){
          								links++;
          							}
          							if (links >= 2){
          								//combine
          								(*cit2).combine(*cit);
          								(*cit).setActive(false);
          								break;
          							}
          							valit2++;
          						}
          						valit++;
          					}

          				}
          				cit2++;
          			}
          			cit++;
          		}
          	}

          	clearNotActiveClusters();


          	//
          	int sinkid = -1;
          	int totalclusterreach = 0;
          	for (unsigned int i =0; i < SinkNodePtr->allSinks.size(); i++){
          		//int foundcount = 0;

          		if (SinkNodePtr->allSinks[i]->NodeID != SinkNodePtr->NodeID){


          			vector<cluster>::iterator clusterit;
          			int clusterreach = 0;

          			for (clusterit = SinkNodePtr->clusters.begin(); clusterit != SinkNodePtr->clusters.end(); clusterit++){
          				set<NODE_ID>::iterator childit;
          				for ( childit = SinkNodePtr->allSinks[i]->children.begin(); childit != SinkNodePtr->allSinks[i]->children.end(); childit++){

          					if ((*clusterit).contains(*childit)){
          						clusterreach += (*clusterit).values.size();
          						break;
          					}

          				}
          			}

          			if (clusterreach > totalclusterreach){
          				totalclusterreach = clusterreach;
          				sinkid = SinkNodePtr->allSinks[i]->NodeID;
          			}


          		}
          	}

          	int cnum = 0;
          	//i need to go down an exta level just to determine if it has sufficent node access. using clusters.
          	if (sinkid == -1){
          		for (unsigned int i =0; i < SinkNodePtr->allSinks.size(); i++){
          			//int foundcount = 0;

          			if (SinkNodePtr->allSinks[i]->NodeID != SinkNodePtr->NodeID){



          				//cnum = allSinks[i]->children.size();
          				if ((unsigned int)cnum > SinkNodePtr->allSinks[i]->children.size()){
          					cnum = SinkNodePtr->allSinks[i]->children.size();
          					sinkid = SinkNodePtr->allSinks[i]->NodeID;
          				}


          			}
          		}
          	}


          	if (sinkid == -1){
          		//throw "error";
          		//dont shift just die
          	}

          	//sink with the most reach;
          	SinkNodePtr->nextSink = sinkid;

          	//TODO:Take out and replace with sinkCalculated
          	SinkNodePtr->minCircleCalculated = true;
          }

          void calcSinkRevisedClusterMethod(){
          //This will use my new method that has just not been implemented. Its a take on the old method but uses the data about a node
          //and its neighbors instead of the data just from using the generated tree. This will be tree independent and passed to each sink.

          	//step 1 Calculate nodes below number and inital clusters
        	  SinkNodePtr->clusters.clear();

          	//clusters


          	map<int, set<int> >::iterator sensorneighborit;

          	for (sensorneighborit = SinkNodePtr->sensorNeighbors.begin(); sensorneighborit != SinkNodePtr->sensorNeighbors.end(); sensorneighborit++){
          		int nsize = (*sensorneighborit).second.size();
          		if (nsize >= 3){
          			cluster newCluster;
          			newCluster.values.push_back((*sensorneighborit).first);

          			set<NODE_ID>::iterator neit;
          			for (neit = (*sensorneighborit).second.begin(); neit != (*sensorneighborit).second.end(); neit++){
          				newCluster.values.push_back((*neit));
          			}
          			SinkNodePtr->clusters.push_back(newCluster);
          		}

          	}


          	clearNotActiveClusters();


          	//Combine clusters
          	//step two combine parents and kids
          	if (SinkNodePtr->clusters.size() > 1){
          		vector<cluster>::iterator cit = SinkNodePtr->clusters.begin();
          		while(cit != SinkNodePtr->clusters.end()){
          			vector<cluster>::iterator cit2 = SinkNodePtr->clusters.begin();

          			while(cit2 != SinkNodePtr->clusters.end()){

          				if ((*cit).values[0] != ((*cit2).values[0]) && (*cit).isActive() && (*cit2).isActive()){

          					vector<int>::iterator valit = (*cit).values.begin();
          					while(valit != (*cit).values.end()){
          						if ((*cit2).contains(*valit)){
          							(*cit2).combine(*cit);
          							(*cit).setActive(false);
          							break;
          						}
          						valit++;
          					}

          				}
          				cit2++;
          			}
          			cit++;
          		}
          	}

          	clearNotActiveClusters();

          		//step three combine clusters who has a node referenced twice in another clusters children.
          	if (SinkNodePtr->clusters.size() > 1){
          		vector<cluster>::iterator cit = SinkNodePtr->clusters.begin();
          		while(cit != SinkNodePtr->clusters.end()){
          			vector<cluster>::iterator cit2 = SinkNodePtr->clusters.begin();

          			while(cit2 != SinkNodePtr->clusters.end()){

          				if ((*cit).values[0] != ((*cit2).values[0]) && (*cit).isActive() && (*cit2).isActive()){

          					vector<int>::iterator valit = (*cit).values.begin();
          					while(valit != (*cit).values.end()){
          						vector<int>::iterator valit2 = (*cit2).values.begin();
          						int links = 0;
          						while(valit2 != (*cit2).values.end()){
          							if (SinkNodePtr->sensorNeighbors[*valit2].find(*valit) != SinkNodePtr->sensorNeighbors[*valit2].end()){
          								links++;
          							}
          							if (links >= 2){
          								//combine
          								(*cit2).combine(*cit);
          								(*cit).setActive(false);
          								break;
          							}
          							valit2++;
          						}
          						valit++;
          					}

          				}
          				cit2++;
          			}
          			cit++;
          		}
          	}

          	clearNotActiveClusters();

          	//Find next sink
          	int sinkid = -1;
          	int totalclusterreach = 0;
          	for (unsigned int i =0; i < SinkNodePtr->allSinks.size(); i++){
          		//int foundcount = 0;

          		if (SinkNodePtr->allSinks[i]->NodeID != SinkNodePtr->NodeID){


          			vector<cluster>::iterator clusterit;
          			int clusterreach = 0;



          			for (clusterit = SinkNodePtr->clusters.begin(); clusterit != SinkNodePtr->clusters.end(); clusterit++){
          				//rethink. many child can be in one cluster.
          				set<NODE_ID>::iterator childit;
          				for ( childit = SinkNodePtr->allSinks[i]->children.begin(); childit != SinkNodePtr->allSinks[i]->children.end(); childit++){

          					if ((*clusterit).contains(*childit)){
          						clusterreach += (*clusterit).values.size();
          						break;
          					}

          				}
          			}

          			clusterreach += int((double)SinkNodePtr->allSinks[i]->children.size() * (double)1.5);

          			if (clusterreach > totalclusterreach){
          				totalclusterreach = clusterreach;
          				sinkid = SinkNodePtr->allSinks[i]->NodeID;
          			}


          		}
          	}

          	int cnum = 0;
          	//i need to go down an exta level just to determine if it has sufficent node access. using clusters.
          	if (sinkid == -1){
          		for (unsigned int i =0; i < SinkNodePtr->allSinks.size(); i++){
          			//int foundcount = 0;

          			if (SinkNodePtr->allSinks[i]->NodeID != SinkNodePtr->NodeID){



          				//cnum = allSinks[i]->children.size();
          				if ((unsigned int)cnum > SinkNodePtr->allSinks[i]->children.size()){
          					cnum = SinkNodePtr->allSinks[i]->children.size();
          					sinkid = SinkNodePtr->allSinks[i]->NodeID;
          				}


          			}
          		}
          	}
          	if (sinkid == -1){
          	}

          	//sink with the most reach;
          	SinkNodePtr->nextSink = sinkid;

          	//TODO:Take out and replace with sinkCalculated
          	SinkNodePtr->minCircleCalculated = true;
          }

          void calcSinkCircleMethod(){
          	 //calculate min circle. using current layout.
              Point p[NUMBER_OF_NODES + NUMBER_OF_SINKS];
              Point b[100];
              int count=0;





          	try {

          		//int nitsize = SinkNodePtr->nodesintree.size();
          			vector<customTreeNode>::iterator top = SinkNodePtr->nodesintree.begin();
          		while (top != SinkNodePtr->nodesintree.end()){
          		  p[count] = Point((*top).x,(*top).y);
          		  count++;
          		  ++top;
          		  if (count >= NUMBER_OF_NODES + NUMBER_OF_SINKS){
          			break;
          		  }
          		}




              //get min circle and loads values
              Circle cir = findSec(count, p, 0, b);
              SinkNodePtr->minCircleX = cir.p.getX();
              SinkNodePtr->minCircleY = cir.p.getY();
              SinkNodePtr->minRadius = cir.getRadius();
              SinkNodePtr->minCircleCalculated = true;
              double lowestSinkDist=-1;
              int lowestSinkID = -1;

              //loads sink based on min circle. It uses the closest. but can be another.
              for (unsigned int i =0; i < SinkNodePtr->allSinks.size(); i++){
                if (SinkNodePtr->allSinks[i]->NodeID != SinkNodePtr->NodeID){
                    //get dist from center of circle to to node.



                    double r2 = sqrt(
                        pow(SinkNodePtr->allSinks[i]->x - SinkNodePtr->minCircleX, 2.0) +
                        pow(SinkNodePtr->allSinks[i]->y - SinkNodePtr->minCircleY, 2.0));

                    if ((r2 < lowestSinkDist || lowestSinkDist == -1) && SinkNodePtr->allSinks[i]->oneHopNeighbors.size() > 0){
                        lowestSinkDist = r2;
                        lowestSinkID = SinkNodePtr->allSinks[i]->NodeID;
                    }
                    //keep track of min.

                }
              }

              if (lowestSinkID <= -1){
                //ERROR!!!!!!!!!!!!!!
                //int hill=0;
                throw "No Next Sink Found Could be a Min Circle ERROR";
                exit(1);
              }else{
            	  SinkNodePtr->nextSink = lowestSinkID;
              }

          		}catch (...){
          		cout << "Catch-all hit" << endl;
          	}
          }

          Circle findSec(int n, Point p[], int m, Point b[])
          {
          	Circle sec =  Circle();

          	// Compute the Smallest Enclosing Circle defined by B
          	if(m == 1)
          	{
          		sec = Circle(b[0]);
          	}
          	else if(m == 2)
          	{
          		sec = Circle(b[0], b[1]);
          	}
          	else if(m == 3)
          	{
          		return Circle( b[0], b[1], b[2]);
          	}

          	// Check if all the points in p are enclosed
          	for(int i=0; i<n; i++)
          	{
          		if(sec.contain(p[i]) == 1)
          		{
          			// Compute B <--- B union P[i].
          			b[m] =  Point(p[i]);
          			// Recurse
          			sec = findSec(i, p, m+1, b);
          		}
          	}

          	return sec;
          }

          void clearNotActiveClusters(){
          	//need to clear clusters marked not active
          	vector<cluster>::iterator it = SinkNodePtr->clusters.begin();
          	while (it != SinkNodePtr->clusters.end()){
          		if (!it->isActive()){

          			it = SinkNodePtr->clusters.erase(it);

          		}else{
          			it++;
          		}
          	}
          }

          //marks nodes in the tree as deleted.
          void markNodesDeleted(NODE_ID id){

          		customTreeNode tn(id,-1,-1);
          		tree<customTreeNode>::breadth_first_iterator top;
          		top=SinkNodePtr->pathSet.begin();


           		bool found = false;

          		if (tn == *top){
          			found = true;
          			(*top).active = false;

          		}else{


          			tree<customTreeNode>::breadth_first_iterator sib=SinkNodePtr->pathSet.begin_breadth_first();

          			while(sib!=SinkNodePtr->pathSet.end_breadth_first()) {

          				if (*sib == tn){
          					found = true;
          					(*sib).active = false;

          					top = sib;

          					int belowtest = (*sib).num_nodes_below;

          					/////DELETE FROM CHILDREN OF SENSORS AND SINKS///////////////////
          					for (unsigned int i = 0; i<SinkNodePtr->sensorChildren.size();i++){

          						set<int>::iterator it = SinkNodePtr->sensorChildren[i].find(tn.ID);
          						if (it != SinkNodePtr->sensorChildren[i].end()){
          							SinkNodePtr->sensorChildren[i].erase(it);
          						}

          					}
          					////////////////////////////////////////////////////
          					updateLostSensorNeighbor(tn.ID);
          					/////////////////////////////////////////////////////

          					for (unsigned int i = 0; i < SinkNodePtr->allSinks.size(); i++){
          						set<int>::iterator it = SinkNodePtr->allSinks[i]->children.find(tn.ID);
          						if (it != SinkNodePtr->allSinks[i]->children.end()){
          							SinkNodePtr->allSinks[i]->children.erase(it);
          						}
          					}

          					vector< tree<customTreeNode> > ::iterator vtit;
          					for (vtit = SinkNodePtr->currenttrees.begin(); vtit != SinkNodePtr->currenttrees.end(); vtit++){
          						tree<customTreeNode> curtree = *vtit;
          						tree<customTreeNode>::iterator tsib=curtree.begin();

          						if ((*tsib).ID != tn.ID){
          							SinkNodePtr->currenttrees.erase(vtit);
          							break;
          						}

          					}
          					/////////////////////////////////////////////////////////////////


          					//Im about to test an actual delete
          					tree<customTreeNode> delsubtree = SinkNodePtr->pathSet.subtree(sib, sib.end());

          					//int pitsize = SinkNodePtr->pathSet.size(sib);

          					tree<customTreeNode>::iterator treeit =delsubtree.begin(sib);

          					belowtest = treeit.number_of_children();

          					int counttest = delsubtree.size(sib);

          					///////////////////////////////////////////////
          					tree<customTreeNode>::iterator cpos = sib.node->first_child;
          					int tsizetotal = 0;
          					int savesizetotal = 0;
          					if (belowtest > 0 && counttest > 1){
          						while (true){

          							if (cpos == sib.node->last_child){
          								tree<customTreeNode> sub= delsubtree.subtree(cpos,cpos.end());
          								int subsize = sub.size();
          								//int subsizei = sub.size(cpos);
          								//int id = (*cpos).ID;
          								int nb = (*cpos).num_nodes_below ;
          								tsizetotal += subsize;
          								savesizetotal += nb;
          								SinkNodePtr->currenttrees.push_back(sub);
          								break;
          							}else{
          								tree<customTreeNode> sub = delsubtree.subtree(cpos,cpos.end());
          								int subsize = sub.size();
          								//int subsizei = sub.size(cpos);
          								//int id = (*cpos).ID;
          								int nb = (*cpos).num_nodes_below ;
          								tsizetotal += subsize;
          								savesizetotal += nb;
          								SinkNodePtr->currenttrees.push_back(sub);

          								cpos=cpos.node->next_sibling;
          							}

          						}
          					}


          					counttest = delsubtree.size(sib);

          					tree<customTreeNode>::breadth_first_iterator delit ;
          					for (delit = delsubtree.begin_breadth_first(); delit != delsubtree.end_breadth_first(); delit++){
          						SinkNodePtr->deletedPaths.insert((*delit).ID);
          						SinkNodePtr->curdeletedPaths.insert((*delit).ID);


          					}


          					SinkNodePtr->pathSet.erase_children(sib);
          					SinkNodePtr->pathSet.erase(sib);


          					belowtest = (*treeit).num_nodes_below;

          					counttest = delsubtree.size(sib);




          					this->calculateNextSink(); //calculates new clusters;

          					if (belowtest >= SinkNodePtr->initalTreeSize * 0.7)
          						SinkNodePtr->levelUpdateTimer = SinkNodePtr->maxLevel;

          					break;
          				}

          				++sib;

          			}
          		}

          		//}


          		for (unsigned int i = 0; i < SinkNodePtr->allSinks.size(); i++){
          			SinkNodePtr->allSinks[i]->removeNodeID(id);
          		}
          		///////////////////////////////////////////////////////////////

          		SinkNodePtr->deletedPaths.insert(id);
          		SinkNodePtr->curdeletedPaths.insert(id);
          		return;

          }


          void updateLostSensorNeighbor(int lost_id){
          	//delete node itself
          		map<int,set<int> >::iterator snnit = SinkNodePtr->sensorNeighbors.find(lost_id);//find(sensorNeighbors.begin(), sensorNeighbors.end(), lost_id);

          		if (snnit != SinkNodePtr->sensorNeighbors.end()){
          			SinkNodePtr->sensorNeighbors.erase(snnit);
          		}

          		//delete node contained in other parts.
          		for (unsigned int i = 0; i<SinkNodePtr->sensorNeighbors.size();i++){

          			set<int>::iterator it = SinkNodePtr->sensorNeighbors[i].find(lost_id);
          			if (it != SinkNodePtr->sensorNeighbors[i].end()){
          				SinkNodePtr->sensorNeighbors[i].erase(it);
          			}

          		}
          }

          void HandleReceive (Ptr<Socket> socket){
                Ptr<Packet> packet;
                  Address from;
                  while (packet = socket->RecvFrom (from))
                    {
                      if (InetSocketAddress::IsMatchingType (from))
                        {
                    	  NS_LOG_INFO ("Received " << packet->GetSize () << " bytes from " <<
                                       InetSocketAddress::ConvertFrom (from).GetIpv4 ());





                          packet->RemoveAllPacketTags ();
                          packet->RemoveAllByteTags ();

                          uint8_t * buff = new uint8_t[packet->GetSerializedSize()];

                          packet->CopyData(buff, packet->GetSerializedSize());

                          message m(buff);

                          NS_LOG_INFO ("Type:" <<m.type << " Rec:"<<m.receiver<<  " got Packet from: "<< m.sender );

                          //message m;

                          switch (m.type){
		
		                case TREESETUP:
			                break;
		                case MYPATH:
			                a3(m);
			                break;
		                case HELLO:
			                a2(m);
			                break;
		                case DATA:
			                dataProcessor(m);
			                break;
		                case MAXLEVELANNOUNCE:
			
			                break;
		                case MAXLEVELRESET:
			                break;
		                case LOST:
			                a5(m);
			                break;
		                case LIFEPROBE:
			
			                break;
		                case LIFERESPONSE:
			
			                break;
		                case SINKSHIFT:
			                a8(m);
			                break;

	
	                }

                          //NS_LOG_LOGIC ("Echoing packet");
                          //socket->SendTo (packet, 0, from);
                        }
                    }
          }

          Ptr<Socket> m_socket;
          Ipv4Address m_peerAddress;
          Address m_local;
        };

}

#endif
