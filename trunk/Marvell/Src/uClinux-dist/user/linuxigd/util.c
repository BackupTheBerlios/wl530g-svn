#include <string.h>
#include <stdio.h>
#include <syslog.h>
#include <arpa/inet.h>
#include <linux/sockios.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>


int GetIpAddressStr(char *address, char *ifname)
{
	int	sockfd;
	struct	ifreq ifr;
	struct	sockaddr_in sin;
	int	ret=0;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if ( sockfd < 0) 
		return 0;		

	memset(&ifr,0,sizeof(struct ifreq));		
    	strcpy(ifr.ifr_name, ifname);
    	
    	if( address )
    	{
		memset(&ifr.ifr_addr, 0, sizeof(struct sockaddr));    	    
		if (ioctl(sockfd, SIOCGIFADDR, &ifr) == 0)
		{
			memcpy(&sin, &ifr.ifr_addr, sizeof(struct sockaddr)); 
			strcpy( address, inet_ntoa(sin.sin_addr) );
			ret = 1;
		}
	}

	close(sockfd);
	
	return ret;
}
