#include "number.h"

char arr_num[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',};


int2023_t from_int(int32_t i) {
    int2023_t int2023;
    for (char &num: int2023.number) {
        num = '0';
    }
    if (i < 0) {
        int2023.number[0] = '-';
        i = i * (-1);
    } else {
        int2023.number[0] = '+';
    }
    int count_num = 0;
    while (i > 0) {
        int2023.number[252 - count_num] = i % 10 + '0';
        i /= 10;
        count_num++;
    }
    return int2023;
}

int2023_t from_string(const char *buff) {
    int2023_t int2023 = from_int(0);
    int num_str = 0;
    int index = 252;
    for (int i = 0; i < 254; ++i) {
        if (buff[num_str] == '\0') {
            break;
        }
        num_str++;
    }
    if (buff[0] == '-') {
        int2023.number[0] = '-';
        for (int i = num_str - 1; i > 0; --i) {
            int2023.number[index] = buff[i];
            index--;
        }
    } else {
        int2023.number[0] = '+';
        for (int i = num_str - 1; i >= 0; --i) {
            int2023.number[index] = buff[i];
            index--;
        }
    }
    if (buff[0] == '+') {
        int2023.number[0] = '+';
    } else if (buff[0] == '-') {
        int2023.number[0] = '-';
    }
    return int2023;
}


bool CheckSignPlus(char symb) {
    if (symb == '+') {
        return true;
    }
    return false;
}


bool CheckSignMinus(char symb) {
    if (symb == '-') {
        return true;
    }
    return false;
}


char CompareNum(const int2023_t &left, const int2023_t &right) {
    for (int i = 1; i <= 252; ++i) {
        if (left.number[i] != right.number[i]) {
            if (right.number[i] > left.number[i]) {
                return 'r';
            } else {
                return 'l';
            }
        }
    }
    return 'l';
}

int2023_t operator+(const int2023_t &lhs, const int2023_t &rhs) {
    int2023_t int2023 = from_int(0);
    int sum_num = 0;
    bool flag = false;
    if ((CheckSignPlus(lhs.number[0]) && CheckSignPlus(rhs.number[0])) ||
        (!CheckSignPlus(lhs.number[0]) && !CheckSignPlus(rhs.number[0]))) {
        for (int i = 252; i > 0; --i) {
            sum_num += int(lhs.number[i] - '0') + int(rhs.number[i] - '0');
            if (sum_num >= 0 && sum_num <= 9) {
                int2023.number[i] = sum_num + '0';
            } else {
                int2023.number[i] = sum_num % 10 + '0';
            }
            sum_num = sum_num / 10;
        }
        if (CheckSignPlus(lhs.number[0]) && CheckSignPlus(rhs.number[0])) {
            int2023.number[0] = '+';
        } else {
            int2023.number[0] = '-';
        }
    } else {
        if (CompareNum(lhs, rhs) == 'r') {
            for (int i = 252; i >= 1; --i) {
                sum_num = (rhs.number[i] - '0') - (lhs.number[i] - '0');
                if (flag) {
                    sum_num -= 1;
                    flag = false;
                }
                if (sum_num < 0) {
                    sum_num += 10;
                    flag = true;
                }
                int2023.number[i] = sum_num + '0';
            }
            int2023.number[0] = rhs.number[0];
        } else {
            for (int i = 252; i >= 1; --i) {
                sum_num = (lhs.number[i] - '0') - (rhs.number[i] - '0');
                if (flag) {
                    sum_num -= 1;
                    flag = false;
                }
                if (sum_num < 0) {
                    sum_num += 10;
                    flag = true;
                }
                int2023.number[i] = sum_num + '0';
            }
            int2023.number[0] = lhs.number[0];
        }
    }
    return int2023;
}

int2023_t operator-(const int2023_t &lhs, const int2023_t &rhs) {
    int2023_t int2023 = from_int(0);
    bool flag = false;
    int sum_num = 0;
    if (!CheckSignMinus(lhs.number[0]) && CheckSignMinus(rhs.number[0]) ||
        CheckSignMinus(lhs.number[0]) && !CheckSignMinus(rhs.number[0])) {
        for (int i = 252; i > 0; --i) {
            sum_num += int(lhs.number[i] - '0') + int(rhs.number[i] - '0');
            if (sum_num >= 0 && sum_num <= 9) {
                int2023.number[i] = sum_num + '0';
            } else {
                int2023.number[i] = sum_num % 10 + '0';
            }
            sum_num = sum_num / 10;
        }
        if (!CheckSignMinus(lhs.number[0]) && CheckSignMinus(rhs.number[0])) {
            int2023.number[0] = '+';
        } else {
            int2023.number[0] = '-';
        }
    } else {
        if (CompareNum(lhs, rhs) == 'r') {
            for (int i = 252; i >= 1; --i) {
                sum_num = (rhs.number[i] - '0') - (lhs.number[i] - '0');
                if (flag) {
                    sum_num -= 1;
                    flag = false;
                }
                if (sum_num < 0) {
                    sum_num += 10;
                    flag = true;
                }
                int2023.number[i] = sum_num + '0';
            }
            if (rhs.number[0] == '-') {
                int2023.number[0] = '+';
            } else {
                int2023.number[0] = '-';
            }
        } else {
            for (int i = 252; i >= 1; --i) {
                sum_num = (lhs.number[i] - '0') - (rhs.number[i] - '0');
                if (flag) {
                    sum_num -= 1;
                    flag = false;
                }
                if (sum_num < 0) {
                    sum_num += 10;
                    flag = true;
                }
                int2023.number[i] = sum_num + '0';
            }

            int2023.number[0] = lhs.number[0];
        }
    }
    return int2023;
}

int2023_t operator*(const int2023_t &lhs, const int2023_t &rhs) {
    int2023_t int2023_ans = from_int(0);
    int2023_t int2023_for_mult = from_int(0);
    int index_left_num;
    int index_right_num;
    int num_l = 0;
    int num_r = 0;
    int count_num_int2023 = 0;
    int mult_num = 0;
    int num_for_sum_digit = 0;
    int sum = 0;
    for (index_left_num = 1; index_left_num <= 252; index_left_num++) {
        if (lhs.number[index_left_num] != '0') {
            break;
        }
    }
    for (index_right_num = 1; index_right_num <= 252; index_right_num++) {
        if (rhs.number[index_right_num] != '0') {
            break;
        }
    }
    for (int i = 252; i >= index_left_num; i--) {
        num_r = lhs.number[i] - '0';
        num_for_sum_digit = 0;
        for (int j = 252; j >= index_right_num - 1; --j) {
            num_l = rhs.number[j] - '0';
            mult_num = num_l * num_r + num_for_sum_digit;
            if (0 <= mult_num && mult_num < 10) {
                num_for_sum_digit = 0;
            } else {
                num_for_sum_digit = mult_num / 10;
                mult_num %= 10;
            }
            int2023_for_mult.number[j] = mult_num + '0';
        }
        for (int j = 252; j > count_num_int2023; --j) {
            sum = (int2023_ans.number[j - count_num_int2023] - '0') + (int2023_for_mult.number[j] - '0') +
                  num_for_sum_digit;
            if (sum > 0) {
                num_for_sum_digit = sum / 10;
                sum %= 10;
            } else {
                num_for_sum_digit = 0;
            }
            int2023_ans.number[j - count_num_int2023] = sum + '0';
        }
        count_num_int2023++;
        for (int j = 252; j > 0; --j) {
            int2023_for_mult.number[j] = '0';
        }
    }
    if (!CheckSignMinus(lhs.number[0]) && CheckSignMinus(rhs.number[0]) ||
        CheckSignMinus(lhs.number[0]) && !CheckSignMinus(rhs.number[0])) {
        int2023_ans.number[0] = '-';
    } else {
        int2023_ans.number[0] = '+';
    }
    return int2023_ans;
}

int2023_t operator/(const int2023_t &lhs, const int2023_t &rhs) {
    int2023_t int2023 = from_int(0);
    int index_left_num;
    int index_right_num;
    int flag_rhs_digit;
    for (index_left_num = 1; index_left_num <= 252; index_left_num++) {
        if (lhs.number[index_left_num] != '0') {
            break;
        }
    }
    for (index_right_num = 1; index_right_num <= 252; index_right_num++) {
        if (rhs.number[index_right_num] != '0') {
            break;
        }
    }
    if (lhs == from_int(0) || rhs == from_int(0)) {
        return int2023;
    }

    if (lhs.number[index_left_num] < rhs.number[index_right_num]) {
        if (index_right_num <= index_left_num) {
            return int2023;
        }
    }
    if (rhs == from_int(1)) {
        return lhs;
    }
    if (rhs.number[index_right_num] <= lhs.number[index_left_num]) {
        flag_rhs_digit = 0;
    } else {
        flag_rhs_digit = 1;
    }
    int res_digit = 0;
    int position = index_left_num + (253 - index_right_num) + flag_rhs_digit;
    int result_length = 254 - position;
    char result[result_length];
    int2023_t remainder = from_int(0);
    for (int i = 0; i < ((253 - index_right_num) + flag_rhs_digit); i++) {
        remainder.number[index_right_num + i - flag_rhs_digit] = lhs.number[index_left_num + i];
    }
    int2023_t divider = rhs;
    divider.number[0] = '+';
    for (int i = 0; i < result_length; i++) {
        int2023_t temp = remainder - divider;
        char temp_sign = temp.number[0];
        for (int j = 0; j < 253; j++) {
            temp.number[j] = remainder.number[j];
        }
        int num_pos = 0;
        while (remainder.number[0] == '+') {
            remainder = remainder - divider;
            num_pos++;
        }
        remainder = temp - (divider * from_int(num_pos - 1));
        if (temp_sign == '+') {
            result[res_digit] = arr_num[num_pos - 1];
        } else {
            result[res_digit] = '0';
        }
        res_digit++;
        for (int j = 2; j < 253; j++) {
            remainder.number[j - 1] = remainder.number[j];
        }
        remainder.number[252] = lhs.number[position];
        position++;
    }
    for (int i = 0; i < result_length; i++) {
        int2023.number[254 - result_length + i - 1] = result[i];
    }
    if ((CheckSignPlus(lhs.number[0]) && CheckSignPlus(rhs.number[0])) ||
        (!CheckSignPlus(lhs.number[0]) && !CheckSignPlus(rhs.number[0]))) {
        int2023.number[0] = '+';
    } else {
        int2023.number[0] = '-';
    }
    return int2023;
}

bool operator==(const int2023_t &lhs, const int2023_t &rhs) {
    for (int i = 0; i < 253; ++i) {
        if (lhs.number[i] != rhs.number[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const int2023_t &lhs, const int2023_t &rhs) {
    for (int i = 0; i < 253; ++i) {
        if (lhs.number[i] != rhs.number[i]) {
            return true;
        }
    }
    return false;
}

std::ostream &operator<<(std::ostream &stream, const int2023_t &value) {
    bool flag_0 = false;
    stream << value.number[0];
    for (int i = 1; i < 253; ++i) {
        if (value.number[i] != '0') {
            flag_0 = true;
        }
        if (flag_0) {
            stream << value.number[i];
        }
    }
    return stream;
}
