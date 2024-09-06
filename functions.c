#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int *to_binary(int a)
{
    int *bin = malloc(8 * sizeof(int));
    for (int i = 0; i < 8; i++)
    {
        bin[i] = (a >> (7 - i)) & 1;
    }
    return bin;
}

char *remplir_masque(int *a, int *b, int *c, int *d)
{
    char *masque = (char *)malloc(sizeof(char) * 32);
    try : printf("Mask Adress : ")
        ;
    scanf("%s", masque);
    if (sscanf(masque, "%d.%d.%d.%d", a, b, c, d) != 4)
        goto try;
    return masque;
}

char *remplir()
{
    char *ip = (char *)malloc(sizeof(char) * 35);
    printf("Enter the IP Address: ");
    scanf("%s", ip);
    return ip;
}
bool verifie_ip(char *ip)
{
    int a;
    int b;
    int c;
    int d;
    if (sscanf(ip, "%d.%d.%d.%d", &a, &b, &c, &d) != 4)
    {
        return false;
    }
    else
    {
        return true;
    }
}
void determine_class(char **ip, int *ip1, int *ip2, int *ip3, int *ip4, char *class)
{
    sscanf(*ip, "%d.%d.%d.%d", ip1, ip2, ip3, ip4);
    if ((*ip1 >= 0 && *ip1 <= 127) && (*ip2 >= 0 && *ip2 <= 255) && (*ip3 >= 0 && *ip3 <= 255) && (*ip4 >= 0 && *ip4 <= 255))
    {
        *class = 'A';
    }
    else if ((*ip1 >= 128 && *ip1 <= 191) && (*ip2 >= 0 && *ip2 <= 255) && (*ip3 >= 0 && *ip3 <= 255) && (*ip4 >= 0 && *ip4 <= 255))
    {
        *class = 'B';
    }
    else if ((*ip1 >= 192 && *ip1 <= 223) && (*ip2 >= 0 && *ip2 <= 255) && (*ip3 >= 0 && *ip3 <= 255) && (*ip4 >= 0 && *ip4 <= 255))
    {
        *class = 'C';
    }
}

bool verifie(int a, int b, int c, int d)
{
    int *bytes1 = to_binary(a);
    int *bytes2 = to_binary(b);
    int *bytes3 = to_binary(c);
    int *bytes4 = to_binary(d);
    char BYTES[32];
    int i;
    int j;
    for (j = 0, i = 0; j < 8, i < 8; j++, i++)
    {
        BYTES[j] = bytes1[i];
    }
    for (j = 8, i = 0; j < 16, i < 8; j++, i++)
    {
        BYTES[j] = bytes2[i];
    }
    for (j = 16, i = 0; j < 24, i < 8; j++, i++)
    {
        BYTES[j] = bytes3[i];
    }
    for (j = 24, i = 0; j < 32, i < 8; j++, i++)
    {
        BYTES[j] = bytes4[i];
    }
    printf("\n");
    for (i = 0; i < 32; i++)
    {
        if (i > 0)
        {
            if (BYTES[i - 1] == 1 && BYTES[i] == 0 && BYTES[i + 1] == 1)
            {
                return false;
            }
            if (BYTES[i - 1] == 0 && BYTES[i] == 1 && BYTES[i + 1] == 0)
            {
                return false;
            }
            if (BYTES[i - 1] == 0 && BYTES[i] == 0 && BYTES[i + 1] == 1)
            {
                return false;
            }
        }
    }
    return true;
}

char *adresse_reseau(int ip1, int ip2, int ip3, int ip4, int bytes1, int bytes2, int bytes3, int bytes4)
{
    char *reseau = (char *)malloc(sizeof(char) * 30);
    int reseau1 = ip1 & bytes1;
    int reseau2 = ip2 & bytes2;
    int reseau3 = ip3 & bytes3;
    int reseau4 = ip4 & bytes4;
    sprintf(reseau, "%d.%d.%d.%d", reseau1, reseau2, reseau3, reseau4);
    printf("Network Address: %d.%d.%d.%d\n", reseau1, reseau2, reseau3, reseau4);
    return reseau;
}

char *adresse_broadcast(int ip1, int ip2, int ip3, int ip4, int bytes1, int bytes2, int bytes3, int bytes4)
{
    char *broadcast = (char *)malloc(sizeof(char) * 30);
    bytes1 = 255 - bytes1;
    bytes2 = 255 - bytes2;
    bytes3 = 255 - bytes3;
    bytes4 = 255 - bytes4;

    int broad1 = bytes1 | ip1;
    int broad2 = bytes2 | ip2;
    int broad3 = bytes3 | ip3;
    int broad4 = bytes4 | ip4;
    sprintf(broadcast, "%d.%d.%d.%d", broad1, broad2, broad3, broad4);
    printf("Broadcast Address: %d.%d.%d.%d\n", broad1, broad2, broad3, broad4);
    free(broadcast);
    return broadcast;
}

void exec()
{
    int a;
    int b;
    int c;
    int d;
    int ip1;
    int ip2;
    int ip3;
    int ip4;
    char class;
refaire:
    char *ip = remplir();
    if (verifie_ip(ip))
    {
        determine_class(&ip, &ip1, &ip2, &ip3, &ip4, &class);
        try:
            char *masque = remplir_masque(&a, &b, &c, &d);
        if (verifie(a, b, c, d))
        {
            printf("----------------------------------------------------\n");
            printf("Class %c\n", class);
            char *reseau = adresse_reseau(ip1, ip2, ip3, ip4, a, b, c, d);
            char *broadcast = adresse_broadcast(ip1, ip2, ip3, ip4, a, b, c, d);
            printf("--------------------------------------------------\n");
        }
        else
        {
            printf("Error: Please try again! Invalid mask address.\n");
            goto try;
        }
    }
    else 
    {
        goto refaire;
    }
}