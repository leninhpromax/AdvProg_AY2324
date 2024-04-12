#include "simpleai.h"
#include <map>

int readMaxGuess()
{
    int maxGuess;
    cout << endl << "Enter the number of incorrect guesses: ";
    cin >> maxGuess;
    return maxGuess;
}

int readWordLen()
{
    int wordLen;
    cout << endl << "Enter the number characters of your secret word: ";
    cin >> wordLen;
    return wordLen;
    
}

/***
    Args:
        wordLen (int): The desired length of input word
        vocabulary (vector<string>): The vocabulary
    Returns:
        answer (vector<string>) : A set or word from the vocabulary where the number of character is equal to wordLen
***/
vector<string> filterWordsByLen(int wordLen, const vector<string>& vocabulary)
{
    vector<string> answer;
    for ( const string& c : vocabulary){
        if (c.length() == wordLen){
            answer.push_back(c);
        }
    }
    //Write your code here
    return answer;
}

/***
    Args:
        selectedChars (set<char>): The predicted characters
    Returns:
        answer (char) : The next character given the provided word is not in the vocabulary
***/

char nextCharWhenWordIsNotInDictionary(const set<char>& selectedChars)
{
      char answer = 'a';
    if (!selectedChars.empty()) {
        char c = *selectedChars.rbegin();
        answer = c + 1;
        if (answer > 'z') {
            answer = 'a';
        }
        while (selectedChars.find(answer) != selectedChars.end()) {
            answer++;
            if (answer > 'z') {
                answer = 'a';
            }
        }
    }
    return answer;
}

/***
    Args:
        candidateWords (vector<string>): The candidate words for the current given string 
    Returns:
        answer (map) : The map which count the occurences of character in the set of candidate words
***/

map<char, int> countOccurrences(const vector<string>& candidateWords)
{
    map<char, int> answer;
    //Write your code here
    for (const string& c : candidateWords) {
        for (char ch : c) {
            answer[ch]++;
        }
    }
    return answer;
}

/***
    Args:
        occurrences (map<char, int>): The map which count the occurences of character in the set of candidate words
        selectedChars (set<char>): The predicted characters
    Returns:
        answer (char) : The most frequent character
***/

char findMostFrequentChar(const map<char, int>& occurrences, const set<char>& selectedChars)
{
    char answer;
    //Write your code here
    int max1 = 0;
    for (const auto& c : occurrences) {
        if (c.second > max1 && selectedChars.find(c.first) == selectedChars.end()) {
            answer = c.first;
            max1 = c.second;
        }
    }
    return answer;
}

/***
    Args:
        candidateWords (vector<string>): The candidate words for the current given string 
        selectedChars (set<char>): The predicted characters
    Returns:
        answer (char) : The most suitable character for prediction
***/

char findBestChar(const vector<string>& candidateWords, const set<char>& selectedChars)
{
    char answer = 'a';
    //Write your code here
// Đếm số lần xuất hiện của mỗi ký tự trong danh sách từ ứng viên
map<char, int> occurrences = countOccurrences(candidateWords);

// Tìm ký tự xuất hiện nhiều nhất trong occurrences mà chưa được dự đoán
answer = findMostFrequentChar(occurrences, selectedChars);

// Trả về ký tự được chọn làm kết quả của hàm findBestChar
return answer;
}

string getWordMask(char nextChar)
{
    string mask;
    cout << "The next char is: " << nextChar << endl;
    cout << "Please give me your answer: ";
    cin >> mask;
    return mask;
}

/***
    Args:
        ch (char): The predicted character by the AI
        mask (string): The response mask by the player
    Returns:
        answer (bool) : return False if the predicted character is the wrong one, True otherwise
***/

bool isCorrectChar(char ch, const string& mask)
{
    bool answer = false;
    //Write your code here
    for (char c : mask){
        if (ch == c){
            answer = true;
            break;
        }
    }

    return answer;
}

/***
    Args:
        mask (string): The response mask by the player
    Returns:
        answer (bool) : return False if the provided mask is not a whole word, True otherwise
        (Example: -False: g__d
                  -True:  good)
***/
bool isWholeWord(const string& mask)
{
    bool answer = false;
    for (char c : mask) {
        if (c == '-') {
            continue; // Bỏ qua ký tự '-'
        }
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            answer = true;
        } else {
            return false; // Trả về false nếu ký tự không phải là một ký tự chữ cái hoặc '-'
        }
    }
    return answer; // Trả về true nếu mask chứa ít nhất một ký tự chữ cái và không chứa ký tự không hợp lệ khác
}

/***
    This function should be used to support the filterWordsByMask function below
    Args:
        mask (string): The response mask by the player
        word (string): input word
        ch (char): The predicted character by the AI
    Returns:
        answer (bool) : return False if the provided mask and the given word is not in the same form.
        Example: - False: mask(-ood), char 'd' vs word(boot)
                 - True: mask(-ood), char 'd'  vs word(good)

***/
bool wordConformToMask(const string& word, const string& mask, char ch) 
{
    bool answer = true;
    //Write your code here
     if (word.length() != mask.length()) {
    answer = false;
  }

  for (int i = 0; i < word.length(); ++i) {
    if (mask[i] != '-' && mask[i] != word[i]) {
      answer = false;
    }
  }
    return answer;
}

/***
    Args:
        mask (string): The response mask by the player
        words (vector<string>): The candidate words
        ch (char): The predicted character by the AI
    Returns:
        answer (bool) : a list of word which satisfiy the mask and the predicted character
        Examples: input words: (good,boot,hood,...)
                  input mask: -ood
                  predicted char: d
                  Return: good,hood
***/
vector<string> filterWordsByMask(const vector<string>& words, const string& mask, char ch)
{
    vector<string> answer;
    //Write your code here
    for (const string& word : words) {
    if (wordConformToMask(word, mask, ch)) {
      answer.push_back(word);
    }
  }
    return answer;
}