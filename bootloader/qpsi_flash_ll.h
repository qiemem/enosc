#pragma once
#include <stm32f7xx.h>

void LL_QSPI_Command(QSPI_CommandTypeDef *cmd);
void LL_QSPI_Transmit(uint8_t *pData);
void LL_QSPI_WriteEnable(void);
void LL_QSPI_StartAutoPoll(uint32_t Match, uint32_t Mask, uint32_t Interval, uint32_t MatchMode);

void LL_QPSI_SetAltBytes(uint32_t AlternateBytes);
void LL_QPSI_SetDataLength(uint32_t NbData);
void LL_QSPI_SetCommunicationConfig(QSPI_CommandTypeDef *cmd, uint32_t FunctionalMode);
void LL_QSPI_SetAddress(uint32_t address);

void LL_QSPI_WaitNotBusy(void);
uint32_t LL_QSPI_WaitFlagTimeout(uint32_t flag);
void LL_QSPI_WaitFlag(uint32_t flag);
void LL_QSPI_ClearFlag(uint32_t flag);


//Chip-specific:
#define QSPI_FLASH_SIZE_BYTES            0x40000    // 256 KBytes
#define QSPI_64KBLOCK_SIZE               0x10000    // 64 KBytes, hence the name "64K Block" :)
#define QSPI_32KBLOCK_SIZE               0x8000     // 32 KBytes, hence the name "32K Block" :)
#define QSPI_SECTOR_SIZE                 0x1000     // 4 KBytes sectors
#define QSPI_PAGE_SIZE                   0x100      // 256 Byte pages
#define QSPI_PAGE_ADDRESS_BITS           8          // 8 bits = 256 addresses per page

#define QSPI_NUM_64KBLOCKS              (QSPI_FLASH_SIZE_BYTES/QSPI_64KBLOCK_SIZE)
#define QSPI_NUM_32KBLOCKS              (QSPI_FLASH_SIZE_BYTES/QSPI_32KBLOCK_SIZE)
#define QSPI_NUM_SECTORS                (QSPI_FLASH_SIZE_BYTES/QSPI_SECTOR_SIZE)

//Board-specific:
#define QSPI_CS_PIN                LL_GPIO_PIN_11
#define LL_GPIO_SetAFPin_QSPI_CS() LL_GPIO_SetAFPin_8_15(LL_GPIO_AF_9)
#define QSPI_CS_GPIO_PORT          GPIOC

#define QSPI_CLK_PIN               LL_GPIO_PIN_2
#define LL_GPIO_SetAFPin_QSPI_CLK() LL_GPIO_SetAFPin_0_7(LL_GPIO_AF_9)
#define QSPI_CLK_GPIO_PORT         GPIOB

#define QSPI_D0_PIN                LL_GPIO_PIN_7
#define LL_GPIO_SetAFPin_QSPI_D0() LL_GPIO_SetAFPin_0_7(LL_GPIO_AF_10)
#define QSPI_D0_GPIO_PORT          GPIOE

#define QSPI_D1_PIN                LL_GPIO_PIN_8
#define LL_GPIO_SetAFPin_QSPI_D1() LL_GPIO_SetAFPin_8_15(LL_GPIO_AF_10)
#define QSPI_D1_GPIO_PORT          GPIOE

#define QSPI_D2_PIN                LL_GPIO_PIN_9
#define LL_GPIO_SetAFPin_QSPI_D2() LL_GPIO_SetAFPin_8_15(LL_GPIO_AF_10)
#define QSPI_D2_GPIO_PORT          GPIOE

#define QSPI_D3_PIN                LL_GPIO_PIN_10
#define LL_GPIO_SetAFPin_QSPI_D3() LL_GPIO_SetAFPin_8_15(LL_GPIO_AF_10)
#define QSPI_D3_GPIO_PORT          GPIOE

//Typical QSPI chip (but may be chip-specific)
/* Reset Operations */
#define RESET_ENABLE_CMD                    0x66
#define RESET_CMD                           0x99
#define DEEP_POWER_DOWN_CMD                 0xB9

/* Identification Operations */
#define READ_ID_CMD                         0x9F
#define READ_MANUF_RELEASE_DP               0xAB
#define READ_UID                            0x4B
#define READ_SERIAL_FLASH_DISCO_PARAM_CMD   0x5A


/* Read Operations */
#define READ_CMD                             0x03
#define FAST_READ_CMD                        0x0B
#define DUAL_OUT_FAST_READ_CMD               0x3B
#define DUAL_INOUT_FAST_READ_CMD             0xBB
#define QUAD_OUT_FAST_READ_CMD               0x6B
#define QUAD_INOUT_FAST_READ_CMD             0xEB

/* Register Operations */
#define READ_STATUS_REG_CMD                  0x05
#define WRITE_STATUS_REG_CMD                 0x01
#define READ_FUNCTION_REG_CMD                0x48
#define WRITE_FUNCTION_REG_CMD               0x42
#define READ_INFO_ROW                       0x62
#define PROG_INFO_ROW                       0x68
#define SECTOR_UNLOCK                       0x26
#define SECTOR_LOCK                         0x24
#define WRITE_ENABLE_CMD                    0x06

/* Program Operations */
#define PAGE_PROG_CMD                        0x02
#define QUAD_IN_FAST_PROG_CMD                0x38

/* Erase Operations */
#define SECTOR_ERASE_CMD                  0x20
       
#define BLOCK_ERASE_32K_CMD                     0x52
#define BLOCK_ERASE_64K_CMD                     0xD8
#define BULK_ERASE_CMD                       0xC7
#define PROG_ERASE_RESUME_CMD                0x30
#define PROG_ERASE_SUSPEND_CMD               0xB0
   
/* Status Register */
#define QSPI_SR_WIP                      ((uint8_t)0x01)    /*!< Write in progress */
#define QSPI_SR_WREN                     ((uint8_t)0x02)    /*!< Write enable latch */
#define QSPI_SR_BLOCKPR                  ((uint8_t)0x5C)    /*!< Block protected against program and erase operations */
#define QSPI_SR_PRBOTTOM                 ((uint8_t)0x20)    /*!< Protected memory area defined by BLOCKPR starts from top or bottom */
#define QSPI_SR_QUADEN                   ((uint8_t)0x40)    /*!< Quad IO mode enabled if =1 */
#define QSPI_SR_SRWREN                   ((uint8_t)0x80)    /*!< Status register write enable/disable */



//From HAL:

typedef struct
{
  uint32_t Instruction;        /* Specifies the Instruction to be sent
                                  This parameter can be a value (8-bit) between 0x00 and 0xFF */
  uint32_t Address;            /* Specifies the Address to be sent (Size from 1 to 4 bytes according AddressSize)
                                  This parameter can be a value (32-bits) between 0x0 and 0xFFFFFFFF */
  uint32_t AlternateBytes;     /* Specifies the Alternate Bytes to be sent (Size from 1 to 4 bytes according AlternateBytesSize)
                                  This parameter can be a value (32-bits) between 0x0 and 0xFFFFFFFF */
  uint32_t AddressSize;        /* Specifies the Address Size
                                  This parameter can be a value of @ref QSPI_AddressSize */
  uint32_t AlternateBytesSize; /* Specifies the Alternate Bytes Size
                                  This parameter can be a value of @ref QSPI_AlternateBytesSize */
  uint32_t DummyCycles;        /* Specifies the Number of Dummy Cycles.
                                  This parameter can be a number between 0 and 31 */
  uint32_t InstructionMode;    /* Specifies the Instruction Mode
                                  This parameter can be a value of @ref QSPI_InstructionMode */
  uint32_t AddressMode;        /* Specifies the Address Mode
                                  This parameter can be a value of @ref QSPI_AddressMode */
  uint32_t AlternateByteMode;  /* Specifies the Alternate Bytes Mode
                                  This parameter can be a value of @ref QSPI_AlternateBytesMode */
  uint32_t DataMode;           /* Specifies the Data Mode (used for dummy cycles and data phases)
                                  This parameter can be a value of @ref QSPI_DataMode */
  uint32_t NbData;             /* Specifies the number of data to transfer. 
                                  This parameter can be any value between 0 and 0xFFFFFFFF (0 means undefined length 
                                  until end of memory)*/
  uint32_t DdrMode;            /* Specifies the double data rate mode for address, alternate byte and data phase
                                  This parameter can be a value of @ref QSPI_DdrMode */
  uint32_t DdrHoldHalfCycle;   /* Specifies the DDR hold half cycle. It delays the data output by one half of 
                                  system clock in DDR mode.
                                  This parameter can be a value of @ref QSPI_DdrHoldHalfCycle */
  uint32_t SIOOMode;          /* Specifies the send instruction only once mode
                                  This parameter can be a value of @ref QSPI_SIOOMode */
}QSPI_CommandTypeDef;


#define QSPI_FUNCTIONAL_MODE_INDIRECT_WRITE ((uint32_t)0x00000000U)          /*!<Indirect write mode*/
#define QSPI_FUNCTIONAL_MODE_INDIRECT_READ  ((uint32_t)QUADSPI_CCR_FMODE_0) /*!<Indirect read mode*/
#define QSPI_FUNCTIONAL_MODE_AUTO_POLLING   ((uint32_t)QUADSPI_CCR_FMODE_1) /*!<Automatic polling mode*/
#define QSPI_FUNCTIONAL_MODE_MEMORY_MAPPED  ((uint32_t)QUADSPI_CCR_FMODE)   /*!<Memory-mapped mode*/

/** @defgroup QSPI_SampleShifting QSPI Sample Shifting
  * @{
  */
#define QSPI_SAMPLE_SHIFTING_NONE           ((uint32_t)0x00000000U)        /*!<No clock cycle shift to sample data*/
#define QSPI_SAMPLE_SHIFTING_HALFCYCLE      ((uint32_t)QUADSPI_CR_SSHIFT) /*!<1/2 clock cycle shift to sample data*/
/**
  * @}
  */ 

/** @defgroup QSPI_ChipSelectHighTime QSPI Chip Select High Time
  * @{
  */
#define QSPI_CS_HIGH_TIME_1_CYCLE           ((uint32_t)0x00000000U)                              /*!<nCS stay high for at least 1 clock cycle between commands*/
#define QSPI_CS_HIGH_TIME_2_CYCLE           ((uint32_t)QUADSPI_DCR_CSHT_0)                      /*!<nCS stay high for at least 2 clock cycles between commands*/
#define QSPI_CS_HIGH_TIME_3_CYCLE           ((uint32_t)QUADSPI_DCR_CSHT_1)                      /*!<nCS stay high for at least 3 clock cycles between commands*/
#define QSPI_CS_HIGH_TIME_4_CYCLE           ((uint32_t)QUADSPI_DCR_CSHT_0 | QUADSPI_DCR_CSHT_1) /*!<nCS stay high for at least 4 clock cycles between commands*/
#define QSPI_CS_HIGH_TIME_5_CYCLE           ((uint32_t)QUADSPI_DCR_CSHT_2)                      /*!<nCS stay high for at least 5 clock cycles between commands*/
#define QSPI_CS_HIGH_TIME_6_CYCLE           ((uint32_t)QUADSPI_DCR_CSHT_2 | QUADSPI_DCR_CSHT_0) /*!<nCS stay high for at least 6 clock cycles between commands*/
#define QSPI_CS_HIGH_TIME_7_CYCLE           ((uint32_t)QUADSPI_DCR_CSHT_2 | QUADSPI_DCR_CSHT_1) /*!<nCS stay high for at least 7 clock cycles between commands*/
#define QSPI_CS_HIGH_TIME_8_CYCLE           ((uint32_t)QUADSPI_DCR_CSHT)                        /*!<nCS stay high for at least 8 clock cycles between commands*/
/**
  * @}
  */

/** @defgroup QSPI_ClockMode QSPI Clock Mode
  * @{
  */
#define QSPI_CLOCK_MODE_0                   ((uint32_t)0x00000000U)         /*!<Clk stays low while nCS is released*/
#define QSPI_CLOCK_MODE_3                   ((uint32_t)QUADSPI_DCR_CKMODE) /*!<Clk goes high while nCS is released*/
/**
  * @}
  */
  
/** @defgroup QSPI_Flash_Select QSPI Flash Select
  * @{
  */
#define QSPI_FLASH_ID_1           ((uint32_t)0x00000000U)
#define QSPI_FLASH_ID_2           ((uint32_t)QUADSPI_CR_FSEL)
/**
  * @}
  */  

  /** @defgroup QSPI_DualFlash_Mode  QSPI Dual Flash Mode
  * @{
  */
#define QSPI_DUALFLASH_ENABLE            ((uint32_t)QUADSPI_CR_DFM)
#define QSPI_DUALFLASH_DISABLE           ((uint32_t)0x00000000U) 
/**
  * @}
  */ 

/** @defgroup QSPI_AddressSize QSPI Address Size 
  * @{
  */
#define QSPI_ADDRESS_8_BITS            ((uint32_t)0x00000000U)           /*!<8-bit address*/
#define QSPI_ADDRESS_16_BITS           ((uint32_t)QUADSPI_CCR_ADSIZE_0) /*!<16-bit address*/
#define QSPI_ADDRESS_24_BITS           ((uint32_t)QUADSPI_CCR_ADSIZE_1) /*!<24-bit address*/
#define QSPI_ADDRESS_32_BITS           ((uint32_t)QUADSPI_CCR_ADSIZE)   /*!<32-bit address*/
/**
  * @}
  */  

/** @defgroup QSPI_AlternateBytesSize QSPI Alternate Bytes Size
  * @{
  */
#define QSPI_ALTERNATE_BYTES_8_BITS    ((uint32_t)0x00000000U)           /*!<8-bit alternate bytes*/
#define QSPI_ALTERNATE_BYTES_16_BITS   ((uint32_t)QUADSPI_CCR_ABSIZE_0) /*!<16-bit alternate bytes*/
#define QSPI_ALTERNATE_BYTES_24_BITS   ((uint32_t)QUADSPI_CCR_ABSIZE_1) /*!<24-bit alternate bytes*/
#define QSPI_ALTERNATE_BYTES_32_BITS   ((uint32_t)QUADSPI_CCR_ABSIZE)   /*!<32-bit alternate bytes*/
/**
  * @}
  */

/** @defgroup QSPI_InstructionMode QSPI Instruction Mode
* @{
*/
#define QSPI_INSTRUCTION_NONE          ((uint32_t)0x00000000U)          /*!<No instruction*/
#define QSPI_INSTRUCTION_1_LINE        ((uint32_t)QUADSPI_CCR_IMODE_0) /*!<Instruction on a single line*/
#define QSPI_INSTRUCTION_2_LINES       ((uint32_t)QUADSPI_CCR_IMODE_1) /*!<Instruction on two lines*/
#define QSPI_INSTRUCTION_4_LINES       ((uint32_t)QUADSPI_CCR_IMODE)   /*!<Instruction on four lines*/
/**
  * @}
  */

/** @defgroup QSPI_AddressMode QSPI Address Mode
* @{
*/
#define QSPI_ADDRESS_NONE              ((uint32_t)0x00000000U)           /*!<No address*/
#define QSPI_ADDRESS_1_LINE            ((uint32_t)QUADSPI_CCR_ADMODE_0) /*!<Address on a single line*/
#define QSPI_ADDRESS_2_LINES           ((uint32_t)QUADSPI_CCR_ADMODE_1) /*!<Address on two lines*/
#define QSPI_ADDRESS_4_LINES           ((uint32_t)QUADSPI_CCR_ADMODE)   /*!<Address on four lines*/
/**
  * @}
  */  

/** @defgroup QSPI_AlternateBytesMode  QSPI Alternate Bytes Mode
* @{                                  
*/
#define QSPI_ALTERNATE_BYTES_NONE      ((uint32_t)0x00000000U)           /*!<No alternate bytes*/
#define QSPI_ALTERNATE_BYTES_1_LINE    ((uint32_t)QUADSPI_CCR_ABMODE_0) /*!<Alternate bytes on a single line*/
#define QSPI_ALTERNATE_BYTES_2_LINES   ((uint32_t)QUADSPI_CCR_ABMODE_1) /*!<Alternate bytes on two lines*/
#define QSPI_ALTERNATE_BYTES_4_LINES   ((uint32_t)QUADSPI_CCR_ABMODE)   /*!<Alternate bytes on four lines*/
/**
  * @}
  */  

/** @defgroup QSPI_DataMode QSPI Data Mode
  * @{
  */
#define QSPI_DATA_NONE                 ((uint32_t)0X00000000)           /*!<No data*/
#define QSPI_DATA_1_LINE               ((uint32_t)QUADSPI_CCR_DMODE_0) /*!<Data on a single line*/
#define QSPI_DATA_2_LINES              ((uint32_t)QUADSPI_CCR_DMODE_1) /*!<Data on two lines*/
#define QSPI_DATA_4_LINES              ((uint32_t)QUADSPI_CCR_DMODE)   /*!<Data on four lines*/
/**
  * @}
  */  

/** @defgroup QSPI_DdrMode QSPI Ddr Mode
  * @{
  */
#define QSPI_DDR_MODE_DISABLE              ((uint32_t)0x00000000U)       /*!<Double data rate mode disabled*/
#define QSPI_DDR_MODE_ENABLE               ((uint32_t)QUADSPI_CCR_DDRM) /*!<Double data rate mode enabled*/
/**
  * @}
  */

/** @defgroup QSPI_DdrHoldHalfCycle QSPI Ddr HoldHalfCycle
  * @{
  */
#define QSPI_DDR_HHC_ANALOG_DELAY           ((uint32_t)0x00000000U)       /*!<Delay the data output using analog delay in DDR mode*/
#define QSPI_DDR_HHC_HALF_CLK_DELAY         ((uint32_t)QUADSPI_CCR_DHHC) /*!<Delay the data output by 1/2 clock cycle in DDR mode*/
/**
  * @}
  */

/** @defgroup QSPI_SIOOMode QSPI SIOO Mode
  * @{
  */
#define QSPI_SIOO_INST_EVERY_CMD       ((uint32_t)0x00000000U)       /*!<Send instruction on every transaction*/
#define QSPI_SIOO_INST_ONLY_FIRST_CMD  ((uint32_t)QUADSPI_CCR_SIOO) /*!<Send instruction only for the first command*/
/**
  * @}
  */

/** @defgroup QSPI_MatchMode QSPI Match Mode
  * @{
  */
#define QSPI_MATCH_MODE_AND                 ((uint32_t)0x00000000U)     /*!<AND match mode between unmasked bits*/
#define QSPI_MATCH_MODE_OR                  ((uint32_t)QUADSPI_CR_PMM) /*!<OR match mode between unmasked bits*/
/**
  * @}
  */  

/** @defgroup QSPI_AutomaticStop QSPI Automatic Stop
  * @{
  */
#define QSPI_AUTOMATIC_STOP_DISABLE        ((uint32_t)0x00000000U)      /*!<AutoPolling stops only with abort or QSPI disabling*/
#define QSPI_AUTOMATIC_STOP_ENABLE         ((uint32_t)QUADSPI_CR_APMS) /*!<AutoPolling stops as soon as there is a match*/
/**
  * @}
  */  

/** @defgroup QSPI_TimeOutActivation QSPI TimeOut Activation
  * @{
  */
#define QSPI_TIMEOUT_COUNTER_DISABLE       ((uint32_t)0x00000000U)      /*!<Timeout counter disabled, nCS remains active*/
#define QSPI_TIMEOUT_COUNTER_ENABLE        ((uint32_t)QUADSPI_CR_TCEN) /*!<Timeout counter enabled, nCS released when timeout expires*/
/**
  * @}
  */  

/** @defgroup QSPI_Flags  QSPI Flags
  * @{
  */
#define QSPI_FLAG_BUSY                 QUADSPI_SR_BUSY /*!<Busy flag: operation is ongoing*/
#define QSPI_FLAG_TO                   QUADSPI_SR_TOF  /*!<Timeout flag: timeout occurs in memory-mapped mode*/
#define QSPI_FLAG_SM                   QUADSPI_SR_SMF  /*!<Status match flag: received data matches in autopolling mode*/
#define QSPI_FLAG_FT                   QUADSPI_SR_FTF  /*!<Fifo threshold flag: Fifo threshold reached or data left after read from memory is complete*/
#define QSPI_FLAG_TC                   QUADSPI_SR_TCF  /*!<Transfer complete flag: programmed number of data have been transferred or the transfer has been aborted*/
#define QSPI_FLAG_TE                   QUADSPI_SR_TEF  /*!<Transfer error flag: invalid address is being accessed*/
/**
  * @}
  */

/** @defgroup QSPI_Interrupts  QSPI Interrupts
  * @{
  */  
#define QSPI_IT_TO                          QUADSPI_CR_TOIE /*!<Interrupt on the timeout flag*/
#define QSPI_IT_SM                          QUADSPI_CR_SMIE /*!<Interrupt on the status match flag*/
#define QSPI_IT_FT                          QUADSPI_CR_FTIE /*!<Interrupt on the fifo threshold flag*/
#define QSPI_IT_TC                          QUADSPI_CR_TCIE /*!<Interrupt on the transfer complete flag*/
#define QSPI_IT_TE                          QUADSPI_CR_TEIE /*!<Interrupt on the transfer error flag*/
