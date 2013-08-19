/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 Network Security Lab, University of Washington, Seattle.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;F
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Sidharth Nabar <snabar@uw.edu>, He Wu <mdzz@u.washington.edu>
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store-module.h"
#include "ns3/wifi-module.h"
#include "ns3/energy-module.h"
#include "ns3/internet-module.h"
#include "ns3/olsr-routing-protocol.h"
#include "ns3/olsr-helper.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <exception>

NS_LOG_COMPONENT_DEFINE ("NS3SIM");

#include "constants.h"
#include "neighbor.h"
#include "message.h"
#include "wsnbasenode.h"
#include "wsnsensornode.h"
#include "wsnsinknode.h"
#include "SinkApplication.h"
#include "SensorApplication.h"
#include "xmlNodeLoader.h"
#define telsek 1


using namespace ns3;


namespace ns3 {




map<int, set<int> > WSNSinkNode::sensorNeighbors;
   

}


void loadOneHopNeighbors(NodeContainer sinkNodes, NodeContainer SensorNodes,int id){

   //int RADIO_RANGE = 15;
   //int NUMBER_OF_NODES = 100;
   //int NUMBER_OF_SINKS = 4;

   if (id >= NUMBER_OF_NODES){
        for (int i = 0; i<NUMBER_OF_NODES; i++){
                
                Ptr<WSNSensorNode> SensorNode = DynamicCast <WSNSensorNode> (SensorNodes.Get(i));
                Ptr<MobilityModel> Sensormb = SensorNode->GetObject<MobilityModel>();
                Vector SensorPosition = Sensormb->GetPosition(); 

                for (int j = 0; j < NUMBER_OF_SINKS;j++){

                        
                        Ptr<WSNSinkNode> SinkNode = DynamicCast <WSNSinkNode> (sinkNodes.Get(j));
                        Ptr<MobilityModel> Sinkmb = SinkNode->GetObject<MobilityModel>();
                        Vector SinkPosition = Sinkmb->GetPosition(); 

                        //distance
                        double r2 = sqrt(pow(SensorPosition.x - SinkPosition.x, 2.0) + pow(SensorPosition.y - SinkPosition.y, 2.0));
                        //NS_LOG_UNCOND ("r2: " <<r2 <<" Sinkx:"<<SinkPosition.x << " Sinky:" << SinkPosition.y);

                        if (r2 <= RADIO_RANGE){

                        	bool ChildPresent = !(SinkNode->children.find(SensorNode->NodeID) == SinkNode->children.end());

							if (!ChildPresent){

									SinkNode->neighbors.Add(SensorNode);
									SinkNode->childrenNodes.Add(SensorNode);
									SinkNode->children.insert(SensorNode->NodeID);
									SensorNode->neighbors.Add(SinkNode);

									if (SinkNode->Active){

											//SensorNode->children.Add(SinkNode);
											SensorNode->Parent = SinkNode;

									}

							}
                        }
                
                }

        }     
   }else{

        Ptr<WSNSensorNode> SensorNodeID = DynamicCast <WSNSensorNode> (SensorNodes.Get(id));
        Ptr<MobilityModel> SensorIdmb = SensorNodeID->GetObject<MobilityModel>();
        Vector SensorPositionID = SensorIdmb->GetPosition(); 
        
        for (int i = 0; i<NUMBER_OF_NODES; i++){
        
                if (i != id){

                        Ptr<WSNSensorNode> CurSensorNode = DynamicCast <WSNSensorNode> (SensorNodes.Get(i));
                        Ptr<MobilityModel> CurSensormb = CurSensorNode->GetObject<MobilityModel>();
                        Vector CurSensorPosition = CurSensormb->GetPosition(); 

                        //distance
                        double r = sqrt(pow(CurSensorPosition.x - SensorPositionID.x, 2.0) + pow(CurSensorPosition.y - SensorPositionID.y, 2.0));
                        if (r <= RADIO_RANGE ){
                        	bool ChildPresent = !(SensorNodeID->children.find(CurSensorNode->NodeID) == SensorNodeID->children.end());

                        	//int scs = SensorNodeID->children.size();
                        	//scs+=0;

                        	if (!ChildPresent){
								SensorNodeID->neighbors.Add(CurSensorNode);
								SensorNodeID->children.insert(CurSensorNode->NodeID);
								SensorNodeID->childrenNodes.Add(CurSensorNode);

								CurSensorNode->neighbors.Add(SensorNodeID);
								CurSensorNode->childrenNodes.Add(SensorNodeID);
								CurSensorNode->children.insert(SensorNodeID->NodeID);

							}
                		}
                
                }        

        }


   }


}


int
main (int argc, char *argv[])
{
  /*
  LogComponentEnable ("EnergySource", LOG_LEVEL_DEBUG);
  LogComponentEnable ("BasicEnergySource", LOG_LEVEL_DEBUG);
  LogComponentEnable ("DeviceEnergyModel", LOG_LEVEL_DEBUG);
  LogComponentEnable ("WifiRadioEnergyModel", LOG_LEVEL_DEBUG);
   */

//{ PyViz v; } 


  std::string phyMode ("DsssRate1Mbps");
  double Prss = -80;            // dBm
  uint32_t PpacketSize = 200;   // bytes
  bool verbose = false;

  int sdf = 0; //
  sdf+= 0;

  // simulation parameters
  uint32_t numPackets = 10000;  // number of packets to send
  double interval = 1;          // seconds
  double startTime = 0.0;       // seconds
  double distanceToRx = 100.0;  // meters

  /*
   * This is a magic number used to set the transmit power, based on other
   * configuration.
   */
  //double offset = 81;

 // LogComponentEnable("OlsrRoutingProtocol", LOG_LEVEL_ALL);


  CommandLine cmd;
  cmd.AddValue ("phyMode", "Wifi Phy mode", phyMode);
  cmd.AddValue ("Prss", "Intended primary RSS (dBm)", Prss);
  cmd.AddValue ("PpacketSize", "size of application packet sent", PpacketSize);
  cmd.AddValue ("numPackets", "Total number of packets to send", numPackets);
  cmd.AddValue ("startTime", "Simulation start time", startTime);
  cmd.AddValue ("distanceToRx", "X-Axis distance between nodes", distanceToRx);
  cmd.AddValue ("verbose", "Turn on all device log components", verbose);
  cmd.Parse (argc, argv);

  // Convert to time object
  Time interPacketInterval = Seconds (interval);

  // disable fragmentation for frames below 2200 bytes
  Config::SetDefault ("ns3::WifiRemoteStationManager::FragmentationThreshold",
                      StringValue ("2200"));
  // turn off RTS/CTS for frames below 2200 bytes
  Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold",
                      StringValue ("2200"));
  // Fix non-unicast data rate to be the same as that of unicast
  Config::SetDefault ("ns3::WifiRemoteStationManager::NonUnicastMode",
                      StringValue (phyMode));

  //NodeContainer c;
  NodeContainer SensorNodes;
  //c.Create (100);     // create 2 nodes

  for (int i = 0; i < 100; i++){
  
      Ptr<WSNSensorNode> SensorNode = CreateObject<WSNSensorNode>();
      SensorNode->NodeID = i;
      SensorNodes.Add(SensorNode);
  
  }

  
  



  //for (int i = 0; i < 100; i++){
  //   SensorNodes.Add (c.Get (i));
 // }

  NodeContainer SinkNodes;
  for (int i = 0; i < 4; i++){
  
      Ptr<WSNSinkNode> SinkNode = CreateObject<WSNSinkNode>();
      SinkNode->NodeID = i+100;
      if (i == 0){
        SinkNode->Active = true;
      }

      SinkNodes.Add(SinkNode);
  
  }


  

  // The below set of helpers will help us to put together the wifi NICs we want
  WifiHelper wifi;
  if (verbose)
    {
      wifi.EnableLogComponents ();
    }
  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);

  /** Wifi PHY **/
  /***************************************************************************/
  YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default ();
  //wifiPhy.Set ("RxGain", DoubleValue (-10));
  //wifiPhy.Set ("TxGain", DoubleValue (offset + Prss));

  wifiPhy.Set ("RxGain", DoubleValue (32));
  wifiPhy.Set ("TxGain", DoubleValue (32));
  //wifiPhy.Set ("CcaMode1Threshold", DoubleValue (0.0));
  /***************************************************************************/

  /** wifi channel **/
  YansWifiChannelHelper wifiChannel;
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel");
  // create wifi channel
  Ptr<YansWifiChannel> wifiChannelPtr = wifiChannel.Create ();
  wifiPhy.SetChannel (wifiChannelPtr);






  /** MAC layer **/
  // Add a non-QoS upper MAC, and disable rate control
  NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default ();
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager", "DataMode",
                                StringValue (phyMode), "ControlMode",
                                StringValue (phyMode));
  // Set it to ad-hoc mode
  wifiMac.SetType ("ns3::AdhocWifiMac");

  /** install PHY + MAC **/
  NetDeviceContainer sensordevices = wifi.Install (wifiPhy, wifiMac, SensorNodes);
  NetDeviceContainer sinkdevices = wifi.Install (wifiPhy, wifiMac, SinkNodes);
//Trying for 15 meters
        PointerValue tmpPhy;
        sensordevices.Get(0)->GetAttribute("Phy", tmpPhy);
        Ptr<Object> wifiPhyLayer = tmpPhy.GetObject();
        Ptr<YansWifiPhy> yansWifiPhyLayer = wifiPhyLayer->GetObject<YansWifiPhy>();
        double fre = yansWifiPhyLayer->GetChannelFrequencyMhz();
        double cha = yansWifiPhyLayer->GetChannelNumber();
        double tga = yansWifiPhyLayer->GetTxGain ();
        double rga = yansWifiPhyLayer->GetRxGain ();
        double pst = yansWifiPhyLayer->GetTxPowerStart ();

    NS_LOG_UNCOND ("Wifi Channel Freq: "  << fre);// wifiPhy.GetAttribute("ChannelFrequencyMhz"));
    NS_LOG_UNCOND ("Wifi Channel Num: "  << cha );//wifiPhy.GetAttribute("ChannelNumber"));
    NS_LOG_UNCOND ("Wifi Channel Num: "  << tga );//wifiPhy.GetAttribute("ChannelNumber"));
    NS_LOG_UNCOND ("Wifi Channel Num: "  << rga );//wifiPhy.GetAttribute("ChannelNumber"));
    NS_LOG_UNCOND ("Wifi Channel Num: "  << pst );//wifiPhy.GetAttribute("ChannelNumber"));




  //Need to make a random placement of the nodes. 
  /** mobility **/
//Sensors
   srand ( time(NULL) );


  bool loadxml = true;

  if (loadxml){

	  xmlNodeLoader xloader(&SinkNodes, &SensorNodes);
	  string xmlname = "/home/chabli/nodestructure.xml";

	  xloader.loadXML((char*)xmlname.c_str());


	  for (int i = 0; i < 100; i++){

		  	   Ptr<WSNSensorNode> SensorNode = DynamicCast <WSNSensorNode> (SensorNodes.Get(i));

	  	       int x = SensorNode->x;
	  	       int y = SensorNode->y;
	  	       MobilityHelper mobility;
	  	       Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
	  	       positionAlloc->Add (Vector (x, y, 0.0));
	  	       positionAlloc->Add (Vector (x, y, 0.0));
	  	       mobility.SetPositionAllocator (positionAlloc);
	  	       mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	  	       mobility.Install (SensorNodes.Get (i));
	  	       NS_LOG_UNCOND ("Sensor NodeID:"  << SensorNode->NodeID << " X:"<<x<<" Y:"<<y);

	  	    }
	  	  //Sinks
	  	    for (int i = 0; i < 4; i++){

	  	    	 Ptr<WSNSinkNode> SinkNode = DynamicCast <WSNSinkNode> (SinkNodes.Get(i));
	  	       int x = SinkNode->x;
	  	       int y = SinkNode->y;

	  	       MobilityHelper mobility;
	  	       Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
	  	       positionAlloc->Add (Vector (x, y, 0.0));
	  	       positionAlloc->Add (Vector (x, y, 0.0));
	  	       mobility.SetPositionAllocator (positionAlloc);
	  	       mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	  	       mobility.Install (SinkNodes.Get (i));
	  	       NS_LOG_UNCOND ("Sink NodeID:"  << SinkNode->NodeID << " X:"<<x<<" Y:"<<y);

	  	    }


  }else{

	  for (int i = 0; i < 100; i++){
	       int x = rand() % 100;
	       int y = rand() % 100;
	       MobilityHelper mobility;
	       Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
	       positionAlloc->Add (Vector (x, y, 0.0));
	       positionAlloc->Add (Vector (x, y, 0.0));
	       mobility.SetPositionAllocator (positionAlloc);
	       mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	       mobility.Install (SensorNodes.Get (i));

	       //Ptr<WSNSensorNode> SensorNode = c.Get (i);
	       Ptr<WSNSensorNode> SensorNode = DynamicCast <WSNSensorNode> (SensorNodes.Get(i));
	       SensorNode->x = x;
	       SensorNode->y = y;
	       NS_LOG_UNCOND ("Sensor NodeID:"  << SensorNode->NodeID << " X:"<<x<<" Y:"<<y);

	    }
	  //Sinks
	    for (int i = 0; i < 4; i++){
	       int x = rand() % 100;
	       int y = rand() % 100;
	       MobilityHelper mobility;
	       Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
	       positionAlloc->Add (Vector (x, y, 0.0));
	       positionAlloc->Add (Vector (x, y, 0.0));
	       mobility.SetPositionAllocator (positionAlloc);
	       mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	       mobility.Install (SinkNodes.Get (i));

	       //Ptr<WSNSensorNode> SensorNode = c.Get (i);
	       Ptr<WSNSinkNode> SinkNode = DynamicCast <WSNSinkNode> (SinkNodes.Get(i));
	       SinkNode->x = x;
	       SinkNode->y = y;

	       NS_LOG_UNCOND ("Sink NodeID:"  << SinkNode->NodeID << " X:"<<x<<" Y:"<<y);

	    }



  }



  /*MobilityHelper mobility;
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  positionAlloc->Add (Vector (0.0, 0.0, 0.0));
  positionAlloc->Add (Vector (2 * distanceToRx, 0.0, 0.0));
  mobility.SetPositionAllocator (positionAlloc);
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (c);*/
 

  /** Energy Model **/
  /***************************************************************************/
  /* energy source */
  BasicEnergySourceHelper basicSourceHelper;
  // configure energy source
  basicSourceHelper.Set ("BasicEnergySourceInitialEnergyJ", DoubleValue (200)); //energy source intial joules
  basicSourceHelper.Set ("BasicEnergySupplyVoltageV", DoubleValue (3.0)); //Assume 1.5V of energy per AA battery. We will use two
  // install source
  EnergySourceContainer sources = basicSourceHelper.Install (SensorNodes);
  /* device energy model */
  WifiRadioEnergyModelHelper radioEnergyHelper;
  // configure radio energy model
  radioEnergyHelper.Set ("TxCurrentA", DoubleValue (0.017));//TX -17dbm:10ma, -3dbm:13ma, 3dbm:17ma
  radioEnergyHelper.Set ("RxCurrentA", DoubleValue (0.016));//Recieve Mode
  radioEnergyHelper.Set ("IdleCurrentA", DoubleValue (0.008)); //Idle Mode
  radioEnergyHelper.Set ("CcaBusyCurrentA", DoubleValue (0.008)); //same as idle
  radioEnergyHelper.Set ("SwitchingCurrentA", DoubleValue (0.008)); //same as idle
  // install device model
  DeviceEnergyModelContainer deviceModels = radioEnergyHelper.Install (sensordevices, sources);
  //DeviceEnergyModelContainer deviceModels = radioEnergyHelper.Install (sinkdevices, sources);
  /***************************************************************************/
 
  /** Internet stack **/
  InternetStackHelper internet;
  
  // Enable OLSR
  NS_LOG_INFO ("Enabling OLSR Routing.");
  OlsrHelper olsr;

  olsr.Set("HelloInterval",TimeValue (Seconds (120)));
  olsr.Set("TcInterval",TimeValue (Seconds (120 * 2)));
  olsr.Set("MidInterval",TimeValue (Seconds (120 * 2)));
  olsr.Set("HnaInterval",TimeValue (Seconds (120 * 2)));


  Ipv4StaticRoutingHelper staticRouting;

  Ipv4ListRoutingHelper list;
  list.Add (staticRouting, 0);
  list.Add (olsr, 10);
  internet.SetRoutingHelper (list);
  //internet.SetRoutingHelper (olsr);
 
  internet.Install (SensorNodes);
  internet.Install (SinkNodes);


  Ipv4AddressHelper ipv4;
  NS_LOG_INFO ("Assign IP Addresses.");
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer sensori = ipv4.Assign (sensordevices);
  Ipv4InterfaceContainer sinki = ipv4.Assign (sinkdevices);


  ///NEED TO LOOP HERE TO MAKE CONNECTS ///////////////////////////

  
//load one hop neighbors as a link to each 

  //This may be taken out and just use the range and hello(once i figure out how ranges work.)

  //for (int i = 0; i < 104; i++){
  //      loadOneHopNeighbors(SinkNodes, SensorNodes, i);
  //}


  /*TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
  Ptr<Socket> recvSink = Socket::CreateSocket (SensorNodes.Get (1), tid);  // node 1, receiver
  InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80); //binds to its own listner port on 80
  recvSink->Bind (local);
  recvSink->SetRecvCallback (MakeCallback (&ReceivePacket));//handles incomming messages.
  InetSocketAddress testrem = InetSocketAddress (Ipv4Address::GetBroadcast (), 80);
  recvSink->SetAllowBroadcast (true);
  recvSink->Connect (testrem);

  Ptr<Socket> source = Socket::CreateSocket (SensorNodes.Get (0), tid);    // node 0, sender
  InetSocketAddress remote = InetSocketAddress (Ipv4Address::GetBroadcast (), 80);
  source->SetAllowBroadcast (true);
  source->Connect (remote);
  InetSocketAddress testlocal = InetSocketAddress (Ipv4Address::GetAny (), 80); //binds to its own listner port on 80
  source->Bind (testlocal);
  source->SetRecvCallback (MakeCallback (&ReceivePacket));//handles incomming messages.*/

  
  /////////////////////////END OF CONNECT LOOPS////////////////////

  /** connect trace sources **/
  /***************************************************************************/
  // all sources are connected to node 1
  // energy source
  Ptr<BasicEnergySource> basicSourcePtr = DynamicCast<BasicEnergySource> (sources.Get (1));
  //basicSourcePtr->TraceConnectWithoutContext ("RemainingEnergy", MakeCallback (&RemainingEnergy));
  // device energy model
  Ptr<DeviceEnergyModel> basicRadioModelPtr =
    basicSourcePtr->FindDeviceEnergyModels ("ns3::WifiRadioEnergyModel").Get (0);
  NS_ASSERT (basicRadioModelPtr != NULL);
  //basicRadioModelPtr->TraceConnectWithoutContext ("TotalEnergyConsumption", MakeCallback (&TotalEnergy));
  /***************************************************************************/
          
  for (int i = 0; i < 4; i++){ 
        Ptr<SinkApplication> c0 = Create<SinkApplication> ();//SinkNodes.Get(i));
        c0->SetStartTime(Seconds(30.0));
        c0->SetStopTime (Seconds(10000.0));
        NS_LOG_UNCOND ("Sink NodeID:"  << i);
        SinkNodes.Get(i)->AddApplication(c0);
  }
       
  for (int i = 0; i < 100; i++){
        Ptr<SensorApplication> c0 = Create<SensorApplication> ();//SensorNodes.Get(i));
        c0->SetStartTime(Seconds(25.00));
        c0->SetStopTime (Seconds(10000.0));
        SensorNodes.Get(i)->AddApplication(c0);
  }

  
  Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper> (("ctest.routes"), std::ios::out);
         list.PrintRoutingTableAllEvery(Seconds(2.0), routingStream);

  /** simulation setup **/
  // start traffic
  //Simulator::Schedule (Seconds (startTime), &GenerateTraffic, source, PpacketSize,
  //SensorNodes.Get (0), numPackets, interPacketInterval);

  Simulator::Stop (Seconds (10000.0));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}




















