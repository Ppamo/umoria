// Copyright (c) 1989-2008 James E. Wilson, Robert A. Koeneke, David J. Grabiner
//
// Umoria is free software released under a GPL v2 license and comes with
// ABSOLUTELY NO WARRANTY. See https://www.gnu.org/licenses/gpl-2.0.html
// for further details.

// Generic helper functions

#include "headers.h"
#include <cassert>

// Insert a long number into a string (was `insert_lnum()` function)
void insertNumberIntoString(char *to_string, const char *from_string, int32_t number, bool show_sign) {
    size_t from_len = strlen(from_string);
    char *to_str_tmp = to_string;
    char *str = nullptr;

    // must be int for strncmp()
    int flag = 1;

    while (flag != 0) {
        str = strchr(to_str_tmp, from_string[0]);
        if (str == nullptr) {
            flag = 0;
        } else {
            flag = strncmp(str, from_string, from_len);
            if (flag != 0) {
                to_str_tmp = str + 1;
            }
        }
    }

    if (str != nullptr) {
        vtype_t str1 = {'\0'};
        vtype_t str2 = {'\0'};

        (void) strncpy(str1, to_string, str - to_string);
        str1[str - to_string] = '\0';
        (void) strcpy(str2, str + from_len);

        if (number >= 0 && show_sign) {
            (void) sprintf(to_string, "%s+%d%s", str1, number, str2);
        } else {
            (void) sprintf(to_string, "%s%d%s", str1, number, str2);
        }
    }
}

// Inserts a string into a string
void insertStringIntoString(char *to_string, const char *from_string, const char *str_to_insert) {
    auto from_len = (int) strlen(from_string);
    auto to_len = (int) strlen(to_string);

    char *bound = to_string + to_len - from_len;
    char *pc = nullptr;

    for (pc = to_string; pc <= bound; pc++) {
        char *temp_obj = pc;
        const char *temp_mtc = from_string;

        int i;
        for (i = 0; i < from_len; i++) {
            if (*temp_obj++ != *temp_mtc++) {
                break;
            }
        }
        if (i == from_len) {
            break;
        }
    }

    if (pc <= bound) {
        char new_string[MORIA_MESSAGE_SIZE];

        (void) strncpy(new_string, to_string, (pc - to_string));

        new_string[pc - to_string] = '\0';

        if (str_to_insert != nullptr) {
            (void) strcat(new_string, str_to_insert);
        }

        (void) strcat(new_string, (pc + from_len));
        (void) strcpy(to_string, new_string);
    }
}

bool isVowel(char ch) {
    switch (ch) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            return true;
        default:
            return false;
    }
}

// http://rus.har.mn/blog/2014-05-19/strtol-error-checking/
bool stringToNumber(const char *str, int *number) {
    // we need to reset `errno`
    errno = 0;

    char *endptr = nullptr;
    long num = strtol(str, &endptr, 10);

    if (errno == ERANGE) {
        switch (num) {
            case LONG_MIN:
                // underflow
                break;
            case LONG_MAX:
                // overflow
                break;
            default:
                // impossible
                assert(false);
        }
        return false;
    }

    // something else happened. die die die
    if (errno != 0) {
        return false;
    }

    // garbage at end of string
    if (*endptr != '\0') {
        return false;
    }

    *number = (int) num;
    return true;
}
