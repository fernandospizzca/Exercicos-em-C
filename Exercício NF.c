#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Max 81

FILE *Arq, *Erro;

typedef struct NF
{
    char Cnpj[19], Nome[36], Serie[4], OcEntrega[3], Data[12], Nota[9], ValorNf[10], NotaSerie[12];
} Nfes;

void Substring(char *Leitura, char *Registro, int Pos, int qtd)
{
    int i = 0;
    int y;
    for (y = Pos - 1; y < Pos - 1 + qtd; y++)
    {
        *(Registro + i) = *(Leitura + y);
        i++;
    }
    *(Registro + i) = '\0';
}

void ArqValid(Nfes *Verif, int Tam)
{
    int j = 0;

    Erro = fopen("Erro.txt", "w");
    while (Tam >= 0)
    {
        if (strcmp((Verif + j)->OcEntrega, "01") == 0 || (strcmp((Verif + j)->OcEntrega, "02") == 0))
        {
            fprintf(Erro, "%s%s%s%s%s%s%s\n", Verif[j].Cnpj, Verif[j].Nome, Verif[j].Serie, Verif[j].Nota, Verif[j].OcEntrega, Verif[j].Data, Verif[j].ValorNf);
        }
        j++;
        Tam--;
    }
    fclose(Erro);
}

void MascaraCnpj(Nfes *Form, char *Formato, int Tam)
{
    char aux[20];
    int cont;
    int k = 0;
    int i = 0;
    int y = 0;

    cont = strlen(Formato);

    while (Tam >= 0)
    {
        k = 0;
        y = 0;
        for (k = 0; k < cont; k++)
        {
            if (Formato[k] != '#')
                aux[k] = *(Formato + k);

            else
            {
                aux[k] = (Form + i)->Cnpj[y];
                y++;
            }
        }
        strcpy(((Form + i)->Cnpj), aux);
        i++;
        Tam--;
    }
}

void MascaraData(Nfes *Form, char *Formato, int Tam)
{
    char aux[13];
    int cont;
    int k = 0;
    int i = 0;
    int y = 0;
    int x = Tam;
    cont = strlen(Formato);

    while (x >= 0)
    {
        y = 0;
        k = 0;
        for (k = 0; k < cont; k++)
        {
            if (Formato[k] != '#')
                aux[k] = *(Formato + k);

            else
            {
                aux[k] = (Form + i)->Data[y];
                y++;
            }
        }
        strcpy(((Form + i)->Data), aux);
        i++;
        x--;
    }
}

void PesqNfFornecedor(Nfes *Nforc, char *fornecedor, int n)
{
    int size = strlen(fornecedor);
    int j = 0;
    int N = n;
    float valtotalfornc = 0;
    char aux[36], aux2[36];

    Substring(((Nforc + j)->Nome), aux, 1, size);

    while (N >= 0)
    {
        if (strcmpi(aux, fornecedor) == 0 && strcmp((Nforc + j)->OcEntrega, "01") != 0 && strcmp((Nforc + j)->OcEntrega, "02") != 0)
        {
            valtotalfornc = valtotalfornc + atof((Nforc + j)->ValorNf) / 100;
            strcpy(aux2, (Nforc + j)->Nome);
        }
        j++;
        N--;
        Substring(((Nforc + j)->Nome), aux, 1, size);
    }
    j = 0;
    if (valtotalfornc > 0)
        printf("\nNotas do fornecedor %s --> %.2f\n", aux2, valtotalfornc);
    else
        printf("\nFornecedor not found\n");
    aux[0] = '\0';
    aux2[0] = '\0';
}

void OrdNota(Nfes *nf, int tam)
{
    int y;
    int j = 1;
    Nfes aux;

    while (j < tam)
    {
        aux = *(nf + j);
        y = j - 1;
        while (y >= 0 && strcmp((nf + y)->NotaSerie,aux.NotaSerie)>0)
        {
            *(nf + y + 1) = *(nf + y);
            y--;
        }
        *(nf + y + 1) = aux;
        j++;
    }

}

int PesqBiNota(Nfes *Nt, char *Pesq, int Inicio, int Fim)
{
    int Meio;

    strupr(Pesq);

    if (Inicio > Fim)
    {
        printf("\nNota not found\n");
        return 0;
    }
    Meio = (Inicio + Fim) / 2;

    if (strcmp(Pesq, (Nt + Meio)->NotaSerie) > 0)
        return (PesqBiNota(Nt, Pesq, Meio + 1, Fim));

    if (strcmp(Pesq, (Nt + Meio)->NotaSerie) < 0)
        return (PesqBiNota(Nt, Pesq, Inicio, Meio - 1));

    printf("\n%s %-8s %-18s %-35s %-11s %-9.2f\n", Nt[Meio].Serie, Nt[Meio].Nota, Nt[Meio].Cnpj, Nt[Meio].Nome, Nt[Meio].Data, atof(Nt[Meio].ValorNf) / 100);

    return 0;
}

int main()
{
    Nfes Notas[1000];
    float ValtotalNf = 0;
    float Valnota;
    char LinhaNfs[Max], PesqForc[40], PesqNota[10];
    int x = 0;
    int z = 0;
    int t = 0;
    int controle = 0;

    Arq = fopen("DevolucaoNF.txt", "r");

    if (Arq == NULL)
    {
        printf("\nErro ao abrir arquivo\n");
        return 0;
    }

    fgets(LinhaNfs, Max, Arq);
    while (!feof(Arq))
    {
        Substring(LinhaNfs, (Notas + x)->Cnpj, 1, 14);
        Substring(LinhaNfs, (Notas + x)->Nome, 15, 35);
        Substring(LinhaNfs, (Notas + x)->Serie, 50, 3);
        Substring(LinhaNfs, (Notas + x)->Nota, 53, 8);
        Substring(LinhaNfs, (Notas + x)->OcEntrega, 61, 2);
        Substring(LinhaNfs, (Notas + x)->Data, 63, 8);
        Substring(LinhaNfs, (Notas + x)->ValorNf, 71, 9);
        Substring(LinhaNfs, (Notas + x)->NotaSerie, 50, 11);
        fgets(LinhaNfs, Max, Arq);
        x++;
        t++;
    }
    fclose(Arq);

    ArqValid(Notas, x);
    MascaraCnpj(Notas, "##.###.###/####-##", x);
    MascaraData(Notas, "##/##/####", t);

    printf("Serie/NF     CNPJ               Fornecedor                          Data        Valor\n");

    while (x >= 0)
    {
        Valnota = atof(Notas[z].ValorNf) / 100;
        if (strcmp((Notas + z)->OcEntrega, "01") != 0 && (strcmp((Notas + z)->OcEntrega, "02") != 0) && Valnota != 0)
        {
            Valnota = atof(Notas[z].ValorNf) / 100;
            ValtotalNf = ValtotalNf + Valnota;
            printf("%s %-8s %-18s %-35s %-11s %-9.2f\n", Notas[z].Serie, Notas[z].Nota, Notas[z].Cnpj, Notas[z].Nome, Notas[z].Data, Valnota);
        }
        z++;
        x--;
    }
    printf("\n\nTotas das Notas aceitas: R$ %.2f\n", ValtotalNf);

    printf("\nInforme o nome completo do fornecedor para pesquisa das notas: ");
    gets(PesqForc);

    PesqNfFornecedor(Notas, PesqForc, t);

    OrdNota(Notas, t);

    printf("\nInforme Numero da Serie e Nota sem espacos, caso deseje efetuar pesquisa, caso contrario informe 0: ");
    gets(PesqNota);

    if (strcmp(PesqNota, "0") != 0)
        PesqBiNota(Notas, PesqNota, 0, t - 1);

    printf("\nDeseja Fazer mais consultas se sim digite 1: ");
    scanf("%i", &controle);
    if (controle == 1)
    {
        getchar();
        return (main());
    }
    else
        return 0;
}
