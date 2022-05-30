#include "s21_string.h"

void *s21_memchr(const void *str, int c, size_t n) {
    const unsigned char *p = str;
    for (int i = 0; i < (int)n; i++) {
        if (*p++ == (unsigned char)c) {
            return (void *)(p - 1);
        }
    }
    return S21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, size_t n) {
    const unsigned char *str_k1, *str_k2;
    str_k1 = str1;
    str_k2 = str2;
    int res = 0;
    while (n != 0) {
        if ((res = *str_k1 - *str_k2) != 0)
            break;
        n--;
        ++str_k1;
        ++str_k2;
    }
    return res;
}

void *s21_memcpy(void *dest, const void *src, size_t n) {
    char *tmp = dest;
    const char *s = src;
    while (n--) {
        *tmp++ = *s++;
    }
    return dest;
}

void *s21_memmove(void *dest, const void *src, size_t n) {
    if (dest < src) {
        char *s = (char *)src;
        char *d = (char *)dest;
        for (unsigned int i = 0; i < n; i++) {
            *(d + i) = *(s + i);
        }
    } else {
        char *s = (char *)src + n;
        char *d = (char *)dest + n;
        for (int i = n - 1; i >= 0; i--) {
            *--d = *--s;
        }
    }
    return dest;
}

void *s21_memset(void *str, int c, size_t n) {
    unsigned char *p = str;
    for (int i = 0; i < (int)n; i++) {
        *(p + i) = (unsigned char)c;
    }
    return p;
}

char *s21_strcat(char *dest, const char *src) {
    char *temp = dest;
    while (*dest) {
        dest++;
    }
    while ((*dest++ = *src++) != '\0') {
    }
    return temp;
}

char *s21_strncat(char *dest, const char *src, size_t n) {
    char *temp = dest;
    while (*dest)
        while (*dest)
            while (*dest)
                dest++;
    while ((*dest++ = *src++) != 0) {
        if (--n == 0) {
            *dest = '\0';
            break;
        }
    }
    return temp;
}

char *s21_strchr(const char *str, int c) {
    while (*str != (char)c) {
        if (*str++ == '\0') {
            return 0;
        }
    }
    return (char *)str;
}

int s21_strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++, str2++;
    }
    return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

int s21_strncmp(const char *str1, const char *str2, size_t n) {
    while (n-- - 1 && *str1 && *str1 == *str2) {
        str1++, str2++;
    }
    return (*str1 - *str2);
}

char *s21_strcpy(char *dest, const char *src) {
    char *tmp = dest;
    while ((*dest++ = *src++) != 0) {
    }
    return tmp;
}

char *s21_strncpy(char *dest, const char *src, size_t n) {
    char *temp = dest;
    int ttp = 0;
    while ((*dest++ = *src++) && ttp++ < (int)n) {
    }
    return temp;
}

size_t s21_strcspn(const char *str1, const char *str2) {
    size_t count = 0;
    while (*str1 && !s21_strchr(str2, *str1++)) {
        count++;
    }
    return count;
}

char *s21_strerror(int errnum) {
    static char *str[] = ERRORS;
    int max;
    char error[4096] = {'\0'};
    char stt[10];
    static char strr[4096] = {'\0'};
    for (int i = 0; i < 4096; i++) strr[i] = '\0';
#if defined(__APPLE__) && defined(__MACH__)
    max = 106;
#else
    max = 133;
#endif
    if (errnum > max || errnum < 0) {
        s21_itoa(errnum, stt);
        s21_strcpy(error, "Unknown error: ");
        s21_strncat(error, stt, s21_strlen(error));
    } else {
        s21_strcat(error, str[errnum]);
    }
    s21_strcat(strr, error);
    return strr;
}

size_t s21_strlen(const char *str) {
    size_t len = 0;
    for (; str[len]; len++) {
    }
    return len;
}

char *s21_strpbrk(const char *str1, const char *str2) {
    int flag = 0;
    char *res = S21_NULL;
    while (*str1 != '\0' && !flag) {
        for (int i = 0; i < (int)s21_strlen(str2); i++) {
            if (*str1 == *(str2 + i)) {
                flag = 1;
                res = (char *)str1;
            }
        }
        str1++;
    }
    return res;
}

char *s21_strrchr(const char *str, int c) {
    char *rchr = S21_NULL;
    while (*str++) {
        if (*str == (char)c) {
            rchr = (char *)str;
        }
    }
    return rchr;
}

size_t s21_strspn(const char *str1, const char *str2) {
    size_t spn = 0;
    while (*str1 && s21_strchr(str2, *str1++)) {
        spn++;
    }
    return spn;
}

char *s21_strstr(const char *haystack, const char *needle) {
    size_t lens1, lens2;
    lens2 = s21_strlen(needle);
    if (!lens2) {
        return (char *)haystack;
    }
    lens1 = s21_strlen(haystack);
    while (lens1 >= lens2) {
        lens1--;
        if (!s21_memcmp(haystack, needle, lens2)) {
            return (char *)haystack;
        }
        haystack++;
    }
    return S21_NULL;
}

char *s21_strtok(char *str, const char *delim) {
    int i = 0;
    while (str[i] != '\0') {
        for (int j = 0; j < (int)s21_strlen(delim); j++) {
            if (str[i] == delim[j]) {
                str[i] = '\0';
            }
        }
        i++;
    }
    if (*str == '\0') {
        return S21_NULL;
    } else {
        return str;
    }
}

void s21_itoa(int m, char *str) {
    if (m < 0) {
        m = abs(m);
        int power = 0, j = 0;
        j = m;
        for (power = 1; j >= 10; j /= 10)
            power = power * 10;
        *str++ = '-';
        for (; power > 0; power /= 10) {
            *str++ = '0' + m / power;
            m %= power;
        }
        *str = '\0';

    } else {
        int power = 0, j = 0;
        j = m;
        for (power = 1; j >= 10; j /= 10)
            power *= 10;

        for (; power > 0; power /= 10) {
            *str++ = '0' + m / power;
            m %= power;
        }
        *str = '\0';
    }
}

void *s21_to_upper(const char *str) {
    static char *buffer;
    buffer = malloc(s21_strlen(str));
    void *pt = NULL;
    ssize_t len = s21_strlen(str) + 1;
    for (size_t i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            buffer[i] = str[i] - 32;
        else
            buffer[i] = str[i];
    }
    buffer[len] = '\0';
    pt = (void *)buffer;
    return pt;
}

void *s21_to_lower(const char *str) {
    static char *buffer;
    buffer = malloc(s21_strlen(str));
    void *pt = NULL;
    ssize_t len = s21_strlen(str) + 1;
    for (size_t i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            buffer[i] = str[i] + 32;
        else
            buffer[i] = str[i];
    }
    buffer[len] = '\0';
    pt = (void *)buffer;
    return pt;
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
    static char *buffer;
    void *pt = NULL;
    int flag = 0;
    int end_p = s21_strlen(src) + s21_strlen(str);
    if (s21_strlen(src) >= start_index) {
        buffer = malloc(end_p);
        for (int i = 0; i < start_index; i++) {
            buffer[i] = src[i];
            flag++;
        }
        for (int i = start_index; i < end_p + start_index; i++) {
            buffer[i] = str[i - start_index];
        }
        for (int i = s21_strlen(str) + flag; i < end_p + start_index; i++) {
            buffer[i] = src[i - s21_strlen(str)];
        }
        buffer[end_p] = '\0';
        pt = (void *)buffer;
    }
    return pt;
}

void *s21_trim(const char *src, const char *trim_chars) {
    int i;
    static char *buffer;
    buffer = malloc(s21_strlen(src));
    void *pt = NULL;
    s21_strcpy(buffer, src);
    for (i = s21_strlen(buffer) - 1; i >= 0 && s21_strchr(trim_chars, buffer[i]) != NULL; i--) {
        buffer[i] = '\0';
    }
    while (buffer[0] != '\0' && s21_strchr(trim_chars, buffer[0]) != NULL) {
        s21_memmove(&buffer[0], &buffer[1], s21_strlen(buffer));
    }
    pt = buffer;
    return pt;
}
