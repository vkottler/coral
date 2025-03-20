/* internal */
#include "cli/text.h"

/* toolchain */
#include <cstdint>

static const std::map<std::string, uint8_t> input_flags = {
    {"1", 1}, {"2", 2}, {"4", 4}, {"8", 8}, {"16", 16},
};

int main(void)
{
    using namespace Coral;

    print_verb_name_condition("name", "verb", true);
    print_verb_name_condition("name", "verb", false);

    std::vector<std::string> flag_strs = {};
    populate_flag_strs<uint8_t>(7 + 32, flag_strs, input_flags,
                                &get_stdout(true));

    return 0;
}
