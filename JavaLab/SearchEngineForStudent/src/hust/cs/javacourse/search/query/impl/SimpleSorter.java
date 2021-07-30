package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.Sort;

import java.util.List;
import java.util.Map;

public class SimpleSorter implements Sort {
    /**
     * 使用重写的compareTo方法对命中list排序
     * @param hits ：命中结果集合
     */
    @Override
    public void sort(List<AbstractHit> hits) {
        hits.sort(AbstractHit::compareTo);
    }

    /**
     *
     * @param hit ：命中文档
     * @return 分数
     */
    @Override
    public double score(AbstractHit hit) {
        double s = 0;
        for (Map.Entry<AbstractTerm, AbstractPosting> entry : hit.getTermPostingMapping().entrySet()) {
            if (entry.getValue() != null) {
                s += entry.getValue().getFreq();
            }
        }
        // 分数倒置
        return -s;
    }
}
