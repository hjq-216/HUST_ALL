package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.query.AbstractHit;

import java.util.Map;

/**
 * 命中结果
 */
public class Hit extends AbstractHit {
    public Hit() {
    }

    public Hit(int docId, String docPath) {
        super(docId, docPath);
    }

    public Hit(int docId, String docPath, Map<AbstractTerm, AbstractPosting> termPostingMapping) {
        super(docId, docPath, termPostingMapping);
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
     * 获取文档路径
     * @return 文档路径
     */
    @Override
    public String getDocPath() {
        return this.docPath;
    }

    /**
     * 获取单词内容
     * @return 单词内容
     */
    @Override
    public String getContent() {
        return this.content;
    }

    /**
     * 设置单词内容
     * @param content ：文档内容
     */
    @Override
    public void setContent(String content) {
        this.content = content;
    }

    /**
     * 获取命中分数
     * @return 命中分数
     */
    @Override
    public double getScore() {
        return this.score;
    }

    /**
     * 设置文档得分
     * @param score ：文档得分
     */
    @Override
    public void setScore(double score) {
        this.score = score;
    }

    /**
     * 返回单词对应posting的map
     * @return 单词对应posting的map
     */
    @Override
    public Map<AbstractTerm, AbstractPosting> getTermPostingMapping() {
        return this.termPostingMapping;
    }

    /**
     * 标准输出
     * @return 指定格式字符串
     */
    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append("\n--------------------------------------");
        builder.append("\n\ndocId: ").append(docId).append("\n\ndocPath: ").append(docPath)
                .append("\n\ncontent: ").append(content).append("\n\nscore: ").append(score).append("\n\n");
        for (Map.Entry<AbstractTerm, AbstractPosting> entry: termPostingMapping.entrySet()) {
            builder.append(entry.getKey().getContent()).append("\t---->\t").append(entry.getValue()).append("\n");
        }
        return builder.toString();
    }

    /**
     * 重写compareTo方法
     * @param o     ：要比较的名字结果
     * @return 命中分数大于对应的名字结果的命中分数则返回1，小于返回-1，等于返回0
     */
    @Override
    public int compareTo(AbstractHit o) {
        return (int) (this.getScore() - o.getScore());
    }
}
