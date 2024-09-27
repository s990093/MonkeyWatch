#include "PrintHelper.h"

PrintHelper::PrintHelper(bool debugMode) : debugMode(debugMode)
{
    // Constructor, initialize debug mode
}

void PrintHelper::printHeader(const String &header)
{
    Serial.println("");
    Serial.println("===================================");
    Serial.println("           " + header);
    Serial.println("===================================");
}

void PrintHelper::printKeyValue(const String &key, const String &value)
{
    Serial.print("🔑 ");
    Serial.print(key);
    Serial.print(": ");
    Serial.println(value);
}

void PrintHelper::printError(const String &errorMessage)
{
    Serial.print("❌ [ERROR] ");
    Serial.println(errorMessage);
}

void PrintHelper::printSuccess(const String &successMessage)
{
    Serial.print("✅ [SUCCESS] ");
    Serial.println(successMessage);
}

void PrintHelper::printDebug(const String &debugMessage)
{
    if (debugMode)
    {
        Serial.print("🐞 [DEBUG] ");
        Serial.println(debugMessage);
    }
}

void PrintHelper::printInfo(const String &infoMessage)
{
    Serial.print("ℹ️ [INFO] ");
    Serial.println(infoMessage);
}

void PrintHelper::printWarning(const String &warningMessage)
{
    Serial.print("⚠️ [WARNING] ");
    Serial.println(warningMessage);
}

void PrintHelper::printDivider()
{
    Serial.println("-----------------------------------");
}

void PrintHelper::printTitle(const String &title)
{
    Serial.println("");
    Serial.println("********** " + title + " **********");
    Serial.println("");
}

void PrintHelper::printTitleEnd()
{
    Serial.println("");

    Serial.println("**************************");
    Serial.println("");
}

void PrintHelper::printSubTitle(const String &subtitle)
{
    Serial.println("");
    Serial.println("----- " + subtitle + " -----");
}

void PrintHelper::printSystemSummary(const String &networkStatus, const String &coreUsage, const String tasks[][2], int taskCount)
{
    printTitle("INFO");
    printInfo("Network status: " + networkStatus);
    printInfo("Using cores: " + coreUsage);
    printInfo("Tasks created:");
    for (int i = 0; i < taskCount; ++i)
    {
        printKeyValue(tasks[i][0], tasks[i][1]);
    }
    printTitleEnd();
}
