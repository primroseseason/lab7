//
//  Header.h
//  lab7
//
//  Created by 高旭 on 2017/11/2.
//  Copyright © 2017年 高旭. All rights reserved.
//

#ifndef menu_h
#define menu_h
int MenuConfig(char *cmd, char *desc, int (*handler)(int argc, char* argv[]));
int ExecuteMenu();
#endif /* Menu_h */
