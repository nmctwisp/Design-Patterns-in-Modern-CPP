#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace boost;


struct Journal {
	std::string title;
	std::vector<std::string> entries;

	Journal(const std::string& title)
		: title{ title } {}

	void add_entry(const std::string& entry) {
		static int count = 1;
		entries.push_back(lexical_cast<std::string>(count++) + ": " + entry);
	}

	void save(const std::string& filename) {
		// Initial instinct would say the Journal object should have the responsibility
		// to save the journal data. This choice may be correct; however, for more complex
		// projects with more objects requiring data persistence such an implementation would 
		// mean that each object's save method would need to be maintained separately. Which 
		// would be error prone if you ever need to generally change the behavior for all
		// save methods across objects

		std::ofstream ofs(filename);
		for (auto& e : entries)
			ofs << e << std::endl;
	}	
};

// Separation of Concerns: Essentially we're saying that the Journal should strictly
// take care of Journal's title and journal entries, but if you want to persist data you
// may want to consider to separate out this feature into a separate component/class.

struct PersistenceManager {
	static void save(const Journal& j, const std::string& filename) {
		std::ofstream ofs(filename);
		for (auto& e : j.entries)
			ofs << e << std::endl;
	}
};

int main() {

	Journal journal{ "Dear Diary" };
	journal.add_entry("I ate a bug");
	journal.add_entry("I cried today");

	//journal.save("diary.txt");
	PersistenceManager pm;
	pm.save(journal, "diary.txt");

	getchar();
	return 0;

}