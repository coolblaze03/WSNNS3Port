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
#include "ns3/simplerouting-repositories.h"
#include "message.h"


namespace ns3 {
namespace SimpleRouting {

#define SIMPLEROUTING_PORT_NUMBER   705

class RoutingProtocol;

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
  void RecvSR (Ptr<Socket> socket);
  
protected:
  virtual void DoInitialize (void);
private:

  void DoDispose ();

  std::map< Ptr<Socket>, Ipv4InterfaceAddress > m_socketAddresses;
  Ptr<Socket> m_socket;
  NeighborSet m_ns;
  ChildSet m_cs;
  Parent m_p;
  Time m_helloInterval;
  Ipv4Address m_address;
  Ipv4Address m_broadcast;
  Ptr<Ipv4> m_ipv4;
  uint32_t m_ifaceId;
  vector<int> ProcessedMessages;

};




} //namespace ns3

}
#endif /* SHORTEST_PATH_ROUTING_H */
