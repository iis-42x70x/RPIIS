#include "pch.h"
#include "gtest/gtest.h"
#include <fstream>
#include <string>
#include <cstdio>
#include <map>
#include <sstream>
#include <clocale>
#include <windows.h>

class TempFile {
public:
    explicit TempFile(const std::string& content) : path("temp_test_file.txt") {
        std::ofstream out(path);
        if (out.is_open()) {
            out << content;
        }
    }

    ~TempFile() {
        if (!path.empty()) {
            std::remove(path.c_str());
        }
    }

    std::string getPath() const { return path; }

    TempFile(const TempFile&) = delete;
    TempFile& operator=(const TempFile&) = delete;

private:
    std::string path;
};

static void ResetSet(Set& s) {
    s.elem_count = 0;
    s.set_count = 0;
    s.brackets_count = 0;
}

void FixRussianOutput() {
    // Óñòàíàâëèâàåì êîäèðîâêó êîíñîëè Windows-1251
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::setlocale(LC_ALL, "Russian");
}

TEST(SymmDiffTest, ComplexElementsTest) {
    FixRussianOutput();

    Set sets[2] = {};
    TempFile tf("{6a, 2b, 3{1,2}, 7f}\n{3cadfs, 4{1,2}, 7b, 3f}");

    ResetSet(sets[0]);
    ResetSet(sets[1]);

    std::cout << "\nÒåñòèðîâàíèå êîìïëåêñíûõ ìíîæåñòâ:\n";
    Do_Symm_Diff(sets, tf.getPath());

    EXPECT_GE(sets[0].elem_count, 4);
}

TEST(SymmDiffTest, ComplexMultiplicity) {
        std::setlocale(LC_ALL, "rus");
    
        Set sets[2] = {};
        TempFile tf("{3a,5b,2c}\n{1a,2b,4d}");
    
        ResetSet(sets[0]);
        ResetSet(sets[1]);
    
        Do_Symm_Diff(sets, tf.getPath());
    }
    
    TEST(SymmDiffTest, EmptySets) {
        Set sets[2] = {};
        TempFile tf("{}\n{}");
    
        ResetSet(sets[0]);
        ResetSet(sets[1]);
    
        testing::internal::CaptureStdout();
        Do_Symm_Diff(sets, tf.getPath());
        testing::internal::GetCapturedStdout();
    
        EXPECT_EQ(sets[0].elem_count, 0);
    }
    
    TEST(SymmDiffTest, FileNotFound) {
        std::setlocale(LC_ALL, "rus");
    
        Set sets[2] = {};
        testing::internal::CaptureStderr();
        Do_Symm_Diff(sets, "íåñóùåñòâóþùèé_ôàéë.txt");
        std::string output = testing::internal::GetCapturedStderr();
    
        std::cerr << output;
    
        EXPECT_NE(output.find("Îøèáêà îòêðûòèÿ ôàéëà!"), std::string::npos);
    }
    
    int main(int argc, char** argv) {
        FixRussianOutput();
        ::testing::InitGoogleTest(&argc, argv);

        int result = RUN_ALL_TESTS();

        if (result == 0) {
            std::cout << "\nÂÑÅ ÒÅÑÒÛ ÏÐÎÉÄÅÍÛ ÓÑÏÅØÍÎ!\n";
        }
        else {
            std::cout << "\nÒÅÑÒÛ ÍÅ ÏÐÎÉÄÅÍÛ, ÈÑÏÐÀÂÜÒÅ ÎØÈÁÊÈ\n";
        }

        return result;
    }