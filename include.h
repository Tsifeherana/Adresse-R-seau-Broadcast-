#include <stdbool.h>
//Prototype
int *to_binary(int a);
char *remplir_masque(int *a, int *b, int *c, int *d);
char *remplir();
bool verifie(int a, int b, int c, int d);
char *adresse_reseau(int ip1, int ip2, int ip3, int ip4, int bytes1, int bytes2, int bytes3, int bytes4);
char *adresse_broadcast(int ip1, int ip2, int ip3, int ip4, int bytes1, int bytes2, int bytes3, int bytes4);
void exec();
void determine_class(char **ip, int *ip1, int *ip2, int *ip3, int *ip4,char *class);
bool verifie_ip(char *ip);