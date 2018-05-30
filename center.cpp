#include "FB_headfile.h"
#pragma comment(lib, "winmm.lib")

bool play()
{
	Picture picture;//定义游戏中用到图片
	Data data;//定义游戏中的数据
	initdata(data);//初始化数据
	picturedeal(picture,1);//处理游戏图片
	//游戏开始界面实现
	gamestartmenu(picture,data);
	getread(picture,data);//提示用户如何玩


 	//picturedeal(picture, 2);//旋转Bird图片
	//thread task(threadplaywing,birdfly);
	//task.join();
	//游戏开始
	while (true)
	{
		birdct(data);//bird控制
		drowpicture(picture,data);//开始游戏画图
		collision(data);//在这里判断死亡加分情况
 		if (!data.life)
			break;
		databack(data);//数据回环
		Sleep(16);
	}
	//得分面板
	scorepanl(picture, data);
	return 0;
}