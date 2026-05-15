/*============================================================================*/
/* ICSF13 - 2026-1 - TRABALHO 1                                               */
/*----------------------------------------------------------------------------*/
/* Bogdan T. Nassu                                                            */
/* Leyza E. B. Dorini                                                         */
/* Daniel Fernando Pigatto                                                    */
/*============================================================================*/
/** Funções pedidas e auxiliares para o 1o trabalho da disciplina ICSF13
 * (Fundamentos de Programação 1), 1o semestre de 2026, profs. Bogdan T. Nassu,
 * Leyza E. B. Dorini e Daniel F. Pigatto, UTFPR Curitiba. */
/*============================================================================*/

#ifndef __TRABALHO1_H
#define __TRABALHO1_H

/*============================================================================*/
/* Funções do trabalho. */

void codificaStreamImagem ();
void decodificaStreamRLE ();

/*----------------------------------------------------------------------------*/
/* Funções auxiliares que DEVEM ser chamadas pelos alunos. */

unsigned int pegaProximoPixel ();
void enviaPixel (unsigned int pixel);
unsigned int pegaProximoBlocoRLE ();
void enviaBlocoRLE (unsigned int bloco);

/*----------------------------------------------------------------------------*/
/* Funções auxiliares que NÃO DEVEM ser chamadas pelos alunos. */

void criaStreamsCod (char* arquivo_img, char* arquivo_rle);
void criaStreamsDecod (char* arquivo_rle);
void salvaStreamImagem (char* arquivo_img);
void destroiStreams ();

/*============================================================================*/
#endif /* __TRABALHO1_H */

