package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractTerm;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class Term extends AbstractTerm {

    /**
     * 无参构造函数
     */
    public Term() {
    }

    /**
     * 有参构造函数
     * @param content
     */
    public Term(String content) {
        super(content);
    }

    /**
     * 重写equals方法
     * @param obj ：要比较的另外一个Term
     * @return 相等则返回true，否则返回false
     */
    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Term){
            return this.content.equals(((Term) obj).content);
        }
        else
            return false;
    }

    /**
     * 标准输出
     * @return 指定格式字符串
     */
    @Override
    public String toString() {
        return this.content;
    }

    /**
     * 返回单词内容
     * @return 单词内容
     */
    @Override
    public String getContent() {
        return this.content;
    }

    /**
     * 设置单词内容
     * @param content：Term的内容
     */
    @Override
    public void setContent(String content) {
        this.content = content;
    }

    /**
     * 重写compareTo方法
     * @param o： 要比较的Term对象
     * @return 大于返回1，小于返回-1，等于返回0
     */
    @Override
    public int compareTo(AbstractTerm o) {
        return this.content.compareTo(o.getContent());
    }

    /**
     *
     * @param out :输出流对象
     */
    @Override
    public void writeObject(ObjectOutputStream out) {
        try {
            out.writeObject(this.content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     *
     * @param in ：输入流对象
     */
    @Override
    public void readObject(ObjectInputStream in) {
        try {
            this.content = (String) in.readObject();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
