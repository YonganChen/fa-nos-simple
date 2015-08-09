# fa-nos-simple
基于友善之臂2451/6410/210开发板的裸机程序，包括硬件验证，调试/测试电路板的工具等

## 目录结构
#### Components
* SOC相关的驱动，头文件或文档，包括UART，IIC，SPI，LCD等驱动，Linker脚本，LCD时序图等
* 常用的组件，例如xprintf，实现类似printf系统调用的功能
* IC的驱动，例如Si470x系列FM IC的驱动
* 其它可能用到的文件，例如图片，音频文件等
#### Projects
* 为每个项目建立的目录，存放项目主程序代码和Makefile

## Projects说明
#### 210-Projects
* faseg48 --     4x8段数码管测试程序
* fadots  --     使用74HC595为驱动芯片的点阵LED测试程序
* fadots-2 --    使用MAX7219为驱动芯片的点阵LED测试程序
* LTC2309Test -- 12bits ADC 芯片LTC2309的测试程序

#### 6410-Projects

#### 2451-Projects
