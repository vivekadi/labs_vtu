#include<ns3/core-module.h>
#include<ns3/network-module.h>
#include<ns3/point-to-point-module.h>
#include<ns3/applications-module.h>
#include<ns3/internet-module.h>
#include<ns3/traffic-control-module.h>

using namespace ns3;
//////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[])
{
	CommandLine cmd;
	cmd.Parse(argc,argv);
	

	NodeContainer n;
	InternetStackHelper stack;
	PointToPointHelper p2p;
	Ipv4AddressHelper addr;
	Ipv4InterfaceContainer intr;
	NetDeviceContainer div;
	UdpEchoServerHelper echoserv(9);
	ApplicationContainer servapp;
	ApplicationContainer cliapp;
	ApplicationContainer sinkapp;
	ApplicationContainer app;
//////////////////////////////////////////////////////////////////////////////////
	
	n.Create(4);
	stack.Install(n);

	p2p.SetDeviceAttribute("DataRate",StringValue("5Mbps"));
	p2p.SetChannelAttribute("Delay",StringValue("1ms"));

	addr.SetBase("10.1.1.0","255.255.255.0");
	div=p2p.Install(n.Get(0),n.Get(2));
	intr=addr.Assign(div);
	
	addr.SetBase("10.1.2.0","255.255.255.0");
	div=p2p.Install(n.Get(1),n.Get(2));
	intr=addr.Assign(div);
	
	addr.SetBase("10.1.4.0","255.255.255.0");
	div=p2p.Install(n.Get(3),n.Get(2));
	intr=addr.Assign(div);

////////////////////////////////////////////////////////////////////////////////

	Ptr<RateErrorModel>em=CreateObject<RateErrorModel>();
	em->SetAttribute("ErrorRate",DoubleValue(0.0001));
	Ipv4GlobalRoutingHelper::PopulateRoutingTables();

	servapp=echoserv.Install(n.Get(3));
	servapp.Start(Seconds(1.0));
	servapp.Stop(Seconds(10.0));

	UdpEchoClientHelper echoclient(intr.GetAddress(1),9);
	echoclient.SetAttribute("MaxPackets",UintegerValue(30));
	echoclient.SetAttribute("Interval",TimeValue(Seconds(1.0)));
	echoclient.SetAttribute("PacketSize",UintegerValue(1024));

	cliapp=echoclient.Install(n.Get(0));
	cliapp.Start(Seconds(2.0));
	cliapp.Stop(Seconds(10.0));

////////////////////////////////////////////////////////////////////////////////////////////////
	
	std::string socketType="ns3::TcpSocketFactory";

	OnOffHelper onoff(socketType,Ipv4Address::GetAny());
	onoff.SetAttribute("OnTime",StringValue("ns3::ConstantRandomVariable[Constant=1]"));
	onoff.SetAttribute("OffTime",StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	onoff.SetAttribute("PacketSize",UintegerValue(1448));
	onoff.SetAttribute("DataRate",StringValue("1Mbps"));

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	Address localAddress1(InetSocketAddress(Ipv4Address::GetAny(),7));
	PacketSinkHelper packetSinkHelper1 (socketType,localAddress1);


	sinkapp=packetSinkHelper1.Install(n.Get(3));
	sinkapp.Start(Seconds(5.0));
	sinkapp.Stop(Seconds(10.0));

/////////////////////////////////////////////////////////////////////////////////////////////////////
	
	AddressValue remoteAddress(InetSocketAddress(intr.GetAddress(1),7));
	onoff.SetAttribute ("Remote",remoteAddress);

	app.Add(onoff.Install(n.Get(1)));
	app.Start(Seconds(6.0));
	app.Stop(Seconds(10.0));

///////////////////////////////////////////////////////////////////////////////////////////////////

	p2p.EnablePcapAll("t2");

	Simulator::Run();
	Simulator::Destroy();
	return 0;
	
}
