package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.Config;

import java.io.IOException;

/**
 * 长度过滤器
 */
public class LengthTermTupleFilter extends AbstractTermTupleFilter {
    /**
     * 构造函数
     *
     * @param input ：Filter的输入，类型为AbstractTermTupleStream
     */
    public LengthTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
    }

    /**
     *
     * @return 长度过滤后的三元组
     * @throws IOException
     */
    @Override
    public AbstractTermTuple next() throws IOException {
        AbstractTermTuple termTuple = input.next();
        if (termTuple == null) {
            return null;
        }
        while (termTuple.term.getContent().length() > Config.TERM_FILTER_MAXLENGTH ||
                termTuple.term.getContent().length() < Config.TERM_FILTER_MINLENGTH ) {
            termTuple = input.next();
            if (termTuple == null) {
                return null;
            }
        }
        return termTuple;
    }
}
