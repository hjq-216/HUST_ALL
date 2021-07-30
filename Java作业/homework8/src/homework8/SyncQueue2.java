package homework8;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SyncQueue2<T> {
    private ArrayList<T> list = new ArrayList<>();
    private static Lock lock = new ReentrantLock();
    private static Condition condition = lock.newCondition();

    public void produce(List<T> list1){
        lock.lock();
        try {
            this.list.addAll(list1);
            System.out.print("Produce elements: ");
            for (T t : list1) {
                System.out.print(t + " ");
            }
            System.out.print("\n");
            condition.signalAll();
        } finally {
            lock.unlock();
        }
    }

    public List<T> consume(){
        List<T> list1 = new ArrayList<>();
        lock.lock();
        try {
            while (this.list.size() == 0){
                condition.await();
            }
            list1.addAll(this.list);
            this.list.clear();
            System.out.print("Consume elements: ");
            for (T t : list1) {
                System.out.print(t + " ");
            }
            System.out.print("\n");
            condition.signalAll();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        finally {
            lock.unlock();
        }
        return list1;
    }


}
