#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
    int flag = 1;
    va_list ap;
    va_start(ap, format);
    while (*format != '\0') {
        struct forms new;
        init(&new);
        int len = 0, shift = 0;
        if (*format != '%' && flag) {
            *str = *format;
            str++;
            format++;
        } else if (*++format == '%') {
            format += 1;
            *str++ = '%';
        } else {
            len = parse(&new, format);
            if (new.type == '\0') {
                flag = 0;
            }
        }
        if (new.type != '\0') {
            shift = check_type(&new, str, ap, &shift);
            str += shift;
        }
        format += len;
    }
    va_end(ap);
    return *str;
}

void init(struct forms *p) {
    p->minus = 0;
    p->plus = 0;
    p->space = 0;
    p->zero = 0;
    p->grid = 0;
    p->width = 0;
    p->precission = 0;
    p->lenght = 0;
    p->type = '\0';
}

int parse(struct forms *p, const char *format) {
    int len = 0, temp = 0;
    while (*format != '%' && *format != '\0' && p->type == '\0') {
        if (!p->width && !p->precission && !p->lenght && !p->type) {
            temp = 0;
            temp += parse_flags(p, format);
            len += temp;
            format += temp;
        }
        if (!p->width && !p->precission) {
            temp = 0;
            temp += parse_width(p, format);
            len += temp;
            format += temp;
        }
        if (!p->precission) {
            temp = 0;
            temp += parse_precission(p, format);
            len += temp;
            format += temp;
        }
        if (!p->lenght) {
            temp = 0;
            temp += parse_lenght(p, format);
            len += temp;
            format += temp;
        }
        if (!p->type) {
            temp = 0;
            temp += parse_type(p, format);
            len += temp;
            format += temp;
        }
    }
    return len;
}

int parse_flags(struct forms *p, const char *format) {
    const char *str = format;
    int len = 0;
    if (*str == '-' || *str == '+' || *str == ' ' || *str == '0' || *str == '#') {
        if (*str == '-') {
            p->minus = 1;
            len += 1;
        }
        if (*str == '+') {
            p->plus = 1;
            len += 1;
        }
        if (*str == ' ') {
            p->space = 1;
            len += 1;
        }
        if (*str == '0') {
            p->zero = 1;
            len += 1;
        }
        if (*str == '#') {
            p->grid = 1;
            len += 1;
        }
    }
    return len;
}

int parse_width(struct forms *p, const char *format) {
    const char *str = format;
    int len = 0;
    if (*str >= '1' && *str <= '9') {
        while (*str >= '0' && *str <= '9') {
            if (*str >= '0' && *str <= '9') {
                int tempNum = *str - 48;
                str++;
                len += 1;
                if (*str >= '0' && *str <= '9') {
                    tempNum *= 10;
                    int tempNum2 = *str - 48;
                    tempNum += tempNum2;
                    p->width = tempNum;
                    str += 1;
                    len += 1;
                } else {
                    p->width = tempNum;
                }
            }
        }
    }
    return len;
}

int parse_precission(struct forms *p, const char *format) {
    const char *str = format;
    int len = 0;
    if (*str == '.') {
        len += 1;
        while (*(str + 1) >= '0' && *(str + 1) <= '9') {
            if (*(str + 1) >= '0' && *(str + 1) <= '9') {
                str++;
                int tempNum = *str - 48;
                len += 1;
                if (*(str + 1) >= '0' && *(str + 1) <= '9') {
                    str += 1;
                    tempNum *= 10;
                    int tempNum2 = *str - 48;
                    tempNum += tempNum2;
                    p->precission = tempNum;
                    len += 1;
                } else {
                    p->precission = tempNum;
                }
            }
        }
    }
    return len;
}

int parse_lenght(struct forms *p, const char *format) {
    const char *str = format;
    int len = 0;
    if (*str == 'h' || *str == 'l') {
        if (*str == 'h') {
            p->lenght = 1;
            len += 1;
        }
        if (*str == 'l') {
            p->lenght = -1;
            len += 1;
        }
    }
    return len;
}

int parse_type(struct forms *p, const char *format) {
    const char *str = format;
    int len = 0;
    if (*str == 'd' || *str == 'i' || *str == 'u' || *str == 'o' ||
        *str == 'x' || *str == 'X' || *str == 'f' || *str == 'F' ||
        *str == 'e' || *str == 'E' || *str == 'q' || *str == 'G' ||
        *str == 'a' || *str == 'A' || *str == 'c' || *str == 's' ||
        *str == 'p' || *str == 'n') {
        p->type = *str;
        len += 1;
    }
    return len;
}

int check_type(struct forms *p, char *str, va_list arg, int *shift) {
    if (p->type == 's') {
        *shift = s_to_string(p, str, arg);
    } else if (p->type == 'c') {
        *shift = c_to_string(p, str, arg);
    } else if (p->type == 'd' || p->type == 'i') {
        *shift = d_to_string(p, str, arg);
    } else if (p->type == 'f') {
        *shift = f_to_string(p, str, arg);
    } else if (p->type == 'u') {
        *shift = u_to_string(p, str, arg);
    }
    return *shift;
}

int s_to_string(struct forms *p, char *str, va_list arg) {
    int i = 0, spaces = 1;
    char buffer[100] = {'\0'};
    char *argument = va_arg(arg, char *);
    int size_of_arg = s21_strlen(argument);
    s21_strcat(buffer, argument);
    if ((p->precission < size_of_arg && p->precission) || ((p->width < size_of_arg) && p->precission == -1)) {
        reduce_after_precission(buffer, p);
    }
    if ((p->width > size_of_arg) && p->minus) {
        add_spaces_or_zeros_right(p, buffer, spaces);
    }
    if ((p->width > size_of_arg) && !p->minus) {
        int dif = p->width - s21_strlen(buffer);
        add_spaces_or_zeros_left(buffer, dif, p, spaces);
    }
    for (int j = 0; j < (int)s21_strlen(buffer); j++) str[j] = buffer[j];
    i = s21_strlen(str);
    return i;
}

void add_spaces_or_zeros_right(struct forms *p, char *str, int flag) {
    char *temp_array = calloc((int)p->width - (int)s21_strlen(str),
                              sizeof(char));
    for (int i = 0; i < (int)p->width - (int)s21_strlen(str); i++) {
        if (flag == 1)
            temp_array[i] = ' ';
    }
    s21_strcat(str, temp_array);
    free(temp_array);
}

void add_spaces_or_zeros_left(char *buffer, int dif, struct forms *p, int flag) {
    char *temp_array = calloc((int)p->width, sizeof(char));
    for (int i = 0; i < dif; i++) {
        if (flag == 1) {
            temp_array[i] = ' ';
        } else if (flag == 0) {
            temp_array[i] = '0';
        }
    }
    s21_strcat(temp_array, buffer);
    int counter = s21_strlen(temp_array);
    for (int j = 0; j < counter; j++)
        buffer[j] = temp_array[j];
    free(temp_array);
}

void reduce_after_precission(char *buffer, struct forms *p) {
    buffer[p->precission] = '\0';
}

int c_to_string(struct forms *p, char *str, va_list arg) {
    int i = 0, spaces = 1;
    if ((!p->minus && !p->width) || (p->minus && !p->width)) {
        char tmp = (char)va_arg(arg, int);
        *(str) = tmp;
        i++;
    } else if ((p->minus && !p->zero) && p->width) {
        char tmp = (char)va_arg(arg, int);
        *(str) = tmp;
        add_spaces_or_zeros_right(p, str, spaces);
        i = s21_strlen(str);
    } else if (!p->minus && !p->zero && p->width) {
        char buffer[100] = {'\0'};
        buffer[0] = (char)va_arg(arg, int);
        int dif = p->width - s21_strlen(buffer);
        add_spaces_or_zeros_left(buffer, dif, p, spaces);
        s21_strcat(str, buffer);
        i = s21_strlen(str);
    }
    return i;
}

void s21_itoa_int(int num, char *str) {
    if (num < 0) {
        num = abs(num);
        int discharge = 0, j = num;
        for (discharge = 1; j >= 10; j /= 10) discharge *= 10;
        for (; discharge > 0; discharge /= 10) {
            *str++ = '0' + num / discharge;
            num %= discharge;
        }
        *str = '\0';
    } else {
        int discharge = 0, j = num;
        for (discharge = 1; j >= 10; j /= 10) discharge *= 10;
        for (; discharge > 0; discharge /= 10) {
            *str++ = 48 + num / discharge;
            num %= discharge;
        }
        *str = '\0';
    }
}

void s21_ftoa(struct forms *p, char *str, long double num) {
    int decimal, sign, l, m, numberWhole = 10;
    char *str1;
    if (p->precission == 0) {
        p->precission = 6;
    }
    if (p->precission != -1) {
        str1 = fcvt(num, p->precission, &decimal, &sign);
        if (num < 0) {
            num *= -1;
        }
        while (numberWhole > -1) {
            l = pow(10, numberWhole);
            m = num / l;
            if (m > 0) {
                break;
            }
            numberWhole--;
        }
        numberWhole += 1;
        char a[1];
        *a = 'Z';
        s21_strcat(str, str1);
        s21_strncat(str, a, 1);
        char buff, buff1;
        buff = str[numberWhole];
        str[numberWhole] = '.';
        numberWhole++;
        for (; numberWhole < (int)s21_strlen(str); numberWhole++) {
            buff1 = str[numberWhole];
            str[numberWhole] = buff;
            buff = buff1;
        }
    }
}

int f_to_string(struct forms *p, char *str, va_list arg) {
    long double num = va_arg(arg, double);
    char ftoaBuff[100] = {'\0'}, jk[100] = {'\0'};
    int spaces = 1, diff = 0, signS = 0, y = 0;
    s21_ftoa(p, ftoaBuff, num);
    if (p->zero) {
        spaces = 0;
    }
    if ((p->plus && num > 0) || num < 0) {
        signS = -1;
    }
    if (p->width > (int)s21_strlen(ftoaBuff)) {
        if (p->minus || (p->plus && p->minus)) {
            add_spaces_or_zeros_right(p, ftoaBuff, spaces);
            if ((p->plus && num > 0) || num < 0) {
                ftoaBuff[s21_strlen(ftoaBuff) - 1] = '\0';
            }
        } else {
            if (spaces == 1) {
                if (p->plus && num > 0) {
                    jk[0] = '+';
                }
                if (num < 0) {
                    jk[0] = '-';
                }
                s21_strcat(jk, ftoaBuff);
                for (int j = s21_strlen(jk); j; j--, y++) {
                    ftoaBuff[y] = jk[y];
                    jk[y] = '\0';
                }
                signS += 1;
            }
            diff = p->width - s21_strlen(ftoaBuff) + signS;
            add_spaces_or_zeros_left(ftoaBuff, diff, p, spaces);
        }
    }
    if (p->plus && num > 0 && signS < 0) {
        jk[0] = '+';
    }
    if (num < 0 && signS < 0) {
        jk[0] = '-';
    }
    s21_strcat(jk, ftoaBuff);
    s21_strcat(str, jk);
    return s21_strlen(str);
}

int d_to_string(struct forms *p, char *str, va_list arg) {
    long int num = 0;
    if (p->lenght == -1) {
        num = va_arg(arg, long int);
    } else if (p->lenght == 1) {
        num = (short int)num;
        num = va_arg(arg, int);
    } else {
        num = (int)num;
        num = va_arg(arg, int);
    }
    char ftoaBuff[100] = {'\0'}, jk[100] = {'\0'};
    int spaces = 1, diff = 0, signS = 0, y = 0;
    s21_itoa_int(num, ftoaBuff);
    if (p->precission > (int)s21_strlen(ftoaBuff)) {
        diff = p->precission - s21_strlen(ftoaBuff);
        add_spaces_or_zeros_left(ftoaBuff, diff, p, 0);
    }

    if (p->zero) {
        spaces = 0;
    }
    if ((p->plus && num > 0) || num < 0) {
        signS = -1;
    }
    if (p->width > (int)s21_strlen(ftoaBuff)) {
        if (p->minus || (p->plus && p->minus)) {
            add_spaces_or_zeros_right(p, ftoaBuff, spaces);
            if ((p->plus && num > 0) || num < 0) {
                ftoaBuff[s21_strlen(ftoaBuff) - 1] = '\0';
            }
        } else {
            if (spaces == 1) {
                if (p->plus && num > 0) {
                    jk[0] = '+';
                }
                if (num < 0) {
                    jk[0] = '-';
                }
                s21_strcat(jk, ftoaBuff);
                for (int j = s21_strlen(jk); j; j--, y++) {
                    ftoaBuff[y] = jk[y];
                    jk[y] = '\0';
                }
                signS += 1;
            }
            if (p->precission < p->width) {
                diff = p->precission - s21_strlen(ftoaBuff);
                add_spaces_or_zeros_left(ftoaBuff, diff, p, spaces);
                spaces = 1;
                s21_strcat(jk, ftoaBuff);
                y = 0;
                for (int j = s21_strlen(jk); j; j--, y++) {
                    ftoaBuff[y] = jk[y];
                    jk[y] = '\0';
                }
                signS = 1;
                diff = p->width - s21_strlen(ftoaBuff);
                add_spaces_or_zeros_left(ftoaBuff, diff, p, spaces);
            }
        }
    }
    if (p->plus && num > 0 && signS < 0) {
        jk[0] = '+';
    }
    if (num < 0 && signS < 0) {
        jk[0] = '-';
    }
    s21_strcat(jk, ftoaBuff);
    s21_strcat(str, jk);
    return s21_strlen(str);
}

void s21_itoa_unsigned(unsigned num, char *str) {
    unsigned discharge = 0, j = num;
    for (discharge = 1; j >= 10; j /= 10) discharge *= 10;
    for (; discharge > 0; discharge /= 10) {
        *str++ = 48 + num / discharge;
        num %= discharge;
    }
    *str = '\0';
}

int u_to_string(struct forms *p, char *str, va_list arg) {
    long unsigned num = 0;
    if (p->lenght == -1) {
        num = va_arg(arg, long int);
    } else if (p->lenght == 1) {
        num = (short unsigned)num;
        num = va_arg(arg, long int);
    } else {
        num = (unsigned)num;
        num = va_arg(arg, long int);
    }
    char ftoaBuff[100] = {'\0'}, jk[100] = {'\0'};
    int spaces = 1, diff = 0, signS = 0, y = 0;
    s21_itoa_unsigned(num, ftoaBuff);
    if (p->precission > (int)s21_strlen(ftoaBuff)) {
        diff = p->precission - s21_strlen(ftoaBuff);
        add_spaces_or_zeros_left(ftoaBuff, diff, p, 0);
    }

    if (p->zero) {
        spaces = 0;
    }
    if (p->width > (int)s21_strlen(ftoaBuff)) {
        if (p->minus || (p->plus && p->minus)) {
            add_spaces_or_zeros_right(p, ftoaBuff, spaces);
        } else {
            if (p->precission < p->width) {
                diff = p->precission - s21_strlen(ftoaBuff);
                add_spaces_or_zeros_left(ftoaBuff, diff, p, spaces);
                spaces = 1;
                s21_strcat(jk, ftoaBuff);
                y = 0;
                for (int j = s21_strlen(jk); j; j--, y++) {
                    ftoaBuff[y] = jk[y];
                    jk[y] = '\0';
                }
                signS = 1;
                diff = p->width - s21_strlen(ftoaBuff);
                add_spaces_or_zeros_left(ftoaBuff, diff, p, spaces);
            }
        }
    }
    s21_strcat(jk, ftoaBuff);
    s21_strcat(str, jk);
    return s21_strlen(str);
}
