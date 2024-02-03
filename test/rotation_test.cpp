#include "doctest.h"
#include "utils.h"

bool str_eq(std::string s1, std::string s2)
{
    for (size_t i = 0; i < s1.length() - 1; i++)
        if (s1[i] != s2[i])
            return false;

    return true;
}

TEST_CASE("testing the rotation of L")
{
    std::string str = "..*."
                      "..*."
                      "..*."
                      "..*.";

    std::string left_str = "...."
                           "****"
                           "...."
                           "....";

    std::string right_str = "...."
                            "...."
                            "****"
                            "....";

    CHECK(str_eq(left_rotate(str, 4), left_str));

    CHECK(str_eq(right_rotate(str, 4), right_str));
}

TEST_CASE("testing the rotation of Z")
{
    std::string str = ".**."
                      "..**"
                      "...."
                      "....";

    std::string left_str = ".*.."
                           "**.."
                           "*..."
                           "....";

    std::string right_str = "...."
                            "...*"
                            "..**"
                            "..*.";

    CHECK(str_eq(left_rotate(str, 4), left_str));

    CHECK(str_eq(right_rotate(str, 4), right_str));
}
