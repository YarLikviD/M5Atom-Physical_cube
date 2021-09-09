float speedLimit = 5; // set the speed limit
float x_limit = 20, y_limit = 20;

struct Pixel
{
    bool is_alive;

    float size;

    float x;
    float y;

    float x_speed;
    float y_speed;

    float elasticity;
    int color;
};

//You can set multiple pixels
Pixel pixels[1] = {
    {true, 10, (float)random(40), (float)random(40), 0, 0, 0.90, 0xFF0000},
};