#include <iostream>

// Shapes - circle, square
// Renderer - raster, vector

// 2x2 Entity Explosion
// 1) RasterCircleRenderer,
// 2) RasterSquareRenderer,
// 3) VectorCircleRenderer
// 4) VectorSquareRenderer

// Our goal is to eliminate the need for multiple renderer class for different shapes

struct Renderer {
	virtual void render_circle(float x, float y, float radius) = 0;
};

struct RasterRenderer : public Renderer {
	void render_circle(float x, float y, float radius) override {
		std::cout << "Rasterizing a circle of radius " << radius << std::endl;
	};
};

struct VectorRenderer : public Renderer {
	void render_circle(float x, float y, float radius) override {
		std::cout << "Drawing a vector circle of radius " << radius << std::endl;
	};
};

struct Shape {
protected:
	// Instead of creating different renderers for each shape, e.g.
	
	// 1) RasterCircleRenderer,
	// 2) RasterSquareRenderer,
	// 3) VectorCircleRenderer
	// 4) VectorSquareRenderer

	// we're instead passing the renderer in as a constructor argument
	// and whenever we come to actually drawing a particuar shape we use that
	// bridge to draw it in the suitable format.
	Renderer& renderer;
	Shape(Renderer& renderer) : renderer(renderer) {};
public:
	virtual void draw() = 0;
	virtual void resize(float factor) = 0;
};

struct Circle : Shape {
	float x;
	float y;
	float radius;

	Circle(Renderer& renderer, float x, float y, float radius)
		: Shape(renderer), x(x), y(y), radius(radius) {};

	void draw() override {
		renderer.render_circle(x, y, radius);
	}

	void resize(float factor) override {
		radius *= factor;
	}

};

int main() {
	RasterRenderer rr;
	Circle raster_circle{ rr, 5, 5, 5 };
	raster_circle.draw();
	raster_circle.resize(2);
	raster_circle.draw();

	return 0;
}