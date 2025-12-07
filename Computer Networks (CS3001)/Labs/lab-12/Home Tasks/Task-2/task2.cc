#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/netanim-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/traffic-control-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("Task2Simulation");

// --- TRACE FUNCTIONS ---

// 1. Trace Queues: Logs queue size (old vs new)
void QueueTrace(Ptr<OutputStreamWrapper> stream, uint32_t oldValue, uint32_t newValue)
{
	*stream->GetStream() << Simulator::Now().GetSeconds() << " " << newValue << std::endl;
}

// 2. Trace Throughput: Logs received bytes
void RxTrace(Ptr<OutputStreamWrapper> stream, Ptr<const Packet> packet, const Address &addr)
{
	*stream->GetStream() << Simulator::Now().GetSeconds() << " " << packet->GetSize() * 8
						 << std::endl;
}

// 3. Trace Drops: Logs dropped packets
void PktDropTrace(Ptr<OutputStreamWrapper> stream, Ptr<const Packet> packet)
{
	*stream->GetStream() << Simulator::Now().GetSeconds() << " DROP" << std::endl;
}

int main(int argc, char *argv[])
{
	Time::SetResolution(Time::NS);

	// --- 1. Create Nodes ---
	NodeContainer nodes;
	nodes.Create(4);
	// n0=UDP Source, n1=TCP Source, n2=Router, n3=Sink

	// --- 2. Install Mobility (Required to silence NetAnim warnings) ---
	MobilityHelper mobility;
	mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility.Install(nodes);

	// --- 3. Create Links ---
	// Link A: n0 <-> n2 (2 Mbps, 10 ms)
	PointToPointHelper p2pSide;
	p2pSide.SetDeviceAttribute("DataRate", StringValue("2Mbps"));
	p2pSide.SetChannelAttribute("Delay", StringValue("10ms"));
	p2pSide.SetQueue("ns3::DropTailQueue", "MaxSize", StringValue("10p"));

	// Link B: n1 <-> n2 (Same as above)

	// Link C: n2 <-> n3 (1.7 Mbps, 20 ms) - THE BOTTLENECK
	PointToPointHelper p2pBottle;
	p2pBottle.SetDeviceAttribute("DataRate", StringValue("1.7Mbps"));
	p2pBottle.SetChannelAttribute("Delay", StringValue("20ms"));
	p2pBottle.SetQueue("ns3::DropTailQueue", "MaxSize", StringValue("10p"));

	// Install Devices
	NetDeviceContainer d0d2 = p2pSide.Install(nodes.Get(0), nodes.Get(2));
	NetDeviceContainer d1d2 = p2pSide.Install(nodes.Get(1), nodes.Get(2));
	NetDeviceContainer d2d3 = p2pBottle.Install(nodes.Get(2), nodes.Get(3));

	// --- 4. Install Internet Stack ---
	InternetStackHelper stack;
	stack.Install(nodes);

	// --- 5. Assign IP Addresses ---
	Ipv4AddressHelper address;

	address.SetBase("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer i0i2 = address.Assign(d0d2);

	address.SetBase("10.1.2.0", "255.255.255.0");
	Ipv4InterfaceContainer i1i2 = address.Assign(d1d2);

	address.SetBase("10.1.3.0", "255.255.255.0");
	Ipv4InterfaceContainer i2i3 = address.Assign(d2d3);

	// --- 6. Enable Global Routing (CRITICAL FIX) ---
	Ipv4GlobalRoutingHelper::PopulateRoutingTables();

	// --- 7. Setup Traffic Sources ---

	// -> UDP Flow (Red) -> n0 to n3 (Port 9)
	uint16_t udpPort = 9;
	PacketSinkHelper packetSinkHelper("ns3::UdpSocketFactory",
									  InetSocketAddress(Ipv4Address::GetAny(), udpPort));
	ApplicationContainer sinkAppsUDP = packetSinkHelper.Install(nodes.Get(3));
	sinkAppsUDP.Start(Seconds(0.0));
	sinkAppsUDP.Stop(Seconds(5.0));

	OnOffHelper onoff("ns3::UdpSocketFactory",
					  Address(InetSocketAddress(i2i3.GetAddress(1), udpPort)));
	onoff.SetConstantRate(DataRate("819200bps")); // 1024 * 8 * 100
	onoff.SetAttribute("PacketSize", UintegerValue(1024));
	ApplicationContainer clientAppsUDP = onoff.Install(nodes.Get(0));
	clientAppsUDP.Start(Seconds(0.1));
	clientAppsUDP.Stop(Seconds(4.5));

	// -> TCP Flow (Blue) -> n1 to n3 (Port 50000)
	uint16_t tcpPort = 50000;
	PacketSinkHelper tcpSinkHelper("ns3::TcpSocketFactory",
								   InetSocketAddress(Ipv4Address::GetAny(), tcpPort));
	ApplicationContainer sinkAppsTCP = tcpSinkHelper.Install(nodes.Get(3));
	sinkAppsTCP.Start(Seconds(0.0));
	sinkAppsTCP.Stop(Seconds(5.0));

	BulkSendHelper source("ns3::TcpSocketFactory", InetSocketAddress(i2i3.GetAddress(1), tcpPort));
	source.SetAttribute("MaxBytes", UintegerValue(0)); // Unlimited
	ApplicationContainer clientAppsTCP = source.Install(nodes.Get(1));
	clientAppsTCP.Start(Seconds(0.5));
	clientAppsTCP.Stop(Seconds(4.0));

	// --- 8. Tracing & Data Collection ---

	// A. FlowMonitor
	FlowMonitorHelper flowmon;
	Ptr<FlowMonitor> monitor = flowmon.InstallAll();

	AsciiTraceHelper ascii;

	// B. Throughput Traces
	Ptr<OutputStreamWrapper> streamUDP = ascii.CreateFileStream("udp_throughput.dat");
	sinkAppsUDP.Get(0)->TraceConnectWithoutContext("Rx", MakeBoundCallback(&RxTrace, streamUDP));

	Ptr<OutputStreamWrapper> streamTCP = ascii.CreateFileStream("tcp_throughput.dat");
	sinkAppsTCP.Get(0)->TraceConnectWithoutContext("Rx", MakeBoundCallback(&RxTrace, streamTCP));

	// C. Queue & Drop Traces
	// We hook into the bottleneck link (n2 -> n3)
	Ptr<OutputStreamWrapper> streamQueue = ascii.CreateFileStream("queue_occupancy.dat");
	Ptr<OutputStreamWrapper> streamDrops = ascii.CreateFileStream("drops.dat");

	// Get the Queue
	PointerValue ptr;
	d2d3.Get(0)->GetAttribute("TxQueue", ptr);
	Ptr<Queue<Packet>> txQueue = ptr.Get<Queue<Packet>>();

	if (txQueue)
	{
		// Trace 1: Queue Size (requires QueueTrace signature)
		txQueue->TraceConnectWithoutContext("PacketsInQueue",
											MakeBoundCallback(&QueueTrace, streamQueue));
	}

	// Trace 2: Drops (requires PktDropTrace signature)
	// Note: PhyTxDrop is on the NetDevice, not the Queue object directly
	d2d3.Get(0)->TraceConnectWithoutContext("PhyTxDrop",
											MakeBoundCallback(&PktDropTrace, streamDrops));

	// --- 9. NetAnim Visualization ---
	AnimationInterface anim("task2.xml");
	anim.SetConstantPosition(nodes.Get(0), 0.0, 0.0);
	anim.SetConstantPosition(nodes.Get(1), 0.0, 20.0);
	anim.SetConstantPosition(nodes.Get(2), 20.0, 10.0);
	anim.SetConstantPosition(nodes.Get(3), 40.0, 10.0);

	anim.UpdateNodeDescription(nodes.Get(0), "n0 (UDP Source)");
	anim.UpdateNodeDescription(nodes.Get(1), "n1 (TCP Source)");
	anim.UpdateNodeDescription(nodes.Get(2), "n2 (Router)");
	anim.UpdateNodeDescription(nodes.Get(3), "n3 (Sink)");

	// --- 10. Run ---
	Simulator::Stop(Seconds(5.0));
	Simulator::Run();

	// --- 11. Print Stats ---
	monitor->CheckForLostPackets();
	Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier>(flowmon.GetClassifier());
	std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats();

	for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin();
		 i != stats.end(); ++i)
	{
		Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow(i->first);
		if (t.sourceAddress == "10.1.1.1")
			std::cout << "Flow UDP (n0->n3): ";
		else if (t.sourceAddress == "10.1.2.1")
			std::cout << "Flow TCP (n1->n3): ";
		else
			std::cout << "Flow Unknown: ";

		std::cout << "TxPackets: " << i->second.txPackets << " RxPackets: " << i->second.rxPackets
				  << " LostPackets: " << i->second.lostPackets
				  << " Throughput: " << i->second.rxBytes * 8.0 / 5.0 / 1024 / 1024 << " Mbps\n";
	}

	Simulator::Destroy();
	return 0;
}
