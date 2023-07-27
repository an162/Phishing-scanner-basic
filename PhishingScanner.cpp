#include <iostream>
#include <fstream>
#include <cstdlib> //for exit function
#include <string>
#include <cctype> //for tolower def
#include <vector>

// Function for User Education
void userEducation() {
    std::cout << "Phishing Scam Warning!\n";
    std::cout << "If an email is flagged as a potential phishing scam:\n";
    std::cout << "1. Do not click on any links or download attachments.\n";
    std::cout << "2. Do not provide sensitive information or reply to the email.\n";
    std::cout << "3. Verify the legitimacy of the email through official channels.\n";
    std::cout << "4. Report the email to your organization's IT or security team.\n";
    std::cout << "5. Help us improve by providing feedback on false positives or negatives.\n";
    std::cout << "Stay safe and protect your personal information!\n";
}

// Function for Feedback Mechanism
void feedbackMechanism(std::vector<std::string>& reportedEmails) {
    std::string feedback;
    do {
        std::cout << "Do you have any feedback on the flagged email? (Y/N): ";
        std::cin >> feedback;
        if (feedback == "Y" || feedback == "y") {
            std::string flaggedEmail;
            std::cout << "Please enter the email content that was flagged: ";
            std::cin.ignore();
            std::getline(std::cin, flaggedEmail);

            // Store the reported email for further analysis
            reportedEmails.push_back(flaggedEmail);
            std::cout << "Thank you for your feedback. We will analyze the reported email.\n";
        } else if (feedback != "N" && feedback != "n") {
            std::cout << "Invalid input. Please enter 'Y' for Yes or 'N' for No.\n";
        }
    } while (feedback != "N" && feedback != "n");
}


//to convert the text to lower case for identification
//helper function (secondary)
std::string toLowercase(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (std::isalpha(c)) {
            result += std::tolower(c);
        } else {
            result += c;
        }
    }
    return result;
}

void FindDangerLevel(std::string ListOfWords,std::string& textToInspect){
    int totalDangerLevel=0;
    textToInspect=toLowercase(textToInspect);

    std::ifstream fileInput(ListOfWords);
    if(!fileInput.is_open()) {
        std::cerr<<"Eroor, could not open file"<<std::endl;
        std::exit(1);
    }
    std::cout<<"Processing text..."<<std::endl;
    std::string line;
    while(getline(fileInput, line)){
        size_t arrow = line.find("->");
        if (arrow != std::string::npos) {
            // Extract the phrase from the beginning up to the hyphen
            std::string phraseToSearchFor = toLowercase(line.substr(0, arrow-1));
            size_t Danger = textToInspect.find(phraseToSearchFor);
            if (Danger != std::string::npos) {Danger=0;
                // Extract the additional number after the hyphen (if any)
                std::string dangerLevelStr = line.substr(arrow + 2);
                // Convert dangerLevelStr to an integer
                int dangerLevel = std::stoi(dangerLevelStr);
                totalDangerLevel+=dangerLevel;//repeated words will not be taken into concideration

            }

        }

    }
    fileInput.close();
     std::cout<<"Danger level is "<< totalDangerLevel<<std::endl;
}

int main(){
     // Simulate the user education process
     userEducation();

    std::string text;
    std::cout<<"Enter Email (copy, paste it if possible)"<<std::endl; //Not very professional indeed lol
                                                                      //would it have been better to make it read a file? or a link?
    getline(std::cin, text);

    FindDangerLevel("WordList.txt", text);



    // vector to store reported emails
    std::vector<std::string> reportedEmails;
     //the feedback mechanism
    feedbackMechanism(reportedEmails);
    return 0;
}
