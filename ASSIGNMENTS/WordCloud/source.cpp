#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include"map.h"

//helper functions
// converts each word into lowercase 
std::string Lower(std::string word) {
    for (int i = 0; i < word.length(); i++) {
        word[i] = tolower(word[i]);
    }
    return word;
}
// remove punctuations
std::string Punctuations(std::string word) {
    std::string new_word = "";
    for (int i = 0; i < word.length(); i++) {
        if (isalnum(word[i])) {  
            new_word += word[i];
        }
    }
    return new_word;
}

bool StopWord(std::string word) {
    std::string stopWords[] = { "a", "an", "and", "able", "about", "also", "always", "any", "around", "as", "at", "because"
        , "been", "before", "being", "between", "both", "by", "can", "could", "did", "do", "does", "down"
        , "during", "each", "few", "for", "from", "further", "had", "has", "have", "he", "her", "here", "hers"
        , "herself", "him", "himself", "his", "how", "i", "if", "in", "into", "is", "it", "its", "itself"
        , "just", "like", "many", "me", "more", "most", "my", "myself", "no", "nor", "not", "of", "off", "on"
        , "once", "only", "or", "other", "our", "ours", "ourselves", "out", "over", "own", "same", "she"
        , "should", "so", "some", "such", "than", "that", "the", "their", "theirs", "them", "themselves", "then"
        , "there", "these", "they", "this", "those", "through", "to", "too", "under", "until", "up", "very"
        , "was", "we", "were", "what", "when", "where", "which", "while", "who", "whom", "why", "will", "with"
        , "would", "you", "your", "yours", "yourself", "yourselves" };

    
    int numWords = 107;  

    for (int i = 0; i < numWords; i++) {
        if (word == stopWords[i]) {
            return true;
        }
    }
    return false;
}



int main(int argc, char* argv[]) {
	std::string wordCount_file_URL;
    if (argc > 2)
        std::cout << "Usage: source.exe <file path/URL>";
    if (argc == 1) {
        std::cout << "Enter name of file (only supports text file currently) : ";
        getline(std::cin, wordCount_file_URL);
    }
    else
        wordCount_file_URL = argv[1];

    //Open the file
        std::ifstream file(wordCount_file_URL);

    // Checking file opening 
    if (!file.is_open()) {
        std::cout << " file not opened " << std::endl;
        return 1;
    }
    ////////////////////////////////////////////////////////
    // map to store keys and values
    //key = words
    //values = frequencies
    std::map<std::string, int> freq;
    // read words
    std::string word;
    while (!file.eof()) {  // While NOT at end of file
        file >> word;

        if (file.fail()) break;  // If reading failed, stop

        word = Punctuations(word);
        word = Lower(word);

        if (word.empty() || StopWord(word)) {
            continue;
        }

        freq[word]++;
    }
    file.close();
    // generating HTML file
    std::ofstream htmlFile("WordCount.html");

    htmlFile << "<html>\n<body>\n";
    htmlFile << "<h1>HI from ehhsen!" << "</h1>\n";
    htmlFile << "<h2>Word Clount for " << wordCount_file_URL << "</h1>\n";
    htmlFile << "<div>\n";

    for (auto it = freq.begin(); it != freq.end(); it++) {
        std::string curr = it->first;   // The word
        int frequency = it->second;            // The count

        // Font size = frequency * 10
        htmlFile << "<span style=\"font-size:" << frequency * 10 << "px;\">";
        htmlFile << curr << "</span>\n";
    }

    htmlFile << "</div>\n</body>\n</html>";
    htmlFile.close();
    std::cout << "html file generated ";
    system("start WordCount.html");

    return 0;


 
}