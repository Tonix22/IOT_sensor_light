#include <stdio.h>
#include <vector>
#include "esp_system.h"
#include "Light_effects.h"
#include "FreeRTOS_wrapper.h"



Light LedStick;

xQueueHandle Light_event = NULL;

static TimerHandle_t hold_next_sound;
static bool sound_released = true;
void sound_action (TimerHandle_t xTimer );

void Light_task(void *arg)
{
    Light_event = xQueueCreate(10, sizeof(uint32_t));
    hold_next_sound = xTimerCreate("Sound", 100/ portTICK_RATE_MS, pdFALSE, 0, sound_action);
    MessageID msg;
    printf("light_stask init\r\n");
    for(;;)
    {
        if (xQueueReceive(Light_event, &msg, portMAX_DELAY))
        {
            if(msg == SOUND && sound_released == true)
            {
                sound_released = false;
                xTimerStart(hold_next_sound, 0 );
            }
        }
    }
}

void Ligth_init(void)
{
    xTaskCreate(Light_task, "Light_task", 2048, NULL, 10, NULL);
}


void sound_action (TimerHandle_t xTimer )
{
    static char toggle = 0;
    toggle^=1;
    static bool frame = 0;
    if(toggle)
    {
        LedStick.Led_stick_off();
    }
    else
    {
        if(frame)
        {
            LedStick.Fill_Led_stick(255,128,0);
        }
        else
        {
            LedStick.Fill_Led_stick(255,0,0);
        }
        frame^=1;
    }
    sound_released = true;
}


void Fade_color(void)
{
    uint8_t leds_num = 0;
    bool orange = false;
    auto it = LedStick.Fade_colors.begin();
    while(1)
    {
        leds_num++;

        for(int j=0; j < leds_num ;j++)
        {
            Color_Frame((*it).RED,(*it).GREEN,(*it).BLUE);
        }
        if(leds_num == LedStick.pixels)
        {
            leds_num = 0;
            it++;
            if(it == LedStick.Fade_colors.end())
            {
                it = LedStick.Fade_colors.begin();
            }
        }
        vTaskDelay(80/ portTICK_RATE_MS);
    }
}

void Flash_color(uint8_t R, uint8_t G, uint8_t B, int ms_rate)
{ 
    LedStick.Fill_Led_stick(R,G,B);

    vTaskDelay(ms_rate/ portTICK_RATE_MS);

    LedStick.Led_stick_off();

    vTaskDelay(ms_rate/ portTICK_RATE_MS); 
}


void Pixel_rainbow(void)
{
   
    int red = 0;
    int green=0;
    int blue=0;

    for(red=0; red < 255; red++)
    {
        vTaskDelay(LedStick.rainbow_delay/ portTICK_RATE_MS);
        LedStick.Fill_Led_stick(red,green,blue);
    }
    for(green=0; green < 255; green++)
    {
        vTaskDelay(LedStick.rainbow_delay/ portTICK_RATE_MS);
        LedStick.Fill_Led_stick(red,green,blue);
    }
    for(red=255; red!=0; red--)
    {
        vTaskDelay(LedStick.rainbow_delay/ portTICK_RATE_MS);
        LedStick.Fill_Led_stick(red,green,blue);
    }
    for(blue=0; blue < 255; blue++)
    {
        vTaskDelay(LedStick.rainbow_delay/ portTICK_RATE_MS);
        LedStick.Fill_Led_stick(red,green,blue);
    }
    for(green=255; green!=0; green--)
    {
        vTaskDelay(LedStick.rainbow_delay/ portTICK_RATE_MS);
        LedStick.Fill_Led_stick(red,green,blue);
    }

    for(blue=255; blue!=0; blue--)
    {
        vTaskDelay(LedStick.rainbow_delay/ portTICK_RATE_MS);
        LedStick.Fill_Led_stick(red,green,blue);
    }
}



