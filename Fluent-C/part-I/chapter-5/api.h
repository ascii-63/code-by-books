// API (header file)

void sendByte(char data, char *destination_ip);
char receiveByte();
int getNumberOfSentBytes();
int getNumberOfReceivedBytes();

struct Sender
{
    char destination_ip[16];
    int socket;
};
struct Sender *createSender(char *destination_ip);
struct Sender *openSender(char *destination_ip);
void sendByteSender(struct Sender *s, char data);
void closeSender(struct Sender *s);
void destroySender(struct Sender *s);