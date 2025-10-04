#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Batsman {
    string name;
    int runs = 0;
    int balls = 0;
    string outType = "Not Out";
};

struct Bowler {
    string name;
    int runsConceded = 0;
    int wicketsTaken = 0;
};

string getWicketType(int type) {
    string types[] = {"Unknown", "Caught", "Bowled", "LBW", "Run Out"};
    return (type >= 1 && type <= 4) ? types[type] : types[0];
}

void printBattingCard(Batsman batsmen[], int count) {
    cout << "\n===== FINAL BATTING SCORECARD =====\n";
    cout << left << setw(20) << "Batsman" << setw(10) << "Runs"
         << setw(10) << "Balls" << setw(15) << "StrikeRate"
         << setw(15) << "Status\n";
    cout << "----------------------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        double sr = batsmen[i].balls ? (double)batsmen[i].runs / batsmen[i].balls * 100 : 0;
        cout << left << setw(20) << batsmen[i].name
             << setw(10) << batsmen[i].runs
             << setw(10) << batsmen[i].balls
             << setw(15) << fixed << setprecision(2) << sr
             << setw(15) << batsmen[i].outType << "\n";
    }
}

void printBowlingCard(Bowler bowlers[], int count) {
    cout << "\n===== BOWLING SCORECARD =====\n";
    cout << left << setw(20) << "Bowler" << setw(15) << "Runs Given" << setw(10) << "Wickets\n";
    cout << "--------------------------------------\n";

    for (int i = 0; i < count; i++) {
        cout << left << setw(20) << bowlers[i].name
             << setw(15) << bowlers[i].runsConceded
             << setw(10) << bowlers[i].wicketsTaken << "\n";
    }
}

int main() {
    int overs;
    int totalRuns = 0;
    int totalWickets = 0;
    cout << "Enter number of overs: "; cin >> overs; cin.ignore();

    Batsman batsmen[11];
    Bowler bowlers[11];
    int bowlerCount = 0;

    cout << "Enter opening striker name: "; getline(cin, batsmen[0].name);
    cout << "Enter opening non-striker name: "; getline(cin, batsmen[1].name);
    int striker = 0, nonStriker = 1, nextBatsman = 2;

    for (int over = 1; over <= overs && totalWickets < 10; over++) {
        string bowlerName;
        cout << "\n--- Over " << over << " ---\nBowler: ";
        getline(cin, bowlerName);

        int bIndex = -1;
        for (int i = 0; i < bowlerCount; i++)
            if (bowlers[i].name == bowlerName) bIndex = i;

        if (bIndex == -1) {
            bowlers[bowlerCount].name = bowlerName;
            bIndex = bowlerCount++;
        }

        
        char wideChoice;
        int wides = 0;
        cout << "Were there wides in this over? (y/n): ";
        cin >> wideChoice;
        if (wideChoice == 'y' || wideChoice == 'Y') {
            cout << "How many wides? ";
            cin >> wides;
        }

        int runsStriker, runsNonStriker;
        int ballsStriker, ballsNonStriker, wkts;

    reenter_over:
        cout << "Runs scored by " << batsmen[striker].name << ": ";
        cin >> runsStriker;
        cout << "Balls faced by " << batsmen[striker].name << ": ";
        cin >> ballsStriker;

        cout << "Runs scored by " << batsmen[nonStriker].name << ": ";
        cin >> runsNonStriker;
        cout << "Balls faced by " << batsmen[nonStriker].name << ": ";
        cin >> ballsNonStriker;

        cout << "Wickets this over: ";
        cin >> wkts;
        cin.ignore();

    
        if (ballsStriker + ballsNonStriker + wkts != 6) {
            cout << " Not possible! Total balls must be 6. Re-enter values.\n";
            goto reenter_over;
        }

        
        batsmen[striker].runs += runsStriker;
        batsmen[striker].balls += ballsStriker;
        batsmen[nonStriker].runs += runsNonStriker;
        batsmen[nonStriker].balls += ballsNonStriker;

        int overRuns = runsStriker + runsNonStriker + wides;
        totalRuns += overRuns;
        bowlers[bIndex].runsConceded += overRuns;
        bowlers[bIndex].wicketsTaken += wkts;

        for (int w = 0; w < wkts && totalWickets < 10; w++) {
            int outType;
            cout << "Which batsman got out? (1 for striker, 2 for non-striker): ";
            int outChoice; cin >> outChoice;
            cout << "How out? (1=Caught 2=Bowled 3=LBW 4=Run Out): ";
            cin >> outType; cin.ignore();

            if (outChoice == 1) {
                batsmen[striker].outType = getWicketType(outType);
                if (nextBatsman < 11) {
                    cout << "Next batsman: ";
                    getline(cin, batsmen[nextBatsman].name);
                    batsmen[nextBatsman].outType = "Not Out";
                    striker = nextBatsman++;
                }
            } else {
                batsmen[nonStriker].outType = getWicketType(outType);
                if (nextBatsman < 11) {
                    cout << "Next batsman: ";
                    getline(cin, batsmen[nextBatsman].name);
                    batsmen[nextBatsman].outType = "Not Out";
                    nonStriker = nextBatsman++;
                }
            }
            totalWickets++;
        }

        cout << "Score: " << totalRuns << "/" << totalWickets 
             << " (+" << wides << " wides)\n";

        swap(striker, nonStriker); 
    }

    printBattingCard(batsmen, nextBatsman);
    printBowlingCard(bowlers, bowlerCount);

    cout << "\nTeam Total: " << totalRuns << "/" << totalWickets << " in " << overs
         << " overs\nRun Rate: " << fixed << setprecision(2)
         << (double)totalRuns / overs << "\n";
}
