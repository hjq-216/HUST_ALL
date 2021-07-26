//
//  main.c
//  8大写字母
//
//  Created by 黄俊淇 on 2018/12/25.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE *fp;
    char a[40];
    int i;
    fp=(fopen("test.txt","w"));
    gets(a);
    a[0]=a[0]+'A'-'a';
    for(i=1;a[i]!='\0';i++)
    {
        if((a[i]>'a'&&a[i]<'z')&&a[i-1]==' ')
            a[i]+='A'-'a';
    }
    puts(a);
    fputc(a,fp);
    fclose(fp);
}
