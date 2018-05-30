#include "FB_headfile.h"
#include <thread>
#include<time.h>
// SRCAND  SRCPAINT
//初始化游戏数据

//void threadplaywing(bool birdfly)
//{
//	while (true)
//	{
//		if (birdfly)
//			mciSendString("play music\\FlappyBird_sfx_wing.mp3", NULL, 0, NULL);
//		Sleep(100);
//	}
//	
//}


void initdata(Data &data)
{
	FILE *fp;
	errno_t err;
	data.landdata = 0;
	int i = 0;
	data.banddata[0][0] = 200;
	data.banddata[1][0] = 400;
	data.banddata[2][0] = 600;
	data.banddata[3][0] = 800;
	data.banddata[4][0] = 1000;

	for (int i = 0; i < 5; i++)
	{
		data.banddata[i][1] =-125;
		data.banddata[i][2] = 300;
	}
	data.nowscore = 0;

	data.speed = 3;
	data.scoreblock = -1;
	//文件操作，获取oldscore
	err=fopen_s(&fp, "score.txt", "r");
	if (!err)
	{
		while (!feof(fp))
		{
			fscanf_s(fp,"%d", &data.oldscore[i++]);
		}
	}
	else
	{
		err = fopen_s(&fp, "score.txt", "w");
		for (; i < 3; i++)
		{
			fprintf(fp, "%d ", 0);
			data.oldscore[i] = 0;
		}
	}
	fclose(fp);
	data.bird.birdhigh = 255;
	data.bird.birdpicture = 0;
	data.bird.number = 0;
	data.bird.flow = 0.2;
	data.bird.up = 0.1;
	data.life = true;
	
}

//bird控制
void birdct(Data &data)
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (data.bird.birdhigh <= 0)
			;
		else
		{
			//mciSendString("play music_wing from 0", NULL, 0, NULL);
			//mciSendString("play music\\FlappyBird_sfx_wing.mp3", NULL, 0, NULL);
			data.bird.birdhigh -= data.bird.up;
			data.bird.up += 1;//上升加速度
			data.bird.flow = 0.1;//下降加速度
			data.bird.number++;
			if (data.bird.number % 5 == 0)//翅膀是接近1秒刷新一个动作
			{
				data.bird.birdpicture++;
				if (data.bird.birdpicture >= 3)
					data.bird.birdpicture = 0;
			}
		}

	}
	else
	{
		if (data.bird.birdhigh >= 360)
			;
		else
		{
			data.bird.birdhigh += data.bird.flow;
			data.bird.flow += 0.3;

			//if (data.bird.flow >= 4)
			//	data.bird.birdpicture = 3;
			//if (data.bird.flow >= 5)
			//	data.bird.birdpicture = 4;
			//if (data.bird.flow >= 6)
			//	data.bird.birdpicture = 5;
			data.bird.birdpicture = 1;
			data.bird.up = 0.1;
		}
	}
}

//数据循环
void databack(Data &data)
{
	//障碍物回环
	for (int i = 0; i < 5; i++)
	{
		if (data.banddata[i][0] <= -50)
		{
			changeband(data, data.banddata[i][0]);
			data.banddata[i][0] = 900;
		}
			
		else
			data.banddata[i][0] -= data.speed;
	}
	data.landdata -= data.speed;
	if (data.landdata <= -50)
		data.landdata = 0;
}

//游戏开始菜单
void gamestartmenu(Picture picture,Data data)
{
	/*thread task(threadplaywing);*/
	int  number = 0, key = 0, a = 0, b = 0, c = 0,  i = 0, score[3],scorekey=0;
	int oldscore[3];
	float n = 0;
	MOUSEMSG msg;
		while (true)
		{
			
			BeginBatchDraw();
			putimage(0, 0, &picture.backgroundpt);
			putimage(50, 100, &picture.gametitle[0], SRCAND);
			putimage(50, 100, &picture.gametitle[1], SRCPAINT);

			putimage(115, 180, &picture.birdpt[number][0], SRCAND);
			putimage(115, 180, &picture.birdpt[number][1],SRCPAINT);

			putimage(20, 340, &picture.button[0][0], SRCAND);
			putimage(20, 340, &picture.button[0][1], SRCPAINT);

			putimage(150, 340, &picture.button[1][0], SRCAND);
			putimage(150, 340, &picture.button[1][1], SRCPAINT);

			//按钮按下绘制分数
			if (scorekey == 1)
			{

				oldscore[0] = data.oldscore[0];
				oldscore[1] = data.oldscore[1];
				oldscore[2] = data.oldscore[2];
				//画第一名
				//data.oldscore[0] = 999;
				if (oldscore[0] == 0)
					putimage(203, 337, &picture.sm_num[0]);
				else
				{
					while (oldscore[0] != 0)
					{
						score[i++] = oldscore[0] % 10;
						oldscore[0] = oldscore[0] / 10;
					}
					//位数
					switch (i)
					{
					case 1:
						putimage(203, 337, &picture.sm_num[score[0]]);
						break;
					case 2:
						putimage(197, 337, &picture.sm_num[score[1]]);
						putimage(212, 337, &picture.sm_num[score[0]]);
						break;
					case 3:
						putimage(190, 335, &picture.sm_num[score[2]]);
						putimage(203, 335, &picture.sm_num[score[1]]);
						putimage(216, 335, &picture.sm_num[score[0]]);
						break;
					}
				}
				i = 0;//复位
					  //画第二名
				//data.oldscore[1] = 999;
				if (oldscore[1] == 0)
					putimage(230, 352, &picture.sm_num[0]);
				else
				{
					while (oldscore[1] != 0)
					{
						score[i++] = oldscore[1] % 10;
						oldscore[1] = oldscore[1] / 10;
					}
					//位数
					switch (i)
					{
					case 1:
						putimage(230, 352, &picture.sm_num[score[0]]);
						break;
					case 2:
						putimage(230, 352, &picture.sm_num[score[1]]);
						putimage(243, 352, &picture.sm_num[score[0]]);
						break;
					case 3:
						putimage(230, 352, &picture.sm_num[score[2]]);
						putimage(243, 352, &picture.sm_num[score[1]]);
						putimage(256, 352, &picture.sm_num[score[0]]);
						break;
					}
				}
				i = 0;//复位
					  //画第三名
				//data.oldscore[2] = 888;
				if (oldscore[2] == 0)
					putimage(185, 356, &picture.sm_num[0]);
				else
				{
					while (oldscore[2] != 0)
					{
						score[i++] =oldscore[2] % 10;
						oldscore[2] =oldscore[2] / 10;
					}
					//位数
					switch (i)
					{
					case 1:
						putimage(185, 356, &picture.sm_num[score[0]]);
						break;
					case 2:
						putimage(172, 356, &picture.sm_num[score[1]]);
						putimage(185, 356, &picture.sm_num[score[0]]);
						break;
					case 3:
						putimage(159, 356, &picture.sm_num[score[2]]);
						putimage(172, 356, &picture.sm_num[score[1]]);
						putimage(185, 356, &picture.sm_num[score[0]]);
						break;
					}
				}
				i = 0;//复位
			}

			putimage(n, 400, &picture.landpt);

			putimage(70, 425, &picture.copyright[0], SRCAND);
			putimage(70, 425, &picture.copyright[1], SRCPAINT);

			FlushBatchDraw();
			EndBatchDraw();

			//减慢bird的图片切换
			key++;
			if (key % 200 == 0)
				number >= 2 ? number = 0 : number++;
			n -= 0.05;
			if (n <= -50)
				n = 0;
			//按键选择
			if (MouseHit())
			{
				msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN)
					if (msg.x >= 20 && msg.x <= 136 && msg.y >= 340 && msg.y <= 410)
					{
						BeginBatchDraw();
						putimage(0, 0, &picture.backgroundpt);
						putimage(50, 100, &picture.gametitle[0], SRCAND);
						putimage(50, 100, &picture.gametitle[1], SRCPAINT);

						putimage(115, 180, &picture.birdpt[number][0], SRCAND);
						putimage(115, 180, &picture.birdpt[number][1], SRCPAINT);

						putimage(20, 345, &picture.button[0][0], SRCAND);
						putimage(20, 345, &picture.button[0][1], SRCPAINT);

						putimage(150, 340, &picture.button[1][0], SRCAND);
						putimage(150, 340, &picture.button[1][1], SRCPAINT);

						putimage(n, 400, &picture.landpt);

						putimage(70, 425, &picture.copyright[0], SRCAND);
						putimage(70, 425, &picture.copyright[1], SRCPAINT);

						FlushBatchDraw();
						
						Sleep(50);
						putimage(0, 0, &picture.backgroundpt);

						putimage(50, 100, &picture.gametitle[0], SRCAND);
						putimage(50, 100, &picture.gametitle[1], SRCPAINT);

						putimage(115, 180, &picture.birdpt[number][0], SRCAND);
						putimage(115, 180, &picture.birdpt[number][1], SRCPAINT);

						putimage(20, 340, &picture.button[0][0], SRCAND);
						putimage(20, 340, &picture.button[0][1], SRCPAINT);

						putimage(150, 340, &picture.button[1][0], SRCAND);
						putimage(150, 340, &picture.button[1][1], SRCPAINT);

						putimage(n, 400, &picture.landpt);

						putimage(70, 425, &picture.copyright[0], SRCAND);
						putimage(70, 425, &picture.copyright[1], SRCPAINT);

						FlushBatchDraw();
						EndBatchDraw();
						/*task.join();*/
						mciSendString("play music\\FlappyBird_sfx_wing.mp3", NULL, 0, NULL);
						//Sleep(100);
						break;
					}
					else if (msg.x >= 150 && msg.x <= 266 && msg.y >= 340 && msg.y <= 410)
					{
						if (scorekey == 0)
							scorekey = 1;
						else
							scorekey = 0;

 						BeginBatchDraw();
						putimage(0, 0, &picture.backgroundpt);
						putimage(50, 100, &picture.gametitle[0], SRCAND);
						putimage(50, 100, &picture.gametitle[1], SRCPAINT);

						putimage(115, 180, &picture.birdpt[number][0], SRCAND);
						putimage(115, 180, &picture.birdpt[number][1], SRCPAINT);

						putimage(20, 340, &picture.button[0][0], SRCAND);
						putimage(20, 340, &picture.button[0][1], SRCPAINT);

						putimage(150, 345, &picture.button[1][0], SRCAND);
						putimage(150, 345, &picture.button[1][1], SRCPAINT);

						putimage(n, 400, &picture.landpt);

						putimage(70, 425, &picture.copyright[0], SRCAND);
						putimage(70, 425, &picture.copyright[1], SRCPAINT);

						FlushBatchDraw();
						Sleep(50);
						putimage(0, 0, &picture.backgroundpt);

						putimage(50, 100, &picture.gametitle[0], SRCAND);
						putimage(50, 100, &picture.gametitle[1], SRCPAINT);

						putimage(115, 180, &picture.birdpt[number][0], SRCAND);
						putimage(115, 180, &picture.birdpt[number][1], SRCPAINT);

						putimage(20, 340, &picture.button[0][0], SRCAND);
						putimage(20, 340, &picture.button[0][1], SRCPAINT);

						putimage(150, 340, &picture.button[1][0], SRCAND);
						putimage(150, 340, &picture.button[1][1], SRCPAINT);

						putimage(n, 400, &picture.landpt);

						putimage(70, 425, &picture.copyright[0], SRCAND);
						putimage(70, 425, &picture.copyright[1], SRCPAINT);

						FlushBatchDraw();
						mciSendString("play music\\FlappyBird_sfx_wing.mp3", NULL, 0, NULL);
						EndBatchDraw();
					}
			}
		}
}

//提示用户如何玩游戏
void getread(Picture picture,Data data)
{
	int n = 0, number = 0, key = 0;
	while (true)
	{
		BeginBatchDraw();
		putimage(0, 0, &picture.backgroundpt);

		putimage(50, 100, &picture.getready[0],SRCAND);
		putimage(50, 100, &picture.getready[1],SRCPAINT);
		
		putimage(60, 180, &picture.birdpt[number][0], SRCAND);
		putimage(60, 180, &picture.birdpt[number][1], SRCPAINT);

		putimage(130, 40, &picture.big_num[data.nowscore][0], SRCAND);
		putimage(130, 40, &picture.big_num[data.nowscore][1], SRCPAINT);

		putimage(90, 180, &picture.button[2][0], SRCAND);
		putimage(90, 180, &picture.button[2][1], SRCPAINT);
		putimage(n, 400, &picture.landpt);
		FlushBatchDraw();
		EndBatchDraw();
		n -= 3;
		if (n <= -50)
			n = 0;
		key++;
		if (key % 7 == 0)
			number >= 2 ? number = 0 : number++;
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			break;
		Sleep(16);
	}
}

//游戏图片加载和旋转
void picturedeal(Picture &picture,int n)
{
	if (n == 1)
	{
		//处理游戏中Bird图片
		loadimage(&picture.birdpt[0][0], "image\\bird2_0_.jpg", 0, 0, false);
		loadimage(&picture.birdpt[0][1], "image\\bird2_0.jpg", 0, 0, false);

		loadimage(&picture.birdpt[1][0], "image\\bird2_1_.jpg", 0, 0, false);
		loadimage(&picture.birdpt[1][1], "image\\bird2_1.jpg", 0, 0, false);

		loadimage(&picture.birdpt[2][0], "image\\bird2_2_.jpg", 0, 0, false);
		loadimage(&picture.birdpt[2][1], "image\\bird2_2.jpg", 0, 0, false);

		//处理障碍物图片
		for (int i = 0; i < 5; i++)
		{
			loadimage(&picture.bandpt[i][0], "image\\pipe_down.jpg", 0, 0, false);
			loadimage(&picture.bandpt[i][1], "image\\pipe_up.jpg", 0, 0, false);
		}

		//处理background图片
		loadimage(&picture.backgroundpt, "image\\bg_day.jpg", 0, false);

		//处理landpt图片
		loadimage(&picture.landpt, "image\\land.jpg", 0, 0, false);

		//处理大号的数字
		loadimage(&picture.big_num[0][0], "image\\big_num0_.jpg", 0, 0, false);
		loadimage(&picture.big_num[0][1], "image\\big_num0.jpg", 0, 0, false);

		loadimage(&picture.big_num[1][0], "image\\big_num1_.jpg", 0, 0, false);
		loadimage(&picture.big_num[1][1], "image\\big_num1.jpg", 0, 0, false);

		loadimage(&picture.big_num[2][0], "image\\big_num2_.jpg", 0, 0, false);
		loadimage(&picture.big_num[2][1], "image\\big_num2.jpg", 0, 0, false);

		loadimage(&picture.big_num[3][0], "image\\big_num3_.jpg", 0, 0, false);
		loadimage(&picture.big_num[3][1], "image\\big_num3.jpg", 0, 0, false);

		loadimage(&picture.big_num[4][0], "image\\big_num4_.jpg", 0, 0, false);
		loadimage(&picture.big_num[4][1], "image\\big_num4.jpg", 0, 0, false);

		loadimage(&picture.big_num[5][0], "image\\big_num5_.jpg", 0, 0, false);
		loadimage(&picture.big_num[5][1], "image\\big_num5.jpg", 0, 0, false);

		loadimage(&picture.big_num[6][0], "image\\big_num6_.jpg", 0, 0, false);
		loadimage(&picture.big_num[6][1], "image\\big_num6.jpg", 0, 0, false);

		loadimage(&picture.big_num[7][0], "image\\big_num7_.jpg", 0, 0, false);
		loadimage(&picture.big_num[7][1], "image\\big_num7.jpg", 0, 0, false);

		loadimage(&picture.big_num[8][0], "image\\big_num8_.jpg", 0, 0, false);
		loadimage(&picture.big_num[8][1], "image\\big_num8.jpg", 0, 0, false);

		loadimage(&picture.big_num[9][0], "image\\big_num9_.jpg", 0, 0, false);
		loadimage(&picture.big_num[9][1], "image\\big_num9.jpg", 0, 0, false);
		
		//处理中号数字
		loadimage(&picture.mid_num[0][0], "image\\mid_num0_.jpg", 0, 0, false);
		loadimage(&picture.mid_num[0][1], "image\\mid_num0.jpg", 0, 0, false);

		loadimage(&picture.mid_num[1][0], "image\\mid_num1_.jpg", 0, 0, false);
		loadimage(&picture.mid_num[1][1], "image\\mid_num1.jpg", 0, 0, false);

		loadimage(&picture.mid_num[2][0], "image\\mid_num2_.jpg", 0, 0, false);
		loadimage(&picture.mid_num[2][1], "image\\mid_num2.jpg", 0, 0, false);

		loadimage(&picture.mid_num[3][0], "image\\mid_num3_.jpg", 0, 0, false);
		loadimage(&picture.mid_num[3][1], "image\\mid_num3.jpg", 0, 0, false);

		loadimage(&picture.mid_num[4][0], "image\\mid_num4_.jpg", 0, 0, false);
		loadimage(&picture.mid_num[4][1], "image\\mid_num4.jpg", 0, 0, false);

		loadimage(&picture.mid_num[5][0], "image\\mid_num5_.jpg", 0, 0, false);
		loadimage(&picture.mid_num[5][1], "image\\mid_num5.jpg", 0, 0, false);

		loadimage(&picture.mid_num[6][0], "image\\mid_num6_.jpg", 0, 0, false);
		loadimage(&picture.mid_num[6][1], "image\\mid_num6.jpg", 0, 0, false);

		loadimage(&picture.mid_num[7][0], "image\\mid_num7_.jpg", 0, 0, false);
		loadimage(&picture.mid_num[7][1], "image\\mid_num7.jpg", 0, 0, false);

		loadimage(&picture.mid_num[8][0], "image\\mid_num8_.jpg", 0, 0, false);
		loadimage(&picture.mid_num[8][1], "image\\mid_num8.jpg", 0, 0, false);

		loadimage(&picture.mid_num[9][0], "image\\mid_num9_.jpg", 0, 0, false);
		loadimage(&picture.mid_num[9][1], "image\\mid_num9.jpg", 0, 0, false);

		//处理小号数字
		loadimage(&picture.sm_num[0], "image\\number_context_00.jpg", 0, 0, false);
		loadimage(&picture.sm_num[1], "image\\number_context_01.jpg", 0, 0, false);
		loadimage(&picture.sm_num[2], "image\\number_context_02.jpg", 0, 0, false);
		loadimage(&picture.sm_num[3], "image\\number_context_03.jpg", 0, 0, false);
		loadimage(&picture.sm_num[4], "image\\number_context_04.jpg", 0, 0, false);
		loadimage(&picture.sm_num[5], "image\\number_context_05.jpg", 0, 0, false);
		loadimage(&picture.sm_num[6], "image\\number_context_06.jpg", 0, 0, false);
		loadimage(&picture.sm_num[7], "image\\number_context_07.jpg", 0, 0, false);
		loadimage(&picture.sm_num[8], "image\\number_context_08.jpg", 0, 0, false);
		loadimage(&picture.sm_num[9], "image\\number_context_09.jpg", 0, 0, false);

		//处理gametitle图片游戏标题
		loadimage(&picture.gametitle[0], "image\\title_.jpg", 0, 0, false);
		loadimage(&picture.gametitle[1], "image\\title.jpg", 0, 0, false);

		//处理getread图片
		loadimage(&picture.getready[0], "image\\text_ready_.jpg", 0, 0, false);
		loadimage(&picture.getready[1], "image\\text_ready.jpg", 0, 0, false);

		//处理所有按钮
		loadimage(&picture.button[0][0], "image\\button_play_.jpg", 0, 0, false);
		loadimage(&picture.button[0][1], "image\\button_play.jpg", 0, 0, false);

		loadimage(&picture.button[1][0], "image\\button_score_.jpg", 0, 0, false);
		loadimage(&picture.button[1][1], "image\\button_score.jpg", 0, 0, false);

		loadimage(&picture.button[2][0], "image\\tutorial_.jpg", 0, 0, false);
		loadimage(&picture.button[2][1], "image\\tutorial.jpg", 0, 0, false);

		loadimage(&picture.button[3][0], "image\\score_panel_.jpg", 0, 0, false);
		loadimage(&picture.button[3][1], "image\\score_panel.jpg", 0, 0, false);

		//处理copyright图片
		loadimage(&picture.copyright[0], "image\\brand_copyright_.jpg", 0, 0, false);
		loadimage(&picture.copyright[1], "image\\brand_copyright.jpg", 0, 0, false);

		//处理奖牌图片
		loadimage(&picture.medals[0][0], "image\\medals_0_.jpg", 0, 0, false);
		loadimage(&picture.medals[0][1], "image\\medals_0.jpg", 0, 0, false);

		loadimage(&picture.medals[1][0], "image\\medals_1_.jpg", 0, 0, false);
		loadimage(&picture.medals[1][1], "image\\medals_1.jpg", 0, 0, false);

		loadimage(&picture.medals[2][0], "image\\medals_2_.jpg", 0, 0, false);
		loadimage(&picture.medals[2][1], "image\\medals_2.jpg", 0, 0, false);

		loadimage(&picture.medals[3][0], "image\\medals_3_.jpg", 0, 0, false);
		loadimage(&picture.medals[3][1], "image\\medals_3.jpg", 0, 0, false);

		//处理gameover图片
		loadimage(&picture.gameover[0], "image\\text_game_over_.jpg", 0, 0, false);
		loadimage(&picture.gameover[1], "image\\text_game_over.jpg", 0, 0, false);

		//处理最新最高分
		loadimage(&picture.newscore,"image\\new.jpg", 0, 0, false);
	
	}
	else if (n == 2)
	{

		//旋转Bird图片
		//rotateimage(&picture.birdpt[0][0], &picture.birdpt[0][0], 0);//PI / 6
		//rotateimage(&picture.birdpt[0][1], &picture.birdpt[0][1], 0);
		//
		//rotateimage(&picture.birdpt[1][0], &picture.birdpt[1][0], 0);//PI / 6
		//rotateimage(&picture.birdpt[1][1], &picture.birdpt[1][1], 0);

		//rotateimage(&picture.birdpt[2][0], &picture.birdpt[2][0], 0);//PI / 6
		//rotateimage(&picture.birdpt[2][1], &picture.birdpt[2][0],0);
		//
		//rotateimage(&picture.birdpt[3][0], &picture.birdpt[3][0], 0);
		//rotateimage(&picture.birdpt[3][1], &picture.birdpt[3][1], 0);

		//rotateimage(&picture.birdpt[4][0], &picture.birdpt[4][0],0);// -PI / 3
		//rotateimage(&picture.birdpt[4][1], &picture.birdpt[4][1],0);

		//rotateimage(&picture.birdpt[5][0], &picture.birdpt[5][0],0);//-PI * 0.7
		//rotateimage(&picture.birdpt[5][1], &picture.birdpt[5][1],0);

 	//	loadimage(&picture.birdpt[3][0],"image\\bird2_0.jpg",0,0,false);
		//loadimage(&picture.birdpt[3][1], "image\\bird2_0_.jpg", 0, 0, false);

		//loadimage(&picture.birdpt[4][0], "image\\bird2_1.jpg", 0, 0, false);
		//loadimage(&picture.birdpt[4][1], "image\\bird2_1_.jpg", 0, 0, false);

		//loadimage(&picture.birdpt[5][0], "image\\bird2_2.jpg", 0, 0, false);
		//loadimage(&picture.birdpt[5][1], "image\\bird2_2_.jpg", 0, 0, false);
	}
	
}

//绘制游戏内容
void drowpicture(Picture picture, Data data)
{
	int score[3],i=0;//分数处理相关数据
	BeginBatchDraw();
	putimage(0, 0, &picture.backgroundpt);

	//障碍物绘制
	for (int i = 0; i < 5; i++)
	{
		putimage(data.banddata[i][0], data.banddata[i][1], &picture.bandpt[i][0]);
		putimage(data.banddata[i][0], data.banddata[i][2],&picture.bandpt[i][1]);
	}

	//分数绘制
	{
		if (data.nowscore > 999)
		{
			putimage(100, 70, &picture.big_num[9][0], SRCAND);
			putimage(100, 70, &picture.big_num[9][1], SRCPAINT);

			putimage(75, 70, &picture.big_num[9][0], SRCAND);
			putimage(75, 70, &picture.big_num[9][1], SRCPAINT);

			putimage(51, 70, &picture.big_num[9][0], SRCAND);
			putimage(51, 70, &picture.big_num[9][1], SRCPAINT);
		}
		else
		{
			if (data.nowscore == 0)
			{
				putimage(100, 70, &picture.big_num[0][0], SRCAND);
				putimage(100, 70, &picture.big_num[0][1], SRCPAINT);
			}
			else
			{
				while (data.nowscore != 0)
				{
					score[i++] = data.nowscore % 10;
					data.nowscore = data.nowscore / 10;
				}
				switch (i)
				{
				case 1:
					putimage(100, 70, &picture.big_num[score[0]][0], SRCAND);
					putimage(100, 70, &picture.big_num[score[0]][1], SRCPAINT);
					break;
				case 2:
					putimage(75, 70, &picture.big_num[score[1]][0], SRCAND);
					putimage(75, 70, &picture.big_num[score[1]][1], SRCPAINT);

					putimage(100, 70, &picture.big_num[score[0]][0], SRCAND);
					putimage(100, 70, &picture.big_num[score[0]][1], SRCPAINT);
					break;
				case 3:
					putimage(51, 70, &picture.big_num[score[2]][0], SRCAND);
					putimage(51, 70, &picture.big_num[score[2]][1], SRCPAINT);

					putimage(75, 70, &picture.big_num[score[1]][0], SRCAND);
					putimage(75, 70, &picture.big_num[score[1]][1], SRCPAINT);

					putimage(100, 70, &picture.big_num[score[0]][0], SRCAND);
					putimage(100, 70, &picture.big_num[score[0]][1], SRCPAINT);
					break;
				}
			}
		}
	}
	
	putimage(data.landdata, 400, &picture.landpt);
	putimage(50, data.bird.birdhigh, &picture.birdpt[data.bird.birdpicture][0],SRCAND);
	putimage(50, data.bird.birdhigh, &picture.birdpt[data.bird.birdpicture][1],SRCPAINT);
	FlushBatchDraw();
	EndBatchDraw();
}

//得分或碰撞
void collision(Data &data)
{
bool first = false, second = false, third = false;
	
if (data.bird.birdhigh >= 360)
data.life = false;
else
{
int i = 0;
for (; i < 5; i++)
{
//bird图片参数 x+23,y+23 r=13
//障碍物参数y+320
if (data.banddata[i][0] < 110 && data.banddata[i][0]>-20)//障碍物进入判断范围
{
//圆心X,Y
int rx = 25 + 23;
int ry = data.bird.birdhigh + 23;

//上方障碍物底部X，Y
int bux = data.banddata[i][0];
int buy = data.banddata[i][1] + 320;//障碍物下方边界

									//下方障碍物顶部X,Y
int bdx = data.banddata[i][0];
int bdy = data.banddata[i][2];


float du = 0, dd = 0;

	if (ry >  buy && ry < data.banddata[i][2])//bird在障碍物中间：//计算点到点距离
		if (rx < bux || rx>(bux + 53))//bird的圆心没进入夹缝中
		{
			if (rx > bux && data.scoreblock != i)//得分，
			{
				data.scoreblock = i;
				data.nowscore++;
			}
			du = sqrt(pow((rx - bux), 2) + pow((ry - buy), 2));
			dd = sqrt(pow((rx - bdx), 2) + pow((ry - bdy), 2));
			if ((du - 13) <= 0 || (dd - 13) <= 0)
				data.life = false;
		}
		else//bird 进入夹缝中
		{
			du = sqrt(pow(ry - buy, 2));
			dd = sqrt(pow(ry - bdy, 2));
			if ((du - 13) <= 0 || (dd - 13) <= 0)
				data.life = false;
		}
	else
	{
		if ((rx + 13) >= data.banddata[i][0])
			data.life = false;
	}
	break;
	}
	}
	}
	}

//得分面板
void scorepanl(Picture picture, Data &data)
   {
	FILE *fp;
	errno_t err;
	int score[3],i=0, nowscore=data.nowscore,oldscore=data.oldscore[0], scorekey = 0;
	int madelscore = data.oldscore[0];
	bool isnewrecored=false,datachange=true;
	int madel = -1;

	MOUSEMSG msg;

	while (true)
	{
		BeginBatchDraw();
		putimage(0, 0, &picture.backgroundpt);

		putimage(40, 100, &picture.gameover[0], SRCAND);
		putimage(40, 100, &picture.gameover[1], SRCPAINT);
		   
		//得分面板
		putimage(25, 180, &picture.button[3][0], SRCAND);
		putimage(25, 180, &picture.button[3][1], SRCPAINT);

		//绘制分数，排名
		{
			//nowscore绘制分数
			if (data.nowscore > 999)
			{
				putimage(194, 215, &picture.mid_num[9][0], SRCAND);
				putimage(194, 215, &picture.mid_num[9][1], SRCPAINT);

				putimage(207, 215, &picture.mid_num[9][0], SRCAND);
				putimage(207, 215, &picture.mid_num[9][1], SRCPAINT);

				putimage(220, 215, &picture.mid_num[9][0], SRCAND);
				putimage(220, 215, &picture.mid_num[9][1], SRCPAINT);
			}
			else
			{
				if (data.nowscore == 0)
				{
					putimage(220, 215, &picture.mid_num[0][0], SRCAND);
					putimage(220, 215, &picture.mid_num[0][1], SRCPAINT);
				}
				else
				{
					i = 0;//复位
					nowscore = data.nowscore;
					while (nowscore != 0)
					{
						score[i++] = nowscore % 10;
						nowscore = nowscore / 10;
					}
					switch (i)
					{
					case 1:
						putimage(220, 215, &picture.mid_num[score[0]][0], SRCAND);
						putimage(220, 215, &picture.mid_num[score[0]][1], SRCPAINT);
						break;
					case 2:
						putimage(207, 215, &picture.mid_num[score[1]][0], SRCAND);
						putimage(207, 215, &picture.mid_num[score[1]][1], SRCPAINT);

						putimage(220, 215, &picture.mid_num[score[0]][0], SRCAND);
						putimage(220, 215, &picture.mid_num[score[0]][1], SRCPAINT);
						break;
					case 3:
						putimage(194, 215, &picture.mid_num[score[2]][0], SRCAND);
						putimage(194, 215, &picture.mid_num[score[2]][1], SRCPAINT);

						putimage(207, 215, &picture.mid_num[score[1]][0], SRCAND);
						putimage(207, 215, &picture.mid_num[score[1]][1], SRCPAINT);

						putimage(220, 215, &picture.mid_num[score[0]][0], SRCAND);
						putimage(220, 215, &picture.mid_num[score[0]][1], SRCPAINT);
						break;
					}
				}
			}

			//加入排名：判断一次是否是新纪录
			/*for(int i=0;i<3;i++)
				data.oldscore[0] = 0;*/
			if (datachange)
			{
				if (data.nowscore > data.oldscore[0])
				{
					data.oldscore[2] = data.oldscore[1];
					data.oldscore[1] = data.oldscore[0];
					data.oldscore[0] = data.nowscore;
					isnewrecored = true;

				}
				else if (data.nowscore > data.oldscore[1])
				{
					data.oldscore[2] = data.oldscore[1];
					data.oldscore[1] = data.nowscore;
				}
				else if (data.nowscore > data.oldscore[2])
					data.oldscore[1] = data.nowscore;
				datachange = false;
			}

			//是新纪录，直接画出nowscore[3]，否则//绘制oldscore[0]
			if (isnewrecored)
			{
				switch (i)
				{
				case 1:
					putimage(220, 255, &picture.mid_num[score[0]][0], SRCAND);
					putimage(220, 255, &picture.mid_num[score[0]][1], SRCPAINT);
					break;
				case 2:
					putimage(207, 255, &picture.mid_num[score[1]][0], SRCAND);
					putimage(207, 255, &picture.mid_num[score[1]][1], SRCPAINT);

					putimage(220, 255, &picture.mid_num[score[0]][0], SRCAND);
					putimage(220, 255, &picture.mid_num[score[0]][1], SRCPAINT);
					break;
				case 3:
					putimage(194, 255, &picture.mid_num[score[2]][0], SRCAND);
					putimage(194, 255, &picture.mid_num[score[2]][1], SRCPAINT);

					putimage(207, 255, &picture.mid_num[score[1]][0], SRCAND);
					putimage(207, 255, &picture.mid_num[score[1]][1], SRCPAINT);

					putimage(220, 255, &picture.mid_num[score[0]][0], SRCAND);
					putimage(220, 255, &picture.mid_num[score[0]][1], SRCPAINT);
					break;
				}
				//putimage(160, 257, &picture.newscore);
			}
			else
			{
				oldscore = data.oldscore[0];
				i = 0;//复位
				if (oldscore == 0)
				{
					putimage(220, 220, &picture.sm_num[0], SRCAND); 
					putimage(220, 220, &picture.sm_num[0], SRCPAINT);
				}
				else
				{
					while (oldscore != 0)
					{
						score[i++] = oldscore % 10;
						oldscore = oldscore / 10;
					}
					//位数
					switch (i)
					{
					case 1:
						putimage(220, 255, &picture.mid_num[score[0]][0], SRCAND);
						putimage(220, 255, &picture.mid_num[score[0]][1], SRCPAINT);
						break;
					case 2:
						putimage(207, 255, &picture.mid_num[score[1]][0], SRCAND);
						putimage(207, 255, &picture.mid_num[score[1]][1], SRCPAINT);

						putimage(220, 255, &picture.mid_num[score[0]][0], SRCAND);
						putimage(220, 255, &picture.mid_num[score[0]][1], SRCPAINT);
						break;
					case 3:
						putimage(194, 255, &picture.mid_num[score[2]][0], SRCAND);
						putimage(194, 255, &picture.mid_num[score[2]][1], SRCPAINT);

						putimage(207, 255, &picture.mid_num[score[1]][0], SRCAND);
						putimage(207, 255, &picture.mid_num[score[1]][1], SRCPAINT);

						putimage(220, 255, &picture.mid_num[score[0]][0], SRCAND);
						putimage(220, 255, &picture.mid_num[score[0]][1], SRCPAINT);
						break;
					}
				}
			}


			//根据按钮显示排		
			if (scorekey == 1)
			{
				
			}
		}

		//奖牌选择
		if ((data.nowscore - madelscore) > 20)
			madel = 3;
		 else if((data.nowscore - madelscore) > 15)
			madel = 2;
		 else if ((data.nowscore - madelscore) > 10)
			 madel = 1;
		 else if ((data.nowscore - madelscore) > 5)
			 madel = 0;
		if (madel != -1)
		{
			putimage(56, 225, &picture.medals[madel][0], SRCAND);
			putimage(56, 225, &picture.medals[madel][1], SRCPAINT);
		}
			putimage(0, 400, &picture.landpt);

			putimage(80, 342, &picture.button[0][0], SRCAND);
			putimage(80, 342, &picture.button[0][1], SRCPAINT);

		FlushBatchDraw();
		EndBatchDraw();

		//按键选择
		if (MouseHit())
		{
			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
				if (msg.x >= 80 && msg.x <=190 && msg.y >= 347 && msg.y <= 517)
				{
					BeginBatchDraw();
 					putimage(0, 0, &picture.backgroundpt);

					putimage(40, 100, &picture.gameover[0], SRCAND);
					putimage(40, 100, &picture.gameover[1], SRCPAINT);

					//得分面板
					putimage(25, 180, &picture.button[3][0], SRCAND);
					putimage(25, 180, &picture.button[3][1], SRCPAINT);
					
					putimage(80, 347, &picture.button[0][0], SRCAND);
					putimage(80, 347, &picture.button[0][1], SRCPAINT);

					putimage(0, 400, &picture.landpt);

					if (madel != -1)
					{
						putimage(56, 225, &picture.medals[madel][0], SRCAND);
						putimage(56, 225, &picture.medals[madel][1], SRCPAINT);
					}
					FlushBatchDraw();
					Sleep(50);
					putimage(0, 0, &picture.backgroundpt);

					putimage(40, 100, &picture.gameover[0], SRCAND);
					putimage(40, 100, &picture.gameover[1], SRCPAINT);

					//得分面板
					putimage(25, 180, &picture.button[3][0], SRCAND);
					putimage(25, 180, &picture.button[3][1], SRCPAINT);

					putimage(80, 342, &picture.button[0][0], SRCAND);
					putimage(80, 342, &picture.button[0][1], SRCPAINT);

					if (madel != -1)
					{
						putimage(56, 225, &picture.medals[madel][0], SRCAND);
						putimage(56, 225, &picture.medals[madel][1], SRCPAINT);
					}

					putimage(0, 400, &picture.landpt);
					FlushBatchDraw();
					EndBatchDraw();

					//写入分数
					err = fopen_s(&fp, "score.txt", "w");
					i = 0;//复位
					for (; i < 3; i++)
					{
						fprintf(fp, "%d ", data.oldscore[i]);
					}
					fclose(fp);
					mciSendString("play music\\FlappyBird_sfx_wing.mp3", NULL, 0, NULL);
					break;
				}
		}			
	}
}

//改变障碍物的Y轴数据
void changeband(Data &data,int n)
{
	srand((unsigned int)time(NULL));
	int j = rand() % 5 + 1;;
	int key= rand() % 10+1;

	for(int i=0;i<5;i++)
 		if (n == data.banddata[i][0])
			if (key % 2 == 0)
			{
				key =  rand() % 10 + j * 10;
				data.banddata[i][1] = -125+key;
				data.banddata[i][2] = 300+key;
			}
			else
			{
				key = rand() % 10 + j * 10;
				data.banddata[i][1] = -125-key;
				data.banddata[i][2] = 300-key;
			}
}
