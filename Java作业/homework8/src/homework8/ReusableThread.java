package homework8;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ReusableThread extends Thread{
    private Runnable runTask = null;
    private static Lock lock = new ReentrantLock();
    private static Condition condition = lock.newCondition();

    public ReusableThread(){
        super();
    }

    @Override
    public void run() {
        lock.lock();
        while (runTask == null){
            try {
                condition.await();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            finally {
                lock.unlock();
            }
        }
        runTask = null;
    }

    public void submit(Runnable task){
        lock.lock();
        try {
            runTask = task;
            task.run();
            condition.signalAll();
        }finally {
            lock.unlock();
        }
    }
}
