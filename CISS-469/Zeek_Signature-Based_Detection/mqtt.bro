module Mqtt;

export
{
	redef enum Notice::Type += {Subscribe };
}

event packet_contents(c: connection, contents: string)
{
	local flag = 0;
	local check = 0;
	for ( s in contents )
	{
		check += 1;
		if ( bytestring_to_hexstr(s) == "82")
		{
			flag = 1;
			local message = bytestring_to_count(hexstr_to_bytestring(bytestring_to_hexstr(contents[check:check+1])));
			if ( bytestring_to_hexstr(contents[message:message+1])  == "23" || bytestring_to_hexstr(contents[message+1:message+2]) == "23" && flag == 1 ){
				NOTICE([$note=Subscribe, $msg=fmt("%s attempts to subscribe to all topics.", c$id$orig_h)]);
		}		
		else
		{
			flag = 0;
		}		
		}
	}
}
