#bin/sh


echo "Add the present system as the gateway in all other systems. For ex route add -net 12.34.0.0 netmask 255.255.0.0 gw myip" 

sudo sysctl net.ipv4.ip_forward=1;


