#include	"unp.h"

int
main(int argc, char **argv)
{
    //sockfd: socket file descriptor
	int					sockfd, n;
	char				recvline[MAXLINE + 1];
    //struct sockaddr_in: Structure describing an Internet (IP) socket address, /linux-3.18.6/include/uapi/linux/in.h
	struct sockaddr_in	servaddr;

	if (argc != 2)
		err_quit("usage: a.out <IPaddress>");

    //AF_INET: Supported address families, Internet IP Protocol, /linux-3.18.6/include/linux/socket.h
    //#define AF_UNSPEC 0
    //#define AF_UNIX       1   /* Unix domain sockets      */
    //#define AF_LOCAL  1   /* POSIX name for AF_UNIX   */
    //#define AF_INET       2   /* Internet IP Protocol     */
    //#define AF_AX25       3   /* Amateur Radio AX.25      */
    //#define AF_IPX        4   /* Novell IPX           */
    //#define AF_APPLETALK  5   /* AppleTalk DDP        */
    //#define AF_NETROM 6   /* Amateur Radio NET/ROM    */
    //#define AF_BRIDGE 7   /* Multiprotocol bridge     */
    //#define AF_ATMPVC 8   /* ATM PVCs         */
    //#define AF_X25        9   /* Reserved for X.25 project    */
    //#define AF_INET6  10  /* IP version 6         */
    //#define AF_ROSE       11  /* Amateur Radio X.25 PLP   */
    //#define AF_DECnet 12  /* Reserved for DECnet project  */
    //#define AF_NETBEUI    13  /* Reserved for 802.2LLC project*/
    //#define AF_SECURITY   14  /* Security callback pseudo AF */
    //#define AF_KEY        15      /* PF_KEY key management API */
    //#define AF_NETLINK    16
    //#define AF_ROUTE  AF_NETLINK /* Alias to emulate 4.4BSD */
    //#define AF_PACKET 17  /* Packet family        */
    //#define AF_ASH        18  /* Ash              */
    //#define AF_ECONET 19  /* Acorn Econet         */
    //#define AF_ATMSVC 20  /* ATM SVCs         */
    //#define AF_RDS        21  /* RDS sockets          */
    //#define AF_SNA        22  /* Linux SNA Project (nutters!) */
    //#define AF_IRDA       23  /* IRDA sockets         */
    //#define AF_PPPOX  24  /* PPPoX sockets        */
    //#define AF_WANPIPE    25  /* Wanpipe API Sockets */
    //#define AF_LLC        26  /* Linux LLC            */
    //#define AF_IB     27  /* Native InfiniBand address    */
    //#define AF_CAN        29  /* Controller Area Network      */
    //#define AF_TIPC       30  /* TIPC sockets         */
    //#define AF_BLUETOOTH  31  /* Bluetooth sockets        */
    //#define AF_IUCV       32  /* IUCV sockets         */
    //#define AF_RXRPC  33  /* RxRPC sockets        */
    //#define AF_ISDN       34  /* mISDN sockets        */
    //#define AF_PHONET 35  /* Phonet sockets       */
    //#define AF_IEEE802154 36  /* IEEE802154 sockets       */
    //#define AF_CAIF       37  /* CAIF sockets         */
    //#define AF_ALG        38  /* Algorithm sockets        */
    //#define AF_NFC        39  /* NFC sockets          */
    //#define AF_VSOCK  40  /* vSockets         */
    //#define AF_MAX        41  /* For now.. */

    //SOCK_STREAM: one of Socket types, stream (connection) socket, /linux-3.18.6/include/linux/net.h
    /**
     * enum sock_type - Socket types
     * @SOCK_STREAM: stream (connection) socket
     * @SOCK_DGRAM: datagram (conn.less) socket
     * @SOCK_RAW: raw socket
     * @SOCK_RDM: reliably-delivered message
     * @SOCK_SEQPACKET: sequential packet socket
     * @SOCK_DCCP: Datagram Congestion Control Protocol socket
     * @SOCK_PACKET: linux specific way of getting packets at the dev level.
     *         For writing rarp and other similar things on the user level.
     *
     * When adding some new socket type please
     * grep ARCH_HAS_SOCKET_TYPE include/asm-* /socket.h, at least MIPS
     * overrides this enum for binary compat reasons.
     */
    /*
     enum sock_type {
     SOCK_STREAM = 1,
     SOCK_DGRAM  = 2,
     SOCK_RAW    = 3,
     SOCK_RDM    = 4,
     SOCK_SEQPACKET  = 5,
     SOCK_DCCP   = 6,
     SOCK_PACKET = 10,
     };
     */
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
    //sin_family: sockaddr_in_family
	servaddr.sin_family = AF_INET;
    //htons: host to network short, /linux-3.18.6/include/linux/byteorder/generic.h
	servaddr.sin_port   = htons(13);	/* daytime server */
    //inet_pton: presentation to number
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

    //SA: def SA struct sockaddr
	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
	}
    
	if (n < 0)
		err_sys("read error");

	exit(0);
}
