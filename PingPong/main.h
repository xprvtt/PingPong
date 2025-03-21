#pragma once

#include <iostream>
#include <vector>
#include <Ctime>
#include <Random>

using namespace std;

/// <summary>функция определяет черные области на поле</summary>
/// <param name="CountCell">колличество зон, предполагается что их равное колличество, тип квадрата, например 11х11 </param>
/// <returns>полнaя строка зон</returns>
vector<bool> IdentifyCentralZone(unsigned int CountCell);
