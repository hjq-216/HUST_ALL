package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.AbstractTermTuple;

/**
 * 三元组类
 */
public class TermTuple extends AbstractTermTuple {
    /**
     * 无参构造
     */
    public TermTuple() {
    }

    /**
     * 有参构造函数
     * @param term
     * @param curpos
     */
    public TermTuple(AbstractTerm term, int curpos){
        this.curPos = curpos;
        this.term = term;
    }

    /**
     * 重写equals方法
     * @param obj ：要比较的另外一个三元组
     * @return 相等返回true，否则返回false
     */
    @Override
    public boolean equals(Object obj) {
        if (obj instanceof TermTuple){
            return this.curPos == ((TermTuple) obj).curPos
                    && this.term.equals(((TermTuple) obj).term);
        }
        return false;
    }

    /**
     * 标准输出
     * @return 指定格式字符串
     */
    @Override
    public String toString() {
        return "{Term: "+term+",CurPos"+curPos+",Freq: "+freq+"}\n";
    }
}
