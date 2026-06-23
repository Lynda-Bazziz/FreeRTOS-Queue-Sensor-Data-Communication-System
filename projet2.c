#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#define DR_REG_RNG_BASE 0x3ff75144

QueueSetHandle_t fileCaptures;
typedef struct {
    char type;
    int valeur;
} capture_t;

void tacheTemp(void *params){
    uint32_t temperature;
    uint32_t delai;
    capture_t msg;
    while(true){
        temperature = READ_PERI_REG(DR_REG_RNG_BASE)%100;
        delai = READ_PERI_REG(DR_REG_RNG_BASE)%1000;
        // envoyer la temperature au monitor
        msg.type = 'T';
        msg.valeur =temperature;
        xQueueSend(fileCaptures,&msg,portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(delai));
    }
}

void tacheHum(void *params){
    uint32_t humidite;
    uint32_t delai;
    capture_t msg;
    while(true){
        humidite = READ_PERI_REG(DR_REG_RNG_BASE)%100;
        delai = READ_PERI_REG(DR_REG_RNG_BASE)%1000;
        // envoyer la temperature au monitor
        msg.type = 'H';
        msg.valeur =humidite;
        xQueueSend(fileCaptures,&msg,portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(delai));
    }
}

void tacheQual(void *params){
    uint32_t qual;
    uint32_t delai;
    capture_t msg;
    while(true){
        qual = READ_PERI_REG(DR_REG_RNG_BASE)%100;
        delai = READ_PERI_REG(DR_REG_RNG_BASE)%1000;
        // envoyer la temperature au monitor
        msg.type = 'Q';
        msg.valeur =qual;
        xQueueSend(fileCaptures,&msg,portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(delai));
    }
}

void tacheMonitor(void* params){
    capture_t msg;
    while(true){
        //récupérer une capture
        if(xQueueReceive(fileCaptures,&msg,pdMS_TO_TICKS(3000))==pdPASS){
            switch(msg.type){
                case 'T': printf("Temperature = %d\n", msg.valeur);
                          break;
                case 'H': printf("Humidité = %d\n", msg.valeur);
                          break;
                case 'Q': printf("Qualité d'air = %d\n", msg.valeur);
                          break;
                default: break;
            }

        }else{
            printf("vérifier vos capteurs\n");
            vTaskDelay(pdMS_TO_TICKS(100));
        }

    }
}

void app_main(void)
{
    fileCaptures = xQueueCreate(5,sizeof(capture_t));
    //xTaskCreate(tacheTemp,"tache",4096,NULL,4,NULL);
    //xTaskCreate(tacheHum,"tache",4096,NULL,4,NULL);
    //xTaskCreate(tacheQual,"tache",4096,NULL,4,NULL);
    xTaskCreate(tacheMonitor,"tache",4096,NULL,3,NULL);
}
