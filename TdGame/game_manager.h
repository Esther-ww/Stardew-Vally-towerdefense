#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include <SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>


#include "manager.h"

class GameManager:public Manager<GameManager>{
	friend class Manager<GameManager>;
public:
	int run(int argc, char** argv) //命令行参数
		//主入口，接收命令行参数，并返回一个整数，代表程序是否运行成功
	{
		Uint64 last_counter = SDL_GetPerformanceCounter();//高精度计时器
		const Uint64 counter_freq = SDL_GetPerformanceFrequency();

		while (!is_quit) {
			while (SDL_PollEvent(&event))//不断拉取事件
			{
				on_input();

				Uint64 current_counter = SDL_GetPerformanceCounter();
				double delta = (double)(current_counter - last_counter / counter_freq);
				last_counter = current_counter;
				if (delta * 1000 < 1000.0 / 60 - delta * 1000);

				//更新数据
				on_update(delta);


				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);//清屏
				//绘制画面
				on_render();

				SDL_RenderPresent(renderer);



			}
		}
		return 0;
	}

protected:
	GameManager() {
		init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL初始化失败!");//初始化断言;
		init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_image 初始化失败！");
		init_assert(Mix_Init(MIX_INIT_MP3), u8"SDL_mixer 初始化失败！");
		init_assert(!TTF_Init(), u8"SDL_ttf 初始化失败！");
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

		SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");//默认关闭（英文输入）把输入法的候选词界面打开，我要看到用户打了啥拼音，显示出来给他选词！”
		window = SDL_CreateWindow(u8"鹈鹕镇保卫战", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
		init_assert(window, u8"创建游戏窗口失败");
		init_assert(renderer, u8"创建渲染器失败");

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);//硬件加速、垂直同步(防止画面撕裂），还能渲染到纹理上

	};
	~GameManager() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();//按申请的顺序倒序释放
	
	};

private:
	SDL_Event event;
	bool is_quit = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
private:
	void init_assert(bool flag, const char* err_msg) {
		if (flag) return;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"游戏启动失败", err_msg, window);
		exit(-1);
	}

	void on_input() {

	}
	void on_update(double delta){

	}
	void on_render() {

	}


};





#endif
