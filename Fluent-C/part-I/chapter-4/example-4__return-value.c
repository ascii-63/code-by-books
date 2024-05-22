// Ethernet driver API

/* Returns the number of total received packets*/
int ethernetDriverGetTotalReceivedPackets();
/* Returns the number of total sent packets*/
int ethernetDriverGetTotalSentPackets();

// Caller’s code
void ethShow()
{
    int received_packets = ethernetDriverGetTotalReceivedPackets();
    int total_sent_packets = ethernetDriverGetTotalSentPackets();
    int successfully_sent_packets = ethernetDriverGetSuccesscullySentPackets();
    int failed_sent_packets = ethernetDriverGetFailedPackets();
    printf("%i packets received\n", received_packets);
    printf("%i packets sent\n", total_sent_packets);
    printf("%i packets successfully sent\n", successfully_sent_packets);
    printf("%i packets failed to send\n", failed_sent_packets);
}
