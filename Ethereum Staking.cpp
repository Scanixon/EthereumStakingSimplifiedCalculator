#include <iostream>
#include <fstream>
#include <string> 
#include <iomanip>
#include "Ethereum Staking.h"

int main(){
 
    double InvestmentAmount = 0,
        YearlyStakingReward = 0,
        reward = 0,
        money = 0,
        reward_sum = 0;
    int StartY = 0, StartM = 0, StartD = 0,
        EndY = 0, EndM = 0, EndD = 0,
        days = 0, PaymentD = 0,
        i = 0;
    bool Reinvest = false, End = false, flag = false, bonus = false;
    std::string date;


    Menu();
    char ans;
    std::cin >> ans;

    switch (ans) {
     case '1':
            InvestmentAmount = 25;
            YearlyStakingReward = 10;
            StartY = 2019;
            StartM = 4;
            StartD = 15;
            EndY = 2021;
            EndM = 4;
            EndD = 15;
            PaymentD = 23;
            Reinvest = true;
            money = InvestmentAmount;
            NewFunction(End, PaymentD, StartD, flag, days, StartY, StartM, date, EndD, EndY, EndM, reward, money, Reinvest, reward_sum, YearlyStakingReward, i, bonus);
            // Bonus 1
            std::cout << "Do Bonus Task 1? y/n \n";
            char o;
            std::cin >> o;
            if (o == 'y') {
                reward = 0;
                money = 0;
                reward_sum = 0;
                days = 0;
                i = 0;
                Reinvest = true;
                End = false;
                flag = false;

                InvestmentAmount = 25;
                YearlyStakingReward = 10;
                StartY = 2019;
                StartM = 4;
                StartD = 15;
                EndY = 2020;
                EndM = 4;
                EndD = 15;
                PaymentD = 23;
                i = 0;

                money = InvestmentAmount;

                NewFunction(End, PaymentD, StartD, flag, days, StartY, StartM, date, EndD, EndY, EndM, reward, money, Reinvest, reward_sum, YearlyStakingReward, i, bonus);
            
                StartY = 2020;
                StartM = 4;
                StartD = 15;
                EndY = 2021;
                EndM = 4;
                EndD = 15;
                Reinvest = true;
                End = false;
                flag = false;
                YearlyStakingReward = 8;
                bonus = true;

                NewFunction(End, PaymentD, StartD, flag, days, StartY, StartM, date, EndD, EndY, EndM, reward, money, Reinvest, reward_sum, YearlyStakingReward, i, bonus);
            }
            return 0;
            break;
     case '2':
            Option2(InvestmentAmount, YearlyStakingReward,
                StartY, StartM, StartD,
                EndY, EndM, EndD,
                PaymentD, ans, Reinvest);
            money = InvestmentAmount;
            NewFunction(End, PaymentD, StartD, flag, days, StartY, StartM, date, EndD, EndY, EndM, reward, money, Reinvest, reward_sum, YearlyStakingReward, i, bonus);
            return 0;
            break;
     case '3':
            return 0;
            break;
     default:
            break;
        }
    
}
void NewFunction(bool& End, int PaymentD, int StartD, bool& flag, int& days, int& StartY, int& StartM, std::string& date, int EndD, int EndY, int EndM, double& reward, double& money, bool Reinvest, double& reward_sum, double YearlyStakingReward, int &i, bool &bonus)
{
    std::cout << "Please enter output file name (including .csv): ";
    std::string h;
    std::cin >> h;
    std::ofstream myfile(h, std::ios::app);
    if(!myfile){
        std::cout << "Failed to create file. Did you remember to put .csv?\n";
        std::cout << "Defaulting to ''schedule.csv'' ...\n";
        h = "schedule.csv";
        myfile.open(h);
    }
    if (bonus != true) {
        myfile << "Line #,Reward Date,Investment Amount,Reward Amount,Total Reward Amount To Date,Staking Reward Rate\n";
    }
    

    while (End == false) {
        i++;
        
        if (PaymentD > StartD && flag == false) {
            // Checks only once if next payment day is in the same month as start
            // e.g. 2022-10-15  &  2022-10-23
            days = rdn(StartY, StartM, PaymentD) - rdn(StartY, StartM, StartD);
            date = std::to_string(StartY) + "-" + std::to_string(StartM) + "-" + std::to_string(PaymentD);
            flag = true;
        }
        else {
            
            // Checks if next iteration is ending
            if (End == false) {
                //// Ends in next month but less than full month since last payment
                //// e.g. 2022-01-22 & 2022-02-05
                if (StartM == 12) {
                    if (StartY + 1 == EndY && 1 == EndM && EndD < PaymentD) {
                        days = rdn(StartY + 1, 1, EndD) - rdn(StartY, StartM, PaymentD);
                        date = std::to_string(StartY + 1) + "-" + std::to_string(1) + "-" + std::to_string(EndD);
                        End = true;
                    }
                }
                if (StartY == EndY && StartM + 1 == EndM && EndD < PaymentD) {
                    days = rdn(StartY, StartM + 1, EndD) - rdn(StartY, StartM, PaymentD);
                    date = std::to_string(StartY) + "-" + std::to_string(StartM + 1) + "-" + std::to_string(EndD);
                    End = true;
                }

                //// End this month
                //// e.g. 2022-01-01 & 2022-01-05
                if (StartY == EndY && StartM == EndM) {
                    days = rdn(StartY, StartM, EndD) - rdn(StartY, StartM, PaymentD);
                    date = std::to_string(StartY) + "-" + std::to_string(StartM) + "-" + std::to_string(EndD);
                    End = true;
                }
            }
            if(End != true){
                if (StartM < 12) {
                    days = rdn(StartY, StartM + 1, PaymentD) - rdn(StartY, StartM, PaymentD);
                    date = std::to_string(StartY) + "-" + std::to_string(StartM + 1) + "-" + std::to_string(PaymentD);
                    StartM++;
                }
                else {
                    days = rdn(StartY + 1, 1, PaymentD) - rdn(StartY, StartM, PaymentD);
                    date = std::to_string(StartY + 1) + "-" + std::to_string(1) + "-" + std::to_string(PaymentD);
                    StartY++;
                    StartM = 1;
                }
            }
        }

        // Daily interest rate * days in that month, divide by 100 cause it's %. 
        // Multiply by current money for reward amount
        reward = money * (((YearlyStakingReward / 365)*days) / 100);

        // Save rewards
        reward_sum = reward_sum + reward;

        // Print
        myfile << "Line " << i << ","
            << date << ","
            << std::fixed << std::setprecision(6) << money << ","
            << reward << ","
            << reward_sum << ","
            << std::fixed << std::setprecision(2) << YearlyStakingReward << "%\n";

        date.clear();
        // If yes on reinvestment, Add rewards to current Eth money pile.
        if (Reinvest == true) {
            money = money + reward;
        }
    }

    myfile.close();
}
void Menu()
{
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "Ethereum Staking profit Calculator\n";
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "1. Example Project \n";
    std::cout << "2. Input Data\n";
    std::cout << "3. End the Program\n";
    std::cout << "Note: See Readme for help :)\n";
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "Your choice: ";
}
void Option2(double& InvestmentAmount, double& YearlyStakingReward, int& StartY, int& StartM, int& StartD, int& EndY, int& EndM, int& EndD, int& PaymentD, char& ans, bool& Reinvest)
{
    system("CLS");
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "1. Text file\n";
    std::cout << "2. Console\n";
    std::cout << "Note: See Readme for help :)\n";
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "Your choice: ";
    char y;
    std::cin >> y;

    if (y == '1') {
        std::cout << "Enter name of txt file (include .txt): ";
        std::string g;
        std::cin >> g;
        std::ifstream file;
        file.open(g);
        if (file) {
            g.clear();
            file >> InvestmentAmount >> YearlyStakingReward
                >> StartY >> StartM >> StartD
                >> EndY >> EndM >> EndD
                >> PaymentD >> g;
            if (g == "YES") { Reinvest = true; std::cout << "YES\n"; }
            else { Reinvest = false; }

            // Check given Variables
            if (InvestmentAmount < 0) { InvestmentAmount = InvestmentAmount - InvestmentAmount - InvestmentAmount; }
            if (YearlyStakingReward < 0) { YearlyStakingReward = YearlyStakingReward - YearlyStakingReward - YearlyStakingReward; }
            if (StartY < 0) { StartY = StartY - StartY - StartY; }
            if (StartM < 0) { StartM = StartM - StartM - StartM; }
            if (StartM > 12) { StartM = 12; std::cout << "Incorrect Month Input. Assuming December...\n"; }
            if (StartD < 0) { StartD = StartD - StartD - StartD; }
            if (StartD > 31 && (StartM == 1 || StartM == 3 || StartM == 5 || StartM == 7 || StartM == 8 || StartM == 10 || StartM == 12)){
                StartD = 31;
                std::cout << "Incorrect Day Input. Assuming 31st...\n";
            }
            if (StartD > 30 && (StartM == 4 || StartM == 6 || StartM == 9 || StartM == 11)){
                StartD = 30;
                std::cout << "Incorrect Day Input. Assuming 30th...\n";
            }
            if(StartD > 29 && StartM == 2) {
                StartD = 28;
                std::cout << "Incorrect Day Input. Assuming 28th...\n";
            }
            if (EndY < 0) { EndY = EndY - EndY - EndY; }
            if (EndM < 0) { EndM = EndM - EndM - EndM; }
            if (EndM > 12) { EndM = 12; std::cout << "Incorrect Month Input. Assuming December...\n"; }
            if (EndD < 0) { EndD = EndD - EndD - EndD; }
            if (EndD > 31 && (EndM == 1 || EndM == 3 || EndM == 5 || EndM == 7 || EndM == 8 || EndM == 10 || EndM == 12)) {
                EndD = 31;
                std::cout << "Incorrect Day Input. Assuming 31st...\n";
            }
            if (EndD > 30 && (EndM == 4 || EndM == 6 || EndM == 9 || EndM == 11)) {
                EndD = 30;
                std::cout << "Incorrect Day Input. Assuming 30th...\n";
            }
            if (EndD > 29 && EndM == 2) {
                EndD = 28;
                std::cout << "Incorrect Day Input. Assuming 28th...\n";
            }
            if (PaymentD < 0) { PaymentD = PaymentD - PaymentD - PaymentD; }
            if (PaymentD > 28) { 
                PaymentD = 28;
                std::cout << "Payment Day cannot be over the 28th. due to the existance of February\n";
                std::cout << "Assuming Payment Day is 28th.\n";
            }

            int b = rdn(EndY, EndM, EndD) - rdn(StartY, StartM, StartD);
            if (b < 0) {
                std::cout << "The End dates are behind the Start dates.\n";
                std::cout << "Switching dates...\n";
                int u, p, t;
                u = EndY;
                p = EndM;
                t = EndD;
                EndY = StartY;
                EndM = StartM;
                EndD = StartD;
                StartY = u;
                StartM = p;
                StartD = t;
            }
        }
        else {
            std::cout << "File doesn't exist...\n";
            std::cout << "Assuming example project parameters...\n";
            InvestmentAmount = 25;
            YearlyStakingReward = 10;
            StartY = 2019;
            StartM = 4;
            StartD = 15;
            EndY = 2021;
            EndM = 4;
            EndD = 15;
            PaymentD = 23;
            Reinvest = true;
        }
    }
    else {
        std::cout << "Investment amount (e.g. 25) : ";
        std::cin >> InvestmentAmount;
        std::cout << "Yearly staking reward (e.g. 10% = 10) : ";
        std::cin >> YearlyStakingReward;
        std::cout << "Start year  (e.g. 2002) : ";
        std::cin >> StartY;
        std::cout << "Start month (e.g. 10) : ";
        std::cin >> StartM;
        std::cout << "Start day   (e.g. 21) : ";
        std::cin >> StartD;
        std::cout << "End year (e.g. 2012) : ";
        std::cin >> EndY;
        std::cout << "End month (e.g. 1) : ";
        std::cin >> EndM;
        std::cout << "End day (e.g. 13) : ";
        std::cin >> EndD;
        std::cout << "Day when rewards are payed out (e.g. 24) : ";
        std::cin >> PaymentD;
        std::cout << "Reinvest the rewards? (y/n) : ";
        std::cin >> ans;
        if (ans == 'y') { Reinvest = true; }
        else { Reinvest = false; }

        // Check given Variables
        if (InvestmentAmount < 0) { InvestmentAmount = InvestmentAmount - InvestmentAmount - InvestmentAmount; }
        if (YearlyStakingReward < 0) { YearlyStakingReward = YearlyStakingReward - YearlyStakingReward - YearlyStakingReward; }
        if (StartY < 0) { StartY = StartY - StartY - StartY; }
        if (StartM < 0) { StartM = StartM - StartM - StartM; }
        if (StartM > 12) { StartM = 12; std::cout << "Incorrect Month Input. Assuming December...\n"; }
        if (StartD < 0) { StartD = StartD - StartD - StartD; }
        if (StartD > 31 && (StartM == 1 || StartM == 3 || StartM == 5 || StartM == 7 || StartM == 8 || StartM == 10 || StartM == 12)) {
            StartD = 31;
            std::cout << "Incorrect Day Input. Assuming 31st...\n";
        }
        if (StartD > 30 && (StartM == 4 || StartM == 6 || StartM == 9 || StartM == 11)) {
            StartD = 30;
            std::cout << "Incorrect Day Input. Assuming 30th...\n";
        }
        if (StartD > 29 && StartM == 2) {
            StartD = 28;
            std::cout << "Incorrect Day Input. Assuming 28th...\n";
        }
        if (EndY < 0) { EndY = EndY - EndY - EndY; }
        if (EndM < 0) { EndM = EndM - EndM - EndM; }
        if (EndM > 12) { EndM = 12; std::cout << "Incorrect Month Input. Assuming December...\n"; }
        if (EndD < 0) { EndD = EndD - EndD - EndD; }
        if (EndD > 31 && (EndM == 1 || EndM == 3 || EndM == 5 || EndM == 7 || EndM == 8 || EndM == 10 || EndM == 12)) {
            EndD = 31;
            std::cout << "Incorrect Day Input. Assuming 31st...\n";
        }
        if (EndD > 30 && (EndM == 4 || EndM == 6 || EndM == 9 || EndM == 11)) {
            EndD = 30;
            std::cout << "Incorrect Day Input. Assuming 30th...\n";
        }
        if (EndD > 29 && EndM == 2) {
            EndD = 28;
            std::cout << "Incorrect Day Input. Assuming 28th...\n";
        }
        if (PaymentD < 0) { PaymentD = PaymentD - PaymentD - PaymentD; }
        if (PaymentD > 28) {
            PaymentD = 28;
            std::cout << "Payment Day cannot be over the 28th. due to the existance of February\n";
            std::cout << "Assuming Payment Day is 28th.\n";
        }
        int b = rdn(EndY, EndM, EndD) - rdn(StartY, StartM, StartD);
        if (b < 0) {
            std::cout << "The End dates are behind the Start dates.\n";
            std::cout << "Switching dates...\n";
            int u, p, t;
            u = EndY;
            p = EndM;
            t = EndD;
            EndY = StartY;
            EndM = StartM;
            EndD = StartD;
            StartY = u;
            StartM = p;
            StartD = t;
        }
    }
}
int rdn(int y, int m, int d) {
    if (m < 3){y--, m += 12;}
    return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + d - 306;
}