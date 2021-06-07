参数：电源DC5V
功能：
1、电平输出：通过调节RV1电位器改变模块阈值，当模块检测距离大于阈值，S引脚输出高电平，D1指示灯亮；反之S引脚输出低电平，D1指示灯灭。
2、串口输出：被动工作模式下，需要通过指令读取测量距离；主动工作模式下，模块以100ms间隔上传测量距离。

指令均以\r\n结束

工作模式查询指令：
主机发送：AT+MODE=？
模块返回：AT+MODE=0或1

被动工作模式设定指令:
主机发送：AT+MODE=0
模块返回：OK

主动工作模式设定指令：
主机发送：AT+MODE=1
模块返回：OK

被动模式读取数据指令：
主机发送：AT+DIST=?
模块返回：Dist=距离cm