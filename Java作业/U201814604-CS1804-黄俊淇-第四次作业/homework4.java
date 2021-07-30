package com.company;

public class homework4 {
    /**
     *  创建一个不规则二维数组
     *  第一行row列
     *  第二行row - 1列
     *  ...
     *  最后一行1列
     *	数组元素值都为默认值
     * @param row 行数
     * @return 创建好的不规则数组
     */
    public static  int[][] createArray(int row){
        int[][] array = new int[row][];
        for (int i = 0; i < row ; i++){
            array[i] = new int[row - i];
        }
        return array;
    }

    /**
     * 逐行打印出二维数组，数组元素之间以空格分开
     * @param a
     */
    public static  void printArray(int[][] a){
        for (int[] i : a){
            for (int j : i){
                System.out.print(j + " ");
            }
            System.out.println("\n");
        }
    }


    public static void main(String args[]){
        int[][] array = createArray(5);
        for (int[] i:array){
            for (int j = 0; j < i.length; j++){
                i[j] = j;
            }
        }

        printArray(array);
    }


}
