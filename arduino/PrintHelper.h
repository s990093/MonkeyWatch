#ifndef PRINT_HELPER_H
#define PRINT_HELPER_H

#include <Arduino.h>

class PrintHelper
{
public:
    PrintHelper(bool debugMode);
    void printHeader(const String &header);
    void printKeyValue(const String &key, const String &value);
    void printError(const String &errorMessage);
    void printSuccess(const String &successMessage);
    void printDebug(const String &debugMessage);
    void printInfo(const String &infoMessage);
    void printWarning(const String &warningMessage);
    void printDivider();
    void printTitleEnd();
    void printTitle(const String &title);
    void printSubTitle(const String &subtitle);
    void printSystemSummary(const String &networkStatus, const String &coreUsage, const String tasks[][2], int taskCount);

private:
    bool debugMode;
};

#endif // PRINT_HELPER_H
