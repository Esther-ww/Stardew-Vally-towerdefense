#define SDL_MAIN_HANDLED
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL2_gfxPrimitives.h>
#include<cJSON.h>

void test_json() {
	std::ifstream file("test.json");
	if (!file.good()) {
		std::cout << "无法打开文件"<<std::endl;
		
		return;
	}
	std::stringstream str_stream;
	str_stream << file.rdbuf();
	file.close();

	cJSON* json_root = cJSON_Parse(str_stream.str().c_str());
	
	cJSON* json_name = cJSON_GetObjectItem(json_root, "name");
	cJSON* json_age = cJSON_GetObjectItem(json_root, "age");
	std::cout << json_name->string << json_name->valuestring << std::endl;
	cJSON* json_item = nullptr;
	
}
void test_csv() {
	std::ifstream file("test.csv");
	if (!file.good()) {
		std::cout << "无法打开文件" << std::endl;

		return;
	}
	std::string str_line;
	while (std::getline(file, str_line)) {
		std::string str_grid;
		std::stringstream str_stream(str_line);
		while (std::getline(str_stream, str_grid, ',')) {

		}
	}
}


int main() {
	void test_json();
	//初始化
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	//创建程序窗口
	SDL_Window* window = SDL_CreateWindow(u8"你好", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

	//渲染
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);

	SDL_Surface* suf_img = IMG_Load("cock.jpg");
	//上传纹理数据
	SDL_Texture* tex_img=SDL_CreateTextureFromSurface(renderer, suf_img);

	//加载字体对象
	TTF_Font* font = TTF_OpenFont("ipix.ttf", 32);
	//渲染字体
	SDL_Color color = { 255,0,0,255 };
	SDL_Surface* suf_text = TTF_RenderUTF8_Blended(font, u8"你好，公鸡", color);
	//字体纹理
	SDL_Texture* tex_text = SDL_CreateTextureFromSurface(renderer, suf_text);

	//加载音乐
	Mix_Music* music = Mix_LoadMUS("music.mp3");
	//淡入(-1永久循环）
	Mix_FadeInMusic(music, -1, 1500);


	int fps = 60;
	//标志位
	bool is_quit = false;
	//让窗口可以移动
	SDL_Event event;
	//图片跟随鼠标
	SDL_Point pos_cursor = { 0,0 };

	SDL_Rect rect_img,rect_text;
	Uint64 last_counter = SDL_GetPerformanceCounter();
	Uint64 counter_freq = SDL_GetPerformanceFrequency();
	rect_img.w = suf_img->w;
	rect_img.h = suf_img->h;

	rect_text.w = suf_text->w;
	rect_text.h = suf_text->h;
	while (!is_quit) {
		while (SDL_PollEvent(&event)) {
			//可以关闭窗口
			if (event.type == SDL_QUIT) {
				is_quit = true;
			}
			//图片跟随鼠标
			else if (event.type == SDL_MOUSEMOTION)
			{
				pos_cursor.x = event.motion.x;
				pos_cursor.y = event.motion.y;  

			}

		}
		//动态延时帧率控制
		Uint64 current_counter = SDL_GetPerformanceCounter();
		double delta = (double)(current_counter - last_counter)/counter_freq;
		last_counter - current_counter;
		if (delta * 1000 < 1000.0 / 60)//1000ms,与期望帧数作比较
		{
			SDL_Delay((Uint32)(1000.0 / 60 - delta * 1000));//延迟，剩下的时间delay,降低cpu占用
		}
		//处理数据
		rect_img.x = pos_cursor.x;
		rect_img.y = pos_cursor.y;

		rect_text.x = pos_cursor.x;
		rect_text.y = pos_cursor.y;
		//背景颜色
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		//清屏
		SDL_RenderClear(renderer);
		//渲染绘图
		SDL_RenderCopy(renderer, tex_img, nullptr, &rect_img);
		   //画一个圆
		filledCircleRGBA(renderer, pos_cursor.x, pos_cursor.y,50,255,0,0,125);
		SDL_RenderCopy(renderer, tex_text, nullptr, &rect_text);

		SDL_RenderPresent(renderer);
	}
	return 0;
	
}