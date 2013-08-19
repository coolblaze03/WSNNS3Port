

#include "ns3/log.h"
#include "ns3/ipv4.h"
#include "ns3/ipv4-route.h"
#include "ns3/pointer.h"
#include "ns3/double.h"
#include "ns3/ipv4-static-routing.h"
#include "simplerouting.h"


NS_LOG_COMPONENT_DEFINE ("SimpleRouting");

namespace ns3 {
namespace SimpleRouting {

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
}

RoutingProtocol::~RoutingProtocol () 
{
  NS_LOG_FUNCTION_NOARGS ();
}

void RoutingProtocol::init () 
{
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

void RoutingProtocol::RecvSR (Ptr<Socket> socket){

	 Ptr<Packet> packet;
	  Address from;
	  while (packet = socket->RecvFrom (from))
		{
		  if (InetSocketAddress::IsMatchingType (from))
			{
			  NS_LOG_UNCOND ("Received " << packet->GetSize () << " bytes from " <<
						   InetSocketAddress::ConvertFrom (from).GetIpv4 ());





			  packet->RemoveAllPacketTags ();
			  packet->RemoveAllByteTags ();

			  uint8_t * buff = new uint8_t[packet->GetSerializedSize()];

			  packet->CopyData(buff, packet->GetSerializedSize());

			  message m(buff);

			  NS_LOG_UNCOND (m.receiver<<  " got Packet from: "<< m.sender );

			  //message m;

			  switch (m.type){

			case TREESETUP:
				break;
			case MYPATH:
				//a3(m);
				break;
			case HELLO:
				//a2(m);
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
	Simulator::Schedule(Seconds(m_helloInterval), &ns3::SimpleRouting::RoutingProtocol::sendHello,this);
	 
	 
	message m;
	m.type = HELLO;
	m.originator = GetObject<Node> ()->GetId();//DynamicCast <WSNBaseNode>(GetObject<Node> ())->NodeID;//SensorNodePtr->NodeID;
	m.sender= GetObject<Node> ()->GetId();//DynamicCast <WSNBaseNode>(GetObject<Node> ())->NodeID;//SensorNodePtr->NodeID;
	m.receiver = ALL;
	
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

Ptr<Ipv4Route>
RoutingProtocol::RouteOutput (Ptr<Packet> p, const Ipv4Header &header, Ptr<NetDevice> oif, enum Socket::SocketErrno &sockerr)
{
  Ipv4Address relay = m_address;//m_rtable->LookupRoute (m_address, header.GetDestination ());
  NS_LOG_FUNCTION (this << header.GetSource () << "->" << relay << "->" << header.GetDestination ());
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
  NS_LOG_FUNCTION (header.GetDestination ());

  if (header.GetDestination () == m_address)
    {
      NS_LOG_DEBUG ("I'm the destination");
      lcb (p, header, m_ipv4->GetInterfaceForDevice (idev));
      return true;
    }
  else if (header.GetDestination () == m_broadcast)
    {
      NS_LOG_DEBUG ("It's broadcast");
      return true;
    }
  else
    {
      Ipv4Address relay = m_address;//m_rtable->LookupRoute (m_address, header.GetDestination ());
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
}
void 
RoutingProtocol::NotifyInterfaceDown (uint32_t interface)
{
  NS_LOG_FUNCTION (this << interface);
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


}
} // namespace ns3


