package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractPostingList;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Collections;
import java.util.List;

public class PostingList extends AbstractPostingList {
    /**
     * 加入一个posting
     * @param posting：Posting对象
     */
    @Override
    public void add(AbstractPosting posting) {
        if (list.contains(posting)){
            return;
        }
        list.add(posting);
    }

    /**
     * 标准输出
     * @return 指定格式字符串
     */
    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        boolean flag = false;
        for (AbstractPosting posting : list) {
            if (flag) {
                builder.append("->");
            }
            flag = true;
            builder.append(posting.toString());
        }
        builder.append("\n");
        return builder.toString();
    }

    /**
     * 将某个posting列表中所有元素加入本列表
     * @param postings：Posting列表
     */
    @Override
    public void add(List<AbstractPosting> postings) {
        for (AbstractPosting posting : postings){
            this.add(posting);
        }
    }

    /**
     * 获取某个posting
     * @param index ：下标
     * @return posting对象
     */
    @Override
    public AbstractPosting get(int index) {
        return list.get(index);
    }

    /**
     * 返回某个posting对象的下标
     * @param posting：指定的Posting对象
     * @return 某个posting对象的下标
     */
    @Override
    public int indexOf(AbstractPosting posting) {
        return list.indexOf(posting);
    }

    /**
     * 获取某个文档id对应的posting的下标
     * @param docId ：文档id
     * @return 文档ID对应的下标
     */
    @Override
    public int indexOf(int docId) {
        for (int i = 0; i < list.size(); i++) {
            if (list.get(i).getDocId() == docId) {
                return i;
            }
        }
        return -1;
    }

    /**
     * 判断是否包含某个posting
     * @param posting： 指定的Posting对象
     * @return 包含则返回true，否则返回false
     */
    @Override
    public boolean contains(AbstractPosting posting) {
        return list.contains(posting);
    }

    /**
     * 移除指定下标的posting
     * @param index：指定的下标
     */
    @Override
    public void remove(int index) {
        list.remove(index);
    }

    /**
     * 移除指定posting
     * @param posting ：定的Posting对象
     */
    @Override
    public void remove(AbstractPosting posting) {
        list.remove(posting);
    }

    /**
     * 返回postingList的大小
     * @return postingList的大小
     */
    @Override
    public int size() {
        return list.size();
    }

    /**
     * 清空列表
     */
    @Override
    public void clear() {
        list.clear();
    }

    /**
     * 判断列表是否为空
     * @return 空则返回true，否则返回false
     */
    @Override
    public boolean isEmpty() {
        return list.isEmpty();
    }

    /**
     * 对list排序
     */
    @Override
    public void sort() {
        Collections.sort(list);
    }

    /**
     *
     * @param out :输出流对象
     */
    @Override
    public void writeObject(ObjectOutputStream out) {
        try {
            out.writeObject(list.size());
            for (AbstractPosting posting : list) {
                posting.writeObject(out);
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
        try {
            int size = (Integer) in.readObject();
            for (int i = 0; i < size; i ++) {
                AbstractPosting posting = new Posting();
                posting.readObject(in);
                list.add(posting);
            }
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
