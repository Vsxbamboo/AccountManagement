//
// Created by vsx on 2024/3/6.
//

#include "tool.h"

/*
 * 将time_t类型转换为字符串，字符串格式为“年-月-日 时:分”
 * */
void timeToString(time_t t, char *pBuf) {
    struct tim *timeinfo;
    timeinfo = localtime(&t);
    strftime(pBuf, 20, "%Y-%m-%d %H:%M", timeinfo);
}

time_t stringToTime(char *pTime) {
    struct tm tml;
    time_t timel;
    sscanf(pTime, "%d-%d-%d %d:%d", &tml.tm_year, &tml.tm_mon, &tml.tm_mday, &tml.tm_hour, &tml.tm_min);
    tml.tm_year -= 1900;
    tml.tm_mon -= 1;
    tml.tm_sec = 0;
    tml.tm_isdst = -1;
    timel = mktime(&tml);
    return timel;
}

void clearthisline() {
    char buf;
    do {
        scanf("%c", &buf);
    } while (buf != '\n');
}

/*
 * str类型的模糊查询，要求str以0结尾
 * 在a中找有没有等于b的子串
 * 存在返回1，不存在返回0
 * */

int fuzz_str_beinclude(char *a, char *b) {
    //a="i" b="teii"
    int alen = strlen(a);
    int blen = strlen(b);
    // 如果b比a长，a不可能是b的子串
    if (alen > blen) {
        return 0;
    } else if (alen == blen) {
        // 如果长度相等，直接比较两个字符串是否完全相同
        return strcmp(a, b) == 0;
    } else { // alen < blen
        for (int i = 0; i <= blen - alen; i++) {
            int match = 1; // 假设找到匹配
            for (int j = 0; j < alen; j++) {
                if (b[i + j] != a[j]) {
                    match = 0; // 发现不匹配，更新标志变量
                    break; // 跳出内层循环
                }
            }
            if (match) {
                // 如果在某个位置找到了匹配，返回1
                return 1;
            }
        }
        // 如果遍历完a中的所有可能的子串后都没有找到与b匹配的，返回0
        return 0;
    }
}
