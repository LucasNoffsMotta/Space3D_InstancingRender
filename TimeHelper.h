#ifndef CLASS_H_TIME_HELPER
#define CLASS_H_TIME_HELPER


static class TimeHelper 
{
private:
	static float CurrentFrame;
	static float LastFrame;
public:
	static float dt;
	static float GetDeltaTime();
	static void Update();
	static void ShowFps();
};


#endif // !CLASS_H_TIME_HELPER
