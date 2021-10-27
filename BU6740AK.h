/**
 * @file BU6740AK.h
 * @author Tobias Salazar (you@domain.com)
 * @brief 	Biblioteca C com intuito de ser generica para qualquer arquitetura de MCU com SPI(Hardware ou Software)
 * 			para comunicação com Painel de Impressora HP com BU6740AK 
 * 			Codigo teve como base a library do site 'http:\\cocus.dx.am\2017\05\04\hp-3550-glcd-hack\'			
 * @version 1.0
 * @date 2020-09-20 
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef BU6740AK_h
#define BU6740AK_h

typedef struct 
{
	unsigned int Up : 1;
	unsigned int Down : 1;
	unsigned int Back : 1;
	unsigned int Help : 1;
	unsigned int Stop : 1;
	unsigned int Menu : 1;
	unsigned int Tick : 1;
}MapKeys;

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief Estrutura modulo de comunicação com BU6740AK
 * 
 */
typedef struct 
{
	 unsigned char current_row ;
	 unsigned char current_col ;
	 void (*Start)(void);
	 void (*Stop)(void);
	 unsigned int(*_Send16)(unsigned int);
	 unsigned char (*_Send8 )(unsigned char );
	 MapKeys KBState;

}BU6740AK;

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief Função que Inicializa o Modulo "Painel"
 * 
 * @param Painel Estrutura com os status e parametros necessario para comunicação
 * @param Send16 Função que envia e recebe 16bit da SPI
 * @param Start  Função que Inicializa uma transmissão
 * @param Stop 	 Função que Finaliza uma transmissão
 * @return int 	 Rotorn de erros caso ocorra ( 0 - OK , 1 - Painel=NULL , 2 - Start=NULL, 3 - Stop= NULL)
 */
int Init(BU6740AK * Painel ,unsigned int(*Send16)(unsigned int) ,void (*Start)(),void (*Stop)() );
/**
 * @brief Obitem o estado das teclas 
 * 
 * @param Painel Estrutura com os status e parametros necessario para comunicação 
 * @return unsigned int 
 */
int GetKey(BU6740AK * Painel);

/**
 * @brief Set the Leds object
 * 
 * @param Painel Estrutura com os status e parametros necessario para comunicação 
 * @param leds 
 */
void SetLeds(BU6740AK * Painel , unsigned char leds);

/**
 * @brief 
 * 
 * @param Painel Estrutura com os status e parametros necessario para comunicação 
 * @param row_data 
 * @param count 
 */
void SendRows(BU6740AK * Painel , unsigned char row_data[], unsigned char count);

/**
 * @brief 
 * 
 * @param Painel Estrutura com os status e parametros necessario para comunicação 
 */
void ClearScreen(BU6740AK * Painel);

/**
 * @brief Set the Column object
 * 
 * @param Painel Estrutura com os status e parametros necessario para comunicação 
 * @param col 
 */
void SetColumn(BU6740AK * Painel,unsigned char col);

/**
 * @brief Set the Row object
 * 
 * @param Painel Estrutura com os status e parametros necessario para comunicação 
 * @param row 
 */
void SetRow(BU6740AK * Painel,unsigned char row);

/**
 * @brief 
 * 
 * @param Painel Estrutura com os status e parametros necessario para comunicação 
 * @param col 
 * @param row 
 * @param txt 
 * @param length 
 */
void PrintText(BU6740AK * Painel ,unsigned char col, unsigned char row, char txt[] , unsigned char length);

/**
 * @brief Imprimi Icones 8x8 que esteja contidos em KeyIcons[] em BU6740AK.cpp
 * 
 * @param Painel Estrutura com os status e parametros necessario para comunicação 
 * @param col 
 * @param row 
 * @param icon_id 
 */
void PrintIcon(BU6740AK * Painel ,unsigned char col, unsigned char row, unsigned char icon_id);


#endif
