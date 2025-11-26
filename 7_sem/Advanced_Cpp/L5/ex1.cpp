#include <forward_list>
#include <iostream>
#include <string>
#include <cctype>
#include <span>

using namespace std;

auto tokenize(const string& txt)
{
    forward_list<span<const char>> tokens;
    size_t start = 0;
    size_t end = 0;
    while(end < txt.size())
    {
        while(end < txt.size() && isspace(txt[end]))
            ++end;
        start = end;
        while(end < txt.size() && !isspace(txt[end]))
            ++end;
        if(start < end)
        {
            tokens.emplace_front(&txt.data()[start], end - start);
        }
    }
    return tokens;
}

int main()
{
    string text = "This is a sample text for tokenization.";
    auto tokens = tokenize(text);
    
    for(const auto& token : tokens)
    {
        cout << string(token.data(), token.size()) << endl;
    }
    
    return 0;
}