/*============================================================================*/
/* ICSF13 - 2026-1 - TRABALHO 1                                               */
/*----------------------------------------------------------------------------*/
/* Bogdan T. Nassu                                                            */
/* Leyza E. B. Dorini                                                         */
/* Daniel Fernando Pigatto                                                    */
/*============================================================================*/
/** Funções auxiliares para o 1o trabalho da disciplina ICSF13 (Fundamentos de
 * Programação 1), 1o semestre de 2022, profs. Bogdan T. Nassu, Leyza E. B.
 * Dorini e Daniel F. Pigatto, UTFPR Curitiba. */
/*============================================================================*/

#include <stdio.h>
#include <stdlib.h>

#include "trabalho1.h"
#include "imagem.h"

/*============================================================================*/
/* Estas variáveis são globais somente para isolar parte do trabalho dos alunos (evita o uso de ponteiros para structs por eles). */

Imagem3C* img = NULL;
int linha_atual;
int coluna_atual;
FILE* stream_rle = NULL;

/*============================================================================*/
/* Cria "streams simulados" para codificar - a entrada é simplesmente uma
 * imagem com uma posição associada, a saída é simplesmente um arquivo. */

void criaStreamsCod (char* arquivo_img, char* arquivo_rle)
{
    unsigned int tam_imagem;

    /* Abre a imagem. */
    img = abreImagem3C (arquivo_img);
    if (!img)
    {
        printf ("Erro abrindo imagem %s\n", arquivo_img);
        exit (1);
    }

    /* Aponta para o início. */
    linha_atual = 0;
    coluna_atual = 0;

    /* Abre o arquivo para mandar os dados codificados. */
    stream_rle = fopen (arquivo_rle, "wb");
    if (!stream_rle)
    {
        printf ("Erro abrindo arquivo %s\n", arquivo_rle);
        exit (1);
    }

    /* Já coloca nas 2 primeiras posições do arquivo o tamanho da imagem. */
    /* Usamos 2 bytes para a altura e 2 bytes para a largura. */
    if (img->altura > 0xFFFF || img->largura > 0xFFFF)
    {
        printf ("A imagem não deve ter mais do que %d linhas/colunas (tem %lu linhas e %lu colunas).\n", 0xFFFF, img->altura, img->largura);
        exit (1);
    }

    tam_imagem = (img->altura << 16) | img->largura;
    fwrite (&tam_imagem, 1, 4, stream_rle);
}

/*----------------------------------------------------------------------------*/
/* Cria "streams simulados" para decodificar - a entrada é simplesmente um
 * arquivo, a saída é uma imagem com uma posição associada. */

void criaStreamsDecod (char* arquivo_rle)
{
    unsigned int tam_imagem, largura, altura;

    /* Abre o arquivo para ler os dados codificados. */
    stream_rle = fopen (arquivo_rle, "rb");
    if (!stream_rle)
    {
        printf ("Erro abrindo arquivo %s\n", arquivo_rle);
        exit (1);
    }

    /* Obtém o tamanho da imagem. São 2 bytes para a altura e 2 bytes para a largura. Lemos os 4 bytes de uma só vez. */
    fread (&tam_imagem, 1, 4, stream_rle);
    altura = tam_imagem >> 16;
    largura = tam_imagem & 0xFFFF;

    /* Cria a imagem. */
    img = criaImagem3C (largura, altura);

    /* Aponta para o início. */
    linha_atual = 0;
    coluna_atual = 0;
}

/*----------------------------------------------------------------------------*/
/* Simplesmente salva a imagem usada no momento. */

void salvaStreamImagem (char* arquivo_img)
{
    if (!img)
    {
        printf ("Primeiro crie um stream para a imagem!\n");
        exit (1);
    }

    if (!salvaImagem3C (img, arquivo_img))
    {
        printf ("Erro salvando imagem %s\n", arquivo_img);
        exit (1);
    }
}

/*----------------------------------------------------------------------------*/
/* Desaloca e fecha os "streams simulados". */

void destroiStreams ()
{
    if (img)
        destroiImagem3C (img);

    if (stream_rle)
        fclose (stream_rle);
}

/*============================================================================*/
/* As funções abaixo são aquelas usadas pelos alunos. Vou supor que todos os
 * streams estão abertos e funcionando. */

/* Retorna o valor do pixel atual, e aponta para o próximo. Retorna
 * 0xFFFFFFFF se não tiver mais pixels para retornar. */

unsigned int pegaProximoPixel ()
{
    unsigned int pixel;

    /* Final do stream. Retorna um valor especial. */
    if (linha_atual == img->altura)
        return (0xFFFFFFFF);

    /* Junta os 3 canais em um único valor. */
    pixel = (img->dados [0][linha_atual][coluna_atual] << 16) |
            (img->dados [1][linha_atual][coluna_atual] << 8) |
            img->dados [2][linha_atual][coluna_atual];

    /* Vai para a próxima posição antes de retornar. */
    coluna_atual++;
    if (coluna_atual == img->largura)
    {
        linha_atual++;
        coluna_atual = 0;
    }

    return (pixel);
}

/*----------------------------------------------------------------------------*/
/* Adiciona um pixel à imagem. Passamos a apontar para o próximo pixel. */

void enviaPixel (unsigned int pixel)
{
    if (pixel > 0xFFFFFF) // Pixel inválido.
        return;

    img->dados [0][linha_atual][coluna_atual] = (pixel & 0xFF0000) >> 16; // R = primeiro byte (de 4).
    img->dados [1][linha_atual][coluna_atual] = (pixel & 0xFF00) >> 8; // G = segundo byte (de 4).
    img->dados [2][linha_atual][coluna_atual] = pixel & 0xFF; // B = último byte.

    coluna_atual++;
    if (coluna_atual >= img->largura) // Terminou uma linha.
    {
        coluna_atual = 0;
        linha_atual++;

        if (linha_atual >= img->altura) // Acabou a imagem. Volta para o início.
            linha_atual = 0;
    }
}

/*----------------------------------------------------------------------------*/
/* Pega o próximo bloco do arquivo que simula o stream RLE. Retorna 0 se não
 * tiver mais blocos para retornar. */

 unsigned int pegaProximoBlocoRLE ()
 {
     unsigned int bloco;

    if (!fread (&bloco, 1, 4, stream_rle))
        return (0);

    return (bloco);
 }

/*----------------------------------------------------------------------------*/
/* Escreve um bloco de 4 bytes no arquivo que simula o stream RLE. */

void enviaBlocoRLE (unsigned int bloco)
{
    fwrite (&bloco, 1, 4, stream_rle);
}

/*============================================================================*/

