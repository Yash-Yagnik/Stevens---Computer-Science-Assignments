package CS284Homework.HW4;

// Yash Yagnik
// I plegde my honor that I have abided by the Stevens Honor System.
import java.util.Random;
import java.util.Stack;

public class Treap<E extends Comparable<E>>{
    private Random priorityGenerator;
    private Node<E> root;

    /**
     * Constructor the declares and empty treap
     */
    public Treap(){
        priorityGenerator = new Random();
        this.root = null;
    }

    /**
     * Constructor the declares and empty treap witha random priority bound
     * @param seed
     */
    public Treap(long seed){
        root = null;
        priorityGenerator = new Random(seed);
    }

    /**
     *
     * @param <E>
     */
    public class Node<E>{
        public E data;
        public int priority;
        public Node<E> left;
        public Node<E> right;

        /**
         *
         */
        public Node(){
            Node newNode = new Node(null, 0);
        }

        /**
         *
         * @param data
         * @param priority
         */
        public Node(E data, int priority){
            if (data == null){
                throw new NullPointerException();
            }
            this.data = data;
            this.priority = priority;
        }

        /**
         *
         * @return
         */
        public Node<E> rotateRight(){
            // Rotate using help from office hours, first make new filler nodes and then set pointer-reference variables
            // Replace all the data that the "this" object uses with the filler Node we created
            Node<E> pivot_right = new Node<>(this.data, this.priority);
            Node<E> pivot = new Node<>(this.left.data, this.left.priority);
            pivot_right.right = this.right;
            pivot_right.left = this.left.right;
            pivot.right = pivot_right;
            pivot.left = this.left.left;

            this.data = pivot.data;
            this.priority = pivot.priority;
            this.left = pivot.left;
            this.right = pivot.right;
            return pivot;
        }

        /**
         *
         * @return
         */
        public Node<E> rotateLeft(){
            // Rotate using help from office hours, first make new filler nodes and then set pointer-reference variables
            // Replace all the data that the "this" object uses with the filler Node we created
            Node<E> pivot_left = new Node<>(this.data, this.priority);
            Node<E> pivot = new Node<>(this.right.data, this.right.priority);
            //Set filler values
            pivot_left.right = this.right.left;
            pivot_left.left = this.left;
            pivot.right = this.right.right;
            pivot.left = pivot_left;
            //Set the this values
            this.data = pivot.data;
            this.priority = pivot.priority;
            this.left = pivot.left;
            this.right = pivot.right;
            return pivot;
        }

    }

    /**
     * Sends the node to the add function and assigns it to a rondom prority
     * @param key
     * @return
     */
    public boolean add(E key){
        int priority = priorityGenerator.nextInt();
        return add(key, priority);
    }

    /**
     * Adds the node to the tree as a bst
     * @param key
     * @param priority
     * @return
     */
    public boolean add(E key, int priority){
        Stack<Node<E>> pancakes = new Stack();
        Node<E> curr = root;
        Node<E> toAdd = new Node<E>(key, priority);
        if (key == null){
            return false;
        }
        if (curr == null){
            root = toAdd;
            return true;
        }
        while (curr != null) {
            pancakes.push(curr);
            if ((key.compareTo(curr.data)) == 0){
                return false;
            }
            if ((key.compareTo(curr.data)) < 0 && curr.left == null) {
                curr.left = toAdd;
                break;
            }
            else if ((key.compareTo(curr.data)) > 0 && curr.right == null){
                curr.right = toAdd;
                break;
            }
            else{
                if ((key.compareTo(curr.data)) < 0){
                    curr = curr.left;
                }
                else if ((key.compareTo(curr.data)) > 0){
                    curr = curr.right;
                }
            }
        }
        this.reheap(pancakes);
        return true;

    }

    /**
     * Reorgnizes the trea with heap properties
     * @param path
     */
    private void reheap(Stack<Node<E>> path) {
        while (!path.isEmpty()) {
            Node<E> root = path.pop();
            if(root.left != null && root.left.priority > root.priority) {
                root.rotateRight();
            }
            if(root.right != null && root.right.priority > root.priority){
                root.rotateLeft();
            }
        }

    }
    // I went to office hours to get help on this my though process was way too complex
        /*
        while (!(path.isEmpty())  && path.peek().priority< temp.priority) {
            Node<E> parent = path.pop();

            if (parent == root){
                root = temp;
            }
            if (temp.data.compareTo(parent.data) > 0) {
                temp = parent.rotateLeft();
                return true;
            }

            else if (temp.data.compareTo(parent.data) < 0){
                temp = parent.rotateRight();
                return true;
            }

            if (!path.empty()) {
                Node<E> grandParent = path.peek();
                if(parent == grandParent.left) {
                    grandParent.left = temp;
                    return true;
                }
                else {
                    grandParent.right = temp;
                    return true;
                }
            }
            else {
                temp = parent.rotateRight();
                return true;
            }
        }
        return false;*/
//    }

    /**
     * Deletes the node the user gives as input
     * @param key
     * @return
     */
    public boolean delete(E key){
        Node<E> curr = root;
        if (key == null){
            return false;
        }

        while (find(key) && curr != null){
            if ((curr.data.compareTo(key)) > 0){
                curr = curr.left;
            }
            else if ((curr.data.compareTo(key)) < 0){
                curr = curr.right;
            }
            else if ((curr.data.compareTo(key)) == 0){
                curr = null;
                return true;
            }
            else{
                return false;
            }
        }
        return false;
    }

    /**
     * Finds if the node is in the tree
     * @param root
     * @param key
     * @return
     */
    public boolean find (Node<E> root, E key){
        Node<E> curr = this.root;
        while (curr != null){
            if ((curr.data.compareTo(key)) > 0){
                curr = curr.left;
            }
            else if ((curr.data.compareTo(key)) < 0){
                curr = curr.right;
            }
            else if ((curr.data.compareTo(key)) == 0){
                return true;
            }
            else{
                return false;
            }
        }
        return false;
    }

    /**
     * Sends this to find
     * @param key
     * @return
     */
    public boolean find(E key){
        return find(root, key);
    }

    // I used urs
    private String toString(Node current, int level){
        StringBuilder s = new StringBuilder();
        for(int i = 0 ; i < level; i++)
            s.append(" ");
        if(current == null)
            s.append("null\n");
        else{
            s.append("(key=" + current.data + ", priority=" + current.priority +")\n");
            s.append(toString(current.left, level + 1));
            s.append(toString(current.right, level + 1));
        }
        return s.toString();
    }
    public String toString(){
        return toString(root, 0);
    }


    public static void main(String[] args) {
        // Treap<String> test = new Treap<String>();
        /*
        test.add("yo", 2);
        test.add("yossir");
        test.add("y");
        test.add("yos");
         */
        //System.out.println(test.find("yo"));
        //test.toString(test.root, 0);
        //System.out.println(test.toString());
        //System.out.println("yo".compareTo("yossir"));
        Treap<Integer> test = new Treap<Integer>();
        test.add(4, 54);
        test.add(2, 93);
        test.add(6, 46);
        test.add(1, 12);
        test.add(3, 84);
        test.add(5, 82);
        test.add(7, 3);
        System.out.println(test);
        //System.out.println(test.find(39));
    }


}
