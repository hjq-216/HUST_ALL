//
//  main.c
//  8实验验证
//
//  Created by 黄俊淇 on 2018/12/25.
//  Copyright © 2018 黄俊淇. All rights reserved.
//

#include <stdio.h>
int  main(void)
{
    short a=0x253f,b=0x7b7d;
    char ch;
    FILE *fp1,*fp2;
    fp1=fopen("d:\\abc1.bin","wb+");
    fp2=fopen("d:\\abc2.txt","w+");
    fwrite(&a,sizeof(short),1,fp1);
    fwrite(&b,sizeof(short),1,fp1);
    fprintf(fp2,"%d %d",a,b);
    
    rewind(fp1); rewind(fp2);
    while((ch = fgetc(fp1)) != EOF)
        putchar(ch);
    putchar('\n');
    
    while((ch = fgetc(fp2)) != EOF)
        putchar(ch);
    putchar('\n');
    
    fclose(fp1);
    fclose(fp2);
    return 0;
}
