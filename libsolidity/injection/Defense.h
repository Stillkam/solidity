#include <string>


using namespace std;

namespace defense {

    class Modifier {
    private:
        string test_modifier = "modifier testModifier() {"\
                           "    require(testState == true, \"for test\");"\
                           "    _;"\
                           "}";
        string name = "testModifier";

    public:
        string getModifier() {
            return test_modifier;
        }

        string getName() {
            return name;
        }

    };

    class Statement {
    private:
        string declar_statement = "bool testState;";
        string init_statement = "testState = false";

    public:
        string getDeclarStatement()
        {
            return declar_statement;
        }

        string getInitStatement()
        {
            return init_statement;
        }
    };

}