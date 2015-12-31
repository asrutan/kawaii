// camFocus.h
// Alex Rutan
// 12/1/15

#ifndef CAMFOCUS_EXIST
#define CAMFOCUS_EXIST

class camFocus
{
    private:
        int xTarget = 0;
	int yTarget = 0;
	int xVelocity = 0;
	int yVelocity = 0;

    public:
        camFocus();
	~camFocus();
        int x;
	int y;
	//bool init();
	//	bool loadTextures();
};

#endif

