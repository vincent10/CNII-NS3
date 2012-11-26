
#reno
./waf --run "scratch/tcpTest --tcpModel=1 --queueLength=100 --ns3::PointToPointNetDevice::DataRate=1Mbps --ns3::PointToPointChannel::Delay=2ms"
cp tcptest.cwnd testResults/test1/tcptest1.cwnd
cp tcpTestpcap-0-0.pcap testResults/test1/tcptest1-0-0.pcap
cp tcpTestpcap-1-0.pcap testResults/test1/tcptest1-1-0.pcap
rm *.pcap
rm tcptest.*
#tahoe
./waf --run "scratch/tcpTest --tcpModel=2 --queueLength=100 --ns3::PointToPointNetDevice::DataRate=1Mbps --ns3::PointToPointChannel::Delay=2ms"
cp tcptest.cwnd testResults/test1/tcptest2.cwnd
cp tcpTestpcap-0-0.pcap testResults/test1/tcptest2-0-0.pcap
cp tcpTestpcap-1-0.pcap testResults/test1/tcptest2-1-0.pcap
rm *.pcap
rm tcptest.*
#newReno
./waf --run "scratch/tcpTest --tcpModel=3 --queueLength=100 --ns3::PointToPointNetDevice::DataRate=1Mbps --ns3::PointToPointChannel::Delay=2ms"
cp tcptest.cwnd testResults/test1/tcptest3.cwnd
cp tcpTestpcap-0-0.pcap testResults/test1/tcptest3-0-0.pcap
cp tcpTestpcap-1-0.pcap testResults/test1/tcptest3-1-0.pcap
rm *.pcap
rm tcptest.*
#rfc793
./waf --run "scratch/tcpTest --tcpModel=4 --queueLength=100 --ns3::PointToPointNetDevice::DataRate=1Mbps --ns3::PointToPointChannel::Delay=2ms"
cp tcptest.cwnd testResults/test1/tcptest4.cwnd
cp tcpTestpcap-0-0.pcap testResults/test1/tcptest4-0-0.pcap
cp tcpTestpcap-1-0.pcap testResults/test1/tcptest4-1-0.pcap
rm *.pcap
rm tcptest.*

##############################################################################

./waf --run "scratch/tcpTest --tcpModel=1 --queueLength=20 --ns3::PointToPointNetDevice::DataRate=5Mbps --ns3::PointToPointChannel::Delay=100ms"
cp tcptest.cwnd testResults/test2/tcptest1.cwnd
cp tcpTestpcap-0-0.pcap testResults/test2/tcptest1-0-0.pcap
cp tcpTestpcap-1-0.pcap testResults/test2/tcptest1-1-0.pcap
rm *.pcap
rm tcptest.*

./waf --run "scratch/tcpTest --tcpModel=2 --queueLength=20 --ns3::PointToPointNetDevice::DataRate=5Mbps --ns3::PointToPointChannel::Delay=100ms"
cp tcptest.cwnd testResults/test2/tcptest2.cwnd
cp tcpTestpcap-0-0.pcap testResults/test2/tcptest2-0-0.pcap
cp tcpTestpcap-1-0.pcap testResults/test2/tcptest2-1-0.pcap
rm *.pcap
rm tcptest.*

./waf --run "scratch/tcpTest --tcpModel=3 --queueLength=20 --ns3::PointToPointNetDevice::DataRate=5Mbps --ns3::PointToPointChannel::Delay=100ms"
cp tcptest.cwnd testResults/test2/tcptest3.cwnd
cp tcpTestpcap-0-0.pcap testResults/test2/tcptest3-0-0.pcap
cp tcpTestpcap-1-0.pcap testResults/test2/tcptest3-1-0.pcap
rm *.pcap
rm tcptest.*

./waf --run "scratch/tcpTest --tcpModel=4 --queueLength=20 --ns3::PointToPointNetDevice::DataRate=5Mbps --ns3::PointToPointChannel::Delay=100ms"
cp tcptest.cwnd testResults/test2/tcptest4.cwnd
cp tcpTestpcap-0-0.pcap testResults/test2/tcptest4-0-0.pcap
cp tcpTestpcap-1-0.pcap testResults/test2/tcptest4-1-0.pcap
rm *.pcap
rm tcptest.*

################################################################################

./waf --run "scratch/tcpTest --tcpModel=1 --queueLength=70 --ns3::PointToPointNetDevice::DataRate=10Mbps --ns3::PointToPointChannel::Delay=700ms"
cp tcptest.cwnd testResults/test3/tcptest1.cwnd
cp tcpTestpcap-0-0.pcap testResults/test3/tcptest1-0-0.pcap
cp tcpTestpcap-1-0.pcap testResults/test3/tcptest1-1-0.pcap
rm *.pcap
rm tcptest.*

./waf --run "scratch/tcpTest --tcpModel=2 --queueLength=70 --ns3::PointToPointNetDevice::DataRate=10Mbps --ns3::PointToPointChannel::Delay=700ms"
cp tcptest.cwnd testResults/test3/tcptest2.cwnd
cp tcpTestpcap-0-0.pcap testResults/test3/tcptest2-0-0.pcap
cp tcpTestpcap-1-0.pcap testResults/test3/tcptest2-1-0.pcap
rm *.pcap
rm tcptest.*

./waf --run "scratch/tcpTest --tcpModel=3 --queueLength=70 --ns3::PointToPointNetDevice::DataRate=10Mbps --ns3::PointToPointChannel::Delay=700ms"
cp tcptest.cwnd testResults/test3/tcptest3.cwnd
cp tcpTestpcap-0-0.pcap testResults/test3/tcptest3-0-0.pcap
cp tcpTestpcap-1-0.pcap testResults/test3/tcptest3-1-0.pcap
rm *.pcap
rm tcptest.*

./waf --run "scratch/tcpTest --tcpModel=4 --queueLength=70 --ns3::PointToPointNetDevice::DataRate=10Mbps --ns3::PointToPointChannel::Delay=700ms"
cp tcptest.cwnd testResults/test3/tcptest4.cwnd
cp tcpTestpcap-0-0.pcap testResults/test3/tcptest4-0-0.pcap
cp tcpTestpcap-1-0.pcap testResults/test3/tcptest4-1-0.pcap
rm *.pcap
rm tcptest.*


