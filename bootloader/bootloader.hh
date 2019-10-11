
#define TICKS_PER_MS 10

#if (PCB_VERSION==2)
#define BOOTLOADER_INPUT_GPIO GPIOC
#define BOOTLOADER_INPUT_PIN GPIO_PIN_0
#define BOOTLOADER_INPUT_RCC_ENABLE __HAL_RCC_GPIOC_CLK_ENABLE

#elif (PCB_VERSION==3)
#define BOOTLOADER_INPUT_GPIO GPIOB
#define BOOTLOADER_INPUT_PIN GPIO_PIN_8
#define BOOTLOADER_INPUT_RCC_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE

#else
#error "bootloader.hh does not recognize PCB_VERISON"
#endif
