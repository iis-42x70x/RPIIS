#include "gtest/gtest.h"
#include "SetUnion.hpp"
#include <fstream>

class SetUnionTest : public ::testing::Test {
protected:
    SetUnion su;

    void SetUp() override {
        // Тестовый файл с вложенными множествами
        std::ofstream tmp("test_input.txt");
        tmp << "A={1, 2, {3,4}, valid_name}\n";
        tmp << "B={2, {3,4}, {5,{6,7}}, 42}\n";
        tmp << "C={1, {3,4}, {3,4}}"; // Проверка дубликатов
        tmp.close();
    }

    void TearDown() override {
        remove("test_input.txt");
    }
};

// 1. Тесты валидации элементов
TEST_F(SetUnionTest, ValidatesNumbers) {
    EXPECT_TRUE(su.is_valid_element("123"));
    EXPECT_TRUE(su.is_valid_element("0"));
    EXPECT_FALSE(su.is_valid_element("12a")); // Буквы в числах
}

TEST_F(SetUnionTest, ValidatesNames) {
    EXPECT_TRUE(su.is_valid_element("valid"));
    EXPECT_TRUE(su.is_valid_element("_valid_2"));
    EXPECT_FALSE(su.is_valid_element("3invalid")); // Начинается с цифры
    EXPECT_FALSE(su.is_valid_element("no-dash")); // Недопустимый символ
}

TEST_F(SetUnionTest, ValidatesTuples) {
    EXPECT_TRUE(su.is_valid_element("<1,2>"));
    EXPECT_TRUE(su.is_valid_element("<a,b>"));
    EXPECT_TRUE(su.is_valid_element("<1,<2,3>>")); // Вложенный кортеж
    EXPECT_FALSE(su.is_valid_element("<1,2")); // Незакрыт
    EXPECT_FALSE(su.is_valid_element("<>")); // Пустой
}

// 2. Тесты вложенных множеств
TEST_F(SetUnionTest, ValidatesNestedSets) {
    EXPECT_TRUE(su.is_valid_element("{1,2}"));
    EXPECT_TRUE(su.is_valid_element("{a,{1,2}}")); // Двойная вложенность
    EXPECT_TRUE(su.is_valid_element("{{1,2},{3,4}}"));
    EXPECT_FALSE(su.is_valid_element("{1,2")); // Незакрыто
    EXPECT_FALSE(su.is_valid_element("{1,{2,3}")); // Несбалансировано
}

// 3. Тесты парсинга
TEST_F(SetUnionTest, ParsesNestedStructures) {
    auto res = su.parse_set("X={1, {2,3}, <4,5>}");
    EXPECT_EQ(res.size(), 3);
    EXPECT_TRUE(res.count("1"));
    EXPECT_TRUE(res.count("{2,3}"));
    EXPECT_TRUE(res.count("<4,5>"));
}

TEST_F(SetUnionTest, HandlesSpacesInNested) {
    auto res = su.parse_set("Y={ 1 , { 2 , 3 } , < 4 , 5 > }");
    EXPECT_EQ(res.size(), 3);
    EXPECT_TRUE(res.count("1"));
    EXPECT_TRUE(res.count("{2,3}"));
    EXPECT_TRUE(res.count("<4,5>"));
}

TEST_F(SetUnionTest, DuplicatesInNested) {
    auto res = su.parse_set("Z={1, 1, {2,3}, {2,3}}");
    EXPECT_EQ(res.size(), 2); // Дубликаты удаляются
}

// 4. Интеграционные тесты
TEST_F(SetUnionTest, FullIntegrationWithNested) {
    su.performUnion("test_input.txt");
    auto result = su.getUnionResult();

    // Ожидаемые элементы
    std::set<std::string> expected = {
        "1", "2", "42", "valid_name",
        "{3,4}", "{5,{6,7}}"
    };

    // Проверяем размер (должно быть 6 элементов, а не 7)
    EXPECT_EQ(result.size(), expected.size());

    // Проверяем каждый элемент
    for (const auto& elem : expected) {
        EXPECT_TRUE(result.count(elem)) << "Missing element: " << elem;
    }
}

// 5. Тесты обработки ошибок
TEST_F(SetUnionTest, InvalidNestedSets) {
    EXPECT_THROW(su.parse_set("X={1, {2,3}"), std::runtime_error); // Не закрыто
    EXPECT_THROW(su.parse_set("Y={1, {2,{3}}"), std::runtime_error); // Несбалансировано
    EXPECT_THROW(su.parse_set("Z={1, <2,3}"), std::runtime_error); // Не закрыт кортеж
}

TEST_F(SetUnionTest, MixedTypesValidation) {
    EXPECT_TRUE(su.is_valid_element("{<1,2>,3}")); // Кортеж внутри множества
    EXPECT_TRUE(su.is_valid_element("<{1,2},3>")); // Множество внутри кортежа
    EXPECT_FALSE(su.is_valid_element("{<1,2>,3")); // Не закрыто
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}