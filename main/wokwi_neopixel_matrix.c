#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "led_strip.h"

#define STRIP_GPIO 10

void app_main(void)
{
  printf("Hello, Wokwi!\n");

  led_strip_handle_t led_strip;

  /* LED strip initialization with the GPIO and pixels number*/
  led_strip_config_t strip_config = {
    .strip_gpio_num = STRIP_GPIO, // The GPIO that connected to the LED strip's data line
    .max_leds = 256, // The number of LEDs in the strip,
    .led_pixel_format = LED_PIXEL_FORMAT_GRB, // Pixel format of your LED strip
    .led_model = LED_MODEL_WS2812, // LED strip model
    .flags.invert_out = false, // whether to invert the output signal (useful when your hardware has a level inverter)
  };

  led_strip_spi_config_t spi_config = {
    .clk_src = SPI_CLK_SRC_DEFAULT, // different clock source can lead to different power consumption
    .flags.with_dma = true, // Using DMA can improve performance and help drive more LEDs
    .spi_bus = SPI2_HOST,   // SPI bus ID
  };
  ESP_ERROR_CHECK(led_strip_new_spi_device(&strip_config, &spi_config, &led_strip));

  while (true) {

    int leds_to_light = 9;

    led_strip_clear(led_strip);
    for (int i = 0; i < leds_to_light; i++) {
      led_strip_set_pixel(led_strip, i, 0, 0, 200);
      led_strip_refresh(led_strip);
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
}
