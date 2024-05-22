// Ethernet driver API

struct EthernetDriverInfo
{
    char name[64];
    char description[1024];
};
/* Returns the driver name and description */
const struct EthernetDriverInfo *ethernetDriverGetInfo();

struct EthernetDriverStat
{
    int received_packets;
    /* Number of received packets */
    int total_sent_packets;
    /* Number of sent packets (success and fail)*/
    int successfully_sent_packets; /* Number of successfully sent packets */
    int failed_sent_packets;
    /* Number of packets failed to send */
};
/* Returns statistics information of the Ethernet driver */
struct EthernetDriverStat ethernetDriverGetStatistics();

// Caller’s code

void ethShow()
{
    struct EthernetDriverStat eth_stat = ethernetDriverGetStatistics();
    printf("%i packets received\n", eth_stat.received_packets);
    printf("%i packets sent\n", eth_stat.total_sent_packets);
    printf("%i packets successfully sent\n", eth_stat.successfully_sent_packets);
    printf("%i packets failed to send\n", eth_stat.failed_sent_packets);

    const struct EthernetDriverInfo *eth_info = ethernetDriverGetInfo();
    printf("Driver name: %s\n", eth_info->name);
    printf("Driver description: %s\n", eth_info->description);
}