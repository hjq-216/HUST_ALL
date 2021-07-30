package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractPostingList;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.impl.Index;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.Sort;
import hust.cs.javacourse.search.util.Config;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class IndexSearcher extends AbstractIndexSearcher {
    /**
     * 打开文档
     * @param indexFile ：指定索引文件
     */
    @Override
    public void open(String indexFile) {
        this.index = new Index();
        index.load(new File(indexFile));
    }

    /**
     *
     * @param queryTerm ：检索词
     * @param sorter ：排序器
     * @return 单个检索词搜索的文档
     */
    @Override
    public AbstractHit[] search(AbstractTerm queryTerm, Sort sorter) {
        // 忽略大小写
        if (Config.IGNORE_CASE) {
            queryTerm.setContent(queryTerm.getContent().toLowerCase());
        }
        AbstractPostingList postingList = index.search(queryTerm);
        if (postingList == null) {
            return new Hit[0];
        }
        List<AbstractHit> result = new ArrayList<>();//命中结果数组
        for (int i = 0; i < postingList.size(); i++) {
            AbstractPosting posting = postingList.get(i);

            AbstractHit hit = new Hit(posting.getDocId(), index.getDocName(posting.getDocId()));
            hit.getTermPostingMapping().put(queryTerm, posting);
            hit.setScore(sorter.score(hit));
            result.add(hit);
        }

        sorter.sort(result);
        AbstractHit[] returnResult = new AbstractHit[result.size()];
        return result.toArray(returnResult);
    }

    /**
     *
     * @param queryTerm1 ：第1个检索词
     * @param queryTerm2 ：第2个检索词
     * @param sorter ：    排序器
     * @param combine ：   多个检索词的逻辑组合方式
     * @return 两个检索词搜索的文档
     */
    @Override
    public AbstractHit[] search(AbstractTerm queryTerm1, AbstractTerm queryTerm2, Sort sorter, LogicalCombination combine) {
        AbstractPostingList postingList1 = index.search(queryTerm1);
        AbstractPostingList postingList2 = index.search(queryTerm2);
        // 如果两个都没找到直接就是空的数组
        if (postingList1 == null && postingList2 == null) {
            return new Hit[0];
        }
        List<AbstractHit> result = new ArrayList<>();
        if (combine == LogicalCombination.AND) {
            // 如果有一个词语根本就不存在，那就直接返回空的数组
            if (postingList1 == null || postingList2 == null) {
                return new Hit[0];
            }
            // 求交集

            for (int i = 0; i < postingList1.size(); i++) {
                int docId = postingList1.get(i).getDocId();
                int sub_index = postingList2.indexOf(docId);
                if (sub_index != -1) {
                    AbstractHit hit = new Hit(docId, index.getDocName(docId));
                    hit.getTermPostingMapping().put(queryTerm1, postingList1.get(i));
                    hit.getTermPostingMapping().put(queryTerm2, postingList2.get(sub_index));
                    hit.setScore(sorter.score(hit));
                    result.add(hit);
                }
            }
        } else if (combine == LogicalCombination.OR) {
            // 如果有一个词语不存在直接退化为对另外一个词语的搜索
            if (postingList1 == null) {
                return search(queryTerm2, sorter);
            }
            if (postingList2 == null) {
                return search(queryTerm1, sorter);
            }

            for (int i = 0; i < postingList1.size(); i++) {
                // 首先添加
                int docId = postingList1.get(i).getDocId();
                int sub_index = postingList2.indexOf(docId);
                if (sub_index == -1) {
                    // 如果在另外一个词语中没有,那就正常添加
                    AbstractHit hit = new Hit(docId, index.getDocName(docId));
                    hit.getTermPostingMapping().put(queryTerm1, postingList1.get(i));
                    hit.setScore(sorter.score(hit));
                    result.add(hit);
                } else {
                    // 如果两个都有，与AND方式类似
                    AbstractHit hit = new Hit(docId, index.getDocName(docId));
                    hit.getTermPostingMapping().put(queryTerm1, postingList1.get(i));
                    hit.getTermPostingMapping().put(queryTerm2, postingList2.get(sub_index));
                    hit.setScore(sorter.score(hit));
                    result.add(hit);
                }
            }
            for (int i = 0; i < postingList2.size(); i++) {
                int docId = postingList2.get(i).getDocId();
                int sub_index = postingList1.indexOf(docId);
                if (sub_index == -1) {
                    // 只有当1中不存在的时候才添加
                    AbstractHit hit = new Hit(docId, index.getDocName(docId));
                    hit.getTermPostingMapping().put(queryTerm2, postingList2.get(i));
                    hit.setScore(sorter.score(hit));
                    result.add(hit);
                }
            }
        }

        sorter.sort(result);
        AbstractHit[] returnResult = new AbstractHit[result.size()];
        return result.toArray(returnResult);
    }
}
