#pragma once

int rdn(int y, int m, int d);
void Option2(double& InvestmentAmount, double& YearlyStakingReward, int& StartY, int& StartM, int& StartD, int& EndY, int& EndM, int& EndD, int& PaymentD, char& ans, bool& Reinvest);
void Menu();
void NewFunction(bool& End, int PaymentD, int StartD, bool& flag, int& days, int& StartY, int& StartM, std::string& date, int EndD, int EndY, int EndM, double& reward, double& money, bool Reinvest, double& reward_sum, double YearlyStakingReward, int &i, bool& bonus);
