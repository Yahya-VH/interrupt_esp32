#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define TOUCH_PIN_1 GPIO_NUM_22
#define TOUCH_PIN_2 GPIO_NUM_23
#define LED_PIN GPIO_NUM_5

int led_state = 0;
int rising_edge_detected_1 = 0;
int rising_edge_detected_2 = 0;

void IRAM_ATTR touch_isr_handler_1()
{
    int touch_value = gpio_get_level(TOUCH_PIN_1);

    if (touch_value == 1 && !rising_edge_detected_1)
    {
        rising_edge_detected_1 = 1;
        
        
    }
    else if (touch_value == 0 && rising_edge_detected_1)
    {
        rising_edge_detected_1 = 0;
        
    led_state = 1;
        gpio_set_level(LED_PIN, led_state);
    }
        
}

void IRAM_ATTR touch_isr_handler_2()
{
    int touch_value = gpio_get_level(TOUCH_PIN_2);

    if (touch_value == 1 && !rising_edge_detected_2)
    {
        rising_edge_detected_2 = 1;
        
       
    }
    else if (touch_value == 0 && rising_edge_detected_2)
    {
        rising_edge_detected_2 = 0; 
        led_state = 0;
        gpio_set_level(LED_PIN, led_state);
        
    }
}

void app_main(void)
{
    gpio_set_direction(TOUCH_PIN_1, GPIO_MODE_INPUT);
    gpio_set_intr_type(TOUCH_PIN_1, GPIO_INTR_ANYEDGE);

    gpio_set_direction(TOUCH_PIN_2, GPIO_MODE_INPUT);
    gpio_set_intr_type(TOUCH_PIN_2, GPIO_INTR_ANYEDGE);

    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(TOUCH_PIN_1, touch_isr_handler_1, (void*)TOUCH_PIN_1);
    gpio_isr_handler_add(TOUCH_PIN_2, touch_isr_handler_2, (void*)TOUCH_PIN_2);

    while (1)
    {
        
    }
}
