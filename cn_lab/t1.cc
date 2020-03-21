
#include<ns3/core-module.h>                //***** Remember these packages as C-PAINT
#include<ns3/point-to-point-module.h>
#include<ns3/network-module.h>
#include<ns3/internet-module.h>
#include<ns3/applications-module.h>
#include<ns3/traffic-control-module.h>

using namespace ns3;


int main(int argc,char *argv[])
{
	CommandLine cmd;
	cmd.Parse(argc,argv);

	NodeContainer n;
	InternetStackHelper stk;
	PointToPointHelper p2p;
	Ipv4AddressHelper addr;
	NetDeviceContainer div;
	Ipv4InterfaceContainer inter;
	UdpEchoServerHelper ecoserv(12);				////
	ApplicationContainer servapp;
	ApplicationContainer cliapp;
	AsciiTraceHelper asc;
	
	n.Create(4);
	stk.Install(n);
	
	p2p.SetDeviceAttribute("DataRate",StringValue("5Mbps"));
	p2p.SetChannelAttribute("Delay", StringValue("1ms"));



	addr.SetBase("10.1.1.0","255.255.255.0");
	div=p2p.Install(n.Get(0),n.Get(1));
	inter=addr.Assign(div);

	addr.SetBase("10.1.2.0","255.255.255.0");
	div=p2p.Install(n.Get(1),n.Get(2));
	inter=addr.Assign(div);

	addr.SetBase("10.1.3.0","255.255.255.0");
	div=p2p.Install(n.Get(2),n.Get(3));
	inter=addr.Assign(div);



	Ptr<RateErrorModel> em=CreateObject<RateErrorModel>();
	em-> SetAttribute("ErrorRate",DoubleValue(0.0001));
	div.Get(0)->SetAttribute("ReceiveErrorModel",PointerValue(em));
	div.Get(1)->SetAttribute("ReceiveErrorModel",PointerValue(em));
	Ipv4GlobalRoutingHelper::PopulateRoutingTables();



	servapp= ecoserv.Install(n.Get(3));
	servapp.Start(Seconds(1.0));
	servapp.Stop(Seconds(10.0));

	UdpEchoClientHelper eclient(inter.GetAddress(1),9);
	eclient.SetAttribute("MaxPackets", UintegerValue(500));
	eclient.SetAttribute("Interval", TimeValue(Seconds(0.0)));
	eclient.SetAttribute("PacketSize", UintegerValue(1024));

	cliapp=eclient.Install(n.Get(0));
	cliapp.Start(Seconds(2.0));
	cliapp.Stop(Seconds(10.0));

	p2p.EnableAsciiAll(asc.CreateFileStream("t1.tr"));
	
	Simulator::Run();
	Simulator::Destroy();

	return 0;
}

	
	

	
	

