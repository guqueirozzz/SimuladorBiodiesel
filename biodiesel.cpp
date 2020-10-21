/*
    DEVELOPERS:
        GUSTAVO ARAUJO QUEIROZ  RA: 222160392
        WILLIAM GABRIEL BARBOSA RA: 221170640
*/

/*
    PROGRAMA DESENVOLVIDO USANDO A IDE ::CODEBLOCKS
    MINGW C++11
*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <thread>
#include <chrono>

// variaveis globais para uso do programa
float qtd_total_oleo_reator 	= 0;
float qtd_total_naoh_reator 	= 0;
float qtd_total_etoh_reator 	= 0;
float qtd_total_glicerina   	= 0;
float qtd_total_decantador  	= 0;
float qtd_total_naoh 			= 0;
float qtd_total_etoh 			= 0;
float qtd_oleo 					= 0;
float qtd_naoh 					= 0;
float qtd_etoh 					= 0;
float qtd_glicerina 			= 0;
float qtd_lavagem				= 0;
float qtd_mistura				= 0;
float qtd_etoh_decantador       = 0;
float qtd_total_mistura 		= 0;
float qtd_total_lavagem 		= 0;
float qtd_mistura_decantador	= 0;
float qtd_biodiesel_total 		= 0;
int ativa_reator            	= 0;
int tempo2                      = clock();
int tempo_oleo                  = 1;
int tempo_dec                   = 1;


void tanque_glicerina(float qtd_glicerina)
{
	printf("\n\n ======================================TANQUE DE GLICERINA================================================");
	qtd_total_glicerina = qtd_total_glicerina + qtd_glicerina;

	printf("\nQuantidade total de glicerina: %.2f", qtd_total_glicerina);
	printf("\n=============================================================================================================");
}

void tanque_biodiesel(float qtd_biodiesel)
{
	printf("\n\n=======================================TANQUE DE BIODIESEL==================================================");
	qtd_biodiesel_total = qtd_biodiesel_total + qtd_biodiesel;
	printf("\n Quantidade de Bio Diesel no Tanque: %.2f", qtd_biodiesel_total);
	printf("\n\n===========================================================================================================");

}

void secador(float qtd_mistura_decantador)
{
	printf("\n\n===========================================SECADOR===========================================");


	if(qtd_naoh == 0 && qtd_etoh == 0 )
	{
		printf("\nO SECADOR AINDA NÃO RECEBEU A MISTURA");
	}
	else
	{
		printf("\nRecebendo %.2f de mistura do tanque de lavagem", qtd_mistura_decantador);
		qtd_mistura_decantador = qtd_mistura_decantador - (qtd_mistura_decantador * 0.015);
		printf("\nApos perder 1,5 por cento do volume, restaram %.2f de mistura no secador", qtd_mistura_decantador);

		std::thread TQ_BIO(tanque_biodiesel, qtd_mistura_decantador);
		TQ_BIO.join();
	}
		printf("\n================================================================================================");

}

void tanque_lavagem(float qtd_mistura_decantador)
{

	printf("\n===========================================TANQUE DE LAVAGEM===========================================");
	printf("\nRecebendo %.2f de Solucao para lavagem.... ", qtd_mistura_decantador);
	qtd_mistura_decantador = qtd_mistura_decantador - (qtd_mistura_decantador * 0.15);
	printf("\nQuantidade de lavagem restante: %.2f", qtd_mistura_decantador);

	std::thread SECADOR(secador, qtd_mistura_decantador);
	SECADOR.join();
	printf("\n=======================================================================================================");
}

void decantador(float qtd_mistura)
{
	printf("\n\n===========================================DECANTADOR===========================================");
	qtd_total_decantador = qtd_total_decantador + qtd_mistura;

	if(tempo_dec == 5 )
    {
        if( qtd_total_decantador >= 3 )
        {
            qtd_glicerina = qtd_total_decantador * 0.05;
            qtd_etoh_decantador = qtd_total_decantador * 0.13;
            qtd_lavagem = qtd_total_decantador * 0.82;
            qtd_mistura_decantador = qtd_glicerina + qtd_etoh + qtd_lavagem;

            qtd_total_decantador = qtd_total_decantador - 3.0;
            printf("\n DECANTADOR PROCESSOU 3L");
            printf("\nQuantidade de mistura no decantador: %.2fL", qtd_total_decantador);
            tempo_dec = 1;
            printf("\n==================================================================================================");

            std::thread TQ_GLI(tanque_glicerina, qtd_glicerina);
            TQ_GLI.join();


            std::thread TQ_LAV(tanque_lavagem, qtd_mistura_decantador);
            TQ_LAV.join();

        }
        else
        {
            printf("\n MISTURA INSUFICIENTE PARA PROCESSAMENTO! ");
            printf("\n Quantidade de mistura disponivel: %.2fL", qtd_total_decantador);
            printf("\n==================================================================================================");
        }
    }
    else
    {
        printf("\nDecantador ainda nao foi ativado");
        printf("\n==================================================================================================");
        tempo_dec++;
    }
}

void reator(float qtd_oleo, float qtd_naoh, float qtd_etoh)
{
	printf("\n\n===========================================REATOR===========================================");
	printf("\nRecebendo %.2fL de Oleo", qtd_oleo);
	printf("\nRecebendo %.2fL de Hidroxido de Sodio", qtd_naoh);
	printf("\nRecebendo %.2fL de Etanol", qtd_etoh);
	qtd_total_oleo_reator = qtd_total_oleo_reator + qtd_oleo;
	qtd_total_naoh_reator = qtd_total_naoh_reator + qtd_naoh;
	qtd_total_etoh_reator = qtd_total_etoh_reator + qtd_etoh;
	printf("\nQuantidade total de oleo no reator: %.2fL", qtd_total_oleo_reator);
	printf("\nQuantidade total de Etanol no reator: %.2fL", qtd_total_etoh_reator);
	printf("\nQuantidade total de Hidroxido de Sodio no reator: %.2fL", qtd_total_naoh_reator);
	printf("\n\n===========================================================================================");

	if(qtd_total_oleo_reator >= 1.25 && qtd_total_etoh_reator >= 2.50 && qtd_total_naoh_reator >= 1.25)
	{

		ativa_reator = 1;
		printf("\n\n===========================================REATOR ATIVADO!===========================================");
		qtd_total_oleo_reator = qtd_total_oleo_reator - 1.25;
		qtd_total_etoh_reator = qtd_total_etoh_reator - 2.50;
		qtd_total_naoh_reator = qtd_total_naoh_reator - 1.25;
		qtd_mistura = 5;

		std::thread TQ_DEC(decantador,qtd_mistura);
		TQ_DEC.join();

	}
	else
	{
      std::thread TQ_DEC2(decantador,0);
      TQ_DEC2.join();
    }

}

void tanque_naoh_etoh()
{

	printf("\n\n============================================TANQUE NAOH/ETOH================================================");

	printf("\nQUANTIDADE TOTAL DE HIDROXIDO DE SODIO: %.2fL", qtd_naoh);
	printf("\nQUANTIDADE TOTAL DE ETANOL: %.2fL", qtd_etoh);
	qtd_naoh = qtd_naoh + 0.3;
	qtd_etoh = qtd_etoh + 0.1;

    std::thread TQ_REATOR(reator, 0.0, 0.3, 0.1);
    TQ_REATOR.join();

}

void tanque_oleo(float qtd_oleo)
{
    printf("\n\n===========================================TANQUE DE OLEO===========================================");

	if(tempo_oleo == 5 )
	{
		float qtd_total_oleo;
	    printf("\nRecebendo %.2fL de oleo...", qtd_oleo);
	    qtd_total_oleo = qtd_total_oleo + qtd_oleo;
        tempo_oleo = 1;

	    if(qtd_total_oleo >= 1.25)
	    {

	    	qtd_total_oleo = qtd_total_oleo - 1.25;
	    	printf("\nEnviando 1.25L de oleo para o reator ");
	    	printf("\nQuantidade de oleo restante: %.2fL ", qtd_total_oleo);

            std::thread TQ_REATOR2(reator, 1.25, 0.0, 0.0);
	    	TQ_REATOR2.join();
		}
		printf("\n\n=================================================================================================");
	}
	else
    {
        printf("\n Tanque de Oleo ainda nao foi abastecido!");
        tempo_oleo++;
    }


}

int main(int argc, char** argv)
{
	using namespace std;
    int tempo = clock();

	while(1)
	{
        int j;
        srand(time(NULL));
        j=rand()%10;
        qtd_oleo =(float)j/10+1;

        thread TQ_OLEO(tanque_oleo, qtd_oleo);
        TQ_OLEO.join();

        thread TQ_ETANOL_NAOH(tanque_naoh_etoh);
        TQ_ETANOL_NAOH.join();

        Sleep(1000);
	}

	return 0;
}
