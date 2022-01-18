#include <iostream>
#include <string>
#include <cctype>

//===============================================================================
//===============================================================================

/*********************************HELPER FUNCTIONS******************************/

// Takes one argument: a string that will be iterated through charcter by 
// character and converted to lower case if posiible in a new string.
// Returns converted string.
std::string LowerCase(std::string& string_to_convert)
{
    int index = 0;
    std::string Lower_case_string = "";

    for (char c : string_to_convert)
    {
        Lower_case_string.push_back(tolower(c));
        index++;
    }
    return Lower_case_string;
}

//===============================================================================
//===============================================================================

// Takes five arguments: two strings that will be compared, the length of 
// one of the string with the pattern to search for, a position to start 
// the snippet of the first string, and a a counter to find the number 
// of characters that match in the two strings. This function Updates 
// the counter, no return.
void CharFinder(std::string& text_string, std::string& pattern_string,
                int& pattern_string_length, int& i, int& match_counter)
{
    std::string snippet = text_string.substr(i, pattern_string_length);

    for (int j = 0; j < pattern_string_length; j++)
    {   
        if ((pattern_string[j] == '#' && isdigit(snippet[j])))
        {
            match_counter++;
        }
        else if ((pattern_string[j] == '%' && isprint(snippet[j])) 
        || (pattern_string[j] == '%' && isspace(snippet[j])))
        {
            match_counter++;
        }
        else if (pattern_string[j] == snippet[j])
        {
            match_counter++;
        } 
    }
}

//===============================================================================
//===============================================================================

// Takes five arguments: two strings that will be compared, a position to start 
// the snippet of the first string, the length of one of the string with the
// pattern to search for, and a boolean value to determine whether the search 
// term was found. This functions updates the boolean value, no return.
void LengthCheck (std::string& text_string, std::string& pattern_string, 
                  int& i, int& pattern_string_length, bool& match_Found)
{
    int match_counter = 0;
    CharFinder(text_string, pattern_string,
        pattern_string_length, i, match_counter);
    if (match_counter == pattern_string_length)
        {
            match_Found = true;
        }
}

//===============================================================================
//===============================================================================

// Takes two arguments: two strings to strings to be compared and determine
// if a set of charaters is common between them. Returns true if common set is 
// found and false otherwise. 
bool Found(std::string& text_string, std::string& pattern_string)
{
    int text_string_length = text_string.length();
    int pattern_string_length = pattern_string.length();
    int i = 0;
    bool match_found = false;

    if (text_string_length == pattern_string_length)
    {
        LengthCheck(text_string, pattern_string, i, 
        pattern_string_length, match_found);
    }
    else
    {
        for (int i = 0; i < text_string_length - pattern_string_length; i++)
        {
            LengthCheck(text_string, pattern_string, i, 
            pattern_string_length, match_found);
        }
    }
    return match_found;
}

//===============================================================================
//===============================================================================

// Takes two arguments: two strings to strings to be compared and determine
// if a set of charaters is common between them. Returns index of first 
// occurrence of set in first string if a match is found and -1 otherwsie.
int FoundIndex(std::string& text_string, std::string& pattern_string)
{
    
    int index = 0;
    int pattern_string_length = pattern_string.length();
    int text_string_length = text_string.length();
    std::string snippet = text_string.substr(index, pattern_string_length);

    while (index <= (text_string_length - pattern_string_length))
    {
        if (Found(snippet, pattern_string))
        {
            return index;
        }
        else
        {
            index++;
            snippet = text_string.substr(index, pattern_string_length);
        }
    }
    return -1;
}

//===============================================================================
//===============================================================================

// Takes two arguments: two strings to strings to be compared and determine
// if a set of charaters is common between them. Returns the number of times
// the set of characters from the first second string occurres in the first
// string.
int FoundCount(std::string& text_string, std::string& pattern_string)
{
    int index = 0;
    int counter = 0;
    int pattern_string_length = pattern_string.length();
    int text_string_length = text_string.length();
    std::string snippet = text_string.substr(index, pattern_string_length);

    do
    { 
        if (Found(snippet, pattern_string))
        {
            counter++;
        }
        index++;
        snippet = text_string.substr(index, pattern_string_length);
    }
    while ((index + pattern_string_length) <= text_string_length);
    return counter;
}

//===============================================================================
//===============================================================================

// Takes 4 argumenst: two strings to be compared to determin the position to 
// replace content in the first string with content in the third string and an
// index with the position. No return.
void StringReplacer (int& index, std::string& text_string,
                    std::string& pattern_string, std::string& new_content)
{
    if (index != -1)
    {
        int pattern_string_length =  pattern_string.length();
        text_string.replace(index, pattern_string_length, new_content);
    }
}

//===============================================================================
//===============================================================================

// Takes four arguments: three strings to be processed with the use of helper 
// functions and a const pointer to a bool to determine if the pattern search
// should be case insensitive or not. No return.
void StringReplace(std::string& text_string, std::string& pattern_string,
                   std::string& new_content, const bool* case_insensitive)
{
    int index;
    if (*case_insensitive)
    {
        std::string lowercase_pattern = LowerCase(pattern_string);
        std::string lowercase_text = LowerCase(text_string);

        index = FoundIndex(lowercase_text, lowercase_pattern);
        
    }
    else
    {
        index = FoundIndex(text_string, pattern_string);
    }
    StringReplacer(index, text_string, pattern_string, new_content);
}

//===============================================================================
//===============================================================================

// Takes two arguments: two strings to be compared. Returns the difference 
// between the number of characters of both strings.
int CharDifference(std::string& first_string, std::string& second_string)
{
    std::string common = "";

    for (char c1 : first_string)
    {
        for (char c2 : second_string)
        {
            if (c1 == c2)
            {
                common.push_back(c1);
                
            }
        }
    }

    int common_length = common.length(), str1_length = first_string.length();
    int difference_count =  str1_length - common_length;
    return difference_count;
}

//===============================================================================
//===============================================================================

/*******************************MAIN FUNCTIONS**********************************/

// Takes three arguments: a string representing the text to search, 
// a string representing the pattern to search for, and a pointer to bool that 
// represents if the search should be case insensitive. Returns true if the 
// pattern is found in the text, false otherwise.
bool ImprovedContains(std::string text_string, std::string pattern_string, 
                      const bool* case_insensitive)
{
    if (*case_insensitive)
    {
        pattern_string = LowerCase(pattern_string);
        text_string = LowerCase(text_string);
    }
    return Found(text_string, pattern_string); 
}

//===============================================================================
//===============================================================================

// Takes three arguments: a string representing the text to search, a string 
// representing the pattern to search for, and a pointer to bool that represents 
// if the search should be case insensitive. Returns the number of times the 
// pattern is found in the text.
int ImprovedMatches(std::string text_string, std::string pattern_string, 
                    const bool* case_insensitive)
{
    if (*case_insensitive)
    {
        pattern_string = LowerCase(pattern_string);
        text_string = LowerCase(text_string);
    }
    return FoundCount(text_string, pattern_string);
}

//===============================================================================
//===============================================================================

// Takes three arguments: a string representing the text to search, a string 
// representing the pattern to search for, and a pointer to bool that represents 
// if the search should be case insensitive. Returns the index in the text 
// that the pattern is found, return -1 if pattern is not found.
int ImprovedFindFirstOf(std::string text_string, std::string pattern_string, 
                        const bool* case_insensitive)
{
    if (*case_insensitive)
    {
        pattern_string = LowerCase(pattern_string);
        text_string = LowerCase(text_string);
    }
    return FoundIndex(text_string, pattern_string);
}

//===============================================================================
//===============================================================================

// Takes four arguments: a string representing the text to search, a string 
// representing the pattern to search for, a string representing the new 
//content to replace the pattern in the text with, and a pointer to bool 
// that represents if the search should be case insensitive.
void ImprovedReplace(std::string& text_string, std::string pattern_string, 
                     std::string new_content, const bool* case_insensitive)
{
    StringReplace(text_string, pattern_string, new_content, case_insensitive);
}

//===============================================================================
//===============================================================================

// Takes three arguments: two strings that will be compared character by 
// character, and a bool that represents if the comparison should be case 
// insensitive. Returns the number of characters that differ between the two 
// strings.
int ImprovedNumberOfDifferences(std::string first_string, 
                                std::string second_string, 
                                bool case_insensitive)
{
    if (case_insensitive)
    {
        first_string = LowerCase(first_string);
        second_string = LowerCase(second_string);
    }
    return CharDifference(first_string, second_string);
}

//===============================================================================
//===============================================================================
