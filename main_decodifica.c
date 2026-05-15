/*============================================================================*/
/* ICSF13 - 2026-1 - TRABALHO 1                                               */
/*----------------------------------------------------------------------------*/
/* Bogdan T. Nassu                                                            */
/* Leyza E. B. Dorini                                                         */
/* Daniel Fernando Pigatto                                                    */
/*============================================================================*/
/** Descompress�o de imagens usando RLE. */
/*============================================================================*/

#include "trabalho1.h"

/*============================================================================*/

#define ARQUIVO_RLE "img/saida_aluno.rles" /*  Coloque aqui o caminho para a imagem que deseja. */
#define ARQUIVO_IMG "img/saida_aluno.bmp" /* Imagem de sa�da. */

/*============================================================================*/

int main ()
{
    criaStreamsDecod (ARQUIVO_RLE);
    decodificaStreamRLE ();
    salvaStreamImagem (ARQUIVO_IMG);

    /* Tchau. */
    destroiStreams ();
    return (0);
}

/*============================================================================*/

