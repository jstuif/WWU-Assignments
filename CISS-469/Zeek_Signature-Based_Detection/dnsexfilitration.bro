export 
{
redef enum Notice::Type += {Exfiltration };
}

event dns_request(c: connection, msg: dns_msg, query: string, qtype: count, qclass: count)
{
	if ( |query| > 52 )
		{
			#bad_ip and bad_domain will print out the IP address and Domain name of the offending request
			NOTICE([$note=Exfiltration, $msg=fmt("Long Domain. Possible DNS exfiltration/tunnel by %s. Offending domain name: %s", c$id$resp_h, query)]);
		}
}
