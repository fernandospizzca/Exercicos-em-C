#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()

{
 int Imagem[8][8] = {{0,0,0,0,0,0,0,0},
                    {0,0,1,1,1,1,0,0},
                    {0,1,0,0,0,0,1,0},
                    {1,0,1,0,0,1,0,1},
                    {1,0,0,0,0,0,0,1},
                    {0,1,0,1,1,0,1,0},
                    {0,1,0,0,0,0,1,0},
                    {0,0,1,1,1,1,0,0}};
int lin, col, Branco=0, Preto=0, Anterior, x=0;
char ImagemC[64];


for (lin=0; lin<8; lin++)
  {

      for(col=0; col<8; col++)
      {
        if(col==0)
           {
            if(Imagem[lin][col] == 0)
            {
               Anterior = 0;
               Branco++;
            }
            else
                if(Imagem[lin][col] == 1)
                 {
                 Anterior = 1;
                 Preto++;
                }
           }

        else
           Anterior = Imagem[lin][col-1];
         if (col > 0)

            if (Imagem[lin][col] == 0)
                Branco++;


           else
               if(Imagem[lin][col] == 1)
                    Preto++;


                  if (Imagem[lin][col] != Anterior && Anterior == 0)
                       {
                         ImagemC[x]=Branco + 48;
                         ImagemC[x+1]= 'B';
                         x += 2;
                         Branco = 0;
                       }

                          else
                            if (Imagem[lin][col] != Anterior && Anterior == 1)
                                        {
                                         ImagemC[x]=Preto + 48;
                                         ImagemC[x+1]= 'P';
                                         x += 2;
                                         Preto = 0;
                                        }
                        if (col == 7){
                            if(Imagem[lin][col] == 0)
                              {
                               ImagemC[x]=Branco + 48;
                               ImagemC[x+1]= 'B';
                               x += 2;
                               Branco = 0;
                               }
                             else
                                if(Imagem[lin][col] == 1)
                                   {
                                    ImagemC[x]=Preto + 48;
                                    ImagemC[x+1]= 'P';
                                    x += 2;
                                    Preto = 0;
                                   }}

        }

       ImagemC[x]='0';
       x++;

    }
      ImagemC[x]='0';
      //ImagemC[x+1]='\0'; //no CodeBlocks sem esse comando printa sugerira no final, no VS Code printa normalmente sem ele e se inserir esse comando ele não printa nada.
      puts(ImagemC);
      return(0);
}