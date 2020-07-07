/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "FreeRTOS_wrapper.h"
#include "esp_system.h"
#include "IO_driver.h"
#include "Light_effects.h"
#include "wifi.h"
#include "imu6050.h"
#include "neopixel.h"
#include "Menu.h"
#include "config.h"

//master
extern xQueueHandle Light_event;
extern xQueueHandle imu_cntrl_queue;

void app_main(void)
{
    esp_set_cpu_freq(ESP_CPU_FREQ_160M);
    printf("Light test Debug\r\n");
    //IO config
    Output_LED_config();
    input_IO_config();
    Thread_safety_GPIO_config();
    //Task
    Ligth_init();
    imu_init();
    //menu
    menu_init();
    // wifi
    wifi_general_cfg();

    #if IMU_TEST
    IMU_msgID msg = IMU_START_CALIBRATION;
    vTaskDelay(1000/ portTICK_RATE_MS);
    xQueueSend(imu_cntrl_queue, &msg, 10/ portTICK_RATE_MS);
    #endif

    for(;;)
    {
        //WIFI_OFF();
        vTaskDelay(5000/ portTICK_RATE_MS);
        #if PIXEL_TEST
        Pixel_rainbow();
        #endif
        //WIFI_ON();
        //vTaskDelay(5000/ portTICK_RATE_MS);

        //Flash_color(255,255,255,100);
        //Fade_color();
        //Pixel_rainbow_Fade();
    }
    
}
