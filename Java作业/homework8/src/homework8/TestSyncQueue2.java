package homework8;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class TestSyncQueue2 {
    public static void main(String[] args){
        SyncQueue2<Integer> syncQueue2 = new SyncQueue2<>();
        Runnable produceTask = () ->{
            while (true){
                try {
                    List<Integer> list = new ArrayList<>();
                    int elementsCount = (int)(Math.random() * 10) + 1;
                    for (int i = 0; i < elementsCount ; ++i){
                        int r = (int)(Math.random() * 10) + 1;
                        list.add(r);
                    }
                    syncQueue2.produce(list);
                    Thread.sleep((int)(Math.random() * 5) + 1);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };

        Runnable consumeTask = ()->{
            while (true){
                try {
                    List<Integer> list = syncQueue2.consume();
                    Thread.sleep((int)(Math.random() * 10) + 1);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };

        ExecutorService es = Executors.newFixedThreadPool(2);
        es.execute(produceTask);
        es.execute(consumeTask);
        es.shutdown();
        while (!es.isTerminated()){}
    }
}
