#include <stdio.h>
#include <string.h>

typedef struct Aluno
{
    char Nome[30];
    int faltas;
    float notas;
} Alunos;

void OrdNota(Alunos *Classe, int tam)
{
    Alunos aux;
    int y;
    int j = 1;
    //Método de inserção.
    while (j < tam)
    {
        aux = *(Classe + j);
        y = j - 1;
        while (y >= 0 && ((Classe + y)->notas) < aux.notas)
        {
            *(Classe + y + 1) = *(Classe + y);
            y--;
        }
        *(Classe + y + 1) = aux;
        j++;
    }

    printf("-------------------------\n");
    printf("Nome        faltas  notas\n");
    for (y = 0; y < tam; y++)
    {
        printf("\n%10s: %4d    %2.2f\n", Classe[y].Nome, Classe[y].faltas, Classe[y].notas);
    }
    printf("-------------------------\n");
}

void OrdFalta(Alunos *Classe, int tam)
{
    Alunos aux;
    int y = 0;
    int j = 0;
    //Método Bolha (Buble Sort).
    for (y = tam - 1; y >= 0; y--)
    {
        for (j = 0; j < tam - 1; j++)
        {
            if (((Classe + j)->faltas) > ((Classe + j + 1)->faltas))
            {
                aux = *(Classe + j);
                *(Classe + j) = *(Classe + j + 1);
                *(Classe + j + 1) = aux;
            }
        }
    }
    printf("-------------------------\n");
    printf("Nome        faltas  notas\n");
    for (y = 0; y < tam; y++)
    {
        printf("\n%10s: %4d    %2.2f\n", Classe[y].Nome, Classe[y].faltas, Classe[y].notas);
    }
    printf("-------------------------\n");
}

main()
{
    Alunos aluno[10];
    int x, y;
    int aux = 0;

    for (x = 0; x < 10; x++)
    {
        printf("Nome: ");
        scanf("%s", &aluno[x].Nome);
        printf("Numero de Faltas: ");
        scanf("%d", &aluno[x].faltas);
        printf("Notas: ");
        scanf("%f", &aluno[x].notas);
    }
    printf("-------------------------\n");
    printf("Nome        faltas  notas\n");
    for (x = 0; x < 10; x++)
    {
        printf("\n%10s: %4d    %2.2f\n\n", aluno[x].Nome, aluno[x].faltas, aluno[x].notas);
    }
    printf("-------------------------\n");

    OrdNota(aluno, 10);
    OrdFalta(aluno, 10);

    return 0;
}