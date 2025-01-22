//1.
set<string> s;
set(string>::iterator it;
pair <set<string>::iterator, bool> ret;

int main() {

	s.insert("There");
	s.insert("World");
	s.insert("World");

	ret = s.insert("Hello");					
	cout << "insert successful? " << ret.second << endl;	// "Hello"
	cout << *(ret.first) << endl;

	ret = s.insert("Hello");					// already in set
	cout << "insert successful? " << ret.second << endl;
	cout << *(ret.first) << endl;					// "Hello"

	std::cout << "Set contains: ";
	for (it = s.begin(); it != s.end(); it++) 		// "set contains: Hello There World "	// ordered by ascii value (alphabet)
		cout << *it << " ";
	cout << endl;
}

// 2.
int count(const int * arr, int size) {
	set<int> s;
	for (const int &x : arr)
		s.insert(x);
	return s.size();	// returns 5
}


// 3.
// Make a map and return the highest number of occurences
#include <map>
map<int, int> m;
int mode(const int *arr, int size) {
	int ret = 0;
	for (int k : arr) {
		if (m.get(k))
			k[]++;
		else
			m.insert(k);
	}
	for (int k : m) {
		if (k.size() > k++.size()) 
			ret++;
	}
	return ret;
}
