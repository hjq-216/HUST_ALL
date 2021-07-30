package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractTermTuple;

import java.util.List;

/**
 * 文档解析
 */
public class Document extends AbstractDocument {
    /**
     * 构造函数
     */
    public Document() {
    }

    /**
     * 有参构造函数
     * @param docId
     * @param docPath
     */
    public Document(int docId, String docPath) {
        super(docId, docPath);
    }

    /**
     *
     * @param docId
     * @param docPath
     * @param tuples
     */
    public Document(int docId, String docPath, List<AbstractTermTuple> tuples) {
        super(docId, docPath, tuples);
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
     * @param docId：文档id
     */
    @Override
    public void setDocId(int docId) {
        this.docId = docId;
    }

    /**
     * 获取文档路径
     * @return 文档路径
     */
    @Override
    public String getDocPath() {
        return this.docPath;
    }

    /**
     * 设置文档路径
     * @param docPath：文档绝对路径
     */
    @Override
    public void setDocPath(String docPath) {
        this.docPath = docPath;
    }

    /**
     * 获取三元组
     * @return 三元组list
     */
    @Override
    public List<AbstractTermTuple> getTuples() {
        return this.tuples;
    }

    /**
     * 添加三元组
     * @param tuple ：要添加的三元组
     */
    @Override
    public void addTuple(AbstractTermTuple tuple) {
        if (tuples.contains(tuple)){
            return;
        }
        tuples.add(tuple);
    }

    /**
     * 判断是否包含某个三元组
     * @param tuple ： 指定的三元组
     * @return 包含则返回true，否则返回false
     */
    @Override
    public boolean contains(AbstractTermTuple tuple) {
        return tuples.contains(tuple);
    }

    /**
     * 获取下标指定的三元组
     * @param index：指定下标位置
     * @return 三元组
     */
    @Override
    public AbstractTermTuple getTuple(int index) {
        return tuples.get(index);
    }

    /**
     * 获取三元组个数
     * @return 三元组个数
     */
    @Override
    public int getTupleSize() {
        return tuples.size();
    }

    /**
     * 标准输出
     * @return 输出指定格式字符串
     */
    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        for(AbstractTermTuple tuple:tuples){
            builder.append(tuple.toString());
        }
        return "{ docId:" + docId + ", docPath:" +docPath+", tuples:\n" + builder.toString() + "}\n";
    }
}
