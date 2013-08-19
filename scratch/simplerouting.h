/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 University of Arizona
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as 
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Author: Junseok Kim <junseok@email.arizona.edu> <engr.arizona.edu/~junseok>
 */

#ifndef SHORTEST_PATH_ROUTING_H
#define SHORTEST_PATH_ROUTING_H

#include <list>
#include "ns3/ipv4-routing-protocol.h"
#include "ns3/nstime.h"
#include "ns3/log.h"
#include "ns3/ipv4.h"
#include "ns3/ipv4-route.h"
#include "ns3/pointer.h"
#include "ns3/double.h"
#include "ns3/ipv4-static-routing.h"
#include "simplerouting-repositories.h"
#include "message.h"


namespace ns3 {
namespace SimpleRouting {

NS_LOG_COMPONENT_DEFINE ("SimpleRouting");

#define SIMPLEROUTING_PORT_NUMBER   705

class RoutingProtocol : public Ipv4RoutingProtocol
{
public:
  static TypeId GetTypeId (void);

  RoutingProtocol ();  
  virtual ~RoutingProtocol ();
  
  // Below are from Ipv4RoutingProtocol
  virtual Ptr<Ipv4Route> RouteOutput (Ptr<Packet> p, const Ipv4Header &header, Ptr<NetDevice> oif, Socket::SocketErrno &sockerr);

  virtual bool RouteInput (Ptr<const Packet> p, const Ipv4Header &header, Ptr<const NetDevice> idev,
                           UnicastForwardCallback ucb, MulticastForwardCallback mcb,
                           LocalDeliverCallback lcb, ErrorCallback ecb);
  virtual void NotifyInterfaceUp (uint32_t interface);
  virtual void NotifyInterfaceDown (uint32_t interface);
  virtual void NotifyAddAddress (uint32_t interface, Ipv4InterfaceAddress address);
  virtual void NotifyRemoveAddress (uint32_t interface, Ipv4InterfaceAddress address);
  virtual void SetIpv4 (Ptr<Ipv4> ipv4);
  virtual void PrintRoutingTable (Ptr<OutputStreamWrapper> stream) const;
  
  void sendHello ();
  void processHello(message m);
  void RecvSR (Ptr<Socket> socket);

  NeighborSet GetNeighbors(){
	  return m_ns;
  }
  

protected:
  //virtual void DoInitialize (void);
private:

  void Initialize ();
  void DoDispose ();
  void SendToNeighbor(message m);
  void broadcastTreeSetup();
  void TreeSetupHandler(message m, Ipv4Address Sender);
  void AddRoutingEntry(SinkNode sn, HopDetails hd){
	  m_rt[sn] = hd;
  }

  Ipv4Address LookupRoute(Ipv4Address Destination){
	  RoutingTable::iterator it;

	  for (it = m_rt.begin(); it!=m_rt.end();it++){
		  if (it->first.MainAddr == Destination){
			  return (it->second.MainAddr);
		  }
	  }
	  //There is nothing in the lookup table yet. This needs to be Destination.
	  return Destination;//m_address;

  }

  std::map< Ptr<Socket>, Ipv4InterfaceAddress > m_socketAddresses;
  Ptr<Socket> m_socket;
  NeighborSet m_ns;
  ChildSet m_cs;
  Parent m_p;
  RoutingTable m_rt;
  Time m_helloInterval;
  Ipv4Address m_address;
  Ipv4Address m_broadcast;
  Ptr<Ipv4> m_ipv4;
  uint32_t m_ifaceId;
  vector<int> ProcessedMessages;

};


NS_OBJECT_ENSURE_REGISTERED (RoutingProtocol);

TypeId
RoutingProtocol::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::SimpleRouting::RoutingProtocol")
    .SetParent<Ipv4RoutingProtocol> ()
    .AddConstructor<RoutingProtocol> ()
     .AddAttribute ("HelloInterval", "HELLO messages emission interval.",
                      TimeValue (Seconds (60)),
                      MakeTimeAccessor (&RoutingProtocol::m_helloInterval),
                      MakeTimeChecker ())
    ;
  return tid;
}


RoutingProtocol::RoutingProtocol ()
{
  NS_LOG_FUNCTION_NOARGS ();
	//GetObject<Node> ()
	//NS_LOG_INFO("Routing Start");//<<GetObject<Node> ()->GetId());//DynamicCast <WSNBaseNode>(GetObject<Node> ())->NodeID);
  //init ();
}

RoutingProtocol::~RoutingProtocol ()
{
  NS_LOG_FUNCTION_NOARGS ();

}

void RoutingProtocol::DoDispose(){
	  if (m_socket != 0)
		  {
			m_socket->Close ();
			m_socket->SetRecvCallback (MakeNullCallback<void, Ptr<Socket> > ());
		  }
	  Ipv4RoutingProtocol::DoDispose ();
}

void RoutingProtocol::Initialize (void)
{
	NS_LOG_INFO("Routing Start" <<DynamicCast <WSNBaseNode>(GetObject<Node> ())->NodeID);//GetObject<Node> ()->GetId());
    if (m_socket == 0)
	{

	  TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
	  m_socket = Socket::CreateSocket (GetObject<Node> (), tid);
	  m_socket->SetAllowBroadcast(true);
	  InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), SIMPLEROUTING_PORT_NUMBER);
	  m_socket->Bind (local);

	  m_socket->BindToNetDevice (m_ipv4->GetNetDevice (1));
	  m_socketAddresses[m_socket] = m_ipv4->GetAddress (1, 0);


	}
	 //m_socket->SetRecvCallback (MakeCallback (&ns3::SimpleRouting::RoutingProtocol::RecvSR, this));
     m_socket->SetRecvCallback (MakeCallback (&RoutingProtocol::RecvSR,  this));
	 Simulator::Schedule(Seconds(0.0), &ns3::SimpleRouting::RoutingProtocol::sendHello,this);
}

void RoutingProtocol::broadcastTreeSetup(){

	          	Ipv4InterfaceAddress iaddr = m_ipv4->GetAddress (1,0);
	          	Ipv4Address addri = iaddr.GetLocal ();

	          	Ptr<WSNSinkNode> ThisNode = DynamicCast<WSNSinkNode> (GetObject<Node> ());

	          	message m;

	          	m.type = TREESETUP;
	          	m.originator = ThisNode->NodeID;
	          	m.sender  = ThisNode->NodeID;
	          	m.receiver = ALL;
	          	m.path.clear();
	          	m.path.push_back(ThisNode->NodeID);
	          	m.flooding = true;
	          	m.sequence = ThisNode->getNewSeq();
	          	m.MiscAddress = addri;
	          	SendToNeighbor(m);
}

void RoutingProtocol::RecvSR (Ptr<Socket> socket){
	NS_LOG_INFO("RecvSR");
	 Ptr<Packet> packet;
	  Address from;
	  while (packet = socket->RecvFrom (from))
		{
		  if (InetSocketAddress::IsMatchingType (from))
			{
			  NS_LOG_INFO ("Received " << packet->GetSize () << " bytes from " <<
						   InetSocketAddress::ConvertFrom (from).GetIpv4 () << " Time:" <<Simulator::Now ().GetSeconds());





			  packet->RemoveAllPacketTags ();
			  packet->RemoveAllByteTags ();

			  uint8_t * buff = new uint8_t[packet->GetSerializedSize()];

			  packet->CopyData(buff, packet->GetSerializedSize());

			  message m(buff);

			  NS_LOG_INFO (DynamicCast <WSNBaseNode>(GetObject<Node> ())->NodeID<<  " got Packet from: "<< m.sender );

			  //message m;

			  vector<int>::iterator it;
			 				it = ProcessedMessages.begin();
			 				while (true){

			 					if (it == ProcessedMessages.end()){
			 						break;
			 					}
			 					if ((*it) == m.sequence){
			 						NS_LOG_INFO("Message Kicked (Dup) " << m.sequence);
			 						return;
			 					}
			 					it++;
			 				}

			 				 ProcessedMessages.push_back(m.sequence);

			  switch (m.type){

			case TREESETUP:
				//if (DynamicCast<WSNSinkNode> (GetObject<Node> ())){
					 //Ignore
				 // }else{
					  TreeSetupHandler(m, InetSocketAddress::ConvertFrom (from).GetIpv4 ());
				 // }
				break;
			case MYPATH:
				//a3(m);
				break;
			case HELLO:
				processHello(m);
				break;
			case DATA:
				//dataProcessor(m);
				break;
			case MAXLEVELANNOUNCE:

				break;
			case MAXLEVELRESET:
				break;
			case LOST:
				//a5(m);
				break;
			case LIFEPROBE:

				break;
			case LIFERESPONSE:

				break;
			case SINKSHIFT:
				//a8(m);
				break;


		}

			  //NS_LOG_LOGIC ("Echoing packet");
			  //socket->SendTo (packet, 0, from);
			}
		}

}

void RoutingProtocol::sendHello ()
{
	Simulator::Schedule(m_helloInterval, &ns3::SimpleRouting::RoutingProtocol::sendHello,this);


	message m;
	m.type = HELLO;
	m.originator =DynamicCast <WSNBaseNode>(GetObject<Node> ())->NodeID;//SensorNodePtr->NodeID;
	m.sender= DynamicCast <WSNBaseNode>(GetObject<Node> ())->NodeID;//SensorNodePtr->NodeID;
	m.receiver = ALL;
	m.MiscAddress = m_ipv4->GetAddress (1, 0).GetLocal();
	m.sequence = DynamicCast <WSNBaseNode>(GetObject<Node> ())->getNewSeq();

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
		 socket->SendTo (pkt1, 0, InetSocketAddress (destination, SIMPLEROUTING_PORT_NUMBER));

	  }

}

void RoutingProtocol::processHello(message m){
	NeighborSet::iterator it;

	bool found = false;

	for (it = m_ns.begin(); it != m_ns.end();it++){
		if (((Neighbor)*it).ID == m.sender ){
			found = true;
			break;
		}
	}

	if (found == false){
		Neighbor t;
		t.ID = m.sender;
		t.neighborMainAddr = m.MiscAddress;
		m_ns.push_back(t);

	}else{
		//SensorNodePtr->duplicated.insert(m.sender);
	}
}

Ptr<Ipv4Route>
RoutingProtocol::RouteOutput (Ptr<Packet> p, const Ipv4Header &header, Ptr<NetDevice> oif, enum Socket::SocketErrno &sockerr)
{
  Ipv4Address relay = LookupRoute(header.GetDestination ());//header.GetDestination ();//m_rtable->LookupRoute (m_address, header.GetDestination ());
  NS_LOG_FUNCTION (this << "ME: "<<m_ipv4->GetAddress (1, 0).GetLocal() << "->" << relay << "->" << header.GetDestination ());
  NS_LOG_INFO ("Relay to " << relay);
  if (m_address == relay)
    {
      NS_LOG_DEBUG ("Can't find route!!");
    }

  Ptr<Ipv4Route> route = Create<Ipv4Route> ();
  route->SetGateway (relay);
  route->SetSource (m_address);
  route->SetDestination (header.GetDestination ());
  route->SetOutputDevice (m_ipv4->GetNetDevice (m_ifaceId));

  sockerr = Socket::ERROR_NOTERROR;

  return route;
}

bool
RoutingProtocol::RouteInput (Ptr<const Packet> p, const Ipv4Header &header, Ptr<const NetDevice> idev,
                             UnicastForwardCallback ucb, MulticastForwardCallback mcb,
                             LocalDeliverCallback lcb, ErrorCallback ecb)
{
  //NS_LOG_FUNCTION (header.GetDestination ());
  NS_LOG_FUNCTION (this << "ME: "<< m_ipv4->GetAddress (1, 0).GetLocal() << "->" << "RI" << "->" << header.GetDestination ());
  if (header.GetDestination () == m_address)
    {
      NS_LOG_DEBUG ("I'm the destination");
      lcb (p, header, m_ipv4->GetInterfaceForDevice (idev));
      return true;
    }
  else if (header.GetDestination () == m_broadcast)
    {
      NS_LOG_DEBUG ("It's broadcast");
      lcb (p, header, m_ipv4->GetInterfaceForDevice (idev));
      return true;
    }
  else
    {
      Ipv4Address relay = LookupRoute(header.GetDestination ());//header.GetDestination ();//m_rtable->LookupRoute (m_address, header.GetDestination ());
      NS_LOG_FUNCTION (this << m_address << "->" << relay << "->" << header.GetDestination ());
      NS_LOG_DEBUG ("Relay to " << relay);
      if (m_address == relay)
        {
          NS_LOG_DEBUG ("Can't find a route!!");
        }
      Ptr<Ipv4Route> route = Create<Ipv4Route> ();
      route->SetGateway (relay);
      route->SetSource (header.GetSource ());
      route->SetDestination (header.GetDestination ());
      route->SetOutputDevice (m_ipv4->GetNetDevice (m_ifaceId));
      ucb (route, p, header);
      return true;
    }
  return false;
}

void
RoutingProtocol::NotifyInterfaceUp (uint32_t interface)
{
  NS_LOG_FUNCTION (this << interface);
  Initialize ();
  if (DynamicCast<WSNSinkNode> (GetObject<Node> ())){
	  Ptr<WSNSinkNode> ThisNode = DynamicCast<WSNSinkNode> (GetObject<Node> ());
	  if (ThisNode->Active){
		  //schedule broadcast
		  Simulator::Schedule(Seconds(10.0), &ns3::SimpleRouting::RoutingProtocol::broadcastTreeSetup,this);
	  }
  }

}
void
RoutingProtocol::NotifyInterfaceDown (uint32_t interface)
{
  NS_LOG_FUNCTION (this << interface);
  if (m_socket != 0)
  {
	m_socket->Close ();
	m_socket->SetRecvCallback (MakeNullCallback<void, Ptr<Socket> > ());
  }
}
void
RoutingProtocol::NotifyAddAddress (uint32_t interface, Ipv4InterfaceAddress address)
{
  NS_LOG_FUNCTION(this << interface << address );//<< m_rtable);
  m_ifaceId = interface;
  m_address = address.GetLocal ();
  m_broadcast = address.GetBroadcast ();
}
void
RoutingProtocol::NotifyRemoveAddress (uint32_t interface, Ipv4InterfaceAddress address)
{
  NS_LOG_FUNCTION(this << interface << address);
}
void
RoutingProtocol::SetIpv4 (Ptr<Ipv4> ipv4)
{
  NS_LOG_FUNCTION(this << ipv4);
  m_ipv4 = ipv4;
}
void
RoutingProtocol::PrintRoutingTable (Ptr<OutputStreamWrapper> stream) const
{

}

void RoutingProtocol::SendToNeighbor(message m){

	  ns3::SimpleRouting::NeighborSet CnSet = GetNeighbors();
	  ns3::SimpleRouting::NeighborSet::iterator iter;
	  for(iter = CnSet.begin(); iter != CnSet.end(); iter++){

			//NS_LOG_INFO (SensorNodePtr->NodeID <<  " Sending Packet to: "<< (iter)->neighborMainAddr);
			m_socket->Connect (InetSocketAddress ((iter)->neighborMainAddr,SIMPLEROUTING_PORT_NUMBER));
			string mess_output = m.Output();
			Ptr<Packet> pkt1 = Create<Packet> (reinterpret_cast<const uint8_t*> (mess_output.c_str()), mess_output.length());
			m_socket->Send (pkt1);

	  }

}

void RoutingProtocol::TreeSetupHandler(message m, Ipv4Address Sender){
	int p = m.path.size();


	//See if path contains redundant paths wich make a loop;
	set<int> dups;
	pair<set<int>::iterator,bool> ret;
	for (int i = 0; i < p ; i++){
		ret = dups.insert(m.path[i]);
		if (ret.second == false){
			NS_LOG_INFO(m_address<<" Duplicates in Path");
			return;
		}
	}
/*
	ret = dups.insert(SensorNodePtr->NodeID);
	if (ret.second == false){
		//cout<<"Duplicates in Path"<<endl;
		return;
	}
*/
	///////////////////////////////
	/*if (SensorNodePtr->level != -1 && p >= SensorNodePtr->level){
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
*/


	//TODO: some calc to see who keeps the sensor. right now last in wins
	//sinkAdd = m.MiscAddress;

	//cout<<"TreeSetup: "<<ID<<" SINK:"<<m.originator<<endl;

	//sets level and then removes it if it is a child.
	//SensorNodePtr->level = p;

	HopDetails CurrentHop;
	CurrentHop.ID = m.sender;
	CurrentHop.MainAddr = Sender;
	CurrentHop.Hops = p;

	SinkNode Sn;
	Sn.ID = m.originator;
	Sn.MainAddr = m.MiscAddress;

	NS_LOG_INFO("Sinks Addy:"<<m.MiscAddress);

	//m_rt[Sn] = CurrentHop;
	AddRoutingEntry(Sn,CurrentHop);

	//setup sensor for future transmittals. Sinks are only for routing so this is skipped.
	if (DynamicCast <WSNSensorNode>(GetObject<Node> ())){
		DynamicCast <WSNSensorNode>(GetObject<Node> ())->pathFromSink = m.path;
		DynamicCast <WSNSensorNode>(GetObject<Node> ())->pathFromSink.push_back(DynamicCast <WSNSensorNode>(GetObject<Node> ())->NodeID);
		DynamicCast <WSNSensorNode>(GetObject<Node> ())->sinkAdd = Sn.MainAddr;
		NS_LOG_INFO("Sinks Addy after:"<<DynamicCast <WSNSensorNode>(GetObject<Node> ())->sinkAdd);
			vector<NODE_ID>::iterator myit;
			for (myit = m.path.begin(); myit != m.path.end() ; myit++){
				NS_LOG_INFO(*myit);
			}
	}


	m.path.push_back(DynamicCast <WSNBaseNode>(GetObject<Node> ())->NodeID);
	//SensorNodePtr->parent = m.sender;

	m_p.ID = m.sender;
	m_p.parentMainAddr = Sender;



	//SensorNodePtr->children.erase(m.sender);
	//SensorNodePtr->disconnected = false;

	message m1 = m;

	//m1.type = TREESETUP;
	//m1.originator  = m.originator;
	m1.sender = DynamicCast <WSNBaseNode>(GetObject<Node> ())->NodeID;
	//m1.path = m.path;
	//m1.sequence = m.sequence;
	//m1.flooding = true;
	SendToNeighbor(m1);


	//SensorNodePtr->power -= .000066912;

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




} //namespace ns3

}
#endif /* SHORTEST_PATH_ROUTING_H */
