#include <iostream>

struct Image {

	virtual void draw() = 0;
};

struct Bitmap : Image {
	Bitmap(const std::string& filename) {
		std::cout << "Loading bitmap from " << filename << std::endl;
	}

	void draw() override {
		std::cout << "Drawing bitmap" << std::endl;
	}
};

struct LazyBitmap : Image {
private:
	std::string filename;
	Bitmap* bmp{ nullptr };
public:
	LazyBitmap(const std::string& filename) : filename(filename) {};

	void draw() override {
		if (!bmp)
			bmp = new Bitmap(filename);
		bmp->draw();
	}
};

int main() {
	Bitmap bmp{ "pokemon.png" };
	bmp.draw();

	return 0;
};