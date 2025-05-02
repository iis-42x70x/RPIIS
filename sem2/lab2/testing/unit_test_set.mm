//
//  unit_test_set.mm
//  Lab2_PIOIVIS_set
//
//  Created by Dmitry Burbas on 01/05/2025.
//

#import <XCTest/XCTest.h>
#define private public
#import "set_of_possible_orient_sets.hpp"
#undef private


using namespace std;

@interface unit_test_set : XCTestCase
@property(nonatomic) set_of_possible_orient_sets *start_obj;
@end

@implementation unit_test_set

- (void)setUp {
    [super setUp];
    // Для тестов создаём объект с пустым начальным множеством
    _start_obj = new set_of_possible_orient_sets(vector<string>{}, 0);
}

- (void)tearDown {
    delete _start_obj;
    [super tearDown];
}

// Тест для факториала
- (void)testFactorial {
    XCTAssertEqual(factorial(0ULL), 1ULL);
    XCTAssertEqual(factorial(1ULL), 1ULL);
    XCTAssertEqual(factorial(5ULL), 120ULL);
}

// Тест для heap-перестановок
- (void)testHeapPermutations {
    vector<string> v = {"A","B","C"};
    auto perms = _start_obj->heap_permutations(v);
    // 3! = 6 перестановок
    XCTAssertEqual(perms.size(), (size_t)6);
    // Проверим, что совпадают все элементы
    XCTAssertTrue(perms[0] == vector<string>({"A","B","C"}));
    XCTAssertTrue(perms[1] == vector<string>({"B","A","C"}));
    XCTAssertTrue(perms[2] == vector<string>({"C","A","B"}));
    XCTAssertTrue(perms[3] == vector<string>({"A","C","B"}));
    XCTAssertTrue(perms[4] == vector<string>({"B","C","A"}));
    XCTAssertTrue(perms[5] == vector<string>({"C","B","A"}));
}

// Тест для генерации неупорядоченных n-элементных выборок

- (void)testGenerateUnorderedPermutations{
    // Исходный набор из трёх строк
    vector<string> v = {"1","2","3"};
    // Генерируем все 2-элементные выборки
    auto comb = _start_obj->generate_unordered_permutations(v, 2);
    
    // Ожидаемый результат: {{"1","2"}, {"1","3"}, {"2","3"}}
    vector<vector<string>> expected = {
        {"1","2"},
        {"1","3"},
        {"2","3"}
    };
    
    // 1) Проверяем количество комбинаций
    XCTAssertEqual(comb.size(), expected.size());
    
    // 2) Пошагово сравниваем каждую комбинацию с expected
    for (size_t i = 0; i < expected.size(); ++i) {
        // Оператор== для vector<string> вернёт true, если все элементы совпадают по порядку
        XCTAssertTrue(comb[i] == expected[i], @"Комбинация %zu ожидается %@, но получена %@",
                      i,
                      [NSString stringWithUTF8String:converttocstring(expected[i]).c_str()],
                      [NSString stringWithUTF8String:converttocstring(comb[i]).c_str()]);
    }
}

// Вспомогательная функция для преобразования vector<string> в строку (для вывода в сообщении XCTest)
static string converttocstring(const vector<string>& arr) {
    string s = "{";
    for (size_t j = 0; j < arr.size(); ++j) {
        s += arr[j];
        if (j + 1 < arr.size()) s += ",";
    }
    s += "}";
    return s;
}


// Тест для обнаружения одинаковых элементов
- (void)testHasIdenticalElements {
    vector<string> ok = {"a","b","c"};
    vector<string> dup = {"{a,b,{d,c,<m,k,n>}}","y","{{<m,k,n>,c,d},b,a}"};
    XCTAssertFalse(_start_obj->has_identical_elements(ok));
    XCTAssertTrue(_start_obj->has_identical_elements(dup));
}

// Тест для функции swap_elem
- (void)testSwapElem {
    vector<string> v = {"one","two"};
    _start_obj->swap_elem(v, 0, 1);
    XCTAssertTrue(v[0] == "two" && v[1] == "one");
}

- (void)testIsWrongInput {
    _start_obj->input_set = {"{a}}","2"};
    XCTAssertTrue(_start_obj->is_wrong_input());
    _start_obj->input_set = {"{a","2"};
    XCTAssertTrue(_start_obj->is_wrong_input());
    _start_obj->input_set = {"ab","2"};
    XCTAssertTrue(_start_obj->is_wrong_input());
    _start_obj->input_set = {"a,b","2"};
    XCTAssertTrue(_start_obj->is_wrong_input());
    _start_obj->input_set = {"a'b","2"};
    XCTAssertTrue(_start_obj->is_wrong_input());
}

- (void)testCalculatePossibleSet {
    _start_obj->input_set = {"a","b","c"};
    _start_obj->numb_of_elem_in_orient_set = 2;
    vector<vector<string>> result = { {"a","b"}, {"b","a"},{"a","c"},{"c","a"},{"b","c"},{"c","b"}};
    _start_obj->calculate_possible_sets(1);
    XCTAssertEqual(result,_start_obj->set_possible_orient_sets);
}

@end
