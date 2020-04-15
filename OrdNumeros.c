#include <stdio.h>

//Ordenação pelo método de seleção.

main()
{
    int N, x, y, j, z, minimo, aux;
    int Vet[100000], VetPar[100000], VetImpar[100000];

    scanf("%i", &N);

    if (N > 1 && N < 100000)
    {

        for (x = 0, y = 0, j = 0; x < N; x++)
        {
            scanf("%i", &Vet[x]);

            if (Vet[x] % 2 == 0)
            {
                VetPar[y] = Vet[x];
                y++;
            }
            else
            {
                VetImpar[j] = Vet[x];
                j++;
            }
        }
        for (z = 0; z < y; z++)
        {
            minimo = z;
            for (x = z + 1; x < y; x++)
            {
                if (VetPar[x] < VetPar[minimo])
                    minimo = x;
            }
            aux = VetPar[minimo];
            VetPar[minimo] = VetPar[z];
            VetPar[z] = aux;

            printf("%i\n", VetPar[z]);
        }
        for (z = 0; z < j; z++)
        {
            minimo = z;
            for (x = z + 1; x < j; x++)
            {
                if (VetImpar[x] > VetImpar[minimo])
                    minimo = x;
            }
            aux = VetImpar[minimo];
            VetImpar[minimo] = VetImpar[z];
            VetImpar[z] = aux;

            printf("%i\n", VetImpar[z]);
        }
    }
    return 0;
}