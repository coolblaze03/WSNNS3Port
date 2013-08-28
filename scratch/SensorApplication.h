#pragma once
#ifndef SENSORAPPLICATION_H_INCLUDED
#define SENSORAPPLICATION_H_INCLUDED

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
#include "wsnsensornode.h"
#include "wsnsinknode.h"
#include "neighbor.h"
#include "simplerouting.h"



using namespace ns3;


namespace ns3 {  

//NS_LOG_COMPONENT_DEFINE ("SensorApp");

   class SensorApplication:public Application{
        protected:
          virtual void DoDispose (void){
                Application::DoDispose ();
          }

        private:
          std::map< Ptr<Socket>, Ipv4InterfaceAddress > m_socketAddresses;
          Ptr<WSNSensorNode> SensorNodePtr;

          virtual void StartApplication (void){

		
                if (m_socket == 0)
                    {
                        
                      TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
                      m_socket = Socket::CreateSocket (GetNode (), tid);
                      m_socket->SetAllowBroadcast(true);
                      InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
                      m_socket->Bind (local);


                      Ptr<Ipv4> m_ipv4 = DynamicCast <WSNSensorNode> (GetNode())->GetObject<Ipv4>();
					  m_socket->BindToNetDevice (m_ipv4->GetNetDevice (1));
					  m_socketAddresses[m_socket] = m_ipv4->GetAddress (1, 0);

					  //m_socketAddresses[m_socket] = m_ipv4->GetAddress (1, 0);
                        
                    }

                  SensorNodePtr = DynamicCast <WSNSensorNode> (GetNode());

                  counter = 0;


		    Ptr<WSNSensorNode> SensorNode = SensorNodePtr;
		   // Ptr<Socket> sock = SensorNode->GetObject<Socket>(); 
		    //Ptr<NetDevice> nd = SensorNode->GetObject<NetDevice>(); 
  /*NS_LOG_INFO ("NEW CALLBACK S");
		    //nd->SetReceiveCallback( MakeCallback( &ns3::SensorApplication::received, this ) );
		    Ptr<Ipv4> cipv4 = SensorNode->GetObject<Ipv4>(); 
		    Ptr<NetDevice> nd = cipv4->GetNetDevice(0);
		    nd->SetReceiveCallback( MakeCallback( &ns3::SensorApplication::received, this ) );
		    
		    RouteInput (packet, ipHeader, device,
		    MakeCallback (&Ipv4L3Protocol::IpForward, this),
		    MakeCallback (&Ipv4L3Protocol::IpMulticastForward, this),
		    MakeCallback (&Ipv4L3Protocol::LocalDeliver, this),
		    MakeCallback (&Ipv4L3Protocol::RouteInputError, this))


  NS_LOG_INFO ("NEW CALLBACK E");
		    if (sock == 0){
			NS_LOG_INFO ("Sink Sock Nothing");
		    }else{
			NS_LOG_INFO ("Sink Sock Something");
			m_socket = sock;
		    }*/

		  m_socket->SetRecvCallback (MakeCallback (&ns3::SensorApplication::HandleReceive, this));
		  NS_LOG_INFO (SensorNodePtr->NodeID <<  " Startring: " <<Simulator::Now ().GetSeconds());

                  powerOn();

                  double delta = 0.1;//seconds
                  double delay = 60*5;//seconds
                  //Simulator::Schedule<(void *)(int), this, int> (Seconds(0.0), &ns3::SensorApplication::runCycle,this, delta);
                  Simulator::Schedule(Seconds(0.0), &ns3::SensorApplication::runCycle,this, delta);
                  Simulator::Schedule(Seconds(0.0), &ns3::SensorApplication::RemainingEnergy,this, delay);
                  Simulator::Schedule(Seconds(0.0), &ns3::SensorApplication::SendRandomMessage,this);
          }

	// callback function - called whenever a MAC packet arrives
	bool received( Ptr<NetDevice> device, Ptr<const Packet> packet, uint16_t protocol, const Address& sourceAddress) {
		cout << "Test Test Test";
		return true;
	}


          void runCycle( double deltaTime)
          {


            Simulator::Schedule(Seconds(deltaTime), &ns3::SensorApplication::runCycle,this, deltaTime);
            //Simulator::Schedule(Seconds(0.0), &ns3::SensorApplication::runCycle,this, deltaTime);

            run();

           // SensorNodePtr->Sleep(Seconds(10));
          }

          uint counter;

          void run(){


        		if (SensorNodePtr->dead)
        			return;
counter++;
        		if (SensorNodePtr->isCycleRunning()) {// run cycles
        			//If the MaxLevelAnnounceCountDown == -1 which means they are all running in sync since it has not recieved notice from the sink on what the levels
        			//are and once the wakeup timer is set and MaxLevelAnnounceCountDown has ended it starts its cycle.
        			if ( SensorNodePtr->MaxLevelAnnounceCountDown == -1 || (SensorNodePtr->wakeUpTimer == 0 && SensorNodePtr->MaxLevelAnnounceCountDown == 0)){



        						//Random Power Consumption to simulate death randomly over time.
        						int myrandom = SensorNodePtr->getRandomNumber() % 1000 + 1;

        						if (myrandom == 7 && SensorNodePtr->pathFromSink.size() != 0 && SensorNodePtr->cnum>50 && SensorNodePtr->maxLevel != -1){



        						}




        					//As long as this node is not dead then process.
        						systemCheck();
        						//processQueues();
        						SensorNodePtr->power -= WAKEUP_ENERY_CONSUMED*4;
        						SensorNodePtr->power -= ENERGY_ACTIVE_LISTENING_AT_RECEIVING*2;
        						SensorNodePtr->cnum++;


        					//If you have gotten into here becasue MaxLevelAnnounceCountDown == -1 then this if will do nothing
        					//If MaxLevelAnnounceCountDown == 0 then it is because wakeuptimer is also 0 then reset wakeuptimer.
        					if (SensorNodePtr->MaxLevelAnnounceCountDown == 0){
        						SensorNodePtr->wakeUpTimer = SensorNodePtr->maxLevel;
        					}

        				}else{

        					//decrement counter. MaxLevelAnnounceCountDown > 0 then do countdown to start wakeuptimer else if it is zero then decrement wakeuptimer.
        					if (SensorNodePtr->MaxLevelAnnounceCountDown > 0 ){
        						SensorNodePtr->MaxLevelAnnounceCountDown--;
        					}else if (SensorNodePtr->MaxLevelAnnounceCountDown == 0){
        						SensorNodePtr->wakeUpTimer--;
        						SensorNodePtr->power -= ENERGY_SLEEP_PROCESSOR_PER_SECOND * (NETWORK_CYCLE/SensorNodePtr->maxLevel);
        					}

        				}


        		}else{//No cycleling

        			systemCheck();
        			//processQueues();
        			//power -= WAKEUP_ENERY_CONSUMED*4;

        			SensorNodePtr->power -= ENERGY_ACTIVE_LISTENING_AT_RECEIVING*2;
        			SensorNodePtr->cnum++;

        		}
          }

          void RemainingEnergy( double delay){
        	  Ptr<EnergySourceContainer> testPtr = SensorNodePtr->GetObject<EnergySourceContainer>();
			  if (testPtr == NULL){
				  int kjsljfw = 0;
					  kjsljfw += 0;
					  return;
			  }else{

			  }
			  int kjsljfw = testPtr->GetN();
			  //int kjsljfw = testPtr->GetRemainingEnergy();
			  kjsljfw += 0;
			  int klsjs = 0;
			  klsjs += 0;

			  Ptr< EnergySource > source = testPtr->Get(0);

			  double remainingenergy = source->GetRemainingEnergy();
			  NS_LOG_UNCOND (SensorNodePtr->NodeID <<  " Remaining Energy: "<< remainingenergy << " Time:" <<Simulator::Now ().GetSeconds() << " Run Counter:" << counter);


			  Simulator::Schedule(Seconds(delay), &ns3::SensorApplication::RemainingEnergy,this, delay);
          }


          void systemCheck(){

        	//Power Depletion Check

            //Ptr<EnergySourceContainer> basicSourcePtr = NULL;//SensorNodePtr->GetObject<EnergySourceContainer>();
            //Ptr<EnergySourceContainer> ESCptr = NULL;//SensorNodePtr->GetObject<EnergySourceContainer>();
        	  Ptr<EnergySourceContainer> testPtr = SensorNodePtr->GetObject<EnergySourceContainer>();
        	  if (testPtr == NULL){
				  int kjsljfw = 0;
					  kjsljfw += 0;
					  return;
			  }else{

			  }

        	  int kjsljfw = testPtr->GetN();
        	  //int kjsljfw = testPtr->GetRemainingEnergy();
			  kjsljfw += 0;
			  int klsjs = 0;
			  klsjs += 0;

			  Ptr< EnergySource > source = testPtr->Get(0);

			  double remainingenergy = source->GetRemainingEnergy();

           /* Ptr<Object> ObjPtr = SensorNodePtr->GetObject<Object>();

            //Object *current = ObjPtr->GetAggregateIterator();
            Object::AggregateIterator iter = ObjPtr->GetAggregateIterator ();

            while (iter.HasNext ())
            {
                  Ptr<const Object> current = iter.Next ();
                  string cname = current->GetInstanceTypeId ().GetName();
                  if (cname == "ns3::EnergySourceContainer"){
                	  int kjsljf = 0;
                	  kjsljf += 0;
                	  Ptr<EnergySourceContainer> escPtr = current->GetObject<EnergySourceContainer>();
                	  if (escPtr == NULL){
                		  int kjsljfw = 0;
                		      kjsljfw += 0;
                	  }else{
                		  int kjsljfw = 0;
                		      kjsljfw += 0;
                	  }
					//ESCptr = DynamicCast <EnergySourceContainer> (current);
					break;
				  }
             }


            //if (ESCptr == NULL)
            //	return;

			*/

            //NS_LOG_INFO (SensorNodePtr->NodeID <<  " Remaining Energy: "<< remainingenergy << " Time:" <<Simulator::Now ().GetSeconds());



          	//if (SensorNodePtr->power <= WAKEUP_ENERY_CONSUMED && SensorNodePtr->dead == false){
          	if (remainingenergy <= WAKEUP_ENERY_CONSUMED && SensorNodePtr->dead == false){
          		char buffer[33];

          		sprintf(buffer, "%d",SensorNodePtr->NodeID);
          		cout<<"Node: "<<buffer<<"Is Dead :"<<tempdeadcounter<<" Messages Sent:"<<messagesSent<< " Time: " <<Simulator::Now ().GetSeconds()<<endl;
          		tempdeadcounter++;
          		a8();
          	}else{
          		//SendRandomMessage();
          	}


          }

          //5% chance to send a random message
          void SendRandomMessage(){
        	  Ptr<EnergySourceContainer> testPtr = SensorNodePtr->GetObject<EnergySourceContainer>();
        	  Ptr< EnergySource > source = testPtr->Get(0);
        	  double remainingenergy = source->GetRemainingEnergy();

        	  if (remainingenergy > 0){
				 Simulator::Schedule(Seconds(0.01), &ns3::SensorApplication::SendRandomMessage,this);

				 //int rnum = SensorNodePtr->getRandomNumber() % 100 + 1;
				// if (rnum == 9 || rnum == 24 || rnum == 46 || rnum == 75 || rnum == 87){
				//	 GenerateDataMessageToSink();
				 //}

				 bool DoSend = SensorNodePtr->GenerateMessage(counter);
				 if (DoSend){
					 GenerateDataMessageToSink();
				 }

				 // if (rnum >= 45 && rnum <= 55){//rnum == 9 || rnum == 24 || rnum == 46 || rnum == 75 || rnum == 87){
				 //				 GenerateDataMessageToSink();
				 //}
        	  }

          }

          int messagesSent;

          void GenerateDataMessageToSink(){
          	if (SensorNodePtr->pathFromSink.size() > 0){
          		message m;
          		m.receiver = SensorNodePtr->parent;
          		m.sender = SensorNodePtr->NodeID;
          		m.originator = SensorNodePtr->NodeID;
          		//m.finalReceiver = SensorNodePtr->pathFromSink[0];
          		m.data = 22;
          		m.path = SensorNodePtr->pathFromSink;
          		m.path.pop_back();
          		m.type = DATA;
          		m.sequence = SensorNodePtr->getNewSeq();

          		SendToSink(m);
          		messagesSent++;

          		SensorNodePtr->power -= ENERGY_SENDING_A_DATA_MESSAGE;
          	}
          }

          virtual void StopApplication (void){
                  if (m_socket != 0) 
                  {
                    m_socket->Close ();
                    m_socket->SetRecvCallback (MakeNullCallback<void, Ptr<Socket> > ());
                  }
          }

           void SendToChildren (void){
                 message m;               
                SendToChildren (m);
           
          }

          void SendToChildren (message m){
                     Ptr<WSNSensorNode> SensorNode = SensorNodePtr;
                Ptr<Ipv4> cipv4 = SensorNode->GetObject<Ipv4>(); 
                Ipv4InterfaceAddress ciaddr = cipv4->GetAddress (1,0);

                for (unsigned int i = 0; i < SensorNode->childrenNodes.GetN(); i++){


                	Ptr<WSNBaseNode> cnode = DynamicCast <WSNBaseNode> (SensorNode->childrenNodes.Get(i));
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
          } 

          void SendToOther (message m){
                              Ptr<WSNSensorNode> SensorNode = SensorNodePtr;
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

          void SendToParent(void){
                message m;               
                SendToChildren (m);
          }

          void SendToParent(message m){
                     Ptr<WSNSensorNode> SensorNode = SensorNodePtr;


                     Ptr<WSNBaseNode> cnode = DynamicCast <WSNBaseNode> (SensorNode->Parent);
                     if (cnode == NULL){
                    	 return;
                     }
                     NS_LOG_INFO (SensorNode->NodeID <<  " Sending Packet Parent: "<< cnode->NodeID);


                     Ptr<Ipv4> ipv4 = SensorNode->Parent->GetObject<Ipv4>();
                     Ipv4InterfaceAddress iaddr = ipv4->GetAddress (1,0);
                     m_socket->Connect (InetSocketAddress (iaddr.GetLocal(),80));
                     //m_socket->Send (Create<Packet> (200));

                     string mess_output = m.Output();
					 Ptr<Packet> pkt1 = Create<Packet> (reinterpret_cast<const uint8_t*> (mess_output.c_str()), mess_output.length());


					 m_socket->Send (pkt1);
          }

      	void SendToNeighbor(message m){


/*
      		  Ptr<Ipv4> stack = SensorNodePtr->GetObject<Ipv4> ();
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
      					NS_LOG_INFO (SensorNodePtr->NodeID <<  " Sending Packet to: "<< (iter)->destAddr.Get());
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
      		Ptr<Ipv4> stack = SensorNodePtr->GetObject<Ipv4> ();
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


      										NS_LOG_INFO (SensorNodePtr->NodeID <<  " Sending Packet to: "<< (iter)->neighborMainAddr);
      										m_socket->Connect (InetSocketAddress ((iter)->neighborMainAddr,80));
      										string mess_output = m.Output();
      										Ptr<Packet> pkt1 = Create<Packet> (reinterpret_cast<const uint8_t*> (mess_output.c_str()), mess_output.length());
      										m_socket->Send (pkt1);


      						          }

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

      	void SendToNeighbor2(message m){



/*

      	Ptr<Ipv4> stack = SensorNodePtr->GetObject<Ipv4> ();
		  Ptr<Ipv4RoutingProtocol> rp_Gw = (stack->GetRoutingProtocol ());
		  Ptr<Ipv4ListRouting> lrp_Gw = DynamicCast<Ipv4ListRouting> (rp_Gw);

		  Ptr<ns3::SimpleRouting::RoutingProtocol> olsrrp_Gw;

		  for (uint32_t i = 0; i < lrp_Gw->GetNRoutingProtocols ();  i++)
			{
			  int16_t priority;
			  Ptr<Ipv4RoutingProtocol> temp = lrp_Gw->GetRoutingProtocol (i, priority);
			  if (DynamicCast<ns3::SimpleRouting::RoutingProtocol> (temp))
			{

				  ns3::SimpleRouting::RoutingProtocol Ols = DynamicCast<ns3::SimpleRouting::RoutingProtocol> (temp)->GetOlsrState();
				  ns3::SimpleRouting::NeighborSet CnSet = Ols.GetNeighbors();
				  ns3::SimpleRouting::NeighborSet::iterator iter;
				  for(iter = CnSet.begin(); iter != CnSet.end(); iter++){


						NS_LOG_INFO (SensorNodePtr->NodeID <<  " Sending Packet to: "<< (iter)->neighborMainAddr);
						m_socket->Connect (InetSocketAddress ((iter)->neighborMainAddr,80));
						string mess_output = m.Output();
						Ptr<Packet> pkt1 = Create<Packet> (reinterpret_cast<const uint8_t*> (mess_output.c_str()), mess_output.length());
						m_socket->Send (pkt1);


				  }

			}


		 }


*/



      	}
	void SendToEveryone(message m){

		  Ptr<Ipv4> stack = SensorNodePtr->GetObject<Ipv4> ();
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
				  NS_LOG_INFO (SensorNodePtr->NodeID <<  " Sending Packet to: "<< (iter)->destAddr.Get());
			        m_socket->Connect (InetSocketAddress ((iter)->destAddr,80));
			     	string mess_output = m.Output();
				Ptr<Packet> pkt1 = Create<Packet> (reinterpret_cast<const uint8_t*> (mess_output.c_str()), mess_output.length());
				m_socket->Send (pkt1);
				
		          }

			}
		    }


	}


	void SendToSink(message m){

		//RoutingProtocol
			/*if (SensorNodePtr->sinkAdd.Get() != 0 && SensorNodePtr->sinkAdd.Get() != 1){
				NS_LOG_INFO (SensorNodePtr->NodeID <<  " Sending Packet to Sink: "<< SensorNodePtr->sinkAdd << " Time:"<<Simulator::Now ().GetSeconds());
			        m_socket->Connect (InetSocketAddress (SensorNodePtr->sinkAdd,80));
			     	string mess_output = m.Output();
				Ptr<Packet> pkt1 = Create<Packet> (reinterpret_cast<const uint8_t*> (mess_output.c_str()), mess_output.length());
				m_socket->Send (pkt1);
			}*/


		 /* Ptr<Ipv4> stack = SensorNodePtr->GetObject<Ipv4> ();
		  Ptr<Ipv4RoutingProtocol> rp_Gw = (stack->GetRoutingProtocol ());
		  Ptr<Ipv4ListRouting> lrp_Gw = DynamicCast<Ipv4ListRouting> (rp_Gw);

		  Ptr<SimpleRouting::RoutingProtocol> srrp_Gw;

		  for (uint32_t i = 0; i < lrp_Gw->GetNRoutingProtocols ();  i++)
			{
			  int16_t priority;
			  Ptr<Ipv4RoutingProtocol> temp = lrp_Gw->GetRoutingProtocol (i, priority);
			  if (DynamicCast<SimpleRouting::RoutingProtocol> (temp))
			  {
				  srrp_Gw = DynamicCast<SimpleRouting::RoutingProtocol> (temp);
				  srrp_Gw->SendToSink(m);
			   }
			}
			*/


		  Ptr<SimpleRouting::RoutingProtocol> srrp_Gw  = SensorNodePtr->GetObject<SimpleRouting::RoutingProtocol> ();
		  srrp_Gw->SendToSink(m);



	}

		

                void a3(message m){
	                int p = m.path.size();


	                //See if path contains redundant paths wich make a loop;
	                set<int> dups; 
	                pair<set<int>::iterator,bool> ret;
	                for (int i = 0; i < p ; i++){
		                ret = dups.insert(m.path[i]);
		                if (ret.second == false){
			                //cout<<"Duplicates in Path"<<endl;
			                return;
		                }
	                }

	                ret = dups.insert(SensorNodePtr->NodeID);
	                if (ret.second == false){
		                //cout<<"Duplicates in Path"<<endl;
		                return;
	                }

	                ///////////////////////////////
	                if (SensorNodePtr->level != -1 && p >= SensorNodePtr->level){
		                neighbor n;
		                n.ID = m.sender;
		                n.pathFromSink = m.path;
		                n.level = m.path.size() - 1;

		                vector<NODE_ID>::iterator it = m.path.end();
		                if (m.path.size() > 0){
				                it--;

			                n.parent = *it;
			                SensorNodePtr->backupParents.push_back(n);
		                }


		                return;
	                }

	                //i added the small protion below to weed out any reception of duplicate messages. It might not be needed but its here for safty. 
	                vector<int>::iterator it;
	                vector<int>::iterator it2;
	                it = m.path.begin();
	                it2 = SensorNodePtr->pathFromSink.begin();
	                while (true){

		                if (it == m.path.end()){
			                return;
		                }
		                if (it2 == SensorNodePtr->pathFromSink.end()){
			                break;
		                }

		                if ((*it) != (*it2)){
			                break;
		                }

		                it++;
		                it2++;
	                }


	                //Testing
	                if (m.path.size() > 0 && SensorNodePtr->pathFromSink.size() > 0 && m.originator == SensorNodePtr->pathFromSink[0] && m.path.size() >= SensorNodePtr->pathFromSink.size()){
		                return;
	                }


	                //cout<<"TreeSetup: "<<ID<<" SINK:"<<m.originator<<endl;

	                //sets level and then removes it if it is a child. 
	                SensorNodePtr->level = p;

	                SensorNodePtr->pathFromSink = m.path;
	                SensorNodePtr->pathFromSink.push_back(SensorNodePtr->NodeID);
	                SensorNodePtr->parent = m.sender;

	                //For ns3 we need to find the parent from the list of neighbornodes and load Parent
	                Ptr<WSNSensorNode> CurSensorNode = SensorNodePtr;

	                for (unsigned int i = 0; i < CurSensorNode->neighbors.GetN(); i++){
	                	  Ptr<WSNSensorNode> NeighborSensorNode = DynamicCast <WSNSensorNode> (CurSensorNode->neighbors.Get(i));

	                	  if (NeighborSensorNode == NULL){

	                		  Ptr<WSNSinkNode> NeighborSinkNode = DynamicCast <WSNSinkNode> (CurSensorNode->neighbors.Get(i));

	                		  if (NeighborSinkNode == NULL){
	                			  continue;
	                		  }else{

	    	                	  try
	    	                	  {
	    	                		  int tempnodeid = NeighborSinkNode->NodeID ;
	    	                		  if (tempnodeid == m.sender){
	    								  CurSensorNode->Parent = NeighborSinkNode;
	    								  break;
	    							  }
	    	                	  }catch (exception& e)
	    	                	  {
	    	                		  cout << e.what() << endl;
	    	                	  }

	    	                	  continue;
	                		  }

	                	  }

	                	  try
	                	  {
	                		  int tempnodeid = NeighborSensorNode->NodeID ;
	                		  int sender = m.sender;
	                		  if (tempnodeid == sender){
								  CurSensorNode->Parent = NeighborSensorNode;
								  int j = 0;
								  j += 1;
								  j = 0;
							  }

	                	  }catch (exception& e)
	                	  {
	                		  cout << e.what() << endl;
	                	  }



					 }

	                SensorNodePtr->children.erase(m.sender);
	                SensorNodePtr->disconnected = false;
	                //Send to kids

	                message m1;

	                m1.type = TREESETUP;
	                m1.originator  = m.originator;
	                m1.sender = SensorNodePtr->NodeID;
	                m1.path = SensorNodePtr->pathFromSink;
	                m1.sequence = m.sequence;
	                m1.flooding = true;
	                SendToChildren(m1);


	                SensorNodePtr->power -= .000066912;

	                //sending to parent;
		                message m2;

		                m2.type = MYPATH;
		                m2.originator  = SensorNodePtr->NodeID;
		                m2.sender = SensorNodePtr->NodeID;
		                m2.path = SensorNodePtr->pathFromSink;
		                m2.sequence = SensorNodePtr->getNewSeq();//m.sequence;
		                m2.flooding = true;
		                m2.x = SensorNodePtr->x;
		                m2.y = SensorNodePtr->y;
		                m2.children =  SensorNodePtr->children;
		                m2.receiver = SensorNodePtr->Parent->NodeID;
		                for (unsigned int i = 0; i < SensorNodePtr->oneHopNeighbors.size();i++){
			                if (SensorNodePtr->oneHopNeighbors.at(i).ID < NUMBER_OF_NODES)
				                m2.neighbors.insert(SensorNodePtr->oneHopNeighbors.at(i).ID);
		                }
		                SendToParent(m2);

		                SensorNodePtr->power -= .000066912;

                }
                vector<int> ProcessedMessages;
                void TreeSetupHandler(message m){
              	                int p = m.path.size();


              	                //See if path contains redundant paths wich make a loop;
              	                set<int> dups;
              	                pair<set<int>::iterator,bool> ret;
              	                for (int i = 0; i < p ; i++){
              		                ret = dups.insert(m.path[i]);
              		                if (ret.second == false){
              			                //cout<<"Duplicates in Path"<<endl;
              			                return;
              		                }
              	                }

              	                ret = dups.insert(SensorNodePtr->NodeID);
              	                if (ret.second == false){
              		                //cout<<"Duplicates in Path"<<endl;
              		                return;
              	                }

              	                ///////////////////////////////
              	                if (SensorNodePtr->level != -1 && p >= SensorNodePtr->level){
              		                neighbor n;
              		                n.ID = m.sender;
              		                n.pathFromSink = m.path;
              		                n.level = m.path.size() - 1;

              		                vector<NODE_ID>::iterator it = m.path.end();
              		                if (m.path.size() > 0){
              				                it--;

              			                n.parent = *it;
              			                SensorNodePtr->backupParents.push_back(n);
              		                }


              		                return;
              	                }






              	                //Testing
              	                if (m.path.size() > 0 && SensorNodePtr->pathFromSink.size() > 0 && m.originator == SensorNodePtr->pathFromSink[0] && m.path.size() >= SensorNodePtr->pathFromSink.size()){
              		                return;
              	                }



              	                //TODO: some calc to see who keeps the sensor. right now last in wins
              	              SensorNodePtr->sinkAdd = m.MiscAddress;

              	                //cout<<"TreeSetup: "<<ID<<" SINK:"<<m.originator<<endl;

              	                //sets level and then removes it if it is a child.
              	                SensorNodePtr->level = p;

              	                SensorNodePtr->pathFromSink = m.path;
              	                SensorNodePtr->pathFromSink.push_back(SensorNodePtr->NodeID);
              	                SensorNodePtr->parent = m.sender;

              	                //For ns3 we need to find the parent from the list of neighbornodes and load Parent
              	               /* Ptr<WSNSensorNode> CurSensorNode = SensorNodePtr;

              	                for (unsigned int i = 0; i < CurSensorNode->neighbors.GetN(); i++){
              	                	  Ptr<WSNSensorNode> NeighborSensorNode = DynamicCast <WSNSensorNode> (CurSensorNode->neighbors.Get(i));

              	                	  if (NeighborSensorNode == NULL){

              	                		  Ptr<WSNSinkNode> NeighborSinkNode = DynamicCast <WSNSinkNode> (CurSensorNode->neighbors.Get(i));

              	                		  if (NeighborSinkNode == NULL){
              	                			  continue;
              	                		  }else{

              	    	                	  try
              	    	                	  {
              	    	                		  int tempnodeid = NeighborSinkNode->NodeID ;
              	    	                		  if (tempnodeid == m.sender){
              	    								  CurSensorNode->Parent = NeighborSinkNode;
              	    								  break;
              	    							  }
              	    	                	  }catch (exception& e)
              	    	                	  {
              	    	                		  cout << e.what() << endl;
              	    	                	  }

              	    	                	  continue;
              	                		  }

              	                	  }

              	                	  try
              	                	  {
              	                		  int tempnodeid = NeighborSensorNode->NodeID ;
              	                		  int sender = m.sender;
              	                		  if (tempnodeid == sender){
              								  CurSensorNode->Parent = NeighborSensorNode;
              								  int j = 0;
              								  j += 1;
              								  j = 0;
              							  }

              	                	  }catch (exception& e)
              	                	  {
              	                		  cout << e.what() << endl;
              	                	  }



              					 }
*/
              	                SensorNodePtr->children.erase(m.sender);
              	                SensorNodePtr->disconnected = false;

              	                //Send to kids

              	                message m1;

              	                m1.type = TREESETUP;
              	                m1.originator  = m.originator;
              	                m1.sender = SensorNodePtr->NodeID;
              	                m1.path = SensorNodePtr->pathFromSink;
              	                m1.sequence = m.sequence;
              	                m1.flooding = true;
              	                SendToNeighbor(m1);


              	                SensorNodePtr->power -= .000066912;

              	                //sending to parent;
              		               /* message m2;

              		                m2.type = MYPATH;
              		                m2.originator  = SensorNodePtr->NodeID;
              		                m2.sender = SensorNodePtr->NodeID;
              		                m2.path = SensorNodePtr->pathFromSink;
              		                m2.sequence = SensorNodePtr->getNewSeq();//m.sequence;
              		                m2.flooding = true;
              		                m2.x = SensorNodePtr->x;
              		                m2.y = SensorNodePtr->y;
              		                m2.children =  SensorNodePtr->children;
              		                m2.receiver = SensorNodePtr->Parent->NodeID;
              		                for (unsigned int i = 0; i < SensorNodePtr->oneHopNeighbors.size();i++){
              			                if (SensorNodePtr->oneHopNeighbors.at(i).ID < NUMBER_OF_NODES)
              				                m2.neighbors.insert(SensorNodePtr->oneHopNeighbors.at(i).ID);
              		                }
              		                */
              		                //SendToParent(m2);

              		               // SensorNodePtr->power -= .000066912;

                              }

                void a4(message m){



                	vector<int>::iterator seqiterator = find(SensorNodePtr->processedSeq.begin(),SensorNodePtr->processedSeq.end(),m.sequence);
                	if (seqiterator != SensorNodePtr->processedSeq.end()){
                		return;//it should not find it or it has been processed
                	}

                	/////////////////////////////////////////////////////////////////////////////
                	if (m.sender == SensorNodePtr->parent){


                	}
                	/////////////////////////////////////////////////////////////////////////////
                	//since children uses a set datastructure there will be no duplicates entered.
                	SensorNodePtr->children.insert(m.sender);

                	message m1;
                	m1.type = MYPATH;
                	m1.originator = m.originator;
                	m1.sender = SensorNodePtr->NodeID;
                	m1.path = m.path;
                	m1.update = m.update;
                	m1.flooding = false;
                	m1.x = m.x;
                	m1.y = m.y;
                	m1.children = m.children;
                	m1.newParent = m.newParent;
                	m1.sequence = m.sequence;
                	m1.neighbors = m.neighbors;

                	SendToParent(m1);

                	SensorNodePtr->processedSeq.push_back(m.sequence);
                	return;

                }

                //hello processor
                void a2(message m){
                	vector<neighbor>::iterator it;

                	bool found = false;

                	for (it = SensorNodePtr->oneHopNeighbors.begin(); it != SensorNodePtr->oneHopNeighbors.end();it++){
                		if (((neighbor)*it).ID == m.sender ){
                			found = true;
                			break;
                		}
                	}

                	if (found == false){
                		neighbor t;
                		SensorNodePtr->s = t;
                		SensorNodePtr->s.ID = m.sender;
                		SensorNodePtr->oneHopNeighbors.push_back(SensorNodePtr->s);

                	}else{
                		SensorNodePtr->duplicated.insert(m.sender);
                	}
                }


                //Data message processor. It will forward the message to the correct target.
                void a7(message m){
                	SensorNodePtr->power -= ENERGY_RECEIVING_A_DATA_MESSAGE;//ENERGY_RECEIVING_A_DATA_MESSAGE;
                	set<NODE_ID>::iterator it;
                	it = SensorNodePtr->children.find(m.sender);

                	if (it == SensorNodePtr->children.end()){

                		return;
                	}



                	if (m.finalReceiver == SensorNodePtr->NodeID){
                		//cout<<"Got data message. from: "<<m.originator<<endl;
                		SensorNodePtr->d.insert(m.data);
                	}else{

                		it = SensorNodePtr->children.find(m.finalReceiver);

                		if (it != SensorNodePtr->children.end()){
                			m.receiver = (*it);
                			m.sender= SensorNodePtr->NodeID;
                			SendToChildren(m);
                			//cout<<"forwarding to receiver: "<<m.receiver<<endl;
                		}else{
                			m.receiver = SensorNodePtr->parent;
                			SendToParent(m);
                			//cout<<"forwarding from: "<<ID<<" forwarding to: "<<m.receiver<<" final destination: "<<m.finalReceiver<<endl;
                		}


                	}

                }

                void a5(message m){
                	if (SensorNodePtr->maxLevel == -1){
                		SensorNodePtr->maxLevel = m.maxLevel;

                		message m1;
                		m1.type = MAXLEVELANNOUNCE;
                		m1.originator = m.originator;
                		m1.sender = SensorNodePtr->NodeID;
                		m1.maxLevel = m.maxLevel;
                		m1.flooding = true;
                		m1.sequence = m.sequence;
                		SendToChildren(m1);

                		//This will set the wakeup timer
                		SensorNodePtr->wakeUpTimer = SensorNodePtr->maxLevel - SensorNodePtr->pathFromSink.size();
                		//when MaxLevelAnnounceCountDown gets to zero it signals to start processing in cycles by using wakeupTimer. This gives all
                		//levels a chance to get the levelannouce so their wakeuptimers can be set.
                		SensorNodePtr->MaxLevelAnnounceCountDown = SensorNodePtr->maxLevel - SensorNodePtr->level;
                	}

                }

                //This will process a lost message and send it to the sink and also make any changes to its own parent if nessasary.
                void a9(message m){
                	SensorNodePtr->power -= ENERGY_RECEIVING_A_DEAD_BROADCAST_MESSAGE;
                	if (m.originator == SensorNodePtr->parent){
                		if (SensorNodePtr->backupParents.size() == 0){

                			if (SensorNodePtr->dead == false){
                				char buffer[33];
                				//itoa(SensorNodePtr->NodeID, buffer, 10);
                				sprintf(buffer, "%d",SensorNodePtr->NodeID);
                				cout<<"Node: "<<buffer<<"Is Dead No backup Parents a09:"<<endl;
                				//tempdeadcounter++;
                			}

                			SensorNodePtr->parent = -2;
                			message m1;
                			m1.type = LOST;
                			m1.originator = SensorNodePtr->NodeID;
                			m1.sender = SensorNodePtr->NodeID;
                			m1.originatorLevel  = SensorNodePtr->level;
                			m1.receiver = ALL;
                			SendToChildren(m1);
                			SendToParent(m1);
                			SendToOther(m1);
                			SensorNodePtr->power -= .000014688;
                			/*char buffer[33];
                			itoa(ID, buffer, 10);*/
                			//cout<<"Node: "<<buffer<<"Is Dead No backup Parents a09:"<<tempdeadcounter<<endl;
                			return;
                		}
                		SensorNodePtr->disconnected = true;
                		vector<neighbor>::iterator it;
                		it = SensorNodePtr->backupParents.begin();
                		neighbor p = *it;
                		message m2;
                		m2.type = LIFEPROBE;
                		m2.sender = SensorNodePtr->NodeID;
                		m2.receiver = p.ID;
                		SendToOther(m2);
                		SensorNodePtr->power -= .00000816;
                		return;
                	}
                	vector<neighbor>::iterator it2;
                	for(it2 = SensorNodePtr->backupParents.begin(); it2 != SensorNodePtr->backupParents.end(); it2++){
                		if ((*it2).ID == m.originator){
                			SensorNodePtr->backupParents.erase(it2);
                			break;
                		}

                	}

                	set<NODE_ID> temp_list;
                	set<NODE_ID>::iterator it3;
                	for(it3 = SensorNodePtr->children.begin(); it3 != SensorNodePtr->children.end(); it3++){
                		if ((*it3) == m.originator){

                			temp_list.insert(*it3);
                			message m3;
                			m3.type = LOST;
                			m3.originator = m.originator ;
                			m3.originatorLevel = m.originatorLevel;
                			m3.receiver = SensorNodePtr->parent;
                			SendToParent(m3);
                			SensorNodePtr->power -= .000014688;
                			char buffer[33];
                			char buffer2[33];
                			//itoa(SensorNodePtr->NodeID, buffer, 10);
                			sprintf(buffer, "%d",SensorNodePtr->NodeID);
                			//itoa(SensorNodePtr->parent, buffer2, 10);
                			sprintf(buffer2, "%d",SensorNodePtr->parent);
                			//cout<<"A9 Node: "<<buffer<<" passing child death message to:"<<buffer2<<endl;
                			SensorNodePtr->children.erase(it3);
                			break;
                		}

                	}

                	/////////////////////////////
                	vector<neighbor>::iterator it4;
                	for(it4 = SensorNodePtr->oneHopNeighbors.begin(); it4 != SensorNodePtr->oneHopNeighbors.end(); it4++){
                		if ((*it4).ID == m.originator){
                			SensorNodePtr->oneHopNeighbors.erase(it4);
                			break;
                		}
                	}
                	/////////////////////////////

                	if (m.sender == SensorNodePtr->parent){
                		//cout<<"RECURSIVE LOOP"<<endl;
                		return;
                	}

                	message m3;
                	m3.type = LOST;
                	m3.originator = m.originator ;
                	m3.originatorLevel = m.originatorLevel;
                	m3.receiver = SensorNodePtr->parent;
                	SendToParent(m3);
                	SensorNodePtr->power -= .000014688;
                	char buffer[33];
                	char buffer2[33];
                	//itoa(SensorNodePtr->NodeID, buffer, 10);

                	//itoa(SensorNodePtr->parent, buffer2, 10);

                	sprintf(buffer, "%d",SensorNodePtr->NodeID);
                	sprintf(buffer2, "%d",SensorNodePtr->parent);
                	//cout<<"A9 e Node: "<<buffer<<" passing death message to:"<<buffer2<<endl;


                }

                //If the node is dying it will send out a lost message to all nodes.
                void a8(){
                	message m;
                	m.type = LOST;
                	m.originator = SensorNodePtr->NodeID;
                	m.sender = SensorNodePtr->NodeID;
                	m.originatorLevel  = SensorNodePtr->level;
                	m.receiver = ALL;
                	SendToChildren(m);
                	SendToParent(m);
                	SendToOther(m);
                	SensorNodePtr->power -= .000014688;
                	SensorNodePtr->dead = true;
                	char buffer[33];
                	char buffer2[33];
                	sprintf(buffer, "%d",SensorNodePtr->NodeID);
                    sprintf(buffer2, "%d",SensorNodePtr->parent);
                	//cout<<"A8 Node: "<<buffer<<" passing death message to:"<<buffer2<<endl;
                }

                //Lifeprobe processor
                void a10(message m){
                	if (SensorNodePtr->NodeID != m.receiver){
                		return;
                	}

                	if (SensorNodePtr->dead == true){
                		message m1;
                		m1.type = LIFERESPONSE;
                		m1.sender = SensorNodePtr->NodeID;
                		m1.receiver = m.sender;
                		m1.alive = false;
                		SendToOther(m1);
                	}else{
                		message m1;
                		m1.type = LIFERESPONSE;
                		m1.sender = SensorNodePtr->NodeID;
                		m1.receiver = m.sender;
                		m1.alive = true;
                		m1.path = SensorNodePtr->pathFromSink;
                		m1.oldLevel  = SensorNodePtr->level;
                		m1.skip = SensorNodePtr->disconnected;
                		SendToOther(m1);
                	}
                	SensorNodePtr->power -= .000011424;

                }



                //Life Response Processor
                void a11(message m){

                	if (SensorNodePtr->NodeID != m.receiver){
                		return;
                	}

                	if (m.alive == true){

                		if (SensorNodePtr->backupParents.size() > 0){

                			if (SensorNodePtr->parent == m.sender){
                				return; //already processed. no need to repeat.
                			}

                			/////SKIP///////////////////////////////////////////////////////////////////

                			vector<int>::iterator fit = find(m.path.begin(), m.path.end(), SensorNodePtr->parent);
                			if (fit != m.path.end()){//contains invalid parent
                				m.skip = true;
                			}



                			if (m.skip){ //Goto the next because the one requested is in an inconsitant state. It is not connected to a sink.

                				neighbor p;

                				vector<neighbor>::iterator it;

                				it = SensorNodePtr->backupParents.begin();
                				p = *it;
                				message m2;
                				m2.type = LIFEPROBE;
                				m2.sender = SensorNodePtr->NodeID;
                				m2.receiver = p.ID;
                				SendToOther(m2);
                				SensorNodePtr->power -= .00000816;
                				return;


                			}

                			vector<int>::iterator fit2 = find(m.path.begin(), m.path.end(), SensorNodePtr->NodeID);
                			if (fit2 != m.path.end()){//contains invalid parent
                				return;
                			}




                			/////END SKIP//////////////////////////////////////////////////////////////'










                			neighbor p;
                			p.ID = m.sender;
                			vector<neighbor>::iterator it = find(SensorNodePtr->backupParents.begin(), SensorNodePtr->backupParents.end(), p);

                			if (it != SensorNodePtr->backupParents.end()){
                				SensorNodePtr->backupParents.erase(it);
                			}

                			//it = SensorNodePtr->backupParents.begin();
                			//p = *it;
                			//int oldparent = SensorNodePtr->parent;
                			//SensorNodePtr->backupParents.erase(it);
                			SensorNodePtr->parent = m.sender;

                			SensorNodePtr->disconnected = false;

                			SensorNodePtr->children.erase(m.sender);

                			SensorNodePtr->pathFromSink = m.path;
                			SensorNodePtr->pathFromSink.push_back(SensorNodePtr->NodeID);

                			message m2;

                			m2.type = MYPATH;
                			m2.originator  = SensorNodePtr->NodeID;
                			m2.sender = SensorNodePtr->NodeID;
                			m2.path = SensorNodePtr->pathFromSink;
                			m2.sequence = SensorNodePtr->getNewSeq();//ID;//m.sequence;
                			m2.flooding = true;
                			m2.update=true;
                			m2.x = SensorNodePtr->x;
                			m2.y = SensorNodePtr->y;
                			m2.newParent = SensorNodePtr->parent;
                			m2.oldLevel = SensorNodePtr->level ;
                			m2.children = SensorNodePtr->children;


                			for (unsigned int i = 0; i < SensorNodePtr->oneHopNeighbors.size();i++){
                				if (SensorNodePtr->oneHopNeighbors.at(i).ID < NUMBER_OF_NODES)
                					m2.neighbors.insert(SensorNodePtr->oneHopNeighbors.at(i).ID);
                			}

                			SendToParent(m2);

                			SensorNodePtr->power -= .000066912;

                			SensorNodePtr->power -= .00007344;
                			SensorNodePtr->level = m.oldLevel + 1 ; //Old level holds level from node the life probe came from.
                		}

                	}else{

                		if (SensorNodePtr->backupParents.size() > 0 ){
                			neighbor p;
                			p.ID = m.sender;
                			vector<neighbor>::iterator it = find(SensorNodePtr->backupParents.begin(), SensorNodePtr->backupParents.end(), p);

                			if (it != SensorNodePtr->backupParents.end()){
                				SensorNodePtr->backupParents.erase(it);
                			}



                			if (SensorNodePtr->backupParents.size() == 0){
                				if (SensorNodePtr->dead == false){

                				}
                				SensorNodePtr->dead = true;
                				message m;
                				m.type = LOST;
                				m.originator = SensorNodePtr->NodeID;
                				m.sender = SensorNodePtr->NodeID;
                				m.originatorLevel  = SensorNodePtr->level;
                				m.receiver = ALL;
                				SendToChildren(m);
                				SendToParent(m);
                				SendToOther(m);
                				SensorNodePtr->power -= .000014688;
                				char buffer[33];
                				//itoa(SensorNodePtr->NodeID, buffer, 10);
                				sprintf(buffer, "%d",SensorNodePtr->NodeID);
                				cout<<"Node: "<<buffer<<"Is Dead No backup Parents a11:"<<tempdeadcounter<<endl;
                				tempdeadcounter++;
                				/*char buffer[33];
                				itoa(ID, buffer, 10);
                				cout<<"Node: "<<buffer<<"Is Dead No backup Parents a11:"<<tempdeadcounter<<endl;*/
                			}else{
                				it = SensorNodePtr->backupParents.begin();
                				p = *it;
                				message m2;
                				m2.type = LIFEPROBE;
                				m2.sender = SensorNodePtr->NodeID;
                				m2.receiver = p.ID;
                				SendToOther(m2);
                				SensorNodePtr->power -= .00000816;
                			}
                		}

                	}

                }


                void a12(){
                	SensorNodePtr->wakeUpTimer = (NETWORK_CYCLE / SensorNodePtr->maxLevel) * (SensorNodePtr->level - 0.5);
                }


                //SINKSHIFT Processor. Forwards message to children, clears all data, then sends hellos.
                void a13(message m){
                		if (SensorNodePtr->parent >= 0){
                			message m1;
                			m1.type = SINKSHIFT;
                			m1.originator  = SensorNodePtr->NodeID;
                			m1.receiver = ALL;
                			m1.nextSink = m.nextSink;
                			m1.networkResetTime = SensorNodePtr->networkResetTime;
                			m1.flooding = true;
                			SendToChildren(m1);

                			SensorNodePtr->parent = -1;

                			//SensorNodePtr->children.clear();

                			vector<neighbor>::iterator it4;
                			for(it4 = SensorNodePtr->oneHopNeighbors.begin(); it4 != SensorNodePtr->oneHopNeighbors.end(); it4++){
                				SensorNodePtr->children.insert((*it4).ID);
                			}

                			//clearQueueKeepSinkShiftAndData(SensorNodePtr->childrenInQueue, m.nextSink);
                			//clearQueueKeepSinkShiftAndData(SensorNodePtr->parentInQueue, m.nextSink);
                			//clearQueueKeepSinkShiftAndData(SensorNodePtr->otherInQueue, m.nextSink);
                			//clearQueueKeepSinkShiftAndData(SensorNodePtr->childrenOutQueue, m.nextSink);
                			//clearQueueKeepSinkShiftAndData(SensorNodePtr->parentOutQueue, m.nextSink);
                			//clearQueueKeepSinkShiftAndData(SensorNodePtr->otherOutQueue, m.nextSink);
                			SensorNodePtr->level = -1;
                			SensorNodePtr->maxLevel = -1;
                			SensorNodePtr->MaxLevelAnnounceCountDown = -1;
                			SensorNodePtr->pathFromSink.clear();
                			//SensorNodePtr->power = NODE_INITIAL_ENERGY;
                			SensorNodePtr->backupParents.clear();
                			SensorNodePtr->dead = false;
                			SensorNodePtr->power -= .00000816;
                			SensorNodePtr->nodeSetupTimer = NODE_SETUP_TIME;
                			SensorNodePtr->countdown(SensorNodePtr->nodeSetupTimer);
                			SensorNodePtr->wakeUpTimer = -1;
                			SensorNodePtr->childernReceptionTimer = -1;
                			SensorNodePtr->childrenTransimissionTimer = -1;
                			SensorNodePtr->parentTransmissionTimer = -1;
                			SensorNodePtr->parentReceptionTimer = -1;
                			SensorNodePtr->sleepTimer = -1;
                			SensorNodePtr->sleepTimer = -1;
                			SensorNodePtr->parent= -2;
                			SensorNodePtr->returnedChildren.clear();
                			SensorNodePtr->cnum = 0;


                			broadcastHello();
                		}


                }


                //Broadcast the hello to all nodes in range.
                void broadcastHello(){
                	message m;
                	m.type = HELLO;
                	m.originator = SensorNodePtr->NodeID;
                	m.sender= SensorNodePtr->NodeID;
                	m.receiver = ALL;

                	SendToChildren(m);
                	SendToParent(m);
                	SendToOther(m);

                	SensorNodePtr->power -= ENERGY_SENDING_A_BROADCAST_MESSAGE;

                }


                void a1(){

                	//SensorNodePtr->oneHopNeighbors.clear();
                	//SensorNodePtr->duplicated.clear();
                	//SensorNodePtr->children.clear();
                	/*clearQueue(SensorNodePtr->childrenInQueue);
                	clearQueue(SensorNodePtr->parentInQueue);
                	clearQueue(SensorNodePtr->otherInQueue);
                	clearQueue(SensorNodePtr->childrenOutQueue);
                	clearQueue(SensorNodePtr->parentOutQueue);
                	clearQueue(SensorNodePtr->otherOutQueue);*/
                	SensorNodePtr->level = -1;
                	SensorNodePtr->maxLevel = -1;
                	SensorNodePtr->MaxLevelAnnounceCountDown = -1;
                	//SensorNodePtr->pathFromSink.clear();

                	if (SensorNodePtr->power == -1)
                		SensorNodePtr->power = NODE_INITIAL_ENERGY;

                	SensorNodePtr->backupParents.clear();
                	SensorNodePtr->dead = false;
                	broadcastHello();
                	SensorNodePtr->power -= .00000816;
                	SensorNodePtr->nodeSetupTimer = NODE_SETUP_TIME;
                	SensorNodePtr->countdown(SensorNodePtr->nodeSetupTimer);
                	SensorNodePtr->wakeUpTimer = -1;
                	SensorNodePtr->childernReceptionTimer = -1;
                	SensorNodePtr->childrenTransimissionTimer = -1;
                	SensorNodePtr->parentTransmissionTimer = -1;
                	SensorNodePtr->parentReceptionTimer = -1;
                	SensorNodePtr->sleepTimer = -1;
                	SensorNodePtr->parent= -2;
                	SensorNodePtr->returnedChildren.clear();
                	SensorNodePtr->cnum = 0;


                }

                void powerOn(){
                	a1();
                }

	//Ipv4Address sinkAdd;
          void HandleReceive (Ptr<Socket> socket){
		NS_LOG_INFO ("Sensor MRX ID:" << SensorNodePtr->NodeID);
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

                          //i added the small protion below to weed out any reception of duplicate messages. It might not be needed but its here for safty.

							vector<int>::iterator it;
							it = ProcessedMessages.begin();
							while (true){

								if (it == ProcessedMessages.end()){
									break;
								}
								if ((*it) == m.sequence){
									NS_LOG_INFO("Message Kicked (Dup)");
									return;
								}
								it++;
							}

							 ProcessedMessages.push_back(m.sequence);

                        switch (m.type){
	
	                        case TREESETUP:
		                        //a3(m);
					//sinkAdd = InetSocketAddress::ConvertFrom (from).GetIpv4 ();
	                        	TreeSetupHandler(m);
		                        break;
	                        case MYPATH:
		                        //a4(m);
		                        break;
	                        case HELLO:
		                        //a2(m);
		                        break;
	                        case DATA:
		                        //a7(m);
		                        break;
	                        case MAXLEVELANNOUNCE:
		                        //a5(m);
		                        break;
	                        case MAXLEVELRESET:
		                        break;
	                        case LOST:
		                        //a9(m);
		                        break;
	                        case LIFEPROBE:
		                        //a10(m);
		                        break;
	                        case LIFERESPONSE:
		                        //a11(m);
		                        break;
	                        case SINKSHIFT:
		                        //sinkAdd = InetSocketAddress::ConvertFrom (from).GetIpv4 ();
	                        	//a13(m);
		                        break;


                        }


                          //NS_LOG_LOGIC ("Echoing packet");
                          //socket->SendTo (packet, 0, from);
                       // SendToChildren();
                        }
                    }
          }

          Ptr<Socket> m_socket;
          Ipv4Address m_peerAddress;
          Address m_local;


/*
// This function analogous to Linux ip_mr_forward()
void
IpMulticastForward (Ptr<Ipv4MulticastRoute> mrtentry, Ptr<const Packet> p, const Ipv4Header &header)
{
  NS_LOG_FUNCTION (this << mrtentry << p << header);
  NS_LOG_LOGIC ("Multicast forwarding logic for node: " << m_node->GetId ());
  // The output interfaces we could forward this onto are encoded
  // in the OutputTtl of the Ipv4MulticastRoute
  for (uint32_t i = 0; i < Ipv4MulticastRoute::MAX_INTERFACES; i++)
    {
      if (mrtentry->GetOutputTtl (i) < Ipv4MulticastRoute::MAX_TTL)
        {
          Ptr<Packet> packet = p->Copy ();
          Ipv4Header h = header;
          h.SetTtl (header.GetTtl () - 1);
          if (h.GetTtl () == 0)
            {
              NS_LOG_WARN ("TTL exceeded.  Drop.");
              m_dropTrace (header, packet, DROP_TTL_EXPIRED, m_node->GetObject<Ipv4> (), i);
              return;
            }
          NS_LOG_LOGIC ("Forward multicast via interface " << i);
          Ptr<Ipv4Route> rtentry = Create<Ipv4Route> ();
          rtentry->SetSource (h.GetSource ());
          rtentry->SetDestination (h.GetDestination ());
          rtentry->SetGateway (Ipv4Address::GetAny ());
          rtentry->SetOutputDevice (GetNetDevice (i));
          SendRealOut (rtentry, packet, h);
          continue; 
        }
    }
}

// This function analogous to Linux ip_forward()
void
IpForward (Ptr<Ipv4Route> rtentry, Ptr<const Packet> p, const Ipv4Header &header)
{
  NS_LOG_FUNCTION (this << rtentry << p << header);
  NS_LOG_LOGIC ("Forwarding logic for node: " << m_node->GetId ());
  // Forwarding
  Ipv4Header ipHeader = header;
  Ptr<Packet> packet = p->Copy ();
  int32_t interface = GetInterfaceForDevice (rtentry->GetOutputDevice ());
  ipHeader.SetTtl (ipHeader.GetTtl () - 1);
  if (ipHeader.GetTtl () == 0)
    {
      // Do not reply to ICMP or to multicast/broadcast IP address 
      if (ipHeader.GetProtocol () != Icmpv4L4Protocol::PROT_NUMBER && 
        ipHeader.GetDestination ().IsBroadcast () == false && 
        ipHeader.GetDestination ().IsMulticast () == false)
        {
          Ptr<Icmpv4L4Protocol> icmp = GetIcmp ();
          icmp->SendTimeExceededTtl (ipHeader, packet);
        }
      NS_LOG_WARN ("TTL exceeded.  Drop.");
      m_dropTrace (header, packet, DROP_TTL_EXPIRED, m_node->GetObject<Ipv4> (), interface);
      return;
    }
  m_unicastForwardTrace (ipHeader, packet, interface);
  SendRealOut (rtentry, packet, ipHeader);
}

void
LocalDeliver (Ptr<const Packet> packet, Ipv4Header const&ip, uint32_t iif)
{
  NS_LOG_FUNCTION (this << packet << &ip);
  Ptr<Packet> p = packet->Copy (); // need to pass a non-const packet up

  m_localDeliverTrace (ip, packet, iif);

  Ptr<Ipv4L4Protocol> protocol = GetProtocol (ip.GetProtocol ());
  if (protocol != 0)
    {
      // we need to make a copy in the unlikely event we hit the
      // RX_ENDPOINT_UNREACH codepath
      Ptr<Packet> copy = p->Copy ();
      enum Ipv4L4Protocol::RxStatus status = 
        protocol->Receive (p, ip, GetInterface (iif));
      switch (status) {
      case Ipv4L4Protocol::RX_OK:
        // fall through
      case Ipv4L4Protocol::RX_ENDPOINT_CLOSED:
        // fall through
      case Ipv4L4Protocol::RX_CSUM_FAILED:
        break;
      case Ipv4L4Protocol::RX_ENDPOINT_UNREACH:
        if (ip.GetDestination ().IsBroadcast () == true || 
          ip.GetDestination ().IsMulticast () == true)
          {
            break;  // Do not reply to broadcast or multicast
          }
        // Another case to suppress ICMP is a subnet-directed broadcast
        bool subnetDirected = false;
        for (uint32_t i = 0; i < GetNAddresses (iif); i++)
          {
            Ipv4InterfaceAddress addr = GetAddress (iif, i);
            if (addr.GetLocal ().CombineMask (addr.GetMask ()) == ip.GetDestination().CombineMask (addr.GetMask ()) &&
              ip.GetDestination ().IsSubnetDirectedBroadcast (addr.GetMask ()))
              {
                subnetDirected = true;
              }
          }
        if (subnetDirected == false)
          {
            GetIcmp ()->SendDestUnreachPort (ip, copy);
          }
      }
    }
}

void
RouteInputError (Ptr<const Packet> p, const Ipv4Header & ipHeader, Socket::SocketErrno sockErrno)
{
  NS_LOG_FUNCTION (this << p << ipHeader << sockErrno);
  NS_LOG_LOGIC ("Route input failure-- dropping packet to " << ipHeader << " with errno " << sockErrno); 
  m_dropTrace (ipHeader, p, DROP_ROUTE_ERROR, m_node->GetObject<Ipv4> (), 0);
}*/

        };
        

}

#endif
