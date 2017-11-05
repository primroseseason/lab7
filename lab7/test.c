//
//  test.c
//  lab7
//
//  Created by 高旭 on 2017/11/2.
//  Copyright © 2017年 高旭. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "menu.h"
int Quit(int argc, char **argv)
{
    exit(0);
}
int argtest(int argc, char **argv)
{
    const char *optString = "lah";
    opterr = 0;
    int opt;
    while ((opt = getopt(argc, argv, optString)) != -1)
    {
        switch (opt)
        {
            case 'l':
                printf("this -l option\n");
                break;
            case 'a':
                printf("this -a option\n");
                break;
            case 'h':
                printf("in this cmd, you have 3 options can use:\n");
                printf("-l\n");
                printf("-a\n");
                printf("-h\n");
                break;
            default:
                break;
        }
    }
    // reset global valuable optind
    optind = 0;
    return 0;
}
int main(int argc, char **argv)
{
    MenuConfig("version", "Author:Gao xu\nProgram Version:1.0\n", NULL);
    MenuConfig("argtest", "test arg option", argtest);
    MenuConfig("quit", "quit from Macbook", Quit);
    int ExcuteMenu(void);
    return 0;
}
