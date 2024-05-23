#include "api.h"

// Implementation

static int number_of_sent_bytes = 0;
static int number_of_received_bytes = 0;

void sendByte(char data, char *destination_ip)
{
    number_of_sent_bytes++;
    /* socket stuff */
}

char receiveByte()
{
    number_of_received_bytes++;
    /* socket stuff */
}

int getNumberOfSentBytes()
{
    return number_of_sent_bytes;
}

int getNumberOfReceivedBytes()
{
    return number_of_received_bytes;
}

struct Sender *createSender(char *destination_ip)
{
    struct Sender *s = malloc(sizeof(struct Sender));
    /* create socket to destination_ip and store it in Sender s*/
    return s;
}

void sendByteSender(struct Sender *s, char data)
{
    number_of_sent_bytes++;
    /* send data via socket stored in Sender s */
}

void destroySender(struct Sender *s)
{
    /* close socket stored in Sender s */
    free(s);
}

struct Sender *openSender(char *destination_ip)
{
    struct Sender *s;
    if (isInSenderList(destination_ip))
    {
        s = getSenderFromList(destination_ip);
    }
    else
    {
        s = createSender(destination_ip);
    }
    increaseNumberOfCallers(s);
    return s;
}

void closeSender(struct Sender *s)
{
    decreaseNumberOfCallers(s);
    if (numberOfCallers(s) == 0)
    {
        /* close socket stored in Sender s */
        free(s);
    }
}