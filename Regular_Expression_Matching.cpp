#include<string>
#include<deque>	
#include<memory>
#include<assert.h>
using namespace std;

//base class of patterns
class Pattern
{
public:
	Pattern() {}
	~Pattern();
	virtual pair<string::iterator, bool> isMatch(string::iterator i, string::iterator end) = 0;
	virtual bool isMatch(char c) = 0;
	virtual bool isProduce(char c) = 0; //当前模式是否生成
protected:
	//string m_pattern_str;

private:

};



Pattern::~Pattern()
{
}

class Char_Pattern : public Pattern
{
public:
	Char_Pattern (string c);
	~Char_Pattern ();

	virtual bool isMatch(char c) {
		string s({ c });
		if (m_is_used == false) {
			m_is_used = true;
			return m_pattern_str == s;
		}
		return false;
			
	}

	virtual bool isProduce(char c) {
		return true;
	}

	virtual pair<string::iterator, bool> isMatch(string::iterator i, string::iterator end)
	{
		if (*m_pattern_str.begin() == *i)
			return make_pair(++i, true);
		else
			return make_pair(i, false);
	}

private:
	string m_pattern_str;
	bool   m_is_used;
};

Char_Pattern :: Char_Pattern(string s) : m_pattern_str(s), m_is_used(false)
{
}

Char_Pattern ::~Char_Pattern ()
{
}

class dot_pattern : public Pattern
{
public:
	dot_pattern(string s) :m_pattern_str(s), m_is_used(false) {}

	virtual bool isMatch(char c) {
		if (m_is_used == false) {
			m_is_used = true;
			return true;
		}
		return false;
	}

	virtual bool isProduce(char c) {
		return true;
	}

	virtual pair<string::iterator, bool> isMatch(string::iterator i, string::iterator end)

	{
		return make_pair(++i,true);
	}

private:
	string m_pattern_str;
	bool   m_is_used;
};

class mutil_pattern : public Pattern
{
public:
	mutil_pattern(string s):m_pattern_str(s), m_match_state(mutil_match_state::INIT), m_match_range(0,65535),m_match_count(0) {}
	enum mutil_match_state
	{
		INIT,
		ZERO_MATCH,
		MUTIL_MATCH
	};

	virtual bool isProduce(char c) {
		if (m_match_state == mutil_match_state::ZERO_MATCH)
		{//this pattern is instanced for zero occurance, so when next char comes it must be false.
			return false;
		}
		else
			return true;
	}

	virtual pair<string::iterator, bool> isMatch(string::iterator i, string::iterator end)
	{
		string::iterator temp_i = i;
		
		char c = *i;
		while(isMatch(c)) {
			m_match_count++;
			++i;
			if (i == end)
				return make_pair(i, true);
			else
				c = *i;
		}
		if (m_match_count >= m_match_range.first) {
			return make_pair(i,true);
		}
		else
			return make_pair(i,false);
	}
	bool can_merge(char c) {
		if (m_pattern_str == string({ c })) 
			return true;
		else
			return false;
	}

	virtual bool isMatch(char c) {
		//if (m_match_state == mutil_match_state::ZERO_MATCH)
		//{//this pattern is instanced for zero occurance, so when next char comes it must be false.
		//	return false;
		//}

		if (m_pattern_str == "."){
			m_match_state = mutil_match_state::MUTIL_MATCH;
			return true;
		}
		else {
			if (m_pattern_str == string({ c })) {
				m_match_state = mutil_match_state::MUTIL_MATCH;
				return true;
			}
			else { //not match
				if (m_match_state == mutil_match_state::INIT) {//zero match
					m_match_state = mutil_match_state::ZERO_MATCH;
					//return true;
					return false;
				}
				else if (m_match_state == mutil_match_state::MUTIL_MATCH)
					return false;
				else
					assert(0); //should not happen
			}
		}
	}

	void add_count() {
		m_match_range.first++;
		m_match_state = mutil_match_state::MUTIL_MATCH;
	}

private:
	mutil_match_state	m_match_state; //this pattern is 0 match or mutil match? true-- mutile match; false-- zero match
	string			m_pattern_str;
	pair<int, int>	m_match_range;
	int				m_match_count;
};


#include<string.h>

class Solution {
private:
	deque<shared_ptr<Pattern>> m_patterns;
	typedef shared_ptr<Pattern> Pattern_pointer;
	
	enum state_enum
	{
		BEGIN,
		CHAR,
		DOT,
		MUTIL
	};
	void create_pattern(string p) {
		const char* str = p.c_str();
		const char* a = str;
		state_enum state = state_enum::BEGIN;
		Pattern_pointer current_p;
		while (*a != '\0')
		{
			if (isalpha(*a) )
			{
				if (*(a + 1) != '*')
					current_p = make_shared<Char_Pattern>(string({ *a }));
				else {
					current_p = make_shared<mutil_pattern>(string({ *a }));
					++a;
					//try to merge and simplify pattern string
					shared_ptr<mutil_pattern> p_mutil = std::dynamic_pointer_cast<mutil_pattern>(current_p);
					while (*(a+1) != '\0' && p_mutil->can_merge(*(a+1))) {
						p_mutil->add_count();
						++a;
					}
				}
			}
			else if(*a == '.')
			{
				if (*(a + 1) != '*')
					current_p = make_shared<dot_pattern>(string({ *a }));
				else {
					current_p = make_shared<mutil_pattern>(string({ *a }));
					++a;
					//m_patterns.push_back(current_p); //.* is enough, can match any last string
					//break;
				}
			}
			++a;
			m_patterns.push_back(current_p);
		}
	}

public:
	bool isMatch(string s, string p) {
		Pattern_pointer last_pattern;
		Pattern_pointer current_pattern;
		create_pattern(p);
		string::iterator i = s.begin();
		while (!m_patterns.empty() && i != s.end() )
		{
			current_pattern = m_patterns.front();
			m_patterns.pop_front();
			pair<string::iterator, bool> result = current_pattern->isMatch(i, s.end());
			if (result.second == true) {
				i = result.first;
			}
			else
			{
				return false;
			}

		}
		if (m_patterns.empty() && i == s.end())
			return true;
		else
			return false;
		//for (auto c : s) {
		//	if (last_pattern && last_pattern->isMatch(c)) {
		//		continue;
		//	}
		//	else 
		//	{
		//		while (true)
		//		{//find a vaild pattern
		//			if (!m_patterns.empty()) {
		//				current_pattern = m_patterns.front();
		//				m_patterns.pop_front();
		//				if (current_pattern->isMatch(c)){
		//					if (current_pattern->isProduce(c)) {
		//						last_pattern = current_pattern;
		//						break;
		//					}
		//				}
		//				else
		//				{//failed to match, false
		//					return false;
		//				}
		//			}
		//			else
		//			{//not enough patterns , false
		//				return false;
		//			}
		//		}
		//	}
		//	
		//}
		//if (m_patterns.empty())
		//	return true; //pattern queue is empty, input string is empty
		//else
		//	return false;
	}
};

//void main()
//{
//	Solution s;
//	//bool result = s.isMatch("aab", "c*a*b");
//	bool result = s.isMatch("ab", ".*c");
//	//bool result = s.isMatch("mississippi", "mis*is*p*.");
//}