package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractPosting;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Collections;
import java.util.List;

public class Posting extends AbstractPosting {
    /**
     * 无参构造函数
     */
    public Posting() {
    }

    /**
     * 有参构造函数
     * @param docId
     * @param freq
     * @param positions
     */
    public Posting(int docId, int freq, List<Integer> positions) {
        super(docId, freq, positions);
    }

    /**
     * 重写equals方法
     * @param obj ：要比较的另外一个Posting
     * @return 相等返回true，否则返回false
     */
    @Override
    public boolean equals(Object obj) {
        if (obj instanceof Posting){
            return this.docId==((Posting) obj).docId
                    && this.freq == ((Posting) obj).freq
                    && this.positions.size() == ((Posting) obj).positions.size()
                    && this.positions.containsAll(((Posting) obj).positions)
                    && ((Posting) obj).positions.containsAll(this.positions);
        }
        return false;
    }

    /**
     * 标准输出
     * @return 输出指定格式字符串
     */
    @Override
    public String toString() {
        return "{\"docId\":" + docId + ",\"freq\":" + freq + ",\"positions\":" + positions + " }";
    }

    /**
     * 获取文档ID
     * @return 文档ID
     */
    @Override
    public int getDocId() {
        return this.docId;
    }

    /**
     * 设置文档ID
     * @param docId：包含单词的文档id
     */
    @Override
    public void setDocId(int docId) {
        this.docId = docId;
    }

    /**
     * 获取词频
     * @return 词频
     */
    @Override
    public int getFreq() {
        return this.freq;
    }

    /**
     * 设置词频
     * @param freq:单词在文档里出现的次数
     */
    @Override
    public void setFreq(int freq) {
        this.freq = freq;
    }

    /**
     * 获取单词出现的位置序列
     * @return 位置序列
     */
    @Override
    public List<Integer> getPositions() {
        return this.positions;
    }

    /**
     * 设置单词出现的位置序列
     * @param positions：单词在文档里出现的位置列表
     */
    @Override
    public void setPositions(List<Integer> positions) {
        this.positions = positions;
    }

    /**
     * 重写compareTo方法
     * @param o： 另一个Posting对象
     * @return 大于返回1，等于返回0，小于返回-1
     */
    @Override
    public int compareTo(AbstractPosting o) {
        return Integer.compare(docId, o.getDocId());
    }

    /**
     * 对位置序列排序
     */
    @Override
    public void sort() {
        Collections.sort(positions);
    }

    /**
     *
     * @param out :输出流对象
     */
    @Override
    public void writeObject(ObjectOutputStream out) {
        try{
            out.writeObject(docId);
            out.writeObject(freq);
            out.writeObject(positions.size());
            for(Integer i:positions){
                out.writeObject(i);//输入坐标
            }
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
        try{
            this.docId = (Integer)in.readObject();
            this.freq = (Integer)in.readObject();
            int size = (Integer) in.readObject();
            for(int i=0;i<size;i++){
                positions.add((Integer)in.readObject());//读取坐标
            }
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
