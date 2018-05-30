#pragma once
#ifndef _FB_HEADFILE_H
#define _FB_HEADFILE_H
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include <time.h>
#include "windows.h"
#include <iostream>
#include <thread>
#include <graphics.h>     
#define PI 3.1415926535
//bird数据
struct Bird
{
	int birdhigh;
	int birdpicture;
	int number;
	float flow;
	float up;
	
};
//游戏中的图片
typedef struct Picture
{
	IMAGE birdpt[3][2];//bird图片
	IMAGE bandpt[5][2];//障碍物图片
	IMAGE backgroundpt;//背景图片
	IMAGE landpt;//下方可以移动土地
	IMAGE big_num[10][2];//大号的数字
	IMAGE mid_num[10][2];//中号数字
	IMAGE sm_num[10];//小号数字
	IMAGE gametitle[2];//游戏的标题
	IMAGE getready[2];//准备阶段标题
	/*所有的按钮和得分面板 
		0:button_play; 1:button_score; 
		2:tutorial.jpg; 3；score_panel*/
	IMAGE button[4][2];
	IMAGE copyright[2];//开始界面的版权文字
	IMAGE medals[4][2];//奖牌
	IMAGE gameover[2];//游戏结束
	IMAGE newscore;//最新的高分
};
//游戏数据
typedef struct Data
{
	int landdata;//下方移动土地
	//障碍物 0是障碍物的x坐标，1是上障碍物的y坐标 2是下方障碍物y坐标
	int banddata[5][3];
	int nowscore;//本次得分
	int speed;//移动速度
	int oldscore[3];//0第一，1第二，2第三
	int scoreblock;//分数锁
	bool life;//bird是否存活
	Bird bird;//bird数据
};
void initdata(Data &data);//初始化游戏数据
void birdct(Data &data);// bird控制
bool play();//开始游戏
void databack(Data &data);//数据处理
void gamestartmenu(Picture picture, Data data);//绘制开始界面
void getread(Picture picture,Data data);//绘制getready界面
void picturedeal(Picture &picture,int n);//游戏图片处理（加载与旋转） n=1 是加载图片
void drowpicture(Picture picture, Data data);//绘制游戏内容
void collision(Data &data);//碰撞
void scorepanl(Picture picture,Data &data);//得分面板
void changeband(Data &data, int n);//改变障碍物的Y轴数据
using namespace std;
#endif

// _FB_HEADFILE_H