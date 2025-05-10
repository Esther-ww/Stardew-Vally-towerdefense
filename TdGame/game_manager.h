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
	int run(int argc, char** argv) //�����в���
		//����ڣ����������в�����������һ����������������Ƿ����гɹ�
	{
		Uint64 last_counter = SDL_GetPerformanceCounter();//�߾��ȼ�ʱ��
		const Uint64 counter_freq = SDL_GetPerformanceFrequency();

		while (!is_quit) {
			while (SDL_PollEvent(&event))//������ȡ�¼�
			{
				on_input();

				Uint64 current_counter = SDL_GetPerformanceCounter();
				double delta = (double)(current_counter - last_counter / counter_freq);
				last_counter = current_counter;
				if (delta * 1000 < 1000.0 / 60 - delta * 1000);

				//��������
				on_update(delta);


				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);//����
				//���ƻ���
				on_render();

				SDL_RenderPresent(renderer);



			}
		}
		return 0;
	}

protected:
	GameManager() {
		init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL��ʼ��ʧ��!");//��ʼ������;
		init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_image ��ʼ��ʧ�ܣ�");
		init_assert(Mix_Init(MIX_INIT_MP3), u8"SDL_mixer ��ʼ��ʧ�ܣ�");
		init_assert(!TTF_Init(), u8"SDL_ttf ��ʼ��ʧ�ܣ�");
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

		SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");//Ĭ�Ϲرգ�Ӣ�����룩�����뷨�ĺ�ѡ�ʽ���򿪣���Ҫ�����û�����ɶƴ������ʾ��������ѡ�ʣ���
		window = SDL_CreateWindow(u8"��������ս", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
		init_assert(window, u8"������Ϸ����ʧ��");
		init_assert(renderer, u8"������Ⱦ��ʧ��");

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);//Ӳ�����١���ֱͬ��(��ֹ����˺�ѣ���������Ⱦ��������

	};
	~GameManager() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();//�������˳�����ͷ�
	
	};

private:
	SDL_Event event;
	bool is_quit = false;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
private:
	void init_assert(bool flag, const char* err_msg) {
		if (flag) return;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"��Ϸ����ʧ��", err_msg, window);
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
