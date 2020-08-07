#ifndef LIGHT_EFFECTS_H
#define LIGHT_EFFECTS_H

#ifdef __cplusplus
extern "C" 
{
#endif

    typedef enum
    {
        ENABLE_SOUND,
        SOUND,
        IMU,
        FADE,
        WIFI_CMD,
        CALIBRATION,
        END_CALIBRATION,
        ABORT_CALIBRATION,
        OFF,
        LOAD_EFFECTS,
    }Light_MessageID;

    void Light_task(void *arg);
    void Ligth_init(void);
    void Pixel_rainbow(void);
    void Flash_color(uint8_t R, uint8_t G, uint8_t B, int ms_rate);
    void Fade_color(void);
    void Fade_colorG(void);
    void Pixel_rainbow_Fade(void);

    #ifdef __cplusplus
        #include "neopixel.h"
        #include "IO_driver.h"
        #include "structs.h"
        #include <vector>
        #include <list>
        typedef std::list<RGB>* list_ptr;
        class Light
        {
            
            public:
            uint8_t pixels        = 8;
            uint8_t rainbow_delay = 10;
            int flash_times       = 1000;
            int fade_cycles       = 1000;
            
            std::list<RGBT> idle_light;
            std::list<RGB> sound_light;
            std::list<RGB> circular_light;
            std::list<RGB> linear_light;

            list_ptr feature_collection[Features];
            
            Light()
            {
                feature_collection[RITH_feature]     = &sound_light;
                feature_collection[CIRCULAR_feature] = &circular_light;
                feature_collection[LINEAR_feature]   = &linear_light;
            }

            std::vector<RGB> Fade_colors
            {
                {255, 0  , 0},
                {255, 128, 0},
            };

            std::vector<RGB> Pixel_Rainbow
            {
                {255, 0,   0  },
                {255, 165, 0  },
                {255, 255, 0  },
                {0,   128, 0  },
                {28,  188, 196},
                {0,   0,   255},
                {75,  0,   130},
                {238, 130, 238},
            };

            void Fill_Led_stick(uint8_t R,uint8_t G,uint8_t B)
            {
                for(int led = 0; led < this->pixels ;led++)
                {
                    Color_Frame(R,G,B);
                }
            }
            void Fill_Led_stick(RGB& LED)
            {
                for(int led = 0; led < this->pixels ;led++)
                {
                    Color_Frame(LED.RED, LED.GREEN,LED.BLUE);
                }
            }
            void Paint_LED(RGB& LED)
            {
                Color_Frame(LED.RED, LED.GREEN,LED.BLUE);
            }
            void Led_stick_off(void)
            {
                Fill_Led_stick(0,0,0);
            }
        };
}
    #endif

#endif