/*
 * lcd.h
 *
 *  Created on: 2012-12-22
 *      Author: chen
 */

#ifndef LCD_H_
#define LCD_H_


#define LCD_S70         // define which lcd to be used in this project: S70, N43

/*
 * S70
 */

#ifdef  LCD_S70

#define VOUT_RGB
#define VCLK         (33300000)     // DCLK Frequency, Hz
#define HOZ_VAL      (800)          // Horizontal display size
#define LINE_VAL     (480)          // Vertical display size
#define TVB          (27)           // Vertical back porch
#define TVFP         (80)           // Vertical front porch
#define TVPW         (10)           // Vertical sync pulse width
#define THB          (100)           // Horizontal back porch 27
#define THFP         (50)          // Horizontal front porch 210
#define THPW         (20)           // Horizontal sync pulse width
#define VIDCON1_VAL  (0x260)         // [10:9]FIXVCLK, [7]IVCLK, [6]IHSYNC, [5]IVSYNC, [4]IVDEN
#define VIDCON2_VAL  (0xc000)
#define VIDCON3_VAL  (0x00)
#define VIDTCON3_VAL (0x80000000)

#endif /* LCD_S70 */

/*
 * N43
 */
#ifdef  LCD_N43

#define VOUT_RGB
#define VCLK         (8690000)    // DCLK Frequency, Hz
#define HOZ_VAL      (480)          // Horizontal display size >=1
#define LINE_VAL     (272)          // Vertical display size >=1
#define TVB          (3)           // Vertical back porch >=1
#define TVFP         (5)           // Vertical front porch >=1
#define TVPW         (20)           // Vertical sync pulse width >=1
#define THB          (44)           // Horizontal back porch >=1
#define THFP         (5)          // Horizontal front porch >=1
#define THPW         (20)           // Horizontal sync pulse width >=1
#define VIDCON1_VAL  (0x08)         // [10:9]FIXVCLK, [7]IVCLK, [6]IHSYNC, [5]IVSYNC, [4]IVDEN
#define VIDCON2_VAL  (0xc000)
#define VIDCON3_VAL  (0x00)
#define VIDTCON3_VAL (0x80000000)

#endif /* LCD_N43 */

#ifdef  LCD_U80

#define VOUT_RGB
#define VCLK         (33000000)     // DCLK Frequency, Hz
#define HOZ_VAL      (800)          // Horizontal display size
#define LINE_VAL     (600)          // Vertical display size
#define TVB          (25)           // Vertical back porch
#define TVFP         (2)           // Vertical front porch
#define TVPW         (5)           // Vertical sync pulse width
#define THB          (250)           // Horizontal back porch
#define THFP         (2)          // Horizontal front porch
#define THPW         (5)           // Horizontal sync pulse width
#define VIDCON1_VAL  (0x260)         // [10:9]FIXVCLK, [7]IVCLK, [6]IHSYNC, [5]IVSYNC, [4]IVDEN
#define VIDCON2_VAL  (0xc000)
#define VIDCON3_VAL  (0x00)
#define VIDTCON3_VAL (0x80000000)

#endif /* LCD_U80 */

#ifdef  LCD_HD97

#define VOUT_RGB
#define VCLK         (50000000)     // DCLK Frequency, Hz
#define HOZ_VAL      (1024)          // Horizontal display size
#define LINE_VAL     (768)          // Vertical display size
#define TVB          (25)           // Vertical back porch
#define TVFP         (2)           // Vertical front porch
#define TVPW         (5)           // Vertical sync pulse width
#define THB          (250)           // Horizontal back porch
#define THFP         (2)          // Horizontal front porch
#define THPW         (50)           // Horizontal sync pulse width
#define VIDCON1_VAL  (0x00)         // [10:9]FIXVCLK, [7]IVCLK, [6]IHSYNC, [5]IVSYNC, [4]IVDEN
#define VIDCON2_VAL  (0xc000)
#define VIDCON3_VAL  (0x00)
#define VIDTCON3_VAL (0x80000000)

#endif /* LCD_HD97 */

#ifdef  LCD_P35

#define VOUT_RGB
#define VCLK         (5000000)     // DCLK Frequency, Hz
#define HOZ_VAL      (320)          // Horizontal display size
#define LINE_VAL     (240)          // Vertical display size
#define TVB          (1)           // Vertical back porch
#define TVFP         (13)           // Vertical front porch
#define TVPW         (12)           // Vertical sync pulse width
#define THB          (1)           // Horizontal back porch
#define THFP         (30)          // Horizontal front porch
#define THPW         (7)           // Horizontal sync pulse width
#define VIDCON1_VAL  (0x2e0)         // [10:9]FIXVCLK, [7]IVCLK, [6]IHSYNC, [5]IVSYNC, [4]IVDEN
#define VIDCON2_VAL  (0xc000)
#define VIDCON3_VAL  (0x00)
#define VIDTCON3_VAL (0x80000000)

#endif /* LCD_P35 */


#endif /* LCD_H_ */
