#include "pch.h"

#include"node.h"
#include <utility>

using std::vector;
using std::priority_queue;
using std::greater;
using std::less;
using std::sort;
using std::round;
using std::unordered_map;
using std::unordered_set;
using std::pair;
using std::make_pair;
using std::make_heap;
using std::pop_heap;
using std::push_heap;
using std::string;
using std::min;
using std::max;

TEST(priority_queue, max_or_min_heap)
{
	//create an pq and initialize

	vector<int> arr{ 7, 4, 3, 5, 6, 1, 2 };
	//default max heap
	priority_queue<int> pq(arr.begin(), arr.end());
	EXPECT_EQ(pq.top(), 7);
	//assign to max heap
	priority_queue<int, vector<int>, less<>> max_pq(arr.begin(), arr.end());
	EXPECT_EQ(max_pq.top(), 7);
	//assign to min heap
	priority_queue<int, vector<int>, greater<>> min_pq(arr.begin(), arr.end());
	EXPECT_EQ(min_pq.top(), 1);
}

TEST(priority_queue, pq_with_pair)
{
	/// see https://stackoverflow.com/questions/11103652/c-vector-of-pairs-initialization
	vector<int> init{ 7, 4, 3, 5, 6, 1, 2 };
	vector<pair<int, int>>  arr;
	for (int i : init) {
		arr.emplace_back(i, 7 - i);
	}

	const priority_queue<pair<int, int>> pq_pair(arr.begin(), arr.end());

	EXPECT_EQ(7, pq_pair.top().first);
	EXPECT_EQ(7, pq_pair.top().first + pq_pair.top().second);

	const priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq_pair_min(arr.begin(), arr.end());
	EXPECT_EQ(1, pq_pair_min.top().first);
}

/// https://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator
/// 自定义比较方法 为按照pair<>.second建造大顶堆
template <typename T, typename U>
class myPairComparator {
public:
	bool operator()(pair<T, U>& a, pair<T, U>& b) {
		return a.second < b.second;
	}
};

TEST(priority_queue, pq_with_customer_comparetor)
{
	vector<int> init{ 7, 4, 3, 5, 6, 1, 2 };
	vector<pair<int, int>>  arr;
	for (int i : init) {
		arr.emplace_back(i, 7 - i);
	}
	priority_queue<pair<int, int>, vector<pair<int, int>>, myPairComparator<int, int>> my_pq(arr.begin(), arr.end());
	EXPECT_EQ(6, my_pq.top().second);
	my_pq.pop();
	EXPECT_EQ(5, my_pq.top().second);

}

/// pq solution by template method.
/// see https://zh.cppreference.com/w/cpp/algorithm/make_heap
TEST(priority_queue, using_array_with_method)
{
	vector<int> arr{ 7, 4, 3, 5, 6, 1, 2 };

	//max heap
	make_heap(arr.begin(), arr.end());
	EXPECT_EQ(7, arr[0]);
	// also max heap
	vector<int> arr_{ 1, 2, 3, 4, 5, 6 };
	make_heap(arr_.begin(), arr_.end(), less<>());
	EXPECT_EQ(6, arr_[0]);


	//min heap   
	make_heap(arr_.begin(), arr_.end(), greater<>());
	EXPECT_EQ(1, arr_[0]);
	//min heap with lambda
	make_heap(arr.begin(), arr.end(), [](int a, int b) { return a > b; });
	EXPECT_EQ(1, arr[0]);
}


TEST(SortStruct, lambda)
{
	//node in node.h
	//use lambda in C++ to define rule for sort template.
	vector<node> arr;

	arr.emplace_back(3, 1);
	arr.emplace_back(3, 2);
	arr.emplace_back(7, 3);
	sort(arr.begin(), arr.end(), [](const node& a, const node& b) { return a.c > b.c; });
	EXPECT_EQ(7, arr[0].a);
	sort(arr.begin(), arr.end(), [](const node& a, const node& b) { return a.c < b.c; });
	EXPECT_EQ(2, arr[0].b);
}

//create dynamic array.
TEST(vectorCtor, complex_vector)
{
	vector<int> arr(10, 2); //size = 10 , all elements initialized to 2.
	EXPECT_EQ(2, arr[9]);
	EXPECT_EQ(10, arr.size());
	//Two-dimensional array , initialed to -1.
	vector<vector<int>> res(10, vector<int>(8, -1));
	EXPECT_EQ(10, res.size());
	EXPECT_EQ(8, res[0].size());
	EXPECT_EQ(-1, res[0][0]);
}


//round float numbers.
//relative function : floor ceil
TEST(math, round)
{
	//C++11 std::round 
	// see https://en.cppreference.com/w/cpp/numeric/math/round
	// see https://stackoverflow.com/questions/485525/round-for-float-in-c

	//naive implement only for positive numbers. -4.4 -> -3
	//double round(double d)
	//{
	//	return floor(d + 0.5);
	//}
	EXPECT_EQ(5, round(5.444));
	EXPECT_EQ(5, round(4.5));
	EXPECT_EQ(4, round(4.444));
	EXPECT_EQ(-5, round(-5.444));
	EXPECT_EQ(-5, round(-4.5));

	//for negative float numbers ,just abandon decimal part.
	EXPECT_EQ(-4, static_cast<int>(-4.6));
	EXPECT_EQ(-4, static_cast<int>(-4.3));

	//floor 
	EXPECT_EQ(-2, floor(-1.1));
	//ceil 
	EXPECT_EQ(-2, ceil(-2.1));
}

// getline(cin,s); // s->string
//string split
// https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/

//reverse hash table.
//see https://stackoverflow.com/questions/8483985/obtaining-list-of-keys-and-values-from-unordered-map
TEST(unordered_map, traverse)
{
	unordered_map<int, int> map;
	map[1] = -1;
	map[2] = -2;
	for (pair<int, int> i : map)
	{
		EXPECT_EQ(i.first, -i.second);
	}
}

/// multi_map
/// see https://docs.microsoft.com/en-us/cpp/standard-library/unordered-multimap-class?view=vs-2019#equal_range
TEST(unordeded_map, mlutimap)
{
	std::unordered_multimap<int, char> map;
	map.insert(std::unordered_multimap<int, char>::value_type(1, 'a'));
	map.insert(std::unordered_multimap<int, char>::value_type(1, 'b'));
	map.insert(std::unordered_multimap<int, char>::value_type(2, 'a'));
	map.insert(std::unordered_multimap<int, char>::value_type(3, 'c'));

	auto it = map.equal_range(1); // pair of iterator first->begin , second->end
	EXPECT_EQ(it.first->first, 1);
	EXPECT_EQ(it.first->second, 'a');
	++it.first;
	EXPECT_EQ(it.first->first, 1);
	EXPECT_EQ(it.first->second, 'b');
	++it.first;
	EXPECT_EQ(it.first, it.second);

	it = map.equal_range(3); //another example.
	EXPECT_EQ(it.first->first, 3);
	EXPECT_EQ(it.first->second, 'c');
	++it.first;
	EXPECT_EQ(it.first, it.second);
}

//Set
// see https://stackoverflow.com/questions/12850927/adding-elements-of-a-vector-to-an-unordered-set
TEST(unordered_set, vector2set)
{
	//build an set from vector.
	std::vector<int> v{ 1, 1, 2, 3 };
	std::unordered_set<int> s(v.begin(), v.end());
	EXPECT_EQ(s.size(), 3);

	//copy_function
	std::vector<int> v_{ 1, 1, 2, 2, 3, 3, 3 };
	std::unordered_set<int> s_;
	std::copy(v_.begin(), v_.end(), std::inserter(s_, s_.end()));
	EXPECT_EQ(s_.size(), 3);
}

//transform set to vector.
// see https://stackoverflow.com/questions/42519867/efficiently-moving-contents-of-stdunordered-set-to-stdvector
TEST(vector, set2vector)
{
	unordered_set<int> set;
	for (size_t i = 0; i < 3; i++)
	{
		set.insert(i);
	}
	const vector<int> res(set.begin(), set.end());
	EXPECT_EQ(3, res.size());
	vector<int> res_;
	res_.insert(res_.end(), set.begin(), set.end());
	EXPECT_EQ(3, res_.size());
}

//transform map to vector<pair<>>
TEST(vector, map2vector)
{
	unordered_map<int, int> map;
	map[1] = 2;
	map[2] = 3;
	map[3] = 5;

	vector<pair<int, int>>  v(map.begin(), map.end());

	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v[0].first, 1);
	EXPECT_EQ(v[0].second, 2);
}


/// get the sum of the vector collection.
/// see https://stackoverflow.com/questions/3221812/how-to-sum-up-elements-of-a-c-vector
TEST(vector, sum)
{
	int sum_of_elems = 0;
	vector<int> arr{ 1,2,3,4,5,6,7,8,9,10 };
	// C++ 11 and higher
	std::for_each(arr.begin(), arr.end(), [&](int n) {
		sum_of_elems += n;
		});
	EXPECT_EQ(55, sum_of_elems);

	sum_of_elems = 0;
	for (auto& n : arr)
		sum_of_elems += n;
	EXPECT_EQ(55, sum_of_elems);
}

// sort vector
TEST(vector, sort)
{
	vector<vector<int>> v{ {5, 9, 4, 12, 4},
								  {7, 9, 3, 4, 7, 9},
								  {6, 5, 11},
								  {5, 8, 7, 3},
								  {5, 9, 5, 1, 1} };

	//降序
	std::sort(v.begin(), v.end(), std::greater<>());
	EXPECT_EQ(7, v[0][0]);

	//升序
	std::sort(v.begin(), v.end());
	EXPECT_EQ(5, v[0][0]);
	EXPECT_EQ(8, v[0][1]);
	EXPECT_EQ(5, v[1][0]);

	//另一种降序排序的方式
	//std::sort(v.begin(), v.end(), std::greater<>());
	//EXPECT_EQ(7, v[0][0]);
}

/// see https://stackoverflow.com/questions/9424173/find-the-smallest-amongst-3-numbers-in-c
TEST(vector, min)
{
	EXPECT_EQ(1, min({ 1,2,3 }));
	EXPECT_EQ(3, max({ 1,2,3 }));
}


// append vector
// https://stackoverflow.com/questions/2551775/appending-a-vector-to-a-vector
TEST(vector, append)
{
	vector<int> a = { 1,2,3 };
	vector<int> b = { 4,5,6 };
	vector<int> c = { 1,2,3,4,5,6 };

	a.insert(end(a), begin(b), end(b));
	EXPECT_EQ(a, c);


	a = { 1,2,3 };
	b = { 4,5,6 };
	std::copy(b.begin(), b.end(), std::back_inserter(a));
	EXPECT_EQ(a, c);

}

/// string 
/// see https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
TEST(string, lowercase)
{
	string s = "AbCdEfG";
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	EXPECT_EQ(s, "abcdefg");
}

// see https://en.wikipedia.org/wiki/XOR_swap_algorithm
// see https://stackoverflow.com/questions/1533131/what-useful-bitwise-operator-code-tricks-should-a-developer-know-about
TEST(bitwise, swap_and_so_on)
{
	int a = 1, b = 2;
	//swap by mathematics
	a = a + b;
	b = a - b;
	a = a - b;
	EXPECT_EQ(a, 2);
	EXPECT_EQ(b, 1);

	//swap by bitwise
	int x = 1, y = 2;
	x = x ^ y;
	y = x ^ y;
	x = x ^ y;
	EXPECT_EQ(x, 2);
	EXPECT_EQ(y, 1);

	// is_even ?
	EXPECT_EQ(x & 1, 0);
	EXPECT_EQ(y & 1, 1);
}

TEST(Type, Int2Bool) {

	/// !!10 == 1 !!0 == 0
	/// !!i(i > 0) => 1 
	/// !!0 => 0
	int a = 10;
	int b = 0;
	EXPECT_FALSE(!a);
	EXPECT_FALSE(b);
	EXPECT_EQ(1, !!a);
	EXPECT_EQ(0, !!b);
	EXPECT_EQ(true, !!a);
	EXPECT_EQ(false, !!b);

	/// 当然 !!-1 == 1 也成立
	a = -a;
	EXPECT_EQ(1, !!a);
	EXPECT_EQ(true, !!a);
}
