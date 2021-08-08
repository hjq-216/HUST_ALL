#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include<getopt.h>

char * PATH = NULL;


const char * track_symbolic_link(const char * path, char * buff, unsigned int size) {
    readlink(path, buff, size);
    return buff;
}

void printStat(struct stat * statBuf, const char * name, int depth) {
    // 缩进
    for (int i = 0; i < depth; i++) {
        printf("\t");
    }
    // 打印文件类型
    switch (statBuf->st_mode & S_IFMT) {
        case S_IFBLK:  printf("b");             break;
        case S_IFCHR:  printf("c");             break;
        case S_IFDIR:  printf("d");             break;//目录
        case S_IFIFO:  printf("p");             break;
        case S_IFLNK:  printf("l");             break;
        case S_IFREG:  printf("-");             break;//一般文件
        case S_IFSOCK: printf("s");             break;//socket
        default:       printf("unknown");       break;
    }


    // 打印权限
    // 拥有者
    statBuf->st_mode & S_IRUSR ? printf("r") : printf("-");
    statBuf->st_mode & S_IWUSR ? printf("w") : printf("-");
    statBuf->st_mode & S_IXUSR ? printf("x") : printf("-");//可执行
    // 同组
    statBuf->st_mode & S_IRGRP ? printf("r") : printf("-");
    statBuf->st_mode & S_IWGRP ? printf("w") : printf("-");
    statBuf->st_mode & S_IXGRP ? printf("x") : printf("-");
    // 其他人
    statBuf->st_mode & S_IROTH ? printf("r") : printf("-");
    statBuf->st_mode & S_IWOTH ? printf("w") : printf("-");
    statBuf->st_mode & S_IXOTH ? printf("x") : printf("-");

    // 硬链接的个数
    printf(" %ld ", statBuf->st_nlink);

    // 文件拥有者
    printf("%s ", getpwuid(statBuf->st_uid)->pw_name);

    // 文件拥有者所在的组
    printf("%s ", getgrgid(statBuf->st_uid)->gr_name);

    // 文件大小
    printf("%10ld", statBuf->st_size);

    // 文件最后修改时间
    char buffer[1080];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&(statBuf->st_mtim.tv_sec)));
    printf(" %s", buffer);

    // 文件名
    switch (statBuf->st_mode & S_IFMT) {
        case S_IFDIR:  {
            printf(" %s \n", name);
            break;
        }
        case S_IFLNK:  {
            // 如果是链接文件
            printf(" %s -> ", name);
            printf(" %s\n", track_symbolic_link(name, buffer, sizeof(buffer)));
            break;
        }
        default:       printf(" %s \n", name);       break;
    }
}


void printdir(char * dir, int depth) {
    DIR * dp;
    struct dirent * entry;
    struct stat statBuf;
    if ((dp = opendir(dir)) == NULL) {
        printf("打开文件夹失败\n");
        return ;
    }

    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name, &statBuf);
        if (entry->d_type == 4) {
            // 如果是目录
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                // 如果等于. 或者..则直接跳过
                continue;
            } else {
                // 否则递归调用
                printStat(&statBuf, entry->d_name, depth);
                printdir(entry->d_name, depth + 1);
            }
        } else {
            // 如果是常规文件
            printStat(&statBuf, entry->d_name, depth);
        }
    }
    chdir("..");
}

void usage() {
    printf("\nUsage: \n"
           "./main -l PATH\n");
}


int main(int argc, char * argv[]) {
    int opt;
    char * string = "l:";
    while((opt = getopt(argc, argv, string)) != -1) {
        switch (opt) {
            case 'l':
                PATH = optarg;
                break;
            case '?':
                usage();
                break;
        }
    }
    if (PATH) {
        printdir(PATH, 0);
    } else {
        usage();
    }
    return 0;
}

