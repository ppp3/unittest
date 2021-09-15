// MathTestProject2.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class SomeClass
{
    public:
        SomeClass() = default;
        void someMethod()
        {
            std::cout << "Say something";
        }

        int otherMethod(int i)
        {
            return i;
        }

        int add(int i, int j)
        {
            return(i + j);
        }

        int getA()
        {
            return a;
        }

    private:
        int a;

};

class SomeMockedClass : public SomeClass
{
public:
    //alter Version
    MOCK_METHOD0(someMethod, void());
    MOCK_METHOD1(otherMethod, int(int));
    MOCK_METHOD1(otherMethod, int(int));
    MOCK_METHOD2(add, int(int, int));
    //MOCK_CONST_METHOD0(get, int, ());

    // Neue Version
    //MOCK_METHOD(int, add, (int, int));

};

TEST(SampleTest, BasicTest)
{
    ASSERT_EQ(2, 2);
}

TEST(SampleTest, BasicMockTest)
{
    SomeMockedClass smc;

    EXPECT_CALL(smc, someMethod).Times(1);
    smc.someMethod();
    smc.someMethod();
}


int main(int argc, char **argv)
{
    std::cout << "Hello World!\n";
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
