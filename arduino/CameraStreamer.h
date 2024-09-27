#ifndef CAMERA_STREAMER_H
#define CAMERA_STREAMER_H

#include <WiFi.h>
#include "esp_camera.h"
#include "esp_timer.h"
#include "img_converters.h"
#include "fb_gfx.h"
#include "fd_forward.h"
#include "fr_forward.h"
#include "rtsp_server.h"

#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27

#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22
class CameraStreamer
{
public:
    CameraStreamer(const char *ssid, const char *password)
        : ssid(ssid), password(password) {}

    void begin()
    {
        connectWiFi();
        initCamera();
        rtsp_server.begin();
    }

    void handle()
    {
        rtsp_server.handle();
    }

private:
    const char *ssid;
    const char *password;

    void connectWiFi()
    {
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.println("Connecting to WiFi...");
        }
        Serial.println("Connected to WiFi");
    }

    void initCamera()
    {
        camera_config_t config;
        config.ledc_channel = LEDC_CHANNEL_0;
        config.ledc_timer = LEDC_TIMER_0;
        config.pin_d0 = Y2_GPIO_NUM;
        config.pin_d1 = Y3_GPIO_NUM;
        config.pin_d2 = Y4_GPIO_NUM;
        config.pin_d3 = Y5_GPIO_NUM;
        config.pin_d4 = Y6_GPIO_NUM;
        config.pin_d5 = Y7_GPIO_NUM;
        config.pin_d6 = Y8_GPIO_NUM;
        config.pin_d7 = Y9_GPIO_NUM;
        config.pin_xclk = XCLK_GPIO_NUM;
        config.pin_pclk = PCLK_GPIO_NUM;
        config.pin_vsync = VSYNC_GPIO_NUM;
        config.pin_href = HREF_GPIO_NUM;
        config.pin_sccb_sda = SIOD_GPIO_NUM;
        config.pin_sccb_scl = SIOC_GPIO_NUM;
        config.pin_pwdn = PWDN_GPIO_NUM;
        config.pin_reset = RESET_GPIO_NUM;
        config.xclk_freq_hz = 20000000;
        config.pixel_format = PIXFORMAT_JPEG;

        if (psramFound())
        {
            config.frame_size = FRAMESIZE_VGA;
            config.jpeg_quality = 10;
            config.fb_count = 2;
        }
        else
        {
            config.frame_size = FRAMESIZE_QVGA;
            config.jpeg_quality = 12;
            config.fb_count = 1;
        }

        esp_err_t err = esp_camera_init(&config);
        if (err != ESP_OK)
        {
            Serial.printf("Camera init failed with error 0x%x", err);
            return;
        }
    }
};

#endif // CAMERA_STREAMER_H
