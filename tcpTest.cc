/* 
 * Author: Jorge Canellas Lardies
 *
 * ns3 script to test diferent TCP Congestion control algorithms
 * response to diferent path properties.
 * 
 * Based on examples given in the ns3 tutorial.
 *
 * Protocols:
 *   1. Tcp Reno
 *   2. Tcp Tahoe
 *   3. Tcp NewReno
 * 
 * Path properties:
 *   1. Delay
 *   2. Data rate
 *   3. Queue Length
 *
 * Measurements:
 *  1. Congestion window changes
 *  2. Delay
 *  3. Throughput
 */


#include <fstream>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("SixthScriptExample");

// ===========================================================================
//
//         node 0                 node 1
//   +----------------+    +----------------+
//   |    ns-3 TCP    |    |    ns-3 TCP    |
//   +----------------+    +----------------+
//   |    10.1.1.1    |    |    10.1.1.2    |
//   +----------------+    +----------------+
//   | point-to-point |    | point-to-point |
//   +----------------+    +----------------+
//           |                     |
//           +---------------------+
//                5 Mbps, 2 ms
//
//
// We want to look at changes in the ns-3 TCP congestion window.  We need
// to crank up a flow and hook the CongestionWindow attribute on the socket
// of the sender.  Normally one would use an on-off application to generate a
// flow, but this has a couple of problems.  First, the socket of the on-off 
// application is not created until Application Start time, so we wouldn't be 
// able to hook the socket (now) at configuration time.  Second, even if we 
// could arrange a call after start time, the socket is not public so we 
// couldn't get at it.
//
// So, we can cook up a simple version of the on-off application that does what
// we want.  On the plus side we don't need all of the complexity of the on-off
// application.  On the minus side, we don't have a helper, so we have to get
// a little more involved in the details, but this is trivial.
//
// So first, we create a socket and do the trace connect on it; then we pass 
// this socket into the constructor of our simple application which we then 
// install in the source node.
// ===========================================================================
//
class MyApp : public Application 
{
public:

  MyApp ();
  virtual ~MyApp();

  void Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate);

private:
  virtual void StartApplication (void);
  virtual void StopApplication (void);

  void ScheduleTx (void);
  void SendPacket (void);

  Ptr<Socket>     m_socket;
  Address         m_peer;
  uint32_t        m_packetSize;
  uint32_t        m_nPackets;
  DataRate        m_dataRate;
  EventId         m_sendEvent;
  bool            m_running;
  uint32_t        m_packetsSent;
};

MyApp::MyApp ()
  : m_socket (0), 
    m_peer (), 
    m_packetSize (0), 
    m_nPackets (0), 
    m_dataRate (0), 
    m_sendEvent (), 
    m_running (false), 
    m_packetsSent (0)
{
}

MyApp::~MyApp()
{
  m_socket = 0;
}

void
MyApp::Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate)
{
  m_socket = socket;
  m_peer = address;
  m_packetSize = packetSize;
  m_nPackets = nPackets;
  m_dataRate = dataRate;
}

void
MyApp::StartApplication (void)
{
  m_running = true;
  m_packetsSent = 0;
  m_socket->Bind ();
  m_socket->Connect (m_peer);
  SendPacket ();
}

void 
MyApp::StopApplication (void)
{
  m_running = false;

  if (m_sendEvent.IsRunning ())
    {
      Simulator::Cancel (m_sendEvent);
    }

  if (m_socket)
    {
      m_socket->Close ();
    }
}

void 
MyApp::SendPacket (void)
{
  Ptr<Packet> packet = Create<Packet> (m_packetSize);
  m_socket->Send (packet);

  if (++m_packetsSent < m_nPackets)
    {
      ScheduleTx ();
    }
}

void 
MyApp::ScheduleTx (void)
{
  if (m_running)
    {
      Time tNext (Seconds (m_packetSize * 8 / static_cast<double> (m_dataRate.GetBitRate ())));
      m_sendEvent = Simulator::Schedule (tNext, &MyApp::SendPacket, this);
    }
}

static void
CwndChange (Ptr<OutputStreamWrapper> stream, uint32_t oldCwnd, uint32_t newCwnd)
{
  NS_LOG_UNCOND (Simulator::Now ().GetSeconds () << "\t" << newCwnd);
  *stream->GetStream () << Simulator::Now ().GetSeconds () << "\t" << newCwnd << std::endl;
}

static void
RxDrop (Ptr<PcapFileWrapper> file, Ptr<const Packet> p)
{
  NS_LOG_UNCOND ("RxDrop at " << Simulator::Now ().GetSeconds ());
  file->Write (Simulator::Now (), p);
}

int 
main (int argc, char *argv[])
{
  uint32_t nTcp = 1;    			//tcp protocol
  uint32_t queueLength = 100;	//Queue length of the app 
  //uint32_t delay = 2;					//Delay in ms
	//uint32_t dataRate = 5;			//Data rate in Mbps
  CommandLine cmd; 						//Enables command line atributes.
	// Add a new arguments
  cmd.AddValue("tcpModel", "Tcp Model(reno:1, tahoe:2, newReno:3, rfc793:4", nTcp); 
  cmd.AddValue("queueLength", "Max queue length in packets", queueLength); 
	//cmd.AddValue("delay", "Delay in ms", delay); 
	//cmd.AddValue("dataRate", "Data rate in Mbps", dataRate); 
  cmd.Parse (argc, argv);
   
  std::ostringstream tcpModel;  

  switch(nTcp){
		case 1:
			tcpModel << "ns3::TcpReno";
			break;
		case 2:
			tcpModel << "ns3::TcpTahoe";
			break;
		case 3:
			tcpModel << "ns3::TcpNewReno";
			break;
		case 4:
			tcpModel << "ns3::TcpRfc793";
	 		break;
  }

  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", 
                      StringValue (tcpModel.str ()));
  Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (1000));
  Config::SetDefault ("ns3::TcpSocket::DelAckCount", UintegerValue (1));
  Config::SetDefault ("ns3::DropTailQueue::MaxPackets", UintegerValue(queueLength));
 

  
  // Set up the topology.

  NodeContainer nodes;
  nodes.Create (2);

  PointToPointHelper pointToPoint;
  //pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  //pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));
	//Ptr<Queue> q = CreateObject<DropTailQueue> ();  
	//pointToPoint.SetQueue(q);
			//CreateObject<DropTailQueue>()->SetAttribute("MaxPackets",10));

  NetDeviceContainer devices;
  devices = pointToPoint.Install (nodes);
  Ptr<RateErrorModel> em = CreateObjectWithAttributes<RateErrorModel> (
      "RanVar", RandomVariableValue (UniformVariable (0., 1.)),
      "ErrorRate", DoubleValue (0.00001));
  devices.Get (1)->SetAttribute ("ReceiveErrorModel", PointerValue (em));
  
	//The topology is now created, we build now the stack protocol.
	InternetStackHelper stack;
  stack.Install (nodes);

 	//Assign IPv4 address to the nodes:
  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.252");
  Ipv4InterfaceContainer interfaces = address.Assign (devices);

 	// Set up the address and the port of the sink(server):
	uint16_t sinkPort = 8080;
  Address sinkAddress (InetSocketAddress (interfaces.GetAddress (1), sinkPort));

	//Set up the tcp protocol of the sink(server) app, and install it in the node:
	PacketSinkHelper packetSinkHelper (
			"ns3::TcpSocketFactory",  		// Tcp protocol
			InetSocketAddress (						// Where:
					Ipv4Address::GetAny (), 	// Returns 0.0.0.0 This device(server)
					sinkPort									// Server port
			)
	);
  ApplicationContainer sinkApps = packetSinkHelper.Install (nodes.Get (1));
  
	//set up start time and stop time:
	sinkApps.Start (Seconds (0.));
  sinkApps.Stop (Seconds (20.));

	// Create the client socket
	Ptr<Socket> ns3TcpSocket = 	Socket::CreateSocket (
																nodes.Get (0), // The client 
																TcpSocketFactory::GetTypeId () //tcp protocol
															);

	// Create the client application that will send the traffic and monitorice
	// the congestion window
	Ptr<MyApp> app = CreateObject<MyApp> ();
  app->Setup (ns3TcpSocket, 			// Client tcp socket
							sinkAddress, 				// Server @ and port
							1040, 							// packet size
							1000, 							// number of packets to be sent
							DataRate ("1Mbps")	// Data generation rate
	);
  nodes.Get (0)->AddApplication (app);
  app->SetStartTime (Seconds (1.));
  app->SetStopTime (Seconds (20.));

  AsciiTraceHelper asciiTraceHelper;
  Ptr<OutputStreamWrapper> stream = asciiTraceHelper.CreateFileStream ("tcptest.cwnd");
  ns3TcpSocket->TraceConnectWithoutContext (
											"CongestionWindow", 	// What do we want to trace
											MakeBoundCallback (
													&CwndChange, 
													stream
											)); 

	// Pcap helper to trace all the events in wireshark
  PcapHelper pcapHelper;
  Ptr<PcapFileWrapper> file = pcapHelper.CreateFile ("tcptest.pcap", std::ios::out, PcapHelper::DLT_PPP);
  pointToPoint.EnablePcapAll("tcpTestpcap");
  
	// We trace the packets dropped
	devices.Get (1)->TraceConnectWithoutContext ("PhyRxDrop", MakeBoundCallback (&RxDrop, file));

  Simulator::Stop (Seconds (20));
  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}

