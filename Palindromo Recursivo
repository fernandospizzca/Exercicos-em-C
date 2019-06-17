#include <stdio.h>
#include <string.h>


int Palin(char *frs, int tam)
{ 
    static int x = 0; 
    char aux[50];
    
    strupr(frs);
    
    if (tam == 1)
    {
     x=0;
     return 1;
    }
    else if(*(frs+x) != *(frs+tam-1))
    {
     x=0;
     return 0;
    } 
    else
    {
     x++;
     return Palin(frs, tam-1);
    }
}

main()
{
    char Frase[50];
    int z;

    scanf("%s", Frase);
    z = strlen(Frase);
    while(strcmpi(Frase, "FIM") != 0)
    { 
     printf("%i\n", Palin(Frase, z));
     scanf("%s", Frase);
     z = strlen(Frase);
    }
return 0;   
}
