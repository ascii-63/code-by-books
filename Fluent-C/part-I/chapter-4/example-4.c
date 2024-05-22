// You want to implement the functionality to display diagnostic information for an
// Ethernet driver to the user. First, you simply add this functionality directly into the
// file with the Ethernet driver implementation and directly access the variables that
// contain the required information:

/* AVOID ERROR SHT BEGIN*/

typedef struct
{
    int rec;
    int snd;
} InternalData;

typedef struct
{
    InternalData internal_data;
} Driver;

Driver driver;

/* AVOID ERROR SHT END*/

void ethShow()
{
    printf("%i packets received\n", driver.internal_data.rec);
    printf("%i packets sent\n", driver.internal_data.snd);
}