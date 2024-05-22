// Ethernet driver API

/* Returns driver status information via out-parameters.
total_sent_packets
--> number of packets tried to send (success and fail)
successfully_sent_packets --> number of packets successfully sent
failed_sent_packets --> number of packets failed to send */
void ethernetDriverGetStatistics(int *total_sent_packets,
                                 int *successfully_sent_packets, int *failed_sent_packets);

// Caller’s code
void ethShow()
{
    int total_sent_packets, successfully_sent_packets, failed_sent_packets;
    ethernetDriverGetStatistics(&total_sent_packets, &successfully_sent_packets,
                                &failed_sent_packets);
    printf("%i packets sent\n", total_sent_packets);
    printf("%i packets successfully sent\n", successfully_sent_packets);
    printf("%i packets failed to send\n", failed_sent_packets);
    int received_packets = ethernetDriverGetTotalReceivedPackets();
    printf("%i packets received\n", received_packets);
}