package homework8;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Test {
    public static void testAdd(){
        SynchronizedContainer<Integer> container = new SynchronizedContainer<>();
        int addLoops = 10;
        Runnable addTask = new Runnable() {
            @Override
            public void run() {
                for (int i = 0; i < addLoops; ++i){
                    container.add(i);
                }
            }
        };

        int addTaskCount = 100;
        ExecutorService es = Executors.newCachedThreadPool();
        for (int i = 0; i < addTaskCount; ++i){
            es.execute(addTask);
        }

        es.shutdown();
        while (!es.isTerminated()){}
        System.out.println("Test add " + (addLoops * addTaskCount) +
                " elements to container");
        System.out.println("Container size = " + container.size() +
                ", correct size = " + (addLoops * addTaskCount));
    }

    public static void testRemove(){
        SynchronizedContainer<Integer> container = new SynchronizedContainer<>();
        int removeLoops = 10;
        int removeTaskCount = 100;
        for (int i = 0; i < removeLoops * removeTaskCount; ++i){
            container.add(i);
        }
        Runnable removeTask = new Runnable() {
            @Override
            public void run() {
                for (int i = 0; i < removeLoops; ++i){
                    container.remove(0);
                }
            }
        };


        ExecutorService es = Executors.newCachedThreadPool();
        for (int i = 0; i < removeTaskCount; ++i){
            es.execute(removeTask);
        }

        es.shutdown();
        while (!es.isTerminated()){}
        System.out.println("Test remove " + (removeLoops * removeTaskCount) +
                " elements to container");
        System.out.println("Container size = " + container.size() +
                ", correct size = 0");
    }


    public static void main(String[] args){
        testAdd();
        testRemove();
    }
}
