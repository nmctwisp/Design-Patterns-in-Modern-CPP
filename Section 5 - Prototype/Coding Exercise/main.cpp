struct Point
{
    int x{ 0 }, y{ 0 };

    Point() {}

    Point(const int x, const int y) : x{ x }, y{ y } {}
};

struct Line
{
    Point* start;
    Point* end;

    Line(Point* const start, Point* const end)
        : start(start), end(end)
    {
    }

    ~Line()
    {
        delete start;
        delete end;
    }

    Line deep_copy() const
    {   
        auto start = new Point(*this->start);
        auto end = new Point(*this->end);
        return Line{ start ,  end };
    };
};

int main() {

    auto one = Point{ 1,2 };
    auto two = Point{ 3,4 };

    Line t{ &one, &two };

    auto test = t.deep_copy();

    return 0;
}