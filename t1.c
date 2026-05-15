//TRABALHO_1 Fund. Prog. 05/2026
//AUTOR: João Vitor Colla de Souza
//FACULDADE: UTFPR - Curitiba

#include "trabalho1.h"

void codificaStreamImagem (){

    unsigned int px_ant, px_atual, cont=1, bloco;

    // Pega o primeiro pixel de todos
    px_ant = pegaProximoPixel();

    // Se a imagem j� estiver vazia logo no come�o, a fun��o n�o faz nada e encerra
    if (px_ant == 0xFFFFFFFF) {
        return;
    }

    // Pega o pr�ximo para come�ar as compara��es
    px_atual = pegaProximoPixel();

    // Enquanto o pixel recebido nao for o sinal de parada ele executa o bloco de codigo
    while(px_atual != 0xFFFFFFFF){

        // Analisa se o pixel anterior e igual ao atual, se for soma 1 ao contador
        if (px_ant == px_atual && cont < 255){
            cont++;

        }

        else{   // Se for diferente ele termina o bloco RLE em que estava e come�a a contar outro e envia o bloco encerrado

            bloco = (cont << 24)| px_ant; // Coloca o valor do contador no primeio byte do bloco RLE e completa os outros 3 bytes do bloco com a cor

            enviaBlocoRLE (bloco); // Envia o bloco pela fun�ao

            cont = 1; // Reinicia a contagem para o proximo bloco
        }

        // Troca o pixel anterior pelo atual e recebe um novo atual
        px_ant = px_atual;
        px_atual = pegaProximoPixel();
    }

    // envia o ultimo bloco que foi interrompido pelo while
    bloco = (cont << 24)| px_ant;
    enviaBlocoRLE (bloco);


}


void decodificaStreamRLE (){

    unsigned int bloco, quantidade, cor, constante = 0x00FFFFFF, i;

    // Recebe da fun��o o primeiro bloco RLE
    bloco = pegaProximoBlocoRLE ();

    // Testa se o bloco de codigo deve ser executado ou se acabou os blocos RLEs
    while(bloco != 0){

        // Joga a quantidade que esta no primeiro (da esquerda) byte para o ultimo (da direita)
        quantidade = bloco >> 24;

        // Extrai somente a cor que esta no bloco
        cor = bloco & constante;

        // Envia a cor para a fun��o "quantidade" vezes
        for (i = 0; i < quantidade; i++){
            enviaPixel (cor);
        }

        // Recebe um novo bloco RLE
        bloco = pegaProximoBlocoRLE ();

    }

}


/*
void decodificaStreamRLE() {
    unsigned int bloco;

    // A fun��o pegaProximoBlocoRLE() retorna 0 quando os blocos acabam.
    while ((bloco = pegaProximoBlocoRLE()) != 0) {

        // 1. Extrair a quantidade (O byte mais significativo)
        unsigned int quantidade = (bloco >> 24) & 0xFF;

        // 2. Extrair a cor (Os tr�s bytes menos significativos)
        unsigned int cor = bloco & 0x00FFFFFF;

        // 3. Enviar a cor o n�mero de vezes especificado na quantidade
        for (unsigned int i = 0; i < quantidade; i++) {
            enviaPixel(cor);
        }
    }
}
*/
