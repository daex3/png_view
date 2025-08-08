#include <raylib.h>
#include <reader_png.c>
#include <pixels_px.c>

int main(int argc, char **argv) {
	if (argc < 2) {
		puts("\x1b[36mUsage:\x1b[m png_view file.png");

		exit(-1);
	}

	Pixels e = read_png(argv[1]);

	InitWindow(0, 0, argv[1]);

	D2 size = { GetScreenWidth(), GetScreenHeight() };

	resize_pixels(&e, &size),

	SetTargetFPS(1);

	Image raylib_image = GenImageColor(e.size.x, e.size.y, BLUE);

	for(size_t i = 0; i < e.len; ++i) {
		Px	*p	= &e.x[i];
		Color	 o	= { p->color.r, p->color.g, p->color.b, 255 };

		ImageDrawPixel(&raylib_image, p->pos.x, p->pos.y, o);
	}

	Texture2D texture = LoadTextureFromImage(raylib_image);

	UnloadImage(raylib_image);

	while (!WindowShouldClose())
		BeginDrawing(),
		ClearBackground(WHITE),

		DrawRectangle(0, 0, texture.width, texture.height, RED),
		DrawTexture(texture, 0, 0, WHITE),

		EndDrawing();

	UnloadTexture(texture),
	CloseWindow();
	free(e.x);
}
