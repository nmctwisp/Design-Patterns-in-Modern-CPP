#include <string>
#include <sstream>

int main() {

	// <p>hello</p>
	auto text = "hello";
	std::string output;
	output += "<p>";
	output += text;
	output += "</p>";
	printf("<p>%s</p>", text);

	// <ul><li>hello</li><li>world</li></ul>
	std::string words[] = { "hello", "world" };
	std::ostringstream oss;
	oss << "<ul>";
	for (auto w : words)
		oss << "<li>" << w << "</li>";
	oss << "</ul>";
	printf(oss.str().c_str());
		
}