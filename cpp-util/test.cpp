#include "pch.h"

#include"node.h"

using std::vector;
using std::priority_queue;
using std::greater;
using std::less;
using std::sort;
using std::round;
using std::unordered_map;
using std::unordered_set;
using std::pair;
using std::make_heap;
using std::pop_heap;
using std::push_heap;
using std::string;

TEST(priority_queue, max_or_min_heap)
{
    //create an pq and initialize

    vector<int> arr{7, 4, 3, 5, 6, 1, 2};
    //default max heap
    priority_queue<int> pq(arr.begin(), arr.end());
    EXPECT_EQ(pq.top(), 7);
    //assign to max heap
    priority_queue<int, vector<int>, less<int>> max_pq(arr.begin(), arr.end());
    EXPECT_EQ(max_pq.top(), 7);
    //assign to min heap
    priority_queue<int, vector<int>, greater<int>> min_pq(arr.begin(), arr.end());
    EXPECT_EQ(min_pq.top(), 1);
}

/// pq solution by template method.
/// see https://zh.cppreference.com/w/cpp/algorithm/make_heap
TEST(priority_queue, using_array_with_method)
{
    vector<int> arr{7, 4, 3, 5, 6, 1, 2};

    //max heap
    make_heap(arr.begin(), arr.end());
    EXPECT_EQ(7, arr[0]);
    // also max heap
    vector<int> arr_{1, 2, 3, 4, 5, 6};
    make_heap(arr_.begin(), arr_.end(), less<int>());
    EXPECT_EQ(6, arr_[0]);


    //min heap   
    make_heap(arr_.begin(), arr_.end(), greater<int>());
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

    arr.push_back(node(3, 1));
    arr.push_back(node(3, 2));
    arr.push_back(node(7, 3));
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

//reverse hashtable.
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
    std::vector<int> v{1, 1, 2, 3};
    std::unordered_set<int> s(v.begin(), v.end());
    EXPECT_EQ(s.size(), 3);

    //copy_function
    std::vector<int> v_{1, 1, 2, 2, 3, 3, 3};
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

/// string 
/// see https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
TEST(string, lowercase)
{
    string s = "AbCdEfG";
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    EXPECT_EQ(s, "abcdefg");
}

/// see https://en.wikipedia.org/wiki/XOR_swap_algorithm
/// see https://stackoverflow.com/questions/1533131/what-useful-bitwise-operator-code-tricks-should-a-developer-know-about
TEST(bitwise, swap_and_so_on)
{
    int a = 1, b = 2;
    //swap 
    a = a + b;
    b = a - b;
    a = a - b;
    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 1);

    int x = 1, y = 2;
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
    EXPECT_EQ(x, 2);
    EXPECT_EQ(y, 1);

    EXPECT_EQ(x & 1, 0);
    EXPECT_EQ(y & 1, 1);
}
