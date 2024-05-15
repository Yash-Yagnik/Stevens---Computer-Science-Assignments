package CS284Homework.HW3;
// Yash Yagnik
// I pledge my honor that I have abided by the Stevens Honor System.
import java.util.Iterator;

public class TaskList<E>{
    private ListQueue<E> all;
    private ListQueue<E> active;
    private ListQueue<E> completed;
    private int LOW_PRIORITY = Integer.MAX_VALUE;
    private int HIGH_PRIORITY = 1;

    // Initializes all the ListQueues in the attributes
    public TaskList(){
        all = new ListQueue();
        active = new ListQueue();
        completed = new ListQueue();
    }

    // Will add the item into active and all queues with default priority as LOW_PRIORITY. If item is null, it will return false. Otherwise returns true
    public boolean createTask(E item){
        if (item == null){
            return false;
        }
        all.offer(item, LOW_PRIORITY);
        active.offer(item, LOW_PRIORITY);
        return true;
    }

    // Will add the item into active and all queues. If item is null, it will return false. Otherwise returns true.
    public boolean createTask(E item, int priority){
        if (item == null){
            return false;
        }

        all.offer(item, priority);
        active.offer(item, priority);
        return true;
    }

    // Returns the completed listqueue
    public ListQueue<E> getCompleted() {
        return completed;
    }

    // Returns the active listqueue
    public ListQueue<E> getActive() {
        return active;
    }

    // Returns the all list queue
    public ListQueue<E> getAll() {
        return all;
    }


    public void printTopThree(){
        Iterator<E> data = active.iterator();
        if (getActive().getSize() - 1 < 3){
            showActiveTasks();
        }
        else {
            for (int i = 0; i < 3; i++) {
                System.out.println( i + ". " + data.next());
            }
        }
    }

    // helper method will use the iterator() to iterate through the queue elements and print them with numbers
    private void printTasks(ListQueue<E> queue){
        int i = 1;
        for(Iterator<E> it = queue.iterator(); it.hasNext();) {
            System.out.println(i + ". " + it.next());
            i++;
        }
    }

    // Calls the printTasks function with the list queue all
    public void showAllTasks(){
        printTasks(all);
    }

    // Calls the printTasks function with the list queue completed
    public void showCompletedTasks(){
        printTasks(completed);
    }

    // Calls the printTasks function with the list queue active
    public void showActiveTasks(){
        printTasks(active);
    }


    // will remove the highest priority task from the front of the queue and returns true if it successfully removes. If it does not exist, it prints an error message and returns false
    public boolean crossOffMostUrgentTask(){
        try{
            E temp = active.getFront();
            active.poll();
            completed.addRear(temp);
            //completed.offer(temp, 1);
            System.out.println("Successfully removed the most urgent task/top of the list task!");
            System.out.println("Task is completed and removed: " + temp);
            return true;
        }
        catch (NullPointerException e){
            System.out.println("Unsuccessful operation! Please try again!");
            return false;
        }
    }

    // emoves the task at the location identified by taskNumber, edge cases where the item is not in the queue or the node to be removed was the head were also covered
    public boolean crossOffTask(int taskNumber){
        E cur = null;
        int holder = taskNumber;

        for(Iterator<E> it = active.iterator(); it.hasNext();) {
            cur = it.next();
            taskNumber--;
            if(taskNumber == 0) break;
        }
        ListQueue.Node<E> toRemove = new ListQueue.Node<E>(cur);
        active.remove(toRemove);
        completed.offer(cur, 1);
        System.out.println("Task number " + holder + " is removed: " + toRemove.getData());
        return true;
    }





}
