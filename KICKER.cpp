#include "KICKER.h"

GPIO_PinState is_charge = GPIO_PIN_RESET;

kicker::kicker(GPIO_TypeDef *_port, uint16_t _pin)
{
    port = _port;
    pin = _pin;
}

void kicker::charge(TIM_HandleTypeDef *_tim1, TIM_HandleTypeDef *_tim2)
{
    __HAL_TIM_SET_COUNTER(_tim2,0);
	__HAL_TIM_SET_COUNTER(_tim1,0);
	HAL_GPIO_WritePin(kicker.port, kicker.pin, 1);
	is_charge = GPIO_PIN_SET;
}

void kicker::kick(TIM_HandleTypeDef *_tim1, TIM_HandleTypeDef *_tim2)
{
    __HAL_TIM_SET_COUNTER(_tim2,0);
	__HAL_TIM_SET_COUNTER(_tim1,0);
	HAL_GPIO_WritePin(kicker.port, kicker.pin, 1);
	is_charge = GPIO_PIN_RESET;
}

void kicker::kick(TIM_HandleTypeDef *_tim1, TIM_HandleTypeDef *_tim2)
{
    __HAL_TIM_SET_COUNTER(_tim2,0);
	__HAL_TIM_SET_COUNTER(_tim1,0);
	HAL_GPIO_WritePin(kicker.port, kicker.pin, 1);
	is_charge = GPIO_PIN_RESET;
}

/* Vale lembrar que precisa ser adicionado na Main:

# LD6 equivale ao charge

# LD5 e LD4 equivalem ao Chip Kick e Kick

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