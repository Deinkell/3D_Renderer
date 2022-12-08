#pragma once

class DibSection;

class FrameWork
{
public:
	FrameWork() = default;
	~FrameWork() = default;

public:
	void Initialize();
	void Ontick();
	FORCEINLINE Color32 test()
	{
		static clock_t st;
		static clock_t ed;
		static bool check = true;
		static Color32 col(0, 255, 0, 0);	
		clock_t rst = st - ed;
		st = clock();

		if (rst > 1000)
		{
			check = !check;
			ed = st;
		}		
		
		if (check)
			return Color32(0, 0, 255, 0);
		else
			return Color32(255, 0, 0, 0);		
	}

private:
	time_t PrevTime = 0 , PostTime = 0;

private:
	DibSection Dib;
};
