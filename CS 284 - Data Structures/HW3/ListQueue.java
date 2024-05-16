package CS284Homework.HW3;
// Yash Yagnik
// I pledge my honor that I have abided by the Stevens Honor System.

import java.util.Iterator;
import java.util.NoSuchElementException;

public class ListQueue<E>{

    private Node<E> front;
    private int size = 0;

    // creates an empty single-linked list representing the priority queue.
    public ListQueue() {
        this.front = null;
    }

    // Creates a one-element single-linked list representing the priority queue. first parameter will be stored in front of the queue
    public ListQueue(Node<E> first){
        front = first;
        size++;
    }

    public E getFront(){
        return front.data;
    }

    public void setFront(Node<E> newFront){
        this.front = newFront;
    }

    public int getSize() {
        return size;
    }

    // Returns the info at the start of the queue.
    public E peek(){
        return front.getData();
    }

    // adds item to a position according to its priority; Also takes care of some edge cases such as if the item you are trying to add is null or if you are replacing the head.
    public boolean offer(E item, int priority){
        Node<E> current = front;
        Node<E> previous = null;
        Node<E> toAdd = new Node(item, priority);

        if (item == null){
            throw new NullPointerException();
        }

        else if (front == null){
            front = toAdd;
            size++;
            return true;
        }

        else if (front.priority > priority){
            Node<E> temp = front;
            front = toAdd;
            toAdd.next = temp;

            size++;
            return true;
        }

        else {
            while (current != null && current.priority <= priority) {
                previous = current;
                current = current.next;
            }
            size++;
            toAdd.next = current;
            previous.next = toAdd;
            return true;
        }
    }


    // Adds item at the end of queue. It always returns true except it throws NullPointerException if the item sent to the method is null
    public boolean addRear(E item){
        Node<E> current = front;
        Node<E> toAdd = new Node(item);
        if (item == null){
            throw new NullPointerException();
        }

        if (front == null){
            front = toAdd;
            return true;
        }

        while (current.next != null){
            current = current.next;
        }
        current.next = toAdd;
        size++;
        return true;
    }

    // Returns the data at the front of the queue and removes it from the queue. Throws NullPointerException if the item at the front of the queue is null.
    public E poll(){
        if (front == null){
            throw new NullPointerException();
        }
        size--;
        E dataHolder = front.getData();
        front = front.next;

        return dataHolder;
    }

    // Takes a node to be removed and removes it from the queue. Correct links needs to be established after the node is removed
    public boolean remove(Node<E> tobeRemoved){
        Node<E> current = front;

        if (tobeRemoved == null){
           return false;
        }
        else if (front == null){
            return false;
        }
        else if (tobeRemoved.equals(front)){
            front = front.next;
            size--;
            return true;
        }
        while(current.next != null && !(tobeRemoved.equals(current.next))){
            current = current.next;
        }
        if (tobeRemoved.equals(current.next)){
            current.next = current.next.next;
            size--;
            return true;
        }
        else {
            return false;
        }

    }

    // method will return an instance of Iter class that we defined inside the ListQueue<E> class
    public Iterator<E> iterator(){
        return new Iter();
    }


    public static class Node<E> {
        private E data;
        private Node<E> next;
        private int priority;
        private int LOW_PRIORITY = Integer.MAX_VALUE;

        //a constructor that creates a node holding dataItem. No priority as a parameter is given, therefore the task will be assigned LOW_PRIORITY
        public Node(E dataItem){
            this.data = dataItem;
            this.priority = LOW_PRIORITY;
        }

        //a constructor that creates a node holding dataItem, with priority as the priority of the task.
        public Node(E dataItem, int priority){
            this.data = dataItem;
            this.priority = priority;

        }

        // a constructor that creates a node holding dataItem, with next as next and priority as the priority of the task
        public Node(E dataItem, Node<E> next, int priority){
            this.data = dataItem;
            this.next = next;
            this.priority = priority;
        }

        // will return the data stored in the attribute
        public E getData(){
            return data;
        }

        // will return the next node
        public Node<E> getNext(){
            return next;
        }

        public boolean equals(Node<E> toCompare) {
            return getData().equals(toCompare.getData());
        }

    }

    private class Iter implements Iterator<E> {
        private Node<E> next = front;

        // will return true when the next Node not equal to null
        public boolean hasNext(){
            return next != null;
        }

        // Return the data stored in the next node (attribute) and updates the next node with the next node of next node. Throws NoSuchElementException if next node is null
        public E next(){
            if (next == null){
                throw new NoSuchElementException();
            }
            E data = next.getData();
            next = next.next;
            return data;
        }

        // Removes front node
        public void remove(){

            if (front.getData() == null){
                throw new UnsupportedOperationException();
            }
            front = front.next;
        }
    }
}
