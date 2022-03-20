/*
Criado por Léo
20/03/2022

Base para a criação da biblioteca:

1. Em Private Variables 

#Variável Booleana para confirmar se o chute foi carregado ou não

GPIO_PinState is_charge = GPIO_PIN_RESET;

2. Em User code begin 0

#funções para carregar ou chutar

void charge()
{
	__HAL_TIM_SET_COUNTER(&htim14,0);
	__HAL_TIM_SET_COUNTER(&htim7,0);
	HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, 1);
	is_charge = GPIO_PIN_SET;
}

void kick()
{
	__HAL_TIM_SET_COUNTER(&htim14,0);
	__HAL_TIM_SET_COUNTER(&htim10,0);
	HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, 1);
	is_charge = GPIO_PIN_RESET;
}

void chip_kick()
{
	__HAL_TIM_SET_COUNTER(&htim14,0);
	__HAL_TIM_SET_COUNTER(&htim10,0);
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, 1);
	is_charge = GPIO_PIN_RESET;
}

--- Cada função acima configura o início da ação. O final de cada ação está na interrupção. 

3. Na Main, antes do While

#Iniciar os timers com interrupt

HAL_TIM_Base_Start_IT(&htim7);
HAL_TIM_Base_Start_IT(&htim10);
HAL_TIM_Base_Start_IT(&htim14);

--- Timer 7 é usado para fazer a contagem do charge. Timer 10, para chutar e, 14 pra  efetuar charges automáticas.

4. Em User code begin 4

#Interrupções dos Timers

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim7)
	{
		HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, 0);
	}

	if(htim == &htim10)
	{
		HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, 0);
		HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, 0);
		if(!is_charge)
		{
			charge();
		}
	}

	if(htim == &htim14)
	{
		__HAL_TIM_SET_COUNTER(&htim7, 0);
		HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, 1);
	}
}

*/

//AINDA DEVE-SE VERIFICAR QUAL INCLUDES É MELHOR!!
#include "main.h"

class kicker{
    public:
        kicker(GPIO_TypeDef *_port, uint16_t _pin);

        void charge(TIM_HandleTypeDef *_tim1, TIM_HandleTypeDef *_tim2);

        void kick(TIM_HandleTypeDef *_tim1, TIM_HandleTypeDef *_tim2);

        void chip_kick(TIM_HandleTypeDef *_tim1, TIM_HandleTypeDef *_tim2);

    private:
        GPIO_TypeDef *port;

        uint16_t pin;
}