package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.index.impl.TermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleScanner;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StringSplitter;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Queue;

public class TermTupleScanner extends AbstractTermTupleScanner {
    public TermTupleScanner() {
    }

    public TermTupleScanner(BufferedReader input) {
        super(input);
    }

    /**
     * 三元组队列
     */
    private Queue<AbstractTermTuple> queue = new LinkedList<>();

    /**
     * 记录使用的三元组位置
     */
    private int pos = 0;

    /**
     *
     * @return 三元组
     * @throws IOException
     */
    @Override
    public AbstractTermTuple next() throws IOException {
        if (queue.isEmpty()){
            String s;
            do {
                s = input.readLine();
                if (s == null)
                    return null;
            }while (s.trim().length() == 0);
            StringSplitter splitter = new StringSplitter();//分割单词
            splitter.setSplitRegex(Config.STRING_SPLITTER_REGEX);
            for (String word : splitter.splitByRegex(s)) {
                TermTuple termTuple = new TermTuple();
                termTuple.curPos = pos;
                if (Config.IGNORE_CASE) {
                    termTuple.term = new Term(word.toLowerCase());
                } else {
                    termTuple.term = new Term(word);
                }
                queue.add(termTuple);
                pos ++;
            }
        }
        return queue.poll();
    }
}
