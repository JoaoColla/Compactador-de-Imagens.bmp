/*============================================================================*/
/* ICSF13 - 2026-1 - TRABALHO 1                                               */
/*----------------------------------------------------------------------------*/
/* Bogdan T. Nassu                                                            */
/* Leyza E. B. Dorini                                                         */
/* Daniel Fernando Pigatto                                                    */
/*============================================================================*/
/** Compress�o de imagens usando RLE. */
/*============================================================================*/

#include "trabalho1.h"

/*============================================================================*/

#define ARQUIVO_IMG "img/teste2.bmp" /*  Coloque aqui o caminho para a imagem que deseja. */
#define ARQUIVO_RLE "img/saida_aluno.rles" /* Sa�da codificada. */

/*============================================================================*/

int main ()
{
    /* Prepara os streams. */
    criaStreamsCod (ARQUIVO_IMG, ARQUIVO_RLE);

    /* Codifica. */
    codificaStreamImagem ();

    /* Tchau. */
    destroiStreams ();
    return (0);
}

/*============================================================================*/

